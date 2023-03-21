#pragma once
#include "octo_tree.hpp"
#include <chrono>

namespace Task
{

namespace detail
{

template<std::floating_point F>
std::pair<Geometry::Point<F>, Geometry::Point<F>>
calc_bounding_box(const Geometry::Point<F>& p)
{
    return {{p.x_ - Math::epsilon<F>, p.y_ - Math::epsilon<F>, p.z_ - Math::epsilon<F>},
            {p.x_ + Math::epsilon<F>, p.y_ + Math::epsilon<F>, p.z_ + Math::epsilon<F>}};
}

template<std::floating_point F>
std::pair<Geometry::Point<F>, Geometry::Point<F>>
calc_bounding_box(const Geometry::Segment<F>& seg)
{
    auto [min_x, max_x] = Math::sort(seg.F_.x_, seg.S_.x_);
    auto [min_y, max_y] = Math::sort(seg.F_.y_, seg.S_.y_);
    auto [min_z, max_z] = Math::sort(seg.F_.z_, seg.S_.z_);

    return {{min_x - Math::epsilon<F>, min_y - Math::epsilon<F>, min_z - Math::epsilon<F>},
            {max_x + Math::epsilon<F>, max_y + Math::epsilon<F>, max_z + Math::epsilon<F>}};
}

template<std::floating_point F>
std::pair<Geometry::Point<F>, Geometry::Point<F>>
calc_bounding_box(const Geometry::Triangle<F>& tr)
{
    auto [min_x, max_x] = Math::sort(tr.P_.x_, tr.Q_.x_, tr.R_.x_);
    auto [min_y, max_y] = Math::sort(tr.P_.y_, tr.Q_.y_, tr.R_.y_);
    auto [min_z, max_z] = Math::sort(tr.P_.z_, tr.Q_.z_, tr.R_.z_);

    return {{min_x - Math::epsilon<F>, min_y - Math::epsilon<F>, min_z - Math::epsilon<F>},
            {max_x + Math::epsilon<F>, max_y + Math::epsilon<F>, max_z + Math::epsilon<F>}};
}

} // namespace detail

template<std::floating_point F>
std::pair<Geometry::Point<F>, Geometry::Point<F>>
calc_bounding_box(const Geometry::Shape<F>& shape)
{
    return std::visit([](const auto& sh) {return detail::calc_bounding_box(sh);}, shape);
}

template<std::floating_point F>
std::pair<Geometry::Point<F>, F>
calc_center_half_width(const std::vector<Geometry::Shape<F>>& shapes)
{
    auto [lowest_point, greatest_point] = calc_bounding_box(shapes.front());

    for (auto itr = shapes.begin() + 1, end = shapes.end(); itr != end; ++itr)
    {
        auto [p1, p2] = calc_bounding_box(*itr);
        
        if (p1.x_ < lowest_point.x_) lowest_point.x_ = p1.x_;
        if (p1.y_ < lowest_point.y_) lowest_point.y_ = p1.y_;
        if (p1.z_ < lowest_point.z_) lowest_point.z_ = p1.z_;

        if (p2.x_ > greatest_point.x_) greatest_point.x_ = p2.x_;
        if (p2.y_ > greatest_point.y_) greatest_point.y_ = p2.y_;
        if (p2.z_ > greatest_point.z_) greatest_point.z_ = p2.z_;
    }

    auto center = (lowest_point + greatest_point) * 0.5;
    
    auto half_width_vec = greatest_point - center;
    
    const auto& half_width_x =  half_width_vec.x_;
    const auto& half_width_y =  half_width_vec.y_;
    const auto& half_width_z =  half_width_vec.z_;

    return {center, std::max(half_width_x, std::max(half_width_y, half_width_z))};
}

template<std::floating_point F>
Geometry::IndexsContainer intersect_shapes(const std::vector<Geometry::Shape<F>>& shapes)
{
    auto depth = static_cast<std::size_t>(log2(static_cast<double>(shapes.size())) / 3 + 1);

#ifdef TIME
    auto start = std::chrono::steady_clock::now();
#endif

    const auto& [center, half_width] = calc_center_half_width(shapes);

#ifdef TIME
    auto end = std::chrono::steady_clock::now();
    std::cout << "time on calc: " << static_cast<std::chrono::duration<double>>(end - start).count() << std::endl;
#endif

#ifdef TIME
    start = std::chrono::steady_clock::now();
#endif

    OctoTree<F> octo_tree (center, half_width, depth);

#ifdef TIME
    end = std::chrono::steady_clock::now();
    std::cout << "time on construct: " << static_cast<std::chrono::duration<double>>(end - start).count() << std::endl;
#endif

#ifdef TIME
    start = std::chrono::steady_clock::now();
#endif

    octo_tree.insert(shapes.cbegin(), shapes.cend());

#ifdef TIME
    end = std::chrono::steady_clock::now();
    std::cout << "time on insert: " << static_cast<std::chrono::duration<double>>(end - start).count() << std::endl;
#endif

#ifdef TIME
    start = std::chrono::steady_clock::now();
#endif

    const auto& indexs = octo_tree.intersect_all();
    
#ifdef TIME
    end = std::chrono::steady_clock::now();
    std::cout << "time on intersection: " << static_cast<std::chrono::duration<double>>(end - start).count() << std::endl;
#endif
    
    return indexs;
}
} // namespace Task