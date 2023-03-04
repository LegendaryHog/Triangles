#pragma once
#include "location.hpp"
#include "point.hpp"
#include "vector.hpp"

namespace Geometry
{
namespace Algorithm
{

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

template<std::floating_point F>
bool test_intersection_R1 (const Triangle<F> &tr_1, const Triangle<F> &tr_2)
{
    if (Location::magic_product (tr_2.R(), tr_2.P(), tr_1.Q()) == Location::Loc2D::Negative)
    {
        return !(Location::magic_product (tr_2.R(), tr_2.P(), tr_1.R()) == Location::Loc2D::Negative ||
                 Location::magic_product (tr_1.Q(), tr_1.R(), tr_2.R()) == Location::Loc2D::Negative ||
                 Location::magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Location::Loc2D::Negative);
    }
    else 
    {
        if (Location::magic_product (tr_2.R(), tr_1.P(), tr_1.Q()) == Location::Loc2D::Negative)
            return false;
        else if (Location::magic_product (tr_1.P(), tr_2.P(), tr_1.Q()) != Location::Loc2D::Negative)
            return true;
        else if (Location::magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Location::Loc2D::Negative ||
                 Location::magic_product (tr_1.Q(), tr_1.R(), tr_2.P()) == Location::Loc2D::Negative)
            return false;
        else
            return true;
    }
}

template<std::floating_point F>
bool test_intersection_R2 (const Triangle<F> &tr_1, const Triangle<F> &tr_2)
{
    if (Location::magic_product (tr_2.R(), tr_2.P(), tr_1.Q()) == Location::Loc2D::Negative)
    {
        if (Location::magic_product (tr_2.R(), tr_2.P(), tr_1.R()) == Location::Loc2D::Negative)
            return false;
        else if (Location::magic_product (tr_1.Q(), tr_1.R(), tr_2.R()) == Location::Loc2D::Negative)
        {
            return !(Location::magic_product (tr_1.Q(), tr_1.R(), tr_2.Q()) == Location::Loc2D::Negative ||
                     Location::magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Location::Loc2D::Negative);
        }
        else
            return !(Location::magic_product (tr_1.R(), tr_1.P(), tr_2.P()) == Location::Loc2D::Negative);
    }
    else
    {
        if (Location::magic_product (tr_2.Q(), tr_2.R(), tr_1.Q()) == Location::Loc2D::Negative)
        {
            return !(Location::magic_product (tr_1.P(), tr_2.Q(), tr_1.Q()) == Location::Loc2D::Positive ||
                     Location::magic_product (tr_2.Q(), tr_2.R(), tr_1.R()) == Location::Loc2D::Negative ||
                     Location::magic_product (tr_1.Q(), tr_1.R(), tr_2.Q()) == Location::Loc2D::Negative);
        }
        else
        {
            if (Location::magic_product (tr_1.P(), tr_2.P(), tr_1.Q()) == Location::Loc2D::Negative)
            {
                return !(Location::magic_product (tr_1.P(), tr_2.P(), tr_1.R()) == Location::Loc2D::Negative ||
                         Location::magic_product (tr_2.R(), tr_2.P(), tr_1.R()) == Location::Loc2D::Negative);
            }
            else 
                return !(Location::magic_product (tr_1.P(), tr_2.Q(), tr_1.Q()) == Location::Loc2D::Positive);
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
    if (Location::magic_product (tr_2.P(), tr_2.Q(), tr_2.R()) == Location::Loc2D::Negative)
        tr_2.swap_QR ();

    auto P2_loc = Location::magic_product (tr_1.P(), tr_1.Q(), tr_2.P()) *
                  Location::magic_product (tr_1.Q(), tr_1.R(), tr_2.P()) *
                  Location::magic_product (tr_1.R(), tr_1.P(), tr_2.P());

    auto P1_loc = Location::Loc2D::Positive;

    auto P1_P2_Q2 = Location::Loc2D::Is_vertice;
    auto P1_Q2_R2 = Location::Loc2D::Is_vertice;
    auto P1_R2_P2 = Location::Loc2D::Is_vertice;
    auto sum_locs = Location::Loc2D::Is_vertice;

    //  interior of tr_2
    if (P1_P2_Q2 == Location::Loc2D::Positive &&
        P1_Q2_R2 == Location::Loc2D::Positive && 
        P1_R2_P2 == Location::Loc2D::Positive)
        return true;
    else if (P1_loc == Location::Loc2D::Neutral &&
            (sum_locs == Location::Loc2D::Is_vertice || sum_locs == Location::Loc2D::On_side))
        return true;
    else if (P1_loc == Location::Loc2D::Negative ||
            ((P1_loc == Location::Loc2D::Neutral) && (sum_locs == Location::Loc2D::Neutral)))
        return test_intersection_R1 (tr_1, tr_2);
    else
        return test_intersection_R2 (tr_1, tr_2);
}

template<std::floating_point F>
void transform_triangle (Triangle<F> &tr_1, Location::Loc3D P1_loc, Location::Loc3D Q1_loc, Location::Loc3D R1_loc, Triangle<F> &tr_2)
{
    if (P1_loc == Location::Loc3D::Above)
    {
        if (Q1_loc == Location::Loc3D::Above && R1_loc != Location::Loc3D::Above)
        {
            tr_1.swap_clockwise ();
            tr_2.swap_QR ();
        }
        else if (Q1_loc != Location::Loc3D::Above && R1_loc == Location::Loc3D::Above)
        {
            tr_1.swap_counterclockwise ();
            tr_2.swap_QR ();
        }
    }
    else if (P1_loc == Location::Loc3D::On)
    {
        if (Q1_loc == Location::Loc3D::Above && R1_loc == Location::Loc3D::Above)
            tr_2.swap_QR ();
        else if (Q1_loc == Location::Loc3D::Above && R1_loc != Location::Loc3D::Above)
            tr_1.swap_counterclockwise ();
        else if (Q1_loc != Location::Loc3D::Above && R1_loc == Location::Loc3D::Above)
            tr_1.swap_clockwise ();
        else if (Q1_loc == Location::Loc3D::On && R1_loc == Location::Loc3D::Below)
        {
            tr_1.swap_clockwise ();
            tr_2.swap_QR ();
        }
        else if (Q1_loc == Location::Loc3D::Below && R1_loc == Location::Loc3D::On)
        {
            tr_1.swap_counterclockwise ();
            tr_2.swap_QR ();
        }
    }
    else
    {
        if (Q1_loc == R1_loc)
            tr_2.swap_QR ();
        else if (Q1_loc == Location::Loc3D::Below && R1_loc != Location::Loc3D::Below)
            tr_1.swap_clockwise ();
        else if (Q1_loc != Location::Loc3D::Below && R1_loc == Location::Loc3D::Below)
            tr_1.swap_counterclockwise ();
        else
            tr_2.swap_QR ();
    }
}

template<std::floating_point F>
bool intersection_in_3D (const Triangle<F> &tr_1_, const Triangle<F> &tr_2_, const Location::Loc3D P1_loc,
                         const Location::Loc3D Q1_loc, const Location::Loc3D R1_loc)
{
    Triangle tr_1 = tr_1_;
    Triangle tr_2 = tr_2_;
    
    auto P2_loc = Location::magic_product (tr_1.P(), tr_1.Q(), tr_1.R(), tr_2.P());
    auto Q2_loc = Location::magic_product (tr_1.P(), tr_1.Q(), tr_1.R(), tr_2.Q());
    auto R2_loc = Location::magic_product (tr_1.P(), tr_1.Q(), tr_1.R(), tr_2.R());

    if (P2_loc != Location::Loc3D::On && P2_loc == Q2_loc && Q2_loc == R2_loc)
        return false;
    else
    {
        transform_triangle (tr_1, P1_loc, Q1_loc, R1_loc, tr_2);
        transform_triangle (tr_2, P2_loc, Q2_loc, R2_loc, tr_1);

        auto new_P1_loc = Location::magic_product (tr_2.P(), tr_2.Q(), tr_2.R(), tr_1.P());
        auto new_P2_loc = Location::magic_product (tr_1.P(), tr_1.Q(), tr_1.R(), tr_2.P());

        if (new_P1_loc == Location::Loc3D::On && new_P2_loc == Location::Loc3D::On)
            return (tr_1.P() == tr_2.P());
        else
        {
            auto KJ_mut_pos = Location::magic_product (tr_1.P(), tr_1.Q(), tr_2.P(), tr_2.Q());
            auto LI_mut_pos = Location::magic_product (tr_1.P(), tr_1.R(), tr_2.P(), tr_2.R());

            return (LI_mut_pos != Location::Loc3D::Below && KJ_mut_pos != Location::Loc3D::Above);
        }
    }
}

} // namespace Algorithm
} // namespace Geometry 

