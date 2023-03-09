#include <gtest/gtest.h>

#include "vector.hpp"
#include "double_comparison.hpp"
#include "intersection.hpp"

using namespace Geometry;

TEST (IntersectionTest_2D, Intersection_R1) 
{ 
    Triangle T2   { Point { 2.0, 0.0, 0.0}, Point { 2.0, 3.0, 0.0}, Point { 0.0, 3.0, 0.0}};
    
    Triangle T1_1 { Point {-1.0, 2.0, 0.0}, Point { 0.0, 1.0, 0.0}, Point { 1.0, 1.0, 0.0}};
    Triangle T1_2 { Point {-1.0, 2.0, 0.0}, Point { 0.0, 1.0, 0.0}, Point { 3.0,-1.0, 0.0}};
    Triangle T1_3 { Point {-1.0, 2.0, 0.0}, Point { 0.0, 1.0, 0.0}, Point {-1.0, 4.0, 0.0}};
    Triangle T1_4 { Point {-1.0, 2.0, 0.0}, Point { 0.0, 1.0, 0.0}, Point { 3.0, 1.0, 0.0}};
    Triangle T1_5 { Point {-1.0, 2.0, 0.0}, Point {-1.0, 4.0, 0.0}, Point {-2.0, 4.0, 0.0}};
    Triangle T1_6 { Point {-1.0, 1.0, 0.0}, Point { 4.0,-2.0, 0.0}, Point { 3.0,-1.0, 0.0}};
    Triangle T1_7 { Point {-1.0, 2.0, 0.0}, Point { 3.0, 1.0, 0.0}, Point { 2.0, 4.0, 0.0}};
    Triangle T1_8 { Point {-1.0, 1.0, 0.0}, Point { 4.0,-2.0, 0.0}, Point {-1.0, 2.0, 0.0}};
    Triangle T1_9 { Point {-1.0, 1.0, 0.0}, Point { 4.0,-2.0, 0.0}, Point { 2.0,10.0, 0.0}};

    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_1, T2) == false);
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_2, T2) == false);
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_3, T2) == false);
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_4, T2) == true);
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_5, T2) == false);
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_6, T2) == false);
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_7, T2) == true);
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_8, T2) == false);
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_9, T2) == true);
}

TEST (IntersectionTest_2D, Intersection_R2)
{
    Triangle T2    { Point { 2.0,  0.0, 0.0}, Point { 0.0, 3.0, 0.0}, Point { 0.0, 0.0, 0.0}};

    Triangle T1_1  { Point {-1.0, -2.0, 0.0}, Point { 3.0,-2.0, 0.0}, Point { 1.0,-1.0, 0.0}};
    Triangle T1_2  { Point {-1.0, -2.0, 0.0}, Point { 3.0,-2.0, 0.0}, Point { 5.0, 1.0, 0.0}};
    Triangle T1_3  { Point {-1.0, -2.0, 0.0}, Point { 3.0,-2.0, 0.0}, Point {-1.0, 2.0, 0.0}};
    Triangle T1_4  { Point {-1.0, -2.0, 0.0}, Point { 3.0,-2.0, 0.0}, Point {-2.0, 1.0, 0.0}};
    Triangle T1_5  { Point {-2.0, -2.0, 0.0}, Point {-1.0,-2.0, 0.0}, Point { 2.0, 3.0, 0.0}};
    Triangle T1_6  { Point {-2.0, -1.0, 0.0}, Point {-1.0,-1.0, 0.0}, Point {-1.0, 3.0, 0.0}};
    Triangle T1_7  { Point {-1.0, -2.0, 0.0}, Point {-1.0, 1.0, 0.0}, Point {-3.0, 0.0, 0.0}};
    Triangle T1_8  { Point {-3.0, -1.0, 0.0}, Point {-1.0, 1.0, 0.0}, Point {-1.0, 3.0, 0.0}};
    Triangle T1_9  { Point {-3.0, -1.0, 0.0}, Point {-1.0, 1.0, 0.0}, Point { 1.0, 6.0, 0.0}};
    Triangle T1_10 { Point {-3.0, -1.0, 0.0}, Point {-1.0, 1.0, 0.0}, Point { 2.0, 6.0, 0.0}};
    Triangle T1_11 { Point {-2.0, -1.0, 0.0}, Point { 1.0, 6.0, 0.0}, Point {-2.0, 4.0, 0.0}};
    Triangle T1_12 { Point {-2.0, -1.0, 0.0}, Point { 2.0, 3.0, 0.0}, Point {-2.0, 4.0, 0.0}};
    Triangle T1_13 { Point {-1.0, -2.0, 0.0}, Point { 5.0, 1.0, 0.0}, Point { 4.0, 1.0, 0.0}};
    Triangle T1_14 { Point {-1.0, -2.0, 0.0}, Point { 5.0, 1.0, 0.0}, Point {-2.0,-2.0, 0.0}};
    Triangle T1_15 { Point {-1.0, -2.0, 0.0}, Point { 5.0, 1.0, 0.0}, Point { 2.0, 2.0, 0.0}};

    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_1, T2) == false);
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_2, T2) == false);
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_3, T2) == true);
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_4, T2) == false);
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_5, T2) == true);
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_6, T2) == false);
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_7, T2) == false);
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_8, T2) == false);
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_9, T2) == false);
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_10, T2) == true);
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_11, T2) == false);
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_12, T2) == true);
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_13, T2) == false);
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_14, T2) == false);
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_15, T2) == true);
}

TEST (IntersectionTest_2D, PartialCase) { 
    Triangle T2   {Point { 2.0, 0.0, 0.0}, Point { 0.0, 3.0, 0.0}, Point { 0.0, 0.0, 0.0}};

    Triangle T1_1 {Point { 0.0, 0.0, 0.0}, Point { 0.0,-3.0, 0.0}, Point {-2.0, 0.0, 0.0}};
    Triangle T1_2 {Point { 2.0, 0.0, 0.0}, Point { 4.0, 0.0, 0.0}, Point { 2.0,-3.0, 0.0}};
    Triangle T1_3 {Point { 0.0, 3.0, 0.0}, Point { 3.0, 3.0, 0.0}, Point { 3.0, 1.0, 0.0}};
    Triangle T1_4 {Point { 1.0, 1.0, 0.0}, Point { 3.0, 1.0, 0.0}, Point { 1.0, 3.0, 0.0}};
    Triangle T1_5 {Point { 1.0, 0.0, 0.0}, Point { 1.0,-2.0, 0.0}, Point { 3.0,-2.0, 0.0}};
    Triangle T1_6 {Point { 0.0, 2.0, 0.0}, Point {-2.0, 4.0, 0.0}, Point {-2.0, 0.0, 0.0}};

    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_1, T2));
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_2, T2));
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_3, T2));
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_4, T2));
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_5, T2));
    EXPECT_TRUE (Algorithm::intersection_in_2D (T1_6, T2));
}
