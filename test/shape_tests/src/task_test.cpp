#include <gtest/gtest.h>
#include "shape.hpp"

using namespace Geometry;

bool is_point(const Shape<double>& shape)
{
    if (std::get_if<Point<double>>(&shape))
        return true;
    else
        return false;
}

bool is_segment(const Shape<double>& shape)
{
    if (std::get_if<Segment<double>>(&shape))
        return true;
    else
        return false;
}

bool is_triangle(const Shape<double>& shape)
{
    if (std::get_if<Triangle<double>>(&shape))
        return true;
    else
        return false;
}

TEST(Task, test_is_obj)
{
    Shape<double> shape_p = Point{1.0, 2.0, 3.0};
    EXPECT_TRUE(is_point(shape_p));
    EXPECT_FALSE(is_segment(shape_p));
    EXPECT_FALSE(is_triangle(shape_p));

    Shape<double> shape_s = Segment{Point{1.0, 2.0, 3.0}, Point{3.0, 2.0, 1.0}};
    EXPECT_FALSE(is_point(shape_s));
    EXPECT_TRUE(is_segment(shape_s));
    EXPECT_FALSE(is_triangle(shape_s));

    Shape<double> shape_tr = Triangle{Point{1.0, 2.0, 3.0}, Point{3.0, 2.0, 1.0}, Point{0.0, 0.0, 0.0}};
    EXPECT_FALSE(is_point(shape_tr));
    EXPECT_FALSE(is_segment(shape_tr));
    EXPECT_TRUE(is_triangle(shape_tr));
}

TEST(Task, make_shape_point)
{
    Point A1 {1.0, 1.000000007, 1.0000000008}, A2 {1.0, 1.0, 1.0}, A3 {0.9999999998, 1.000000009, 1.000000006};
    Point origin {1.0, 1.0, 1.0};
    
    auto shape1 = make_shape(A1, A2, A3);
    auto shape2 = make_shape(A1, A3, A2);
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
    
    Point<double> shape_res1 {}, shape_res2 {}, shape_res3 {}, shape_res4 {}, shape_res5 {}, shape_res6 {};
    EXPECT_NO_THROW(shape_res1 = std::get<Point<double>>(shape1));
    EXPECT_NO_THROW(shape_res2 = std::get<Point<double>>(shape2));
    EXPECT_NO_THROW(shape_res3 = std::get<Point<double>>(shape3));
    EXPECT_NO_THROW(shape_res4 = std::get<Point<double>>(shape4));
    EXPECT_NO_THROW(shape_res5 = std::get<Point<double>>(shape5));
    EXPECT_NO_THROW(shape_res6 = std::get<Point<double>>(shape6));

    EXPECT_EQ(shape_res1, origin);
    EXPECT_EQ(shape_res2, origin);
    EXPECT_EQ(shape_res3, origin);
    EXPECT_EQ(shape_res4, origin);
    EXPECT_EQ(shape_res5, origin);
    EXPECT_EQ(shape_res6, origin);
}

TEST(Task, make_shape_segment)
{
    Point A1 {1.0, 1.0}, A2 {6.0, 6.0}, A3 {12.0, 12.0};
    Segment origin {A1, A3};
    
    auto shape1 = make_shape(A1, A2, A3);
    auto shape2 = make_shape(A1, A3, A2);
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
    
    Segment<double> shape_res1 {}, shape_res2 {}, shape_res3 {}, shape_res4 {}, shape_res5 {}, shape_res6 {};
    EXPECT_NO_THROW(shape_res1 = std::get<Segment<double>>(shape1));
    EXPECT_NO_THROW(shape_res2 = std::get<Segment<double>>(shape2));
    EXPECT_NO_THROW(shape_res3 = std::get<Segment<double>>(shape3));
    EXPECT_NO_THROW(shape_res4 = std::get<Segment<double>>(shape4));
    EXPECT_NO_THROW(shape_res5 = std::get<Segment<double>>(shape5));
    EXPECT_NO_THROW(shape_res6 = std::get<Segment<double>>(shape6));

    EXPECT_EQ(shape_res1, origin);
    EXPECT_EQ(shape_res2, origin);
    EXPECT_EQ(shape_res3, origin);
    EXPECT_EQ(shape_res4, origin);
    EXPECT_EQ(shape_res5, origin);
    EXPECT_EQ(shape_res6, origin);

    Point C1 {47.0020025995995, 12.31053506688523, 16.152460708286874};
    Point C2 {47.00207827133622, 12.885672173487198, 24.10804409365877};
    Point C3 {47.00204043546786, 12.598103620186214, 20.13025240097282};

    Point B1 {34.01277621741285, 13.885420399738456, 9.127259440689663};
    Point B2 {47.693609448366374, 3.0528520775851318, 25.362178038371134};
    Point B3 {40.85319283288961, 8.469136238661793, 17.2447187395304};

    auto shapeC = make_shape(C1, C2, C3);
    auto shapeB = make_shape(B1, B2, B3);

    Segment C1C3 {C1, C2}, B1B3 {B1, B2};
    EXPECT_TRUE(is_segment(shapeC));
    EXPECT_FALSE(is_triangle(shapeC));
    EXPECT_TRUE(is_segment(shapeB));

    Segment<double> shapeC_res {}, shapeB_res {};
    EXPECT_NO_THROW(shapeC_res = std::get<Segment<double>>(shapeC));
    EXPECT_NO_THROW(shapeB_res = std::get<Segment<double>>(shapeB));

    EXPECT_EQ(shapeC_res, C1C3);
    EXPECT_EQ(shapeB_res, B1B3);
}

TEST(Task, make_shape_segment_epsilon)
{
    Point A1 {1.0, 1.0}, A2 {6.0000000021, 5.999999996, -0.0000000001}, A3 {12.0, 12.0};
    Segment origin {A1, A3};
    
    auto shape1 = make_shape(A1, A2, A3);
    auto shape2 = make_shape(A1, A3, A2);
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
    
    Segment<double> shape_res1 {}, shape_res2 {}, shape_res3 {}, shape_res4 {}, shape_res5 {}, shape_res6 {};
    EXPECT_NO_THROW(shape_res1 = std::get<Segment<double>>(shape1));
    EXPECT_NO_THROW(shape_res2 = std::get<Segment<double>>(shape2));
    EXPECT_NO_THROW(shape_res3 = std::get<Segment<double>>(shape3));
    EXPECT_NO_THROW(shape_res4 = std::get<Segment<double>>(shape4));
    EXPECT_NO_THROW(shape_res5 = std::get<Segment<double>>(shape5));
    EXPECT_NO_THROW(shape_res6 = std::get<Segment<double>>(shape6));

    EXPECT_EQ(shape_res1, origin);
    EXPECT_EQ(shape_res2, origin);
    EXPECT_EQ(shape_res3, origin);
    EXPECT_EQ(shape_res4, origin);
    EXPECT_EQ(shape_res5, origin);
    EXPECT_EQ(shape_res6, origin);
}

TEST(Task, make_shape_triangle)
{
    Point A1 {1.0, 1.0}, A2 {6.0000000021, 5.999999996, -0.0000000001}, A3 {2.0, 2.0, -1.0};
    
    auto shape1 = make_shape(A1, A2, A3);
    auto shape2 = make_shape(A1, A3, A2);
    auto shape3 = make_shape(A2, A1, A3);
    auto shape4 = make_shape(A2, A3, A1);
    auto shape5 = make_shape(A3, A1, A2);
    auto shape6 = make_shape(A3, A2, A1);

    EXPECT_TRUE(is_triangle(shape1));
    EXPECT_TRUE(is_triangle(shape2));
    EXPECT_TRUE(is_triangle(shape3));
    EXPECT_TRUE(is_triangle(shape4));
    EXPECT_TRUE(is_triangle(shape5));
    EXPECT_TRUE(is_triangle(shape6));
    
    Triangle<double> shape_res1 {}, shape_res2 {}, shape_res3 {}, shape_res4 {}, shape_res5 {}, shape_res6 {};
    EXPECT_NO_THROW(shape_res1 = std::get<Triangle<double>>(shape1));
    EXPECT_NO_THROW(shape_res2 = std::get<Triangle<double>>(shape2));
    EXPECT_NO_THROW(shape_res3 = std::get<Triangle<double>>(shape3));
    EXPECT_NO_THROW(shape_res4 = std::get<Triangle<double>>(shape4));
    EXPECT_NO_THROW(shape_res5 = std::get<Triangle<double>>(shape5));
    EXPECT_NO_THROW(shape_res6 = std::get<Triangle<double>>(shape6));
}