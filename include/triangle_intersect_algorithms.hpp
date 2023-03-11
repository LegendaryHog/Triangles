#pragma once
#include "location.hpp"
#include "point.hpp"
#include "vector.hpp"

namespace Geometry
{
namespace Algorithm
{

//  prds - Position Related to Direction on the Plane 
template <std::floating_point F>
Location::Loc2D define_prds (const Point<F>& def_point, const Point<F>& vec_origin, 
                             const Point<F>& vec_end, const Vector<F>& normal)
{
    Vector<F> normal_def_point = vector_product (Vector<F> {def_point, vec_origin},
                                                 Vector<F> {def_point, vec_end}).normalize ();
    auto sign = static_cast<int>(scalar_product (normal, normal_def_point));
    //  Can I remake this with casting?
    switch (sign)
    {
        case -1:
            return Location::Loc2D::Right;
        case 0:
            return Location::Loc2D::On;
        case 1:
            return Location::Loc2D::Left;
        default:
            throw std::runtime_error ("Objects are located in different planes\n");
    }
}

//  Vector normal which defined orientation of tr_1
template <std::floating_point F>
bool test_intersection_R1 (const Triangle<F> &tr_1, const Triangle<F> &tr_2, const Vector<F>& normal)
{   
    if (define_prds (tr_2.R_, tr_2.P_, tr_1.Q_, normal) == Location::Loc2D::Right)
    {
        return !(define_prds (tr_2.R_, tr_2.P_, tr_1.R_, normal) == Location::Loc2D::Right ||
                 define_prds (tr_1.Q_, tr_1.R_, tr_2.R_, normal) == Location::Loc2D::Right ||
                 define_prds (tr_1.P_, tr_2.P_, tr_1.R_, normal) == Location::Loc2D::Right);
    }
    else 
    {
        if (define_prds (tr_2.R_, tr_1.P_, tr_1.Q_, normal) == Location::Loc2D::Right)
            return false;
        else if (define_prds (tr_1.P_, tr_2.P_, tr_1.Q_, normal) != Location::Loc2D::Right)
            return true;
        else if (define_prds (tr_1.P_, tr_2.P_, tr_1.R_, normal) == Location::Loc2D::Right ||
                 define_prds (tr_1.Q_, tr_1.R_, tr_2.P_, normal) == Location::Loc2D::Right)
            return false;
        else
            return true;
    }
}

template <std::floating_point F>
bool test_intersection_R2 (const Triangle<F>& tr_1, const Triangle<F>& tr_2, const Vector<F>& normal)
{
    if (define_prds (tr_2.R_, tr_2.P_, tr_1.Q_, normal) == Location::Loc2D::Right)
    {
        if (define_prds (tr_2.R_, tr_2.P_, tr_1.R_, normal) == Location::Loc2D::Right)
            return false;
        else if (define_prds (tr_1.Q_, tr_1.R_, tr_2.R_, normal) == Location::Loc2D::Right)
        {
            return !(define_prds (tr_1.Q_, tr_1.R_, tr_2.Q_, normal) == Location::Loc2D::Right ||
                     define_prds (tr_2.Q_, tr_2.R_, tr_1.R_, normal) == Location::Loc2D::Right);
        }
        else
            return !(define_prds (tr_1.R_, tr_1.P_, tr_2.P_, normal) == Location::Loc2D::Right);
    }
    else
    {
        if (define_prds (tr_2.Q_, tr_2.R_, tr_1.Q_, normal) == Location::Loc2D::Right)
        {
            return !(define_prds (tr_1.P_, tr_2.Q_, tr_1.Q_, normal) == Location::Loc2D::Left ||
                     define_prds (tr_2.Q_, tr_2.R_, tr_1.R_, normal) == Location::Loc2D::Right ||
                     define_prds (tr_1.Q_, tr_1.R_, tr_2.Q_, normal) == Location::Loc2D::Right);
        }
        else
        {
            if (define_prds (tr_1.P_, tr_2.P_, tr_1.Q_, normal) == Location::Loc2D::Right)
            {
                return !(define_prds (tr_1.P_, tr_2.P_, tr_1.R_, normal) == Location::Loc2D::Right ||
                         define_prds (tr_2.R_, tr_2.P_, tr_1.R_, normal) == Location::Loc2D::Right);
            }
            else 
                return !(define_prds (tr_1.P_, tr_2.Q_, tr_1.Q_, normal) == Location::Loc2D::Left);
        }
    }
}

template <std::floating_point F>
bool intersection_in_2D (const Triangle<F>& tr_1_, const Triangle<F>& tr_2_)
{
    Triangle<F> tr_1 = tr_1_, tr_2 = tr_2_;
    //  Return a normal vector by the 1st triangle
    Vector<F> normal = vector_product (Vector<F> {tr_1.P_, tr_1.Q_}, 
                                       Vector<F> {tr_1.P_, tr_1.R_}).normalize();
    std::cout << "normal: (" << normal.x_ << " " << normal.y_ << " " << normal.z_ << ")" << std::endl;

    //  Swap tr_2.Q() and tr_2.R() if P2, Q2, R2 are clockwise
    if (define_prds (tr_2.P_, tr_2.Q_, tr_2.R_, normal) == Location::Loc2D::Right)
        tr_2.swap_QR ();

    auto P1_P2_Q2 = define_prds (tr_1.P_, tr_2.P_, tr_2.Q_, normal);
    auto P1_Q2_R2 = define_prds (tr_1.P_, tr_2.Q_, tr_2.R_, normal);
    auto P1_R2_P2 = define_prds (tr_1.P_, tr_2.R_, tr_2.P_, normal);

    //  Define position of P1
    if (P1_P2_Q2 == Location::Loc2D::Left && P1_Q2_R2 == Location::Loc2D::Left && P1_R2_P2 == Location::Loc2D::Left)
        return true;
    else if (tr_1.P_ == tr_2.P_ || tr_1.P_ == tr_2.Q_ || tr_1.P_ == tr_2.R_)
        return true;
    else if ((P1_P2_Q2 * P1_Q2_R2 * P1_R2_P2 == Location::Loc2D::On) &&
             (P1_P2_Q2 != Location::Loc2D::Right && P1_Q2_R2 != Location::Loc2D::Right ||
              P1_Q2_R2 != Location::Loc2D::Right && P1_R2_P2 != Location::Loc2D::Right ||
              P1_R2_P2 != Location::Loc2D::Right && P1_P2_Q2 != Location::Loc2D::Right))
        return true;
    else if (P1_P2_Q2 == Location::Loc2D::Left && P1_Q2_R2 == Location::Loc2D::Left ||
             P1_Q2_R2 == Location::Loc2D::Left && P1_R2_P2 == Location::Loc2D::Left ||
             P1_R2_P2 == Location::Loc2D::Left && P1_P2_Q2 == Location::Loc2D::Left) 
        return test_intersection_R1 (tr_1, tr_2, normal);
    else
        return test_intersection_R2 (tr_1, tr_2, normal);
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
bool intersection_in_3D (Triangle<F> tr_1, Triangle<F> tr_2, Location::Loc3D P1_loc,
                         Location::Loc3D Q1_loc, Location::Loc3D R1_loc)
{   
    auto P2_loc = Location::magic_product (tr_1.P_, tr_1.Q_, tr_1.R_, tr_2.P_);
    auto Q2_loc = Location::magic_product (tr_1.P_, tr_1.Q_, tr_1.R_, tr_2.Q_);
    auto R2_loc = Location::magic_product (tr_1.P_, tr_1.Q_, tr_1.R_, tr_2.R_);

    if (P2_loc != Location::Loc3D::On && P2_loc == Q2_loc && Q2_loc == R2_loc)
        return false;
    else
    {
        transform_triangle (tr_1, P1_loc, Q1_loc, R1_loc, tr_2);
        transform_triangle (tr_2, P2_loc, Q2_loc, R2_loc, tr_1);

        auto new_P1_loc = Location::magic_product (tr_2.P_, tr_2.Q_, tr_2.R_, tr_1.P_);
        auto new_P2_loc = Location::magic_product (tr_1.P_, tr_1.Q_, tr_1.R_, tr_2.P_);

        if (new_P1_loc == Location::Loc3D::On && new_P2_loc == Location::Loc3D::On)
            return (tr_1.P_ == tr_2.P_);
        else
        {
            auto KJ_mut_pos = Location::magic_product (tr_1.P_, tr_1.Q_, tr_2.P_, tr_2.Q_);
            auto LI_mut_pos = Location::magic_product (tr_1.P_, tr_1.R_, tr_2.P_, tr_2.R_);

            return (LI_mut_pos != Location::Loc3D::Below && KJ_mut_pos != Location::Loc3D::Above);
        }
    }
}

} // namespace Algorithm
} // namespace Geometry 

