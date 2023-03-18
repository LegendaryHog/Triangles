#pragma once
#include "double_comparison.hpp"
#include <cmath> // for std::sqrt
#include <iostream>

namespace Geometry{

template<std::floating_point F>
struct Point
{
    F x_, y_, z_;

    Point (F x = 0.0, F y = 0.0, F z = 0.0): x_ {x}, y_ {y}, z_ {z} {}

    bool operator== (const Point &other) const
    {
        return (Compare::are_equal (x_, other.x_) && Compare::are_equal (y_, other.y_) &&
                Compare::are_equal (z_, other.z_));
    }

    bool operator!= (const Point &other) const { return !(*this == other); }

    bool is_valid () const { return (x_ == x_ && y_ == y_ && z_ == z_); }

    std::ostream& print (std::ostream& out = std::cout) const { return out << "(" << x_ << ", " << y_ << ", " << z_ << ")"; }
};
template<std::floating_point F>
Point<F> operator+(const Point<F>& p1, const Point<F>& p2)
{
    return Point{p1.x_ + p2.x_, p1.y_ + p2.y_, p1.z_ + p2.z_};
}

template<std::floating_point F>
std::ostream& operator<<(std::ostream& out, const Point<F>& p)
{
    return p.print(out);
}

template<std::floating_point F>
F distance (const Point<F>& first, const Point<F>& second)
{
    if (first == second)
        return 0.0;
    else
    {
        auto x_diff = first.x_ - second.x_;
        auto y_diff = first.y_ - second.y_;
        auto z_diff = first.z_ - second.z_;

        return std::sqrt (x_diff * x_diff + y_diff * y_diff + z_diff * z_diff);
    }
}

template<std::floating_point F>
Point<F> scan_point()
{
    Point<F> point {};
    std::cin >> point.x_ >> point.y_ >> point.z_;
    return point;
}

} // namespace Geometry