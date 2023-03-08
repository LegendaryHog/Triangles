#pragma once
#include "point.hpp"
#include "vector.hpp"

#include <algorithm> // for std::swap

namespace Geometry{

template<std::floating_point F>
struct Triangle
{
    Point<F> P_, Q_, R_;

    Triangle(const Point<F>& P, const Point<F>& Q, const Point<F>& R)
    :P_ {P}, Q_ {Q}, R_ {R}
    {}

    Triangle(Point<F>&& P, Point<F>&& Q, Point<F>&& R)
    :P_ {std::move(P)}, Q_ {std::move(Q)}, R_ {std::move(R)}
    {}


    bool operator== (const Triangle &rhs) const
    {
        return (P_ == rhs.P_ && Q_ == rhs.Q_ && R_ == rhs.R_);
    }

    void swap_QR () { std::swap (Q_, R_); }

    void swap_clockwise ()
    {
        std::swap (P_, R_);
        std::swap (Q_, R_);
    }

    void swap_counterclockwise ()
    {
        std::swap (P_, Q_);
        std::swap (R_, Q_);
    }
};

} // namespace Geometry