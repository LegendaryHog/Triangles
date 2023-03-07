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

enum ShapeType
{
    IsPoint    = 0,
    IsSegment  = 1,
    IsTriangle = 2,
};

template<std::floating_point F>
using Shape = std::pair<ShapeType, std::variant<Geometry::Point<F>, Geometry::Segment<F>, Geometry::Triangle<F>>>;

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
    Geometry::Vector<F> p1p2 {p1, p2}, p1p3 {p1, p3};

    if (Geometry::are_collinear(p1p2, p1p3))
    {   
        auto prod = Geometry::scalar_product(p1p2, p1p3);
        if (Compare::are_equal(prod, 0.0))
            if (p1p2.is_zero())
                if (p1p3.is_zero())
                    return std::make_pair(ShapeType::IsPoint, p1);
                else
                    return std::make_pair(ShapeType::IsSegment, Geometry::Segment{p1, p3});
            else
                return std::make_pair(ShapeType::IsSegment, Geometry::Segment{p1, p2});
        else if (prod < 0)
            return std::make_pair(ShapeType::IsSegment, Geometry::Segment{p2, p3});
        else if (p1p2.module() > p1p3.module())
            return std::make_pair(ShapeType::IsSegment, Geometry::Segment{p1, p2});
        else
            return std::make_pair(ShapeType::IsSegment, Geometry::Segment{p1, p3});
    }
    else
        return std::make_pair(ShapeType::IsTriangle, Geometry::Triangle{p1, p2, p3});
}

template<std::floating_point F>
Shape<F> scan_shape()
{
    Geometry::Point<F> p1 = scan_point<F>(), p2 = scan_point<F>(), p3 = scan_point<F>();
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
    for (std::size_t i = 0; i < size - 1; i++)
        for (std::size_t j = i + 1; j < size; j++)
            if (std::visit([](const auto& obj1, const auto& obj2) {return Geometry::are_intersecting(obj1, obj2);},
            shapes[i].second, shapes[j].second))
            {
                indexs.insert(i);
                indexs.insert(j);
            }
    
    for (auto index: indexs)
        std::cout << index << ' ';
    std::cout << std::endl;
}
} // namespace Task