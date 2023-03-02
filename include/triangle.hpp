#ifndef INCLUDE_TRIANGLE_HPP
#define INCLUDE_TRIANGLE_HPP

#include "point.hpp"
#include "vector.hpp"

#include <algorithm> // for std::swap

namespace Geom_Objects
{

enum Tr_Type {
    Triangle_ = 2,
    Segment_ = 1,
    Point_ = 0,
};


class Triangle
{
    Point P_, Q_, R_;
    Tr_Type type_;

    public:
    Triangle (const Point &P, const Point &Q, const Point &R) : P_ {P}, Q_ {Q}, R_ {R}, type_ {type_calc()} {}

    bool operator== (const Triangle &rhs) const
    {
        return (P_ == rhs.P_ && Q_ == rhs.Q_ && R_ == rhs.R_);
    }

    Tr_Type type() const & {return type_;};

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
    Tr_Type type_calc() const
    {
        if (is_point())
            return Tr_Type::Point_;
        else if (is_segment())
            return Tr_Type::Segment_;
        else
            return Tr_Type::Triangle_;
    }

    public:
    const Point& P() const & noexcept {return P_;}
    const Point& Q() const & noexcept {return Q_;}
    const Point& R() const & noexcept {return R_;}
    
    Point& P() & noexcept {return P_;}
    Point& Q() & noexcept {return Q_;}
    Point& R() & noexcept {return R_;}
};

} // namespace Geom_Objects

#endif // INCLUDE_TRIANGLE_HPP
