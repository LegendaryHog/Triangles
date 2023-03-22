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

TEST(IntersectionTest_2D, Problem_Cyclic_Permutation_Deficit)
{
    Triangle blue {Point{17.348719012630276, 14.44947008496748, 0.0}, 
                   Point{6.924895189828961, 3.9257440970926503, 0.0},
                   Point{11.656308581139456, 1.600646115179307, 0.0}};

    Triangle green{Point{7.136605526488715, 7.274655471373606, 0.0},
                   Point{13.71521457273856,6.915583692871211, 0.0}, 
                   Point{12.133772594648583, 38.23631927044342, 0.0}};

    EXPECT_TRUE (Algorithm::intersection_in_2D (blue, green));
    EXPECT_TRUE (Algorithm::intersection_in_2D (green, blue));
}

TEST(IntersectionTest_2D, Problem)
{
    Triangle blue {Point{7.316825105697096, 3.8701882025938934, 0.0},
                   Point{8.99487815035528, 6.466567288049715, 0.0},
                   Point{5.757177658271756, 4.918519254424907, 0.0}};
    
    Triangle green{Point{8.008480302821877, 6.553977693675142, 0.0},
                   Point{8.42948662398759, 5.60698141117058, 0.0},
                   Point{8.013269774616896, 8.768418936594259, 0.0}};

    EXPECT_TRUE (Algorithm::intersection_in_2D (blue, green));
    EXPECT_TRUE (Algorithm::intersection_in_2D (green, blue));
}
