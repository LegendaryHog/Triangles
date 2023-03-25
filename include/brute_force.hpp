#pragma once
#include <iostream>
#include "shape.hpp"

namespace Task
{

template<std::floating_point F>
Geometry::IndexesContainer intersect_shapes(const std::vector<Geometry::Shape<F>>& shapes)
{
    Geometry::IndexesContainer indexes {};
    auto size = shapes.size();
    for (std::size_t i = 0; i < size - 1; i++)
        for (std::size_t j = i + 1; j < size; j++)
            if (Geometry::are_intersecting(shapes[i], shapes[j]))
                indexes.insert({i, j});
    return indexes;
}
} // namespace Task