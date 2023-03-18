#pragma once

#include "point.hpp"
#include "vector.hpp"
#include "triangle.hpp"
#include <iostream>

namespace Geometry{

template<std::floating_point Float>
struct Segment {
    Point<Float> F_, S_;

    Segment() = default;
    Segment(const Point<Float>& F, const Point<Float>& S): F_ {F}, S_ {S} {}
    Segment(Point<Float>&& F, Point<Float>&& S): F_ {std::move(F)}, S_ {std::move(S)} {}

    void swap_points() noexcept
    {
        std::swap(F_, S_);
    }
};

template<std::floating_point F>
std::ostream& operator<<(std::ostream& out, const Segment<F>& seg)
{
    return out << "Segment(" << seg.F_ << ", " << seg.S_ << ")";
}

template<std::floating_point Float>
bool operator==(const Segment<Float>& lhs, const Segment<Float>& rhs)
{
    return (lhs.F_ == rhs.F_) && (lhs.S_ == rhs.S_) || (lhs.F_ == rhs.S_) && (lhs.S_ == rhs.F_);
}
} //namespace Geometry