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
    Undefined = 0,
};

template<std::floating_point F>
LocPoints laying_in_same_half(const Point<F>& A, const Point<F>& B, const Point<F>& C, const Point<F>& D)
{
    Vector AB {A, B}, AC {A, C}, AD {A, D};

    auto prod = scalar_product(vector_product(AB, AC), vector_product(AB, AD));

    if (Compare::are_equal(prod, 0.0))
        return LocPoints::Undefined;
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
 * Points P, Q, R make a plane. Let normal of this plane [RP, RQ]
 * (vector of rotate with order of points P, Q, R), lets normal of PQR 
 * make the up direction
 * 
 * If M is on the plane, than return    Loc3D::On 
 * If M is above the plane, than return Loc3D::Above
 * If M is below the plane, than retunr Loc3D::Below
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
    else if (product > 0.0)
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