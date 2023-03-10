#pragma once
#include <utility>
#include <variant>
#include <concepts>
#include <vector>
#include <iostream>
#include <unordered_set>
#include "point.hpp"
#include "segment.hpp"
#include "triangle.hpp"
#include "intersection.hpp"

namespace Task
{

template<std::floating_point F>
using Shape = std::variant<Geometry::Point<F>, Geometry::Segment<F>, Geometry::Triangle<F>>;

template<std::floating_point F>
Geometry::Point<F> scan_point()
{
    Geometry::Point<F> point {};
    std::cin >> point.x_ >> point.y_ >> point.z_;
    return point;
}

template<std::floating_point F>
Shape<F> make_shape(Geometry::Point<F> p1, Geometry::Point<F> p2, Geometry::Point<F> p3)
{
    Geometry::Vector p1p2 {p1, p2}, p1p3 {p1, p3};

    if (Geometry::are_collinear(p1p2, p1p3))
    {   
        auto prod = Geometry::scalar_product(p1p2, p1p3);
        if (Compare::are_equal(prod, 0.0))
            if (p1p2.is_zero())
                if (p1p3.is_zero())
                    return p1;
                else
                    return Geometry::Segment{p1, p3};
            else
                return Geometry::Segment{p1, p2};
        else if (prod < 0.0)
            return Geometry::Segment{p2, p3};
        else if (p1p2.module() > p1p3.module())
            return Geometry::Segment{p1, p2};
        else
            return Geometry::Segment{p1, p3};
    }
    else
        return Geometry::Triangle{p1, p2, p3};
}

template<std::floating_point F>
Shape<F> scan_shape()
{
    Geometry::Point p1 = scan_point<F>(), p2 = scan_point<F>(), p3 = scan_point<F>();
    return make_shape(p1, p2, p3);
}

template<std::floating_point F>
std::vector<Shape<F>> scan_shapes()
{
    std::size_t num_of_shapes = 0;
    std::cin >> num_of_shapes;

    std::vector<Shape<F>> shapes {};
    shapes.reserve(num_of_shapes);

    for (std::size_t i = 0; i < num_of_shapes; i++)
        shapes.push_back(scan_shape<F>());

    return shapes;
}

template<std::floating_point F>
void intersect_shapes(const std::vector<Shape<F>>& shapes)
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