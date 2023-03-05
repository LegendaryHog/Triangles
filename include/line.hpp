#pragma once
#include "double_comparison.hpp"
#include "point.hpp"
#include "vector.hpp"

namespace Geometry{

template<std::floating_point F>
class Line
{
    Vector<F> drc_vec_;
public:
    Point<F> point_;

    Line (const Point<F> &p1, const Point<F> &p2)
        : point_ {p1}, drc_vec_ {p1.x_ - p2.x_, p1.y_ - p2.y_, p1.z_ - p2.z_}
    {
#ifndef RELEASE
        if (p1 == p2)
            throw std::invalid_argument {"In constructor of Line(Point, Point): two equal points"};
#endif
    }

    Line (const Point<F> &p, const Vector<F> &vec) : point_ {p}, drc_vec_ {vec}
    {
#ifndef RELEASE
        if (vec.is_zero ())
            throw std::invalid_argument {"In constructor of Line(Point, Vector): null drc vector"};
#endif
    }

    const Vector<F> &drc_vec () const { return drc_vec_; }

    const Vector<F> &drc_vec(const Vector<F> &new_vec) &
    {
#ifndef RELEASE
        if (new_vec.is_zero ())
            throw std::invalid_argument {"In method of change drc_vec(): null vector"};
#endif

        drc_vec_ = new_vec;
        return drc_vec_;
    }

    bool operator== (const Line &other) const
    {
        if (!are_collinear(drc_vec_, other.drc_vec_))
            return false;
        return are_collinear(Vector {point_, other.point_}, drc_vec_);
    }

    bool operator!= (const Line &other) const { return !(*this == other); }
};

template<std::floating_point F>
bool are_parallel (const Line<F> &line1, const Line<F> &line2)
{
    return are_collinear (line1.drc_vec (), line2.drc_vec ());
}

template<std::floating_point F>
F distance (const Line<F> &line, const Point<F> &pt)
{
    Vector dot_vec {pt, line.point_};
    auto coef = scalar_product (dot_vec, line.drc_vec ()) /
                  scalar_product (line.drc_vec (), line.drc_vec ());
    return (dot_vec - coef * line.drc_vec ()).module ();
}

template<std::floating_point F>
F distance (const Point<F> &pt, const Line<F> &line) { return distance (line, pt); }

template<std::floating_point F>
F distance (const Line<F> &line1, const Line<F> &line2)
{
    if (are_parallel (line1, line2))
        return distance (line1.point_, line2);

    Vector dots_vec {line1.point_, line2.point_};
    return triple_product (dots_vec, line1.drc_vec (), line2.drc_vec ()) /
           vector_product (line1.drc_vec (), line2.drc_vec ()).module ();
}

template<std::floating_point F>
bool are_intersecting (const Line<F> &line1, const Line<F> &line2)
{
    return Compare::are_equal (distance (line1, line2), 0.0);
}

template<std::floating_point F>
bool is_belong (const Point<F> &pt, const Line<F> &line)
{
    return Compare::are_equal (distance (pt, line), 0.0);
}

template<std::floating_point F>
bool is_belong (const Line<F> &line, const Point<F> &pt) { return is_belong (pt, line); }

template<std::floating_point F>
bool in_plane (const Line<F> &line1, const Line<F> &line2)
{
    return are_parallel (line1, line2) || are_intersecting (line1, line2);
}

} //namespace Geometry