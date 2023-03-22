#pragma once
#include "octo_tree.hpp"
#include <chrono>

namespace Task
{

template<std::floating_point F>
std::pair<Geometry::Point<F>, F> 
compute_space_box(const std::vector<Geometry::Shape<F>>& shapes)
{
    auto [center_box, hw_box_x, hw_box_y, hw_box_z] = Geometry::compute_box(shapes.front());
    auto min_x = center_box.x_ - hw_box_x, max_x = center_box.x_ + hw_box_x;
    auto min_y = center_box.y_ - hw_box_y, max_y = center_box.y_ + hw_box_y;
    auto min_z = center_box.z_ - hw_box_z, max_z = center_box.z_ + hw_box_z;

    for (auto itr = shapes.begin() + 1, end = shapes.end(); itr != end; ++itr)
    {
        auto [center, hw_x, hw_y, hw_z] = Geometry::compute_box(*itr);
        const auto& act_min_x = center.x_ - hw_x, act_max_x = center.x_ + hw_x;
        const auto& act_min_y = center.y_ - hw_y, act_max_y = center.y_ + hw_y;
        const auto& act_min_z = center.z_ - hw_z, act_max_z = center.z_ + hw_z;
        
        if (act_min_x < min_x) min_x = act_min_x;
        if (act_min_y < min_y) min_y = act_min_y;
        if (act_min_z < min_z) min_z = act_min_z;

        if (act_max_x > max_x) max_x = act_max_x;
        if (act_max_y > max_y) max_y = act_max_y;
        if (act_max_z > max_z) max_z = act_max_z;
    }

    return {Geometry::Point{(max_x + min_x) * 0.5, (max_y + min_y) * 0.5, (max_z + min_z) * 0.5},
            std::max({max_x - min_x, max_y - min_y, max_z - min_z}) * 0.5};
}

//#define TIME
template<std::floating_point F>
Geometry::IndexsContainer intersect_shapes(const std::vector<Geometry::Shape<F>>& shapes)
{
    auto depth = static_cast<std::size_t>(log2(static_cast<double>(shapes.size())) / 3 + 1);

#ifdef TIME
    auto start = std::chrono::steady_clock::now();
#endif

    const auto& [center, half_width] = compute_space_box(shapes);

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