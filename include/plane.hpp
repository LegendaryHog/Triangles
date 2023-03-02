#pragma once

#include "double_comparison.hpp"
#include "line.hpp"
#include "point.hpp"
#include "vector.hpp"

#include <stdexcept> //  std::invalid_argument

namespace Geom_Objects
{

class Plane
{
    //  By an origin and normal vector of the plane
    Vector normal_;
    Point origin_;

public:

    Plane (const Point &origin, const Vector &normal)
    {
        if (normal.is_zero ())
            throw std::invalid_argument {"Zero vector was given to constructor of Plane\n"};
        normal_ = normal * (1 / normal.module ());
        origin_ = origin;
    }

    //  Bad idea to construct a plane by 4 doubles
    Plane (double A, double B, double C, double D)
    {
        normal_ = {A, B, C};
        if (normal_.is_zero ())
            throw std::invalid_argument {"Zero vector was given to constructor of Plane\n"};
        if (cmp::are_equal (A, 0.0))
        {
            if (cmp::are_equal (B, 0.0))
                origin_ = {0, 0, -D / C};
            else
                origin_ = {0, -D / B, 0};
        }
        else
            origin_ = {-D / A, 0, 0};

        normal_ *= (1 / normal_.module ());
    }

    const Point &origin () const { return origin_; };
    const Vector &norm_vec () const { return normal_; };
};

//  block with Plane and Point
inline double distance (const Point &p, const Plane &pl)
{
    const Point &origin = pl.origin ();
    Vector diff         = {p.x_ - origin.x_, p.y_ - origin.y_, p.z_ - origin.z_};
    return std::abs (scalar_product (diff, pl.norm_vec ()));
}
inline double distance (const Plane &pl, const Point &p) { return (distance (p, pl)); };

inline bool is_belong (const Point &p, const Plane &pl)
{
    return cmp::are_equal (distance (p, pl), 0.0);
}

//  block with Plane and Line
inline bool are_intersect (const Line &line, const Plane &pl)
{
    return !are_orthogonal (line.drc_vec (), pl.norm_vec ());
}
inline bool are_intersect (const Plane &pl, const Line &line) { return are_intersect (line, pl); };

inline bool are_parallel (const Plane &pl, const Line &line) { return !are_intersect (line, pl); }
inline bool are_parallel (const Line &line, const Plane &pl) { return are_parallel (pl, line); }

inline bool is_belong (const Line &line, const Plane &pl)
{
    return are_parallel (line, pl) && is_belong (line.point_, pl);
}

inline double distance (const Plane &pl, const Line &line)
{
    if (are_intersect (line, pl))
        throw std::logic_error {"Distance is undefined\n"};
    if (is_belong (line, pl))
        return 0.0;
    Vector diff {pl.origin (), line.point_};
    return std::abs (scalar_product (diff, pl.norm_vec ()));
}
inline double distance (const Line &line, const Plane &pl) { return distance (pl, line); }

//  block with Plane and Plane
inline bool are_parallel (const Plane &pl1, const Plane &pl2)
{
    return are_collinear (pl1.norm_vec (), pl2.norm_vec ());
}

inline bool are_intersect (const Plane &pl1, const Plane &pl2) { return !are_parallel (pl1, pl2); }

inline bool are_equal (const Plane &pl1, const Plane &pl2)
{
    return are_parallel (pl1, pl2) && is_belong (pl1.origin (), pl2);
}

inline double distance (const Plane &pl1, const Plane &pl2)
{
    if (!are_parallel (pl1, pl2))
        throw std::logic_error {"Distance is undefined\n"};
    if (are_equal (pl1, pl2))
        return 0.0;
    Vector diff {pl1.origin (), pl2.origin ()};
    return std::abs (scalar_product (pl1.norm_vec (), diff));
}

} //  namespace Geom_Objects
