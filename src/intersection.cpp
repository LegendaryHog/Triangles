#if 0

#include "intersection.hpp"
#include "point.hpp"
#include "vector.hpp"
#include "segment.hpp"

#define ALGORITHM_TESTING

namespace Geometry
{

#ifndef ALGORITHM_TESTING
namespace
{
#endif // ALGORITHM_TESTING


enum LocPoints {
    InSame = 1,
    InDifferent = -1,
    OnLine = 0,
};

template<std::floating_point F>
LocPoints laying_in_same_half(const Point<F>& A, const Point<F>& B, const Point<F>& C, const Point<F>& D)
{
    Vector AB {A, B}, AC {A, C}, AD {A, D};

    auto prod = scalar_product(vector_product(AB, AC), vector_product(AB, AD));

    if (Compare::are_equal(prod, 0.0))
        return LocPoints::OnLine;
    else if (prod > 0.0)
        return  LocPoints::InSame;
    else
        return LocPoints::InDifferent;
}

template<std::floating_point F>
bool point_belong_triangle(const Point<F>& point_A, const Triangle<F>& tr)
{
    if (magic_product(tr.P(), tr.Q(), tr.R(), point_A) != Loc3D::On)
        return false;
    
    return laying_in_same_half(tr.P(), tr.Q(), tr.R(), point_A) != LocPoints::InDifferent &&
           laying_in_same_half(tr.Q(), tr.R(), tr.P(), point_A) != LocPoints::InDifferent &&
           laying_in_same_half(tr.R(), tr.P(), tr.Q(), point_A) != LocPoints::InDifferent;
}

template<std::floating_point F>
bool are_intersecting(const Segment<F>& seg1, const Segment<F>& seg2)
{
    Vector F1S1 {seg1.F_, seg1.S_};
    Vector F2S2 {seg2.F_, seg2.S_};
    
    Line line1 {seg1.F_, F1S1}, line2 {seg2.F_, F2S2};
    if (!are_intersecting(line1, line2))
        return false;

    if (line1 == line2)
    {
        Segment seg2_cpy {seg2};

        const auto& A1 = seg1.F_;
        const auto& B1 = seg1.S_;
        if (scalar_product(F1S1, F2S2) < 0.0)
            seg2_cpy.swap_points();
        const auto& A2 = seg2_cpy.F_;
        const auto& B2 = seg2_cpy.S_;

        Vector B1A2 {B1, A2};
        Vector B2A1 {B2, A1};

        auto prod_B1A2_B2A1 = scalar_product(B1A2, B2A1);

        return prod_B1A2_B2A1 > 0.0 || Compare::are_equal(prod_B1A2_B2A1, 0.0); 
    }

    return laying_in_same_half(seg1.F_, seg1.S_, seg2.F_, seg2.S_) != LocPoints::InSame &&
           laying_in_same_half(seg2.F_, seg2.S_, seg1.F_, seg1.S_) != LocPoints::InSame;
}

template<std::floating_point F>
bool seg_tr_intersecting_2D(const Segment<F>& seg, const Triangle<F>& tr)
{
    if (point_belong_triangle(seg.F_, tr) || point_belong_triangle(seg.S_, tr))
        return true;

    return are_intersecting(seg, Segment {tr.P(), tr.Q()}) ||
           are_intersecting(seg, Segment {tr.Q(), tr.R()}) ||
           are_intersecting(seg, Segment {tr.R(), tr.P()});
}

template<std::floating_point Float>
bool seg_tr_intersecting_3D(const Segment<Float>& seg, const Triangle<Float>& tr)
{
    const auto& P = tr.P(), Q = tr.Q(), R = tr.R(), F = seg.F_, S = seg.S_;

    if (point_belong_segment(P, seg) ||
        point_belong_segment(Q, seg) ||
        point_belong_segment(R, seg))   
        return true;

    if (magic_product(P, F, S, Q) != magic_product(P, F, S, R) &&
        magic_product(Q, F, S, P) != magic_product(Q, F, S, R) &&
        magic_product(R, F, S, P) != magic_product(R, F, S, Q))
        return true;
    return false;
}

template<std::floating_point F>
bool segment_and_triangle_intersecting(const Segment<F>& seg, const Triangle<F>& tr)
{
    auto F_loc = magic_product(tr.P(), tr.Q(), tr.R(), seg.F_);
    auto S_loc = magic_product(tr.P(), tr.Q(), tr.R(), seg.S_);

    if (F_loc != Loc3D::On && S_loc != Loc3D::On && F_loc == S_loc)
        return false;

    if (F_loc == Loc3D::On && S_loc == Loc3D::On)
        return seg_tr_intersecting_2D(seg, tr);
    else
        return seg_tr_intersecting_3D(seg, tr);
}

template<std::floating_point F>
void point_transformation (Point<F> &point, const Point<F> &origin, const Vector<F> &x_axis,
                           const Vector<F> &y_axis)
{
    auto diff_x = point.x_ - origin.x_;
    auto diff_y = point.y_ - origin.y_;
    auto diff_z = point.z_ - origin.z_;

    point.x_ = x_axis.x_ * diff_x + x_axis.y_ * diff_y + x_axis.z_ * diff_z;
    point.y_ = y_axis.x_ * diff_x + y_axis.y_ * diff_y + y_axis.z_ * diff_z;
    point.z_ = 0.0;
}

template<std::floating_point F>
void space_transformation (Triangle<F> &tr_1, Triangle<F> &tr_2)
{
    Vector x_axis {tr_1.P(), tr_1.Q()};
    x_axis *= (1 / x_axis.module ());

    Vector normal = vector_product (Vector {tr_1.P(), tr_1.Q()}, Vector {tr_1.P(), tr_1.R()});
    normal *= (1 / normal.module ());

    Vector y_axis = vector_product (normal, x_axis);

    point_transformation (tr_1.Q(), tr_1.P(), x_axis, y_axis);
    point_transformation (tr_1.R(), tr_1.P(), x_axis, y_axis);

    point_transformation (tr_2.P(), tr_1.P(), x_axis, y_axis);
    point_transformation (tr_2.Q(), tr_1.P(), x_axis, y_axis);
    point_transformation (tr_2.R(), tr_1.P(), x_axis, y_axis);
    tr_1.P() = {0.0, 0.0, 0.0}; //  this is origin
}

enum class Case {       //   3^1     3^0
    PointAndPoint       = 0 * 3 + 0 * 1,
    PointAndSegment     = 0 * 3 + 1 * 1,
    PointAndTriangle    = 0 * 3 + 2 * 1,
    SegmentAndPoint     = 1 * 3 + 0 * 1,
    SegmentAndSegment   = 1 * 3 + 1 * 1,
    SegmentAndTriangle  = 1 * 3 + 2 * 1,
    TriangleAndPoint    = 2 * 3 + 0 * 1,
    TriangleAndSegment  = 2 * 3 + 1 * 1,
    TriangleAndTriangle = 2 * 3 + 2 * 1,
};

template<std::floating_point F>
Case case_of_intersection(const Triangle<F>& tr1, const Triangle<F>& tr2)
{
    return static_cast<Case>(3 * tr1.type() + 1 * tr2.type());
}

template<std::floating_point F>
bool test_intersection_R1 (const Triangle<F> &tr_1, const Triangle<F> &tr_2)
{
    if (magic_product (tr_2.R(), tr_2.P(), tr_1.Q()) == Loc2D::Negative)
    {
        return !(magic_product (tr_2.R(), tr_2.P(), tr_1.R()) == Loc2D::Negative ||
                 magic_product (tr_1.Q(), tr_1.R(), tr_2.R()) == Loc2D::Negative ||
                 magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Loc2D::Negative);
    }
    else 
    {
        if (magic_product (tr_2.R(), tr_1.P(), tr_1.Q()) == Loc2D::Negative)
            return false;
        else if (magic_product (tr_1.P(), tr_2.P(), tr_1.Q()) != Loc2D::Negative)
            return true;
        else if (magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Loc2D::Negative ||
                 magic_product (tr_1.Q(), tr_1.R(), tr_2.P()) == Loc2D::Negative)
            return false;
        else
            return true;
    }
}

template<std::floating_point F>
bool test_intersection_R2 (const Triangle<F> &tr_1, const Triangle<F> &tr_2)
{
    if (magic_product (tr_2.R(), tr_2.P(), tr_1.Q()) == Loc2D::Negative)
    {
        if (magic_product (tr_2.R(), tr_2.P(), tr_1.R()) == Loc2D::Negative)
            return false;
        else if (magic_product (tr_1.Q(), tr_1.R(), tr_2.R()) == Loc2D::Negative)
        {
            return !(magic_product (tr_1.Q(), tr_1.R(), tr_2.Q()) == Loc2D::Negative ||
                     magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Loc2D::Negative);
        }
        else
            return !(magic_product (tr_1.R(), tr_1.P(), tr_2.P()) == Loc2D::Negative);
    }
    else
    {
        if (magic_product (tr_2.Q(), tr_2.R(), tr_1.Q()) == Loc2D::Negative)
        {
            return !(magic_product (tr_1.P(), tr_2.Q(), tr_1.Q()) == Loc2D::Positive ||
                     magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Loc2D::Negative ||
                     magic_product (tr_1.Q(), tr_1.R(), tr_2.Q()) == Loc2D::Negative);
        }
        else
        {
            if (magic_product (tr_1.P(), tr_2.P(), tr_1.Q()) == Loc2D::Negative)
            {
                return !(magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Loc2D::Negative ||
                         magic_product (tr_2.R(), tr_2.P(), tr_1.R()) == Loc2D::Negative);
            }
            else 
                return !(magic_product (tr_1.P(), tr_2.Q(), tr_1.Q()) == Loc2D::Positive);
        }
    }
}

template<std::floating_point F>
bool intersection_in_2D (const Triangle<F> &tr_1_, const Triangle<F> &tr_2_)
{
    Triangle tr_1 = tr_1_;
    Triangle tr_2 = tr_2_;
    space_transformation (tr_1, tr_2);

    //  if swap tr_2.Q() and tr_2.R()
    if (magic_product (tr_2.P(), tr_2.Q(), tr_2.R()) == Loc2D::Negative)
        tr_2.swap_QR ();

    auto P2_loc = magic_product (tr_1.P(), tr_1.Q(), tr_2.P()) *
                  magic_product (tr_1.Q(), tr_1.R(), tr_2.P()) *
                  magic_product (tr_1.R(), tr_1.P(), tr_2.P());

    auto P1_loc = Loc2D::Positive;

    auto P1_P2_Q2 = Loc2D::Is_vertice;
    auto P1_Q2_R2 = Loc2D::Is_vertice;
    auto P1_R2_P2 = Loc2D::Is_vertice;
    auto sum_locs = Loc2D::Is_vertice;

    //  interior of tr_2
    if (P1_P2_Q2 == Loc2D::Positive &&
        P1_Q2_R2 == Loc2D::Positive && 
        P1_R2_P2 == Loc2D::Positive)
        return true;
    else if (P1_loc == Loc2D::Neutral &&
            (sum_locs == Loc2D::Is_vertice || sum_locs == Loc2D::On_side))
        return true;
    else if (P1_loc == Loc2D::Negative ||
            ((P1_loc == Loc2D::Neutral) && (sum_locs == Loc2D::Neutral)))
        return test_intersection_R1 (tr_1, tr_2);
    else
        return test_intersection_R2 (tr_1, tr_2);
}

template<std::floating_point F>
void transform_triangle (Triangle<F> &tr_1, const Loc3D P1_loc, const Loc3D Q1_loc, const Loc3D R1_loc, Triangle<F> &tr_2)
{
    if (P1_loc == Loc3D::Above)
    {
        if (Q1_loc == Loc3D::Above && R1_loc != Loc3D::Above)
        {
            tr_1.swap_clockwise ();
            tr_2.swap_QR ();
        }
        else if (Q1_loc != Loc3D::Above && R1_loc == Loc3D::Above)
        {
            tr_1.swap_counterclockwise ();
            tr_2.swap_QR ();
        }
    }
    else if (P1_loc == Loc3D::On)
    {
        if (Q1_loc == Loc3D::Above && R1_loc == Loc3D::Above)
            tr_2.swap_QR ();
        else if (Q1_loc == Loc3D::Above && R1_loc != Loc3D::Above)
            tr_1.swap_counterclockwise ();
        else if (Q1_loc != Loc3D::Above && R1_loc == Loc3D::Above)
            tr_1.swap_clockwise ();
        else if (Q1_loc == Loc3D::On && R1_loc == Loc3D::Below)
        {
            tr_1.swap_clockwise ();
            tr_2.swap_QR ();
        }
        else if (Q1_loc == Loc3D::Below && R1_loc == Loc3D::On)
        {
            tr_1.swap_counterclockwise ();
            tr_2.swap_QR ();
        }
    }
    else
    {
        if (Q1_loc == R1_loc)
            tr_2.swap_QR ();
        else if (Q1_loc == Loc3D::Below && R1_loc != Loc3D::Below)
            tr_1.swap_clockwise ();
        else if (Q1_loc != Loc3D::Below && R1_loc == Loc3D::Below)
            tr_1.swap_counterclockwise ();
        else
            tr_2.swap_QR ();
    }
}

template<std::floating_point F>
bool intersection_in_3D (const Triangle<F> &tr_1_, const Triangle<F> &tr_2_, const Loc3D P1_loc,
                         const Loc3D Q1_loc, const Loc3D R1_loc)
{
    Triangle tr_1 = tr_1_;
    Triangle tr_2 = tr_2_;
    
    auto P2_loc = magic_product (tr_1.P(), tr_1.Q(), tr_1.R(), tr_2.P());
    auto Q2_loc = magic_product (tr_1.P(), tr_1.Q(), tr_1.R(), tr_2.Q());
    auto R2_loc = magic_product (tr_1.P(), tr_1.Q(), tr_1.R(), tr_2.R());

    if (P2_loc != Loc3D::On && P2_loc == Q2_loc && Q2_loc == R2_loc)
        return false;
    else
    {
        transform_triangle (tr_1, P1_loc, Q1_loc, R1_loc, tr_2);
        transform_triangle (tr_2, P2_loc, Q2_loc, R2_loc, tr_1);

        auto new_P1_loc = magic_product (tr_2.P(), tr_2.Q(), tr_2.R(), tr_1.P());
        auto new_P2_loc = magic_product (tr_1.P(), tr_1.Q(), tr_1.R(), tr_2.P());

        if (new_P1_loc == Loc3D::On && new_P2_loc == Loc3D::On)
            return (tr_1.P() == tr_2.P());
        else
        {
            auto KJ_mut_pos = magic_product (tr_1.P(), tr_1.Q(), tr_2.P(), tr_2.Q());
            auto LI_mut_pos = magic_product (tr_1.P(), tr_1.R(), tr_2.P(), tr_2.R());

            return (LI_mut_pos != Loc3D::Below && KJ_mut_pos != Loc3D::Above);
        }
    }
}

#ifndef ALGORITHM_TESTING
} // anonymous namespace
#endif // ALGORITHM_TESTING

template<std::floating_point F>
bool are_intersecting (const Triangle<F> &tr_1, const Triangle<F> &tr_2)
{
    switch(case_of_intersection(tr_1, tr_2))
    {
        case Case::PointAndPoint:
            return tr_1.P() == tr_2.P();
        case Case::PointAndSegment:
            return point_belong_segment(tr_1.P(), Segment {tr_2});
        case Case::PointAndTriangle:
            return point_belong_triangle(tr_1.P(), tr_2);
        case Case::SegmentAndPoint:
            return point_belong_segment(tr_2.P(), Segment {tr_1});
        case Case::SegmentAndSegment:
            return are_intersecting(Segment {tr_1}, Segment {tr_2});
        case Case::SegmentAndTriangle:
            return segment_and_triangle_intersecting(Segment {tr_1}, tr_2);
        case Case::TriangleAndPoint:
            return point_belong_triangle(tr_2.P(), tr_1);
        case Case::TriangleAndSegment:
            return segment_and_triangle_intersecting(Segment {tr_2}. tr_1);
        case Case::TriangleAndTriangle:
        {
            auto P1_loc = magic_product (tr_2.P(), tr_2.Q(), tr_2.R(), tr_1.P());
            auto Q1_loc = magic_product (tr_2.P(), tr_2.Q(), tr_2.R(), tr_1.Q());
            auto R1_loc = magic_product (tr_2.P(), tr_2.Q(), tr_2.R(), tr_1.R());

            if (P1_loc != Loc3D::On && P1_loc == Q1_loc && Q1_loc == R1_loc)
                return false;
            else if (P1_loc == Loc3D::On && Q1_loc == Loc3D::On && R1_loc == Loc3D::On)
                return intersection_in_2D (tr_1, tr_2);
            else
                return intersection_in_3D (tr_1, tr_2, P1_loc, Q1_loc, R1_loc);
        }
    }
}

} // namespace Geometry
#endif