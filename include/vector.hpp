#pragma once
#include "double_comparison.hpp"
#include "point.hpp"

#include <cmath> // for std::sqrt

namespace Geometry{

template<std::floating_point F>
struct Vector
{
    F x_, y_, z_;

    Vector (F x = 0.0, F y = 0.0, F z = 0.0): x_ {x}, y_ {y}, z_ {z} {}

    Vector (const Point<F> &pt): x_ {pt.x_}, y_ {pt.y_}, z_ {pt.z_} {}

    Vector (const Point<F> &first, const Point<F> &second)
    :x_ {Compare::are_equal (first.x_, second.x_) ? 0.0 : second.x_ - first.x_},
     y_ {Compare::are_equal (first.y_, second.y_) ? 0.0 : second.y_ - first.y_},
     z_ {Compare::are_equal (first.z_, second.z_) ? 0.0 : second.z_ - first.z_}
    {}

    bool operator== (const Vector &other) const
    {
        return (Compare::are_equal (x_, other.x_) && Compare::are_equal (y_, other.y_) &&
                Compare::are_equal (z_, other.z_));
    }

    bool operator!= (const Vector &other) const { return !(*this == other); }

    Vector &operator+= (const Vector &rhs)
    {
        x_ = Compare::are_equal (x_, -rhs.x_) ? 0.0 : x_ + rhs.x_;
        y_ = Compare::are_equal (y_, -rhs.y_) ? 0.0 : y_ + rhs.y_;
        z_ = Compare::are_equal (z_, -rhs.z_) ? 0.0 : z_ + rhs.z_;

        return *this;
    }

    Vector operator+ (const Vector &other) const
    {
        Vector sum = *this;
        return (sum += other);
    }

    Vector &operator-= (const Vector &rhs)
    {
        x_ = Compare::are_equal (x_, rhs.x_) ? 0.0 : x_ - rhs.x_;
        y_ = Compare::are_equal (y_, rhs.y_) ? 0.0 : y_ - rhs.y_;
        z_ = Compare::are_equal (z_, rhs.z_) ? 0.0 : z_ - rhs.z_;

        return *this;
    }

    Vector operator- (const Vector &other) const
    {
        Vector diff = *this;
        return (diff -= other);
    }

    Vector &operator*= (F coeff)
    {
        x_ *= coeff;
        y_ *= coeff;
        z_ *= coeff;

        return *this;
    }

    Vector operator- () const { return Vector {-x_, -y_, -z_}; }

    F norm () const { return x_ * x_ + y_ * y_ + z_ * z_; }

    F module () const { return std::sqrt (norm ()); }

    Vector &normalize ()
    {
        operator*= (1 / module ());

        return *this;
    }

    bool is_zero () const
    {
        return (Compare::are_equal (x_, 0.0) && Compare::are_equal (y_, 0.0) && Compare::are_equal (z_, 0.0));
    }

    void print () const { std::cout << "(" << x_ << ", " << y_ << ", " << z_ << ")" << std::endl; }
};

template<std::floating_point F>
Vector operator* (const Vector<F> &vec, F coeff)
{
    Vector product = vec;
    return (product *= coeff);
}

template<std::floating_point F>
Vector operator* (F coeff, const Vector<F> &vec) { return vec * coeff; }

template<std::floating_point F>
F scalar_product (const Vector<F> &lhs, const Vector<F> &rhs)
{
    auto xx = lhs.x_ * rhs.x_;
    auto yy = lhs.y_ * rhs.y_;
    auto zz = lhs.z_ * rhs.z_;

    auto tmp_product = Compare::are_equal (xx, -yy) ? 0.0 : xx + yy;
    auto product     = Compare::are_equal (tmp_product, -zz) ? 0.0 : tmp_product + zz;

    return product;
}

template<std::floating_point F>
Vector<F> vector_product (const Vector<F> &lhs, const Vector<F> &rhs)
{
    auto ly_rz     = lhs.y_ * rhs.z_;
    auto lz_ry     = lhs.z_ * rhs.y_;
    auto product_1 = Compare::are_equal (ly_rz, lz_ry) ? 0.0 : ly_rz - lz_ry;

    auto lz_rx     = lhs.z_ * rhs.x_;
    auto lx_rz     = lhs.x_ * rhs.z_;
    auto product_2 = Compare::are_equal (lz_rx, lx_rz) ? 0.0 : lz_rx - lx_rz;

    auto lx_ry     = lhs.x_ * rhs.y_;
    auto ly_rx     = lhs.y_ * rhs.x_;
    auto product_3 = Compare::are_equal (lx_ry, ly_rx) ? 0.0 : lx_ry - ly_rx;

    return Vector {product_1, product_2, product_3};
}

template<std::floating_point F>
F triple_product (const Vector<F> &first, const Vector<F> &second, const Vector<F> &third)
{
    return scalar_product (first, vector_product (second, third));
}

template<std::floating_point F>
bool are_collinear (const Vector<F> &first, const Vector<F> &second)
{
    return vector_product (first, second).is_zero ();
}

template<std::floating_point F>
bool are_coplanar (const Vector<F> &first, const Vector<F> &second, const Vector<F> &third)
{
    return Compare::are_equal (triple_product (first, second, third), 0.0);
}

template<std::floating_point F>
bool are_orthogonal (const Vector<F> &first, const Vector<F> &second)
{
    return Compare::are_equal (scalar_product (first, second), 0.0);
}

} // namespace Geometry