#include <gtest/gtest.h>
#include "task.hpp"

using namespace Task;

bool is_point(const Shape<double>& shape)
{
    if (std::get_if<Geometry::Point<double>>(&shape))
        return true;
    else
        return false;
}

bool is_segment(const Shape<double>& shape)
{
    if (std::get_if<Geometry::Segment<double>>(&shape))
        return true;
    else
        return false;
}

bool is_triangle(const Shape<double>& shape)
{
    if (std::get_if<Geometry::Triangle<double>>(&shape))
        return true;
    else
        return false;
}

TEST(Task, test_is_obj)
{
    Shape<double> shape_p = Geometry::Point{1.0, 2.0, 3.0};
    EXPECT_TRUE(is_point(shape_p));
    EXPECT_FALSE(is_segment(shape_p));
    EXPECT_FALSE(is_triangle(shape_p));

    Shape<double> shape_s = Geometry::Segment{Geometry::Point{1.0, 2.0, 3.0}, Geometry::Point{3.0, 2.0, 1.0}};
    EXPECT_FALSE(is_point(shape_s));
    EXPECT_TRUE(is_segment(shape_s));
    EXPECT_FALSE(is_triangle(shape_s));

    Shape<double> shape_tr = Geometry::Triangle{Geometry::Point{1.0, 2.0, 3.0}, Geometry::Point{3.0, 2.0, 1.0}, Geometry::Point{0.0, 0.0, 0.0}};
    EXPECT_FALSE(is_point(shape_tr));
    EXPECT_FALSE(is_segment(shape_tr));
    EXPECT_TRUE(is_triangle(shape_tr));

    Geometry::Point A4 {1.0, 1.0}, A5 {6.0, 6.0}, A6 {2.0, 2.0};
    Geometry::Point A7 {0.9999999999987, 1.000000004, -0.000000003};
}

TEST(Task, make_shape_point)
{
    Geometry::Point A1 {1.0, 1.000000007, 1.0000000008}, A2 {1.0, 1.0, 1.0}, A3 {0.9999999998, 1.000000009, 1.000000006};
    Geometry::Point origin {1.0, 1.0, 1.0};
    
    auto shape1 = make_shape(A1, A2, A3);
    auto shape2 = make_shape(A1, A3, A3);
    auto shape3 = make_shape(A2, A1, A3);
    auto shape4 = make_shape(A2, A3, A1);
    auto shape5 = make_shape(A3, A1, A2);
    auto shape6 = make_shape(A3, A2, A1);

    EXPECT_TRUE(is_point(shape1));
    EXPECT_TRUE(is_point(shape2));
    EXPECT_TRUE(is_point(shape3));
    EXPECT_TRUE(is_point(shape4));
    EXPECT_TRUE(is_point(shape5));
    EXPECT_TRUE(is_point(shape6));
    
    Geometry::Point<double> shape_res1 {}, shape_res2 {}, shape_res3 {}, shape_res4 {}, shape_res5 {}, shape_res6 {};
    EXPECT_NO_THROW(shape_res1 = std::get<Geometry::Point<double>>(shape1));
    EXPECT_NO_THROW(shape_res2 = std::get<Geometry::Point<double>>(shape2));
    EXPECT_NO_THROW(shape_res3 = std::get<Geometry::Point<double>>(shape3));
    EXPECT_NO_THROW(shape_res4 = std::get<Geometry::Point<double>>(shape4));
    EXPECT_NO_THROW(shape_res5 = std::get<Geometry::Point<double>>(shape5));
    EXPECT_NO_THROW(shape_res6 = std::get<Geometry::Point<double>>(shape6));

    EXPECT_EQ(shape_res1, origin);
    EXPECT_EQ(shape_res2, origin);
    EXPECT_EQ(shape_res3, origin);
    EXPECT_EQ(shape_res4, origin);
    EXPECT_EQ(shape_res5, origin);
    EXPECT_EQ(shape_res6, origin);
}

TEST(Task, make_shape_segment)
{
    Geometry::Point A1 {1.0, 1.0}, A2 {6.0, 6.0}, A3 {12.0, 12.0};
    Geometry::Segment origin {A1, A3};
    
    auto shape1 = make_shape(A1, A2, A3);
    auto shape2 = make_shape(A1, A3, A3);
    auto shape3 = make_shape(A2, A1, A3);
    auto shape4 = make_shape(A2, A3, A1);
    auto shape5 = make_shape(A3, A1, A2);
    auto shape6 = make_shape(A3, A2, A1);

    EXPECT_TRUE(is_segment(shape1));
    EXPECT_TRUE(is_segment(shape2));
    EXPECT_TRUE(is_segment(shape3));
    EXPECT_TRUE(is_segment(shape4));
    EXPECT_TRUE(is_segment(shape5));
    EXPECT_TRUE(is_segment(shape6));
    
    Geometry::Segment<double> shape_res1 {}, shape_res2 {}, shape_res3 {}, shape_res4 {}, shape_res5 {}, shape_res6 {};
    EXPECT_NO_THROW(shape_res1 = std::get<Geometry::Segment<double>>(shape1));
    EXPECT_NO_THROW(shape_res2 = std::get<Geometry::Segment<double>>(shape2));
    EXPECT_NO_THROW(shape_res3 = std::get<Geometry::Segment<double>>(shape3));
    EXPECT_NO_THROW(shape_res4 = std::get<Geometry::Segment<double>>(shape4));
    EXPECT_NO_THROW(shape_res5 = std::get<Geometry::Segment<double>>(shape5));
    EXPECT_NO_THROW(shape_res6 = std::get<Geometry::Segment<double>>(shape6));

    EXPECT_EQ(shape_res1, origin);
    EXPECT_EQ(shape_res2, origin);
    EXPECT_EQ(shape_res3, origin);
    EXPECT_EQ(shape_res4, origin);
    EXPECT_EQ(shape_res5, origin);
    EXPECT_EQ(shape_res6, origin);
}

TEST(Task, make_shape_segment_epsilon)
{
    Geometry::Point A1 {1.0, 1.0}, A2 {6.0000000021, 5.999999996, -0.0000000001}, A3 {12.0, 12.0};
    Geometry::Segment origin {A1, A3};
    
    auto shape1 = make_shape(A1, A2, A3);
    auto shape2 = make_shape(A1, A3, A3);
    auto shape3 = make_shape(A2, A1, A3);
    auto shape4 = make_shape(A2, A3, A1);
    auto shape5 = make_shape(A3, A1, A2);
    auto shape6 = make_shape(A3, A2, A1);

    EXPECT_TRUE(is_segment(shape1));
    EXPECT_TRUE(is_segment(shape2));
    EXPECT_TRUE(is_segment(shape3));
    EXPECT_TRUE(is_segment(shape4));
    EXPECT_TRUE(is_segment(shape5));
    EXPECT_TRUE(is_segment(shape6));
    
    Geometry::Segment<double> shape_res1 {}, shape_res2 {}, shape_res3 {}, shape_res4 {}, shape_res5 {}, shape_res6 {};
    EXPECT_NO_THROW(shape_res1 = std::get<Geometry::Segment<double>>(shape1));
    EXPECT_NO_THROW(shape_res2 = std::get<Geometry::Segment<double>>(shape2));
    EXPECT_NO_THROW(shape_res3 = std::get<Geometry::Segment<double>>(shape3));
    EXPECT_NO_THROW(shape_res4 = std::get<Geometry::Segment<double>>(shape4));
    EXPECT_NO_THROW(shape_res5 = std::get<Geometry::Segment<double>>(shape5));
    EXPECT_NO_THROW(shape_res6 = std::get<Geometry::Segment<double>>(shape6));

    EXPECT_EQ(shape_res1, origin);
    EXPECT_EQ(shape_res2, origin);
    EXPECT_EQ(shape_res3, origin);
    EXPECT_EQ(shape_res4, origin);
    EXPECT_EQ(shape_res5, origin);
    EXPECT_EQ(shape_res6, origin);
}

TEST(Task, make_shape_triangle)
{
    Geometry::Point A1 {1.0, 1.0}, A2 {6.0000000021, 5.999999996, -0.0000000001}, A3 {0.0, 0.0};
    Geometry::Segment origin {A1, A3};
    
    auto shape1 = make_shape(A1, A2, A3);
    auto shape2 = make_shape(A1, A3, A3);
    auto shape3 = make_shape(A2, A1, A3);
    auto shape4 = make_shape(A2, A3, A1);
    auto shape5 = make_shape(A3, A1, A2);
    auto shape6 = make_shape(A3, A2, A1);

    EXPECT_TRUE(is_segment(shape1));
    EXPECT_TRUE(is_segment(shape2));
    EXPECT_TRUE(is_segment(shape3));
    EXPECT_TRUE(is_segment(shape4));
    EXPECT_TRUE(is_segment(shape5));
    EXPECT_TRUE(is_segment(shape6));
    
    Geometry::Segment<double> shape_res1 {}, shape_res2 {}, shape_res3 {}, shape_res4 {}, shape_res5 {}, shape_res6 {};
    EXPECT_NO_THROW(shape_res1 = std::get<Geometry::Segment<double>>(shape1));
    EXPECT_NO_THROW(shape_res2 = std::get<Geometry::Segment<double>>(shape2));
    EXPECT_NO_THROW(shape_res3 = std::get<Geometry::Segment<double>>(shape3));
    EXPECT_NO_THROW(shape_res4 = std::get<Geometry::Segment<double>>(shape4));
    EXPECT_NO_THROW(shape_res5 = std::get<Geometry::Segment<double>>(shape5));
    EXPECT_NO_THROW(shape_res6 = std::get<Geometry::Segment<double>>(shape6));
}