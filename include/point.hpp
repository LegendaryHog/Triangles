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

    Point& operator+=(const Point &rhs)
    {
        x_ = Compare::are_equal (x_, -rhs.x_) ? 0.0 : x_ + rhs.x_;
        y_ = Compare::are_equal (y_, -rhs.y_) ? 0.0 : y_ + rhs.y_;
        z_ = Compare::are_equal (z_, -rhs.z_) ? 0.0 : z_ + rhs.z_;

        return *this;
    }

    Point& operator-=(const Point &rhs)
    {
        x_ = Compare::are_equal (x_, rhs.x_) ? 0.0 : x_ - rhs.x_;
        y_ = Compare::are_equal (y_, rhs.y_) ? 0.0 : y_ - rhs.y_;
        z_ = Compare::are_equal (z_, rhs.z_) ? 0.0 : z_ - rhs.z_;

        return *this;
    }

    Point& operator*=(F coeff)
    {
        x_ *= coeff;
        y_ *= coeff;
        z_ *= coeff;

        return *this;
    }

    bool is_valid () const { return (x_ == x_ && y_ == y_ && z_ == z_); }
};

template<std::floating_point F>
bool operator==(const Point<F>& lhs, const Point<F>& rhs)
{
    return (Compare::are_equal (lhs.x_, rhs.x_) && Compare::are_equal (lhs.y_, rhs.y_) &&
            Compare::are_equal (lhs.z_, rhs.z_));
}

template<std::floating_point F>
Point<F> operator+(const Point<F>& lhs, const Point<F>& rhs)
{
    Point lhs_cpy = lhs;
    return (lhs_cpy += rhs);
}

template<std::floating_point F>
Point<F> operator-(const Point<F>& vec)
{
    return Point{-vec.x_, -vec.y_, -vec.z_};
}

template<std::floating_point F>
Point<F> operator-(const Point<F>& lhs, const Point<F>& rhs)
{
    Point lhs_cpy = lhs;
    return (lhs_cpy -= rhs);
}

template<std::floating_point F>
Point<F> operator* (const Point<F> &vec, F coeff)
{
    Point product = vec;
    return (product *= coeff);
}

template<std::floating_point F>
Point<F> operator* (F coeff, const Point<F> &vec) { return vec * coeff; }

template<std::floating_point F>
std::ostream& operator<<(std::ostream& out, const Point<F>& p)
{
    return out << "Point(" << p.x_ << ", " << p.y_ << ", " << p.z_ << ")";
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