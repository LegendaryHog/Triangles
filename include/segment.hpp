#pragma once

#include "point.hpp"
#include "vector.hpp"
#include "triangle.hpp"
#include <iostream>

namespace Geometry{

template<std::floating_point Float>
struct Segment {
    Point<Float> F_, S_;
    
    Segment(const Point<Float>& F, const Point<Float>& S): F_ {F}, S_ {S}
    {
        #ifndef RELEASE
        if (F_ == S_)
            throw std::invalid_argument{"try to create segment from equal dots"};
        #endif
    }

    Segment(const Triangle<Float>& tr)
    {
        #ifndef RELEASE
        if (tr.type() != TriangleType::Segment_)
            throw std::logic_error{"In ctor Segmnet by Triangle type of Triangle isnt Segemnt_"};
        #endif

        Vector PQ {tr.P(), tr.Q()};
        Vector RQ {tr.R(), tr.Q()};

        if (scalar_product(PQ, RQ) < 0.0 || tr.P() == tr.R())
        {
            F_ = tr.P();
            S_ = tr.R();
        }
        else
        {
            F_ = tr.Q();
            if (PQ.norm() > RQ.norm())
                S_ = tr.P();
            else
                S_ = tr.R();
        }
    }

    void swap_points() noexcept
    {
        std::swap(F_, S_);
    }
};
} //namespace Geometry