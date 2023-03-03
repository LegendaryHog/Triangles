#pragma once

#include "double_comparison.hpp"
#include "line.hpp"
#include "point.hpp"
#include "vector.hpp"

#include <stdexcept> //  std::invalid_argument

namespace Geometry{

template<std::floating_point F>
class Plane
{
    //  By an origin and normal vector of the plane
    Vector<F> normal_;
    Point<F> origin_;

public:

    Plane (const Point<F> &origin, const Vector<F> &normal)
    {
        if (normal.is_zero ())
            throw std::invalid_argument {"Zero vector was given to constructor of Plane\n"};
        normal_ = normal * (1 / normal.module ());
        origin_ = origin;
    }

    //  Bad idea to construct a plane by 4 doubles
    Plane (F A, F B, F C, F D)
    {
        normal_ = {A, B, C};
        if (normal_.is_zero ())
            throw std::invalid_argument {"Zero vector was given to constructor of Plane\n"};
        if (Compare::are_equal (A, 0.0))
        {
            if (Compare::are_equal (B, 0.0))
                origin_ = {0, 0, -D / C};
            else
                origin_ = {0, -D / B, 0};
        }
        else
            origin_ = {-D / A, 0, 0};

        normal_ *= (1 / normal_.module ());
    }

    const Point<F> &origin () const { return origin_; };
    const Vector<F> &norm_vec () const { return normal_; };
};

//  block with Plane and Point
template<std::floating_point F>
F distance (const Point<F> &p, const Plane<F> &pl)
{
    const auto &origin = pl.origin ();
    Vector diff         = {p.x_ - origin.x_, p.y_ - origin.y_, p.z_ - origin.z_};
    return std::abs (scalar_product (diff, pl.norm_vec ()));
}

template<std::floating_point F>
F distance (const Plane<F> &pl, const Point<F> &p) { return (distance (p, pl)); };

template<std::floating_point F>
bool is_belong (const Point<F> &p, const Plane<F> &pl)
{
    return Compare::are_equal (distance (p, pl), 0.0);
}

//  block with Plane and Line
template<std::floating_point F>
bool are_intersect (const Line<F> &line, const Plane<F> &pl)
{
    return !are_orthogonal (line.drc_vec (), pl.norm_vec ());
}

template<std::floating_point F>
bool are_intersect (const Plane<F> &pl, const Line<F> &line) { return are_intersect (line, pl); };

template<std::floating_point F>
bool are_parallel (const Plane<F> &pl, const Line<F> &line) { return !are_intersect (line, pl); }
template<std::floating_point F>
bool are_parallel (const Line<F> &line, const Plane<F> &pl) { return are_parallel (pl, line); }

template<std::floating_point F>
bool is_belong (const Line<F> &line, const Plane<F> &pl)
{
    return are_parallel (line, pl) && is_belong (line.point_, pl);
}

template<std::floating_point F>
F distance (const Plane<F> &pl, const Line<F> &line)
{
    if (are_intersect (line, pl))
        throw std::logic_error {"Distance is undefined\n"};
    if (is_belong (line, pl))
        return 0.0;
    Vector diff {pl.origin (), line.point_};
    return std::abs (scalar_product (diff, pl.norm_vec ()));
}

template<std::floating_point F>
F distance (const Line<F> &line, const Plane<F> &pl) { return distance (pl, line); }

//  block with Plane and Plane
template<std::floating_point F>
bool are_parallel (const Plane<F> &pl1, const Plane<F> &pl2)
{
    return are_collinear (pl1.norm_vec (), pl2.norm_vec ());
}

template<std::floating_point F>
bool are_intersect (const Plane<F> &pl1, const Plane<F> &pl2) { return !are_parallel (pl1, pl2); }

template<std::floating_point F>
bool are_equal (const Plane<F> &pl1, const Plane<F> &pl2)
{
    return are_parallel (pl1, pl2) && is_belong (pl1.origin (), pl2);
}

template<std::floating_point F>
F distance (const Plane<F> &pl1, const Plane<F> &pl2)
{
    if (!are_parallel (pl1, pl2))
        throw std::logic_error {"Distance is undefined\n"};
    if (are_equal (pl1, pl2))
        return 0.0;
    Vector diff {pl1.origin (), pl2.origin ()};
    return std::abs (scalar_product (pl1.norm_vec (), diff));
}

} //  namespace Geometry