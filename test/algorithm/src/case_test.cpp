#include "intersection.hpp"
#include <gtest/gtest.h>

using namespace Geometry;

enum class Case {       //   3^1     3^0
    PointAndPoint       = 0 * 3 + 0 * 1,
    PointAndSegment     = 0 * 3 + 1 * 1,
    PointAndTriangle    = 0 * 3 + 2 * 1,
    SegmentAndPoint     = 1 * 3 + 0 * 1,
    SegmentAndSegment   = 1 * 3 + 1 * 1,
    SegmentAndTriangle  = 1 * 3 + 2 * 1,
    TriangleAndPoint    = 2 * 3 + 0 * 1,
    TriangleAndSegment  = 2 * 3 + 1 * 1,
    TriangleAndTriangle = 2 * 3 + 2 * 1,
};

template<std::floating_point F>
Case case_of_intersection(const Triangle<F>& tr1, const Triangle<F>& tr2)
{
    return static_cast<Case>(3 * tr1.type() + 1 * tr2.type());
}

TEST(Case_, case_of_intersection_)
{
    Point A {12.0, 32.4, 1.0}, B {-14.0, 45.5, 33.7}, C {1.0, 0.0, 0.0};

    Triangle tr1 {A, A, A}, tr2 {B, B, B}, tr3 {A, B, A}, tr4 {C, C, A};
    Triangle tr5 {A, B, C};

    EXPECT_TRUE(case_of_intersection(tr1, tr2) == Case::PointAndPoint);
    EXPECT_TRUE(case_of_intersection(tr1, tr1) == Case::PointAndPoint);
    EXPECT_TRUE(case_of_intersection(tr1, tr3) == Case::PointAndSegment);
    EXPECT_TRUE(case_of_intersection(tr2, tr3) == Case::PointAndSegment);
    EXPECT_TRUE(case_of_intersection(tr1, tr4) == Case::PointAndSegment);
    EXPECT_TRUE(case_of_intersection(tr1, tr5) == Case::PointAndTriangle);
    EXPECT_TRUE(case_of_intersection(tr2, tr5) == Case::PointAndTriangle);
    EXPECT_TRUE(case_of_intersection(tr3, tr1) == Case::SegmentAndPoint);
    EXPECT_TRUE(case_of_intersection(tr4, tr1) == Case::SegmentAndPoint);
    EXPECT_TRUE(case_of_intersection(tr3, tr2) == Case::SegmentAndPoint);
    EXPECT_TRUE(case_of_intersection(tr3, tr4) == Case::SegmentAndSegment);
    EXPECT_TRUE(case_of_intersection(tr4, tr3) == Case::SegmentAndSegment);
    EXPECT_TRUE(case_of_intersection(tr3, tr3) == Case::SegmentAndSegment);
    EXPECT_TRUE(case_of_intersection(tr3, tr5) == Case::SegmentAndTriangle);
    EXPECT_TRUE(case_of_intersection(tr4, tr5) == Case::SegmentAndTriangle);
    EXPECT_TRUE(case_of_intersection(tr5, tr1) == Case::TriangleAndPoint);
    EXPECT_TRUE(case_of_intersection(tr5, tr2) == Case::TriangleAndPoint);
    EXPECT_TRUE(case_of_intersection(tr5, tr3) == Case::TriangleAndSegment);
    EXPECT_TRUE(case_of_intersection(tr5, tr4) == Case::TriangleAndSegment);
    EXPECT_TRUE(case_of_intersection(tr5, tr5) == Case::TriangleAndTriangle);
}