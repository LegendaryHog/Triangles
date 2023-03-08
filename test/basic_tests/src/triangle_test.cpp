#include "triangle.hpp"
#include "segment.hpp"

#include <gtest/gtest.h>

using namespace Geometry;

TEST (Triangles, Swap_QR)
{
    Point P {872892.0, 15231284.0, 0.000024578};
    Point Q {1635.98561, 337618.98, -8841.0};
    Point R {-8374.61, -0.387491, 0.01367};
    Triangle tr {P, Q, R};

    tr.swap_QR ();

    EXPECT_TRUE (tr.Q_ == R && tr.R_ == Q);
}

TEST (Triangles, Swap_Clockwise)
{
    Point P {781.982374, -2894.162, 0.01234};
    Point Q {-0.0017263782, 9483.93, 3252.71};
    Point R {8745802.720, 0.000834942, -0.000913674};
    Triangle tr {P, Q, R};

    tr.swap_clockwise ();

    EXPECT_TRUE (tr.P_ == R && tr.Q_ == P && tr.R_ == Q);
}

TEST (Triangles, Swap_Counterclockwise)
{
    Point P {747891.8348, -0.00058741, -12653.147};
    Point Q {4789734.8975, -357891.578, -0.0000736518};
    Point R {0.000276851, 15736.81, -96124.0};

    Triangle tr {P, Q, R};
    tr.swap_counterclockwise ();

    EXPECT_TRUE (tr.P_ == Q && tr.Q_ == R && tr.R_ == P);
}
