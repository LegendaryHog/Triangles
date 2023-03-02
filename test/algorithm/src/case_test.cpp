#include "intersection.hpp"
#include "algorithm_testing.hpp"
#include <gtest/gtest.h>

using namespace Geometry;

TEST(Case_, case_of_intersection_)
{
    Point A {12.0, 32.4, 1.0}, B {-14.0, 45.5, 33.7}, C {1.0, 0.0, 0.0};

    Triangle tr1 {A, A, A}, tr2 {B, B, B}, tr3 {A, B, A}, tr4 {C, C, A};
    Triangle tr5 {A, B, C};

    EXPECT_TRUE(case_of_intersection(tr1, tr2) == Case::Point_n_Point);
    EXPECT_TRUE(case_of_intersection(tr1, tr1) == Case::Point_n_Point);
    EXPECT_TRUE(case_of_intersection(tr1, tr3) == Case::Point_n_Segment);
    EXPECT_TRUE(case_of_intersection(tr2, tr3) == Case::Point_n_Segment);
    EXPECT_TRUE(case_of_intersection(tr1, tr4) == Case::Point_n_Segment);
    EXPECT_TRUE(case_of_intersection(tr1, tr5) == Case::Point_n_Triangle);
    EXPECT_TRUE(case_of_intersection(tr2, tr5) == Case::Point_n_Triangle);
    EXPECT_TRUE(case_of_intersection(tr3, tr1) == Case::Segment_n_Point);
    EXPECT_TRUE(case_of_intersection(tr4, tr1) == Case::Segment_n_Point);
    EXPECT_TRUE(case_of_intersection(tr3, tr2) == Case::Segment_n_Point);
    EXPECT_TRUE(case_of_intersection(tr3, tr4) == Case::Segment_n_Segment);
    EXPECT_TRUE(case_of_intersection(tr4, tr3) == Case::Segment_n_Segment);
    EXPECT_TRUE(case_of_intersection(tr3, tr3) == Case::Segment_n_Segment);
    EXPECT_TRUE(case_of_intersection(tr3, tr5) == Case::Segment_n_Triangle);
    EXPECT_TRUE(case_of_intersection(tr4, tr5) == Case::Segment_n_Triangle);
    EXPECT_TRUE(case_of_intersection(tr5, tr1) == Case::Triangle_n_Point);
    EXPECT_TRUE(case_of_intersection(tr5, tr2) == Case::Triangle_n_Point);
    EXPECT_TRUE(case_of_intersection(tr5, tr3) == Case::Triangle_n_Segment);
    EXPECT_TRUE(case_of_intersection(tr5, tr4) == Case::Triangle_n_Segment);
    EXPECT_TRUE(case_of_intersection(tr5, tr5) == Case::Triangle_n_Triangle);
}