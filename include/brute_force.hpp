#pragma once
#include <utility>
#include <variant>
#include <concepts>
#include <vector>
#include <iostream>
#include <unordered_set>
#include "shape.hpp"
#include "intersection.hpp"

namespace Task
{

template<std::floating_point F>
std::vector<Geometry::Shape<F>> scan_shapes()
{
    std::size_t num_of_shapes = 0;
    std::cin >> num_of_shapes;

    std::vector<Geometry::Shape<F>> shapes {};
    shapes.reserve(num_of_shapes);

    for (std::size_t i = 0; i < num_of_shapes; i++)
        shapes.push_back(Geometry::scan_shape<F>());

    return shapes;
}

template<std::floating_point F>
void intersect_shapes(const std::vector<Geometry::Shape<F>>& shapes)
{
    std::unordered_set<int> indexs {};
    auto size = shapes.size();
    for (int i = 0; i < size - 1; i++)
        for (int j = i + 1; j < size; j++)
            if (std::visit([](const auto& obj1, const auto& obj2) {return Geometry::are_intersecting(obj1, obj2);},
            shapes[i], shapes[j]))
                indexs.insert({i, j});
    
    for (auto index: indexs)
        std::cout << index << ' ';
    std::cout << std::endl;
}
} // namespace Task