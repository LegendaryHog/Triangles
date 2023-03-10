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
    Right = -1,
    On = 0,
    Left = 1
};

//  prds - Position Related to Direction on the Surface
template <std::floating_point F>
Location::Loc2D define_prds (const Point<F>& def_point, const Point<F>& vec_origin, 
                             const Point<F>& vec_end, const Vector<F>& normal)
{
    Vector<F> normal_def_point = vector_product (Vector<F> {def_point, vec_origin},
                                                 Vector<F> {def_point, vec_end});
    auto product = scalar_product (normal, normal_def_point);

    if (Compare::are_equal (product, 0.0))
        return Location::Loc2D::On;
    else if (product < 0.0)
        return Location::Loc2D::Right;
    else
        return Location::Loc2D::Left;
}

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
} // namespace Location
} // namespace Geometry
