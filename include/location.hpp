#pragma once
#include "point.hpp"
#include "vector.hpp"

namespace Geometry
{
namespace Location
{

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

enum class Loc3D
{
    Below = -1,
    On    = 0,
    Above = 1
};

enum Loc2D
{
    Negative = -1,
    Neutral  = 0,
    Positive = 1,
    Is_vertice = 1,
    On_side = 2
};

/*
 * Let P, Q, R (in this very order) and M be points in R^3.
 *
 * Then magic_product(P, Q, R, M) is prcisely the sign of
 * triple product (v_PM, v_QM, v_RM), where v_PM is a vector
 * with initial point P and terminal point M, v_QM - vector
 * with initial point Q and terminal point M, v_RM - vector
 * with initial point R and terminal point M.
 */
template<std::floating_point F>
Loc3D magic_product (const Point<F>& P, const Point<F>& Q, const Point<F>& R, const Point<F>& M)
{
    auto elem_21 = M.x_ - Q.x_;
    auto elem_22 = M.y_ - Q.y_;
    auto elem_23 = M.z_ - Q.z_;

    auto elem_31 = M.x_ - R.x_;
    auto elem_32 = M.y_ - R.y_;
    auto elem_33 = M.z_ - R.z_;

    auto product = (M.x_ - P.x_) * (elem_22 * elem_33 - elem_23 * elem_32) -
                   (M.y_ - P.y_) * (elem_21 * elem_33 - elem_23 * elem_31) +
                   (M.z_ - P.z_) * (elem_21 * elem_32 - elem_22 * elem_31);

    if (Compare::are_equal (product, 0.0))
        return Loc3D::On;
    else if (product > 0)
        return Loc3D::Above;
    else
        return Loc3D::Below;
}

template<std::floating_point F>
Loc2D magic_product (const Point<F>& P, const Point<F>& Q, const Point<F>& M)
{
    auto product = (P.x_ - M.x_) * (Q.y_ - M.y_) - (P.y_ - M.y_) * (Q.x_ - M.x_);
    //  Positive product is considered when points locate in counterclockwise ordering
    if (Compare::are_equal (product, 0.0))
        return Loc2D::Neutral;
    else if (product > 0)
        return Loc2D::Positive;
    else
        return Loc2D::Negative;
}
} // namespace Location
} // namespace Geometry