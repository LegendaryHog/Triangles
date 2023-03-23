#pragma once
#include "octo_tree.hpp"
#include <chrono>

namespace Task
{

template<std::floating_point F>
Geometry::IndexsContainer intersect_shapes(const std::vector<Geometry::Shape<F>>& shapes)
{
    Geometry::OctoTree<F> octo_tree(shapes.cbegin(), shapes.cend());
    const auto& indexs = octo_tree.find_all_intersections();
    
    return indexs;
}
} // namespace Task