#pragma once
#include "point.hpp"
#include "shape.hpp"

namespace Math
{

template<std::floating_point F>
std::pair<F, F> sort(F f1, F f2)
{
    if (f1 > f2)
        return {f2, f1};
    else
        return {f1, f2};
}

template<std::floating_point F>
std::pair<F, F> sort(F f1, F f2, F f3)
{
    auto [min, max] = sort(f1, f2);
    if (f3 < min)
        return {f3, max};
    else if (f3 > max)
        return {min, f3};
    else
        return {min, max};
}

} // namespace Math

namespace Geometry
{
template<std::floating_point Float>
class BoundingBox final
{
    using size_type = unsigned;
    const Shape<Float>* ptr_shape_ = nullptr;
    ShapeIndT shape_index_ = 0;

    Point<Float> center_ {};
    Float half_width_x_ = 0;
    Float half_width_y_ = 0;
    Float half_width_z_ = 0;

public:
    BoundingBox() = default;

    BoundingBox(const Shape<Float>* ptr_sh, ShapeIndT sh_ind, const Point<Float>& center,
    Float hx, Float hy, Float hz)
    :ptr_shape_ {ptr_sh}, shape_index_ {sh_ind}, center_ {center},
     half_width_x_ {hx}, half_width_y_ {hy}, half_width_z_ {hz}
    {}

    const Shape<Float>& shape() const {return *ptr_shape_;}
    size_type shape_index() const {return shape_index_;}
    const Point<Float>& center() const {return center_;}
    Float half_width_x() const {return half_width_x_;}
    Float half_width_y() const {return half_width_y_;}
    Float half_width_z() const {return half_width_z_;}
};

template<std::floating_point Float>
std::ostream& operator<<(std::ostream& out, const BoundingBox<Float>& obj)
{
    return (out << "ind: " << obj.shape_index() << ", " << obj.shape());
}

template<std::floating_point Float>
using Box = std::tuple<Point<Float>, Float, Float, Float>;

namespace detail
{
template<std::floating_point Float>
Box<Float> compute_box(const Point<Float>& p)
{
    return {p, Math::epsilon<Float>, Math::epsilon<Float>, Math::epsilon<Float>};
}

template<std::floating_point Float>
Box<Float> compute_box(const Segment<Float>& seg)
{
    return {(seg.F_ + seg.S_) * 0.5, std::abs(seg.F_.x_ - seg.S_.x_) * 0.5 + Math::epsilon<Float>,
    std::abs(seg.F_.y_ - seg.S_.y_) * 0.5 + Math::epsilon<Float>, std::abs(seg.F_.z_ - seg.S_.z_) * 0.5 + Math::epsilon<Float>};
}

template<std::floating_point Float>
Box<Float> compute_box(const Triangle<Float>& tr)
{
    auto [min_x, max_x] = Math::sort(tr.P_.x_, tr.Q_.x_, tr.R_.x_);
    auto [min_y, max_y] = Math::sort(tr.P_.y_, tr.Q_.y_, tr.R_.y_);
    auto [min_z, max_z] = Math::sort(tr.P_.z_, tr.Q_.z_, tr.R_.z_);

    return {{(min_x + max_x) * 0.5, (min_y + max_y) * 0.5, (min_z + max_z) * 0.5},
            (max_x - min_x) * 0.5 + Math::epsilon<Float>, (max_y - min_y) * 0.5 + Math::epsilon<Float>,
            (max_z - min_z) * 0.5 + Math::epsilon<Float>};
}

} // namespace detail

template<std::floating_point Float>
Box<Float> compute_box(const Shape<Float>& shape)
{
    return std::visit([](const auto& sh) -> Box<Float> {return detail::compute_box(sh);}, shape);
}

template<std::floating_point Float>
BoundingBox<Float> make_bound(const Shape<Float>& shape, ShapeIndT index)
{
    auto [center, half_width_x, half_width_y, half_width_z] = compute_box(shape);
    return BoundingBox<Float>{&shape, index, center, half_width_x, half_width_y, half_width_z};
}

template<std::floating_point Float>
bool are_intersecting(const BoundingBox<Float>& bound1, const BoundingBox<Float>& bound2)
{
    if (std::abs(bound1.center().x_ - bound2.center().x_) > bound1.half_width_x() + bound2.half_width_x())
        return false;

    if (std::abs(bound1.center().y_ - bound2.center().y_) > bound1.half_width_y() + bound2.half_width_y())
        return false;

    if (std::abs(bound1.center().z_ - bound2.center().z_) > bound1.half_width_z() + bound2.half_width_z())
        return false;
    
    return are_intersecting(bound1.shape(), bound2.shape());
}
} // namespace Geometry
