#pragma once

#include "point.hpp"
#include "vector.hpp"
#include "triangle.hpp"
#include <iostream>

namespace Geometry{

template<std::floating_point Float>
struct Segment {
    Point<Float> F_, S_;

    Segment(const Point<Float>& F, const Point<Float>& S): F_ {F}, S_ {S} {}
    Segment(Point<Float>&& F, Point<Float>&& S): F_ {std::move(F)}, S_ {std::move(S)} {}

    void swap_points() noexcept
    {
        std::swap(F_, S_);
    }
};
} //namespace Geometry