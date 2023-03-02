#pragma once
#include "double_comparison.hpp"
#include "point.hpp"

#include <cmath> // for std::sqrt

namespace Geom_Objects
{

struct Vector
{
    double x_, y_, z_;

    Vector (const double x = 0.0, const double y = 0.0, const double z = 0.0)
        : x_ {x}, y_ {y}, z_ {z}
    {}

    Vector (const Point &pt) : x_ {pt.x_}, y_ {pt.y_}, z_ {pt.z_} {}

    Vector (const Point &first, const Point &second)
        : x_ {cmp::are_equal (first.x_, second.x_) ? 0.0 : second.x_ - first.x_},
          y_ {cmp::are_equal (first.y_, second.y_) ? 0.0 : second.y_ - first.y_},
          z_ {cmp::are_equal (first.z_, second.z_) ? 0.0 : second.z_ - first.z_}
    {}

    bool operator== (const Vector &other) const
    {
        return (cmp::are_equal (x_, other.x_) && cmp::are_equal (y_, other.y_) &&
                cmp::are_equal (z_, other.z_));
    }

    bool operator!= (const Vector &other) const { return !(*this == other); }

    Vector &operator+= (const Vector &rhs)
    {
        x_ = cmp::are_equal (x_, -rhs.x_) ? 0.0 : x_ + rhs.x_;
        y_ = cmp::are_equal (y_, -rhs.y_) ? 0.0 : y_ + rhs.y_;
        z_ = cmp::are_equal (z_, -rhs.z_) ? 0.0 : z_ + rhs.z_;

        return *this;
    }

    Vector operator+ (const Vector &other) const
    {
        Vector sum = *this;
        return (sum += other);
    }

    Vector &operator-= (const Vector &rhs)
    {
        x_ = cmp::are_equal (x_, rhs.x_) ? 0.0 : x_ - rhs.x_;
        y_ = cmp::are_equal (y_, rhs.y_) ? 0.0 : y_ - rhs.y_;
        z_ = cmp::are_equal (z_, rhs.z_) ? 0.0 : z_ - rhs.z_;

        return *this;
    }

    Vector operator- (const Vector &other) const
    {
        Vector diff = *this;
        return (diff -= other);
    }

    Vector &operator*= (const double coeff)
    {
        x_ *= coeff;
        y_ *= coeff;
        z_ *= coeff;

        return *this;
    }

    Vector operator- () const { return Vector {-x_, -y_, -z_}; }

    double norm () const { return x_ * x_ + y_ * y_ + z_ * z_; }

    double module () const { return std::sqrt (norm ()); }

    Vector &normalize ()
    {
        operator*= (1 / module ());

        return *this;
    }

    bool is_zero () const
    {
        return (cmp::are_equal (x_, 0.0) && cmp::are_equal (y_, 0.0) && cmp::are_equal (z_, 0.0));
    }

    void print () const { std::cout << "(" << x_ << ", " << y_ << ", " << z_ << ")" << std::endl; }
};

inline Vector operator* (const Vector &vec, const double coeff)
{
    Vector product = vec;
    return (product *= coeff);
}

inline Vector operator* (const double coeff, const Vector &vec) { return vec * coeff; }

inline double scalar_product (const Vector &lhs, const Vector &rhs)
{
    auto xx = lhs.x_ * rhs.x_;
    auto yy = lhs.y_ * rhs.y_;
    auto zz = lhs.z_ * rhs.z_;

    auto tmp_product = cmp::are_equal (xx, -yy) ? 0.0 : xx + yy;
    auto product     = cmp::are_equal (tmp_product, -zz) ? 0.0 : tmp_product + zz;

    return product;
}

inline Vector vector_product (const Vector &lhs, const Vector &rhs)
{
    auto ly_rz     = lhs.y_ * rhs.z_;
    auto lz_ry     = lhs.z_ * rhs.y_;
    auto product_1 = cmp::are_equal (ly_rz, lz_ry) ? 0.0 : ly_rz - lz_ry;

    auto lz_rx     = lhs.z_ * rhs.x_;
    auto lx_rz     = lhs.x_ * rhs.z_;
    auto product_2 = cmp::are_equal (lz_rx, lx_rz) ? 0.0 : lz_rx - lx_rz;

    auto lx_ry     = lhs.x_ * rhs.y_;
    auto ly_rx     = lhs.y_ * rhs.x_;
    auto product_3 = cmp::are_equal (lx_ry, ly_rx) ? 0.0 : lx_ry - ly_rx;

    return Vector {product_1, product_2, product_3};
}

inline double triple_product (const Vector &first, const Vector &second, const Vector &third)
{
    return scalar_product (first, vector_product (second, third));
}

inline bool are_collinear (const Vector &first, const Vector &second)
{
    return vector_product (first, second).is_zero ();
}

inline bool are_coplanar (const Vector &first, const Vector &second, const Vector &third)
{
    return cmp::are_equal (triple_product (first, second, third), 0.0);
}

inline bool are_orthogonal (const Vector &first, const Vector &second)
{
    return cmp::are_equal (scalar_product (first, second), 0.0);
}

} // namespace Geom_Objects
