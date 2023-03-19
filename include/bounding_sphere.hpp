#pragma once
#include "point.hpp"
#include "shape.hpp"

namespace Task
{
template<std::floating_point Float>
struct BoundingSphere
{
    Geometry::Shape<Float> shape_ {};
    std::size_t shape_index_ = 0;
    Geometry::Point<Float> center_ {};
    Float radius_ = 0;

    const Geometry::Shape<Float>& shape()  const {return shape_;}
    std::size_t shape_index() const {return shape_index_;}
    const Geometry::Point<Float>& center() const {return center_;}
    Float radius() const {return radius_;}
};

template<std::floating_point Float>
std::ostream& operator<<(std::ostream& out, const BoundingSphere<Float>& obj)
{
    return std::visit([&](const auto& sh) -> std::ostream& {return (out << "ind: " << obj.shape_index() << ", " << sh);}, obj.shape_);
}

namespace detail
{

template<std::floating_point F>
constexpr F epsilon = 1e-6;


template<std::floating_point Float>
BoundingSphere<Float> make_bound(const Geometry::Point<Float>& p, std::size_t index)
{
    return {p, index, p, epsilon<Float>};
}

template<std::floating_point Float>
BoundingSphere<Float> make_bound(const Geometry::Segment<Float>& seg, std::size_t index)
{
    return {seg, index, (seg.F_ + seg.S_) * 0.5, Geometry::distance(seg.F_, seg.S_) * 0.5 + epsilon<Float>};
}

template<std::floating_point Float>
BoundingSphere<Float> make_bound(const Geometry::Triangle<Float>& tr, std::size_t index)
{
    auto PQ = Geometry::distance(tr.P_, tr.Q_);
    auto QR = Geometry::distance(tr.Q_, tr.R_);
    auto RP = Geometry::distance(tr.R_, tr.P_);

    if (PQ > QR)
        if (PQ > RP)
            return {tr, index, tr.R_, std::max(QR, RP) + epsilon<Float>};
        else
            return {tr, index, tr.Q_, std::max(PQ, QR) + epsilon<Float>};
    else
        if (QR > RP)
            return {tr, index, tr.P_, std::max(RP, PQ) + epsilon<Float>};
        else
            return {tr, index, tr.Q_, std::max(PQ, QR) + epsilon<Float>};
}

} // namespace detail

template<std::floating_point Float>
BoundingSphere<Float> make_bound(const Geometry::Shape<Float>& shape, std::size_t index)
{
    return std::visit([index](const auto& sh){return detail::make_bound(sh, index);}, shape);
}

} // namespace Task
