#include "segment.hpp"
#include <gtest/gtest.h>
#include <vector>

using namespace Geom_Objects;

TEST(Segment_, ctor_by_triangle)
{
    Point A1 {1.0, 0.0}, B1 {-4.0, 0.0}, C1 {15.0, 0.0};
    Triangle tr1 {A1, B1, C1};

    Point A2 {1.0, 3.0}, B2 {34.0, 102.0}, C2 {11.0, 33.0};
    Triangle tr2 {A2, B2, C2};

    Point A3 {3.0, 4.0}, B3 {-15.0, -14.0}, C3 {7.0, 8.0};
    Triangle tr3 {A3, B3, C3};

    Segment seg1 {tr1};
    Segment seg2 {tr2};
    Segment seg3 {tr3};

    EXPECT_TRUE(seg1.F_ == B1 || seg1.F_ == C1);
    EXPECT_TRUE(seg1.F_ != seg1.S_);
    EXPECT_TRUE(seg1.S_ == B1 || seg1.S_ == C1);

    EXPECT_TRUE(seg2.F_ == A2 || seg2.F_ == B2);
    EXPECT_TRUE(seg2.F_ != seg2.S_);
    EXPECT_TRUE(seg2.S_ == A2 || seg2.S_ == B2);

    EXPECT_TRUE(seg3.F_ == B3 || seg3.F_ == C3);
    EXPECT_TRUE(seg3.F_ != seg3.S_);
    EXPECT_TRUE(seg3.S_ == B3 || seg3.S_ == C3);
}