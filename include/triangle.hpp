#pragma once
#include "point.hpp"
#include "vector.hpp"

#include <algorithm> // for std::swap

namespace Geometry{

enum TriangleType {
    Triangle_ = 2,
    Segment_  = 1,
    Point_    = 0,
};

template<std::floating_point F>
class Triangle
{
    Point<F> P_, Q_, R_;
    TriangleType type_;

public:
    Triangle (const Point<F> &P, const Point<F> &Q, const Point<F> &R) : P_ {P}, Q_ {Q}, R_ {R}, type_ {type_calc()} {}

    bool operator== (const Triangle &rhs) const
    {
        return (P_ == rhs.P_ && Q_ == rhs.Q_ && R_ == rhs.R_);
    }

    TriangleType type() const & {return type_;};

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

    bool is_point () const { return (P_ == Q_ && Q_ == R_); }

    bool is_segment () const
    {
        Vector PQ {P_, Q_};
        Vector PR {P_, R_};
        
        return are_collinear (PQ, PR);
    }

private:
    TriangleType type_calc() const
    {
        if (is_point())
            return TriangleType::Point_;
        else if (is_segment())
            return TriangleType::Segment_;
        else
            return TriangleType::Triangle_;
    }

    public:
    const Point<F>& P() const & noexcept {return P_;}
    const Point<F>& Q() const & noexcept {return Q_;}
    const Point<F>& R() const & noexcept {return R_;}
    
    Point<F>& P() & noexcept {return P_;}
    Point<F>& Q() & noexcept {return Q_;}
    Point<F>& R() & noexcept {return R_;}
};

} // namespace Geometry