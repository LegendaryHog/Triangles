#pragma once
#include "triangle.hpp"
#include "point.hpp"
#include "vector.hpp"
#include "line.hpp"
#include "segemnt.hpp"

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
bool are_intersecting (const Point<F>& point, const Triangle<F>& triangle)
{
    if (magic_product(tr.P(), tr.Q(), tr.R(), point) != Loc3D::On)
        return false;
    
    return laying_in_same_half(triangle.P(), triangle.Q(), triangle.R(), point) != LocPoints::InDifferent &&
           laying_in_same_half(triangle.Q(), triangle.R(), triangle.P(), point) != LocPoints::InDifferent &&
           laying_in_same_half(triangle.R(), triangle.P(), triangle.Q(), point) != LocPoints::InDifferent;
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

    return laying_in_same_half(seg1.F_, seg1.S_, seg2.F_, seg2.S_) != LocPoints::InSame &&
           laying_in_same_half(seg2.F_, seg2.S_, seg1.F_, seg1.S_) != LocPoints::InSame;
}

template<std::floating_point F>
bool are_intersecting (const Segment<F>& segment, const Triangle<F>& triangle)
{
    auto F_loc = magic_product(triangle.P(), triangle.Q(), triangle.R(), segment.F_);
    auto S_loc = magic_product(triangle.P(), triangle.Q(), triangle.R(), segment.S_);

    if (F_loc != Loc3D::On && S_loc != Loc3D::On && F_loc == S_loc)
        return false;

    if (F_loc == Loc3D::On && S_loc == Loc3D::On)
        return seg_tr_intersecting_2D(segment, triangle);
    else
        return seg_tr_intersecting_3D(segment, triangle);
}

template<std::floating_point F>
bool are_intersecting (const Triangle<F>& tr_1, const Triangle<F>& tr_2)

template<std::floating_point F>
bool are_intersecting (const Triangle<F>& tr_1, const Triangle<F>& tr_2)

template<std::floating_point F>
bool are_intersecting (const Triangle<F>& tr_1, const Triangle<F>& tr_2)

template<std::floating_point F>
bool are_intersecting (const Triangle<F>& tr_1, const Triangle<F>& tr_2)
template<std::floating_point F>

bool are_intersecting (const Triangle<F>& tr_1, const Triangle<F>& tr_2)

} // namespace Geometry