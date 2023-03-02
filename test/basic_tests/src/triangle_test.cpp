#include "triangle.hpp"
#include "segment.hpp"

#include <gtest/gtest.h>

using namespace Geom_Objects;

TEST (Triangles, Swap_QR)
{
    Point P {872892, 15231284, 0.000024578};
    Point Q {1635.98561, 337618.98, -8841};
    Point R {-8374.61, -0.387491, 0.01367};
    Triangle tr {P, Q, R};

    tr.swap_QR ();

    EXPECT_TRUE (tr.Q() == R && tr.R() == Q);
}

TEST (Triangles, Swap_Clockwise)
{
    Point P {781.982374, -2894.162, 0.01234};
    Point Q {-0.0017263782, 9483.93, 3252.71};
    Point R {8745802.720, 0.000834942, -0.000913674};
    Triangle tr {P, Q, R};

    tr.swap_clockwise ();

    EXPECT_TRUE (tr.P() == R && tr.Q() == P && tr.R() == Q);
}

TEST (Triangles, Swap_Counterclockwise)
{
    Point P {747891.8348, -0.00058741, -12653.147};
    Point Q {4789734.8975, -357891.578, -0.0000736518};
    Point R {0.000276851, 15736.81, -96124};

    Triangle tr {P, Q, R};
    tr.swap_counterclockwise ();

    EXPECT_TRUE (tr.P() == Q && tr.Q() == R && tr.R() == P);
}

TEST (Triangles, Is_Point)
{
    Point pt_1 {743874, 9817498.19, -0.017847};

    Triangle tr_1 {pt_1, pt_1, pt_1};
    EXPECT_TRUE (tr_1.is_point ());

    Point pt_21 {0.000000253201, 493193.712904, 238710.0830};
    Point pt_22 {0.000000253202, 493193.812904, 238710.1829};
    Point pt_23 {0.000000353200, 493193.912904, 238710.2831};

    Triangle tr_2 {pt_21, pt_22, pt_23};
    EXPECT_TRUE (tr_2.is_point ());

    Point pt_31 {48752,   -104581.25, 8502.1924};
    Point pt_32 {0.00014, -582.561,   523.154};
    Point pt_33 {671.1581, 0.0,       98714.051};

    Triangle tr_3 {pt_31, pt_32, pt_33};
    EXPECT_FALSE (tr_3.is_point ());
}

TEST (Triangles, Is_Segment)
{
    Point pt_11 {73240.874, -127.7935, 12597.987124};
    Point pt_12 {pt_11.x_ / 2.0, pt_11.y_ / 2.0, pt_11.z_ / 2.0};
    Point pt_31 {pt_11.x_ / 3.0, pt_11.y_ / 3.0, pt_11.z_ / 3.0};

    Triangle tr_1 {pt_11, pt_12, pt_31};
    EXPECT_TRUE (tr_1.is_segment ());

    Point pt_21 {-0.36742, 0.00043102, 16784.9891};
    Point pt_22 {87210.71, -0.000141485, 70134.1240};

    Triangle tr_21 {pt_21, pt_21, pt_31};
    EXPECT_TRUE (tr_21.is_segment ());

    Triangle tr_22 {pt_21, pt_31, pt_21};
    EXPECT_TRUE (tr_22.is_segment ());

    Triangle tr_23 {pt_31, pt_21, pt_21};
    EXPECT_TRUE (tr_23.is_segment ());

    Point pt_3 {6020.412, 0.004691, -41769.1245};

    Triangle tr_3 {pt_3, pt_3, pt_3};
    EXPECT_TRUE (tr_3.is_segment ());

    Point pt_41 {12478.975, -0.7194, 0.00016624};
    Point pt_42 {766.24, 523652341.8902, -104.24};
    Point pt_43 {0.00001535, 0.124, 752.14556};

    Triangle tr_4 {pt_41, pt_42, pt_43};
    EXPECT_FALSE (tr_4.is_segment ());
}

