#pragma once
#include <iostream>
#include <unordered_set>
#include "shape.hpp"

namespace Task
{

template<std::floating_point F>
std::unordered_set<std::size_t> intersect_shapes(const std::vector<Geometry::Shape<F>>& shapes)
{
    std::unordered_set<std::size_t> indexs {};
    auto size = shapes.size();
    for (std::size_t i = 0; i < size - 1; i++)
        for (std::size_t j = i + 1; j < size; j++)
            if (Geometry::are_intersecting(shapes[i], shapes[j]))
                indexs.insert({i, j});
    return indexs;
}
} // namespace Task