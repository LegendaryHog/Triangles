#pragma once
#include "point.hpp"
#include "shape.hpp"

namespace Geometry
{
template<std::floating_point Float>
class BoundingSphere final
{
    const Shape<Float>* ptr_shape_ = nullptr;
    std::size_t  shape_index_ = 0;
    Point<Float> center_ {};
    Float        radius_ = 0;

public:
    BoundingSphere() = default;

    BoundingSphere(const Shape<Float>* ptr_sh, std::size_t sh_ind, const Point<Float>& center, Float rad)
    :ptr_shape_ {ptr_sh}, shape_index_ {sh_ind}, center_ {center}, radius_ {rad}
    {}

    const Shape<Float>& shape()  const {return *ptr_shape_;}
    std::size_t shape_index()    const {return shape_index_;}
    const Point<Float>& center() const {return center_;}
    Float radius() const {return radius_;}
};

template<std::floating_point Float>
std::ostream& operator<<(std::ostream& out, const BoundingSphere<Float>& obj)
{
    return std::visit([&](const auto& sh) -> std::ostream& {return (out << "ind: " << obj.shape_index() << ", " << sh);}, obj.shape());
}

namespace detail
{

template<std::floating_point Float>
using Sphere = std::pair<Point<Float>, Float>;

template<std::floating_point Float>
Sphere<Float> compute_sphere(const Point<Float>& p)
{
    return {p, Math::epsilon<Float>};
}

template<std::floating_point Float>
Sphere<Float> compute_sphere(const Segment<Float>& seg)
{
    return {(seg.F_ + seg.S_) * 0.5, Geometry::distance(seg.F_, seg.S_) * 0.5 + Math::epsilon<Float>};
}

template<std::floating_point Float>
Sphere<Float> compute_sphere(const Triangle<Float>& tr)
{
    auto PQ = Geometry::distance(tr.P_, tr.Q_);
    auto QR = Geometry::distance(tr.Q_, tr.R_);
    auto RP = Geometry::distance(tr.R_, tr.P_);

    if (PQ > QR)
        if (PQ > RP)
            return {tr.R_, std::max(QR, RP) + Math::epsilon<Float>};
        else
            return {tr.Q_, std::max(PQ, QR) + Math::epsilon<Float>};
    else
        if (QR > RP)
            return {tr.P_, std::max(RP, PQ) + Math::epsilon<Float>};
        else
            return {tr.Q_, std::max(PQ, QR) + Math::epsilon<Float>};
}

} // namespace detail

template<std::floating_point Float>
BoundingSphere<Float> make_bound(const Shape<Float>& shape, std::size_t index)
{
    auto [center, radius] = std::visit([](const auto& sh) -> detail::Sphere<Float> {return detail::compute_sphere(sh);}, shape);
    return BoundingSphere<Float>{&shape, index, center, radius};
}

} // namespace Geometry
