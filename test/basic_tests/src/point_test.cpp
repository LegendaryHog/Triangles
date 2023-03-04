#include "double_comparison.hpp"
#include "point.hpp"

#include <cmath> // for NAN
#include <gtest/gtest.h>

using namespace Geometry;

TEST (Points, Equality)
{
    Point pt_1 {1.0, 2.0, 3.0};
    Point pt_2 {2.0, 3.0, 4.0};
    Point pt_3 {1.000001, 2.000002, 3.000003};

    EXPECT_TRUE (pt_1 == pt_1);

    EXPECT_FALSE (pt_1 == pt_2);
    EXPECT_FALSE (pt_2 == pt_1);

    EXPECT_TRUE (pt_1 == pt_3);
    EXPECT_TRUE (pt_3 == pt_1);
}

TEST (Points, Inequality)
{
    Point pt_1 {1.0, 2.0, 3.0};
    Point pt_2 {2.0, 3.0, 4.0};
    Point pt_3 {1.000001, 2.000002, 3.000003};

    EXPECT_FALSE (pt_1 != pt_1);

    EXPECT_TRUE (pt_1 != pt_2);
    EXPECT_TRUE (pt_2 != pt_1);

    EXPECT_FALSE (pt_1 != pt_3);
    EXPECT_FALSE (pt_3 != pt_1);
}

TEST (Points, Distance)
{
    Point A {10000000.0};
    Point B {10000001.0};
    EXPECT_TRUE (Compare::are_equal (distance (A, B), 0.0));

    Point C {7824.911267, 0.00007648923, -1327012.8};
    Point D {-646302456.76891, 873927.1216, 0.000000001324241};
    EXPECT_TRUE (Compare::are_equal (distance (C, D), 646312234.85));

    Point E {0.0000000376418, 0.000003512, 0.00008487};
    Point F {0.0000000141879, 0.000001824, -0.00009831};
    EXPECT_TRUE (Compare::are_equal (distance (E, F), 0.000183187778779));
}

TEST (Points, Validity)
{
    EXPECT_FALSE ((Point<double> {NAN, NAN, NAN}.is_valid ()));

    EXPECT_FALSE ((Point<double> {NAN, NAN, 0.0}.is_valid ()));

    EXPECT_FALSE ((Point<double> {NAN, 0.0, NAN}.is_valid ()));

    EXPECT_FALSE ((Point<double> {0.0, NAN, NAN}.is_valid ()));

    EXPECT_FALSE ((Point<double> {NAN, 0.0, 0.0}.is_valid ()));

    EXPECT_FALSE ((Point<double> {0.0, NAN, 0.0}.is_valid ()));

    EXPECT_FALSE ((Point<double> {0.0, 0.0, NAN}.is_valid ()));

    EXPECT_TRUE (Point<double> {}.is_valid ());
}