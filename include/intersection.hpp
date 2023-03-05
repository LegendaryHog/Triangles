#pragma once
#include "triangle.hpp"
#include "point.hpp"
#include "vector.hpp"
#include "line.hpp"
#include "segment.hpp"
#include "location.hpp"
#include "triangle_intersect_algorithms.hpp"

namespace Geometry
{

template<std::floating_point F>
bool are_intersecting (const Point<F>& p1, const Point<F>& p2)
{
    return p1 == p2;
}

template<std::floating_point F>
bool are_intersecting (const Point<F>& point, const Segment<F>& segment)
{
    Vector PF {point, segment.F_};
    Vector PS {point, segment.S_};

    if (!are_collinear(PF, PS))
        return false;
    else if (scalar_product(PF,PS) < 0.0 || segment.F_ == point || segment.S_ == point)
        return true;
    else
        return false;
}

template<std::floating_point F>
bool are_intersecting (const Point<F>& point, const Triangle<F>& triangle)
{
    if (Location::magic_product(triangle.P(), triangle.Q(), triangle.R(), point) != Location::Loc3D::On)
        return false;
    
    return Location::laying_in_same_half(triangle.P(), triangle.Q(), triangle.R(), point) != Location::LocPoints::InDifferent &&
           Location::laying_in_same_half(triangle.Q(), triangle.R(), triangle.P(), point) != Location::LocPoints::InDifferent &&
           Location::laying_in_same_half(triangle.R(), triangle.P(), triangle.Q(), point) != Location::LocPoints::InDifferent;
}

template<std::floating_point F>
bool are_intersecting (const Segment<F>& segment, const Point<F>& point)
{
    return are_intersecting(point, segment);
}

template<std::floating_point F>
bool are_intersecting (const Segment<F>& seg1, const Segment<F>& seg2)
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

    return Location::laying_in_same_half(seg1.F_, seg1.S_, seg2.F_, seg2.S_) != Location::LocPoints::InSame &&
           Location::laying_in_same_half(seg2.F_, seg2.S_, seg1.F_, seg1.S_) != Location::LocPoints::InSame;
}

namespace Algorithm
{

template<std::floating_point F>
bool seg_tr_intersecting_2D(const Segment<F>& seg, const Triangle<F>& tr)
{
    if (are_intersecting(seg.F_, tr) || are_intersecting(seg.S_, tr))
        return true;

    return are_intersecting(seg, Segment {tr.P(), tr.Q()}) ||
           are_intersecting(seg, Segment {tr.Q(), tr.R()}) ||
           are_intersecting(seg, Segment {tr.R(), tr.P()});
}

template<std::floating_point Float>
bool seg_tr_intersecting_3D(const Segment<Float>& seg, const Triangle<Float>& tr, Location::Loc3D F_loc, Location::Loc3D S_loc)
{
    const auto& P = tr.P(), Q = tr.Q(), R = tr.R();
    Segment seg_cpy = seg;

    if (F_loc == Location::Loc3D::On)
    {
        seg_cpy.swap_points();
        F_loc = S_loc;
    }

    const auto& F = seg_cpy.F_, S = seg_cpy.S_;

    Location::Loc3D outside {};
    if (F_loc == Location::Loc3D::Above)
        outside = Location::Loc3D::Below;
    else
        outside = Location::Loc3D::Above;


    return Location::magic_product(P, R, F, S) != outside &&
           Location::magic_product(R, Q, F, S) != outside &&
           Location::magic_product(Q, P, F, S) != outside;
}
} // namespace Algorithm

template<std::floating_point F>
bool are_intersecting (const Segment<F>& segment, const Triangle<F>& triangle)
{
    auto F_loc = Location::magic_product(triangle.P(), triangle.Q(), triangle.R(), segment.F_);
    auto S_loc = Location::magic_product(triangle.P(), triangle.Q(), triangle.R(), segment.S_);

    if (F_loc != Location::Loc3D::On && S_loc != Location::Loc3D::On && F_loc == S_loc)
        return false;

    if (F_loc == Location::Loc3D::On && S_loc == Location::Loc3D::On)
        return Algorithm::seg_tr_intersecting_2D(segment, triangle);
    else
        return Algorithm::seg_tr_intersecting_3D(segment, triangle, F_loc, S_loc);
}

template<std::floating_point F>
bool are_intersecting (const Triangle<F>& triangle, const Point<F>& point)
{
    return are_intersecting(point, triangle);
}

template<std::floating_point F>
bool are_intersecting (const Triangle<F>& triangle, const Segment<F>& segment)
{
    return are_intersecting(segment, triangle);
}

template<std::floating_point F>
bool are_intersecting (const Triangle<F>& tr_1, const Triangle<F>& tr_2)
{
    auto P1_loc = Location::magic_product (tr_2.P(), tr_2.Q(), tr_2.R(), tr_1.P());
    auto Q1_loc = Location::magic_product (tr_2.P(), tr_2.Q(), tr_2.R(), tr_1.Q());
    auto R1_loc = Location::magic_product (tr_2.P(), tr_2.Q(), tr_2.R(), tr_1.R());

    if (P1_loc != Location::Loc3D::On && P1_loc == Q1_loc && Q1_loc == R1_loc)
        return false;
    else if (P1_loc == Location::Loc3D::On && Q1_loc == Location::Loc3D::On && R1_loc == Location::Loc3D::On)
        return Algorithm::intersection_in_2D (tr_1, tr_2);
    else
        return Algorithm::intersection_in_3D (tr_1, tr_2, P1_loc, Q1_loc, R1_loc);
}
} // namespace Geometry