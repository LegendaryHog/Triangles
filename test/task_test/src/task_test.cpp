#include <gtest/gtest.h>
#include "task.hpp"

using namespace Task;

TEST(Task, make_shape)
{
    auto is_point = [](const Shape<double>& shape)
    {
        if (std::get_if<Geometry::Point<double>>(&shape))
            return true;
        else
            return false;
    };

    auto is_segment = [](const Shape<double>& shape)
    {
        if (std::get_if<Geometry::Segment<double>>(&shape))
            return true;
        else
            return false;
    };

    auto is_triangle = [](const Shape<double>& shape)
    {
        if (std::get_if<Geometry::Triangle<double>>(&shape))
            return true;
        else
            return false;
    };

    Shape<double> shape1 = Geometry::Point<double>{1.0, 2.0, 3.0};
    EXPECT_TRUE(is_point(shape1));
}