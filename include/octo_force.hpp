#pragma once
#include "octo_tree.hpp"

namespace Task
{

template<std::floating_point F>
Geometry::IndexesContainer intersect_shapes(const std::vector<Geometry::Shape<F>>& shapes)
{
    Geometry::OctoTree<F> octo_tree(shapes.cbegin(), shapes.cend());
    return octo_tree.find_all_intersections();
}
} // namespace Task