#pragma once
#include <variant>
#include <vector>
#include "point.hpp"
#include "segment.hpp"
#include "triangle.hpp"
#include "vector.hpp"
#include "intersection.hpp"

namespace Geometry
{

template<std::floating_point F>
using Shape = std::variant<Geometry::Point<F>, Geometry::Segment<F>, Geometry::Triangle<F>>;

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
        shapes.push_back(Geometry::scan_shape<F>());

    return shapes;
}


template<std::floating_point F>
bool are_intersecting(const Shape<F>& shape1, const Shape<F>& shape2)
{
    return std::visit([](const auto& sh1, const auto& sh2) -> bool {return Geometry::are_intersecting(sh1, sh2);},
           shape1, shape2);
}

} // namespace Geoemtry
