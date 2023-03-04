#include "intersection.hpp"
#include <gtest/gtest.h>

using namespace Geometry;

TEST(Triangles, are_intersecting_)
{
    Point A1 {0.0, 0.0}, B1 {3.0, 0.0}, C1 {0.0, 3.0};
    Triangle tr1 {A1, B1, C1};

    Point A2 {1.0, 0.0}, B2 {-1.0, -1.0} , C2 {4.0, -1.0};
    Triangle tr2 {A2, B2, C2};

    Point D1 {1.5, 1.5}, D2 {2.5, 0.5}, D3 {1.0, 1.0}, D4 {2.0, 2.0}, D5 {-0.5, 4.0 };
    Point D6 {0.0, -0.5}, D7 {1.0, -1.0}, D8 {-2.5, -1.5}, D9 {1.0, -0.5}, D10 {2.5001, -0.5};

    EXPECT_TRUE(are_intersecting(A1, tr1));
    EXPECT_TRUE(are_intersecting(B1, tr1));
    EXPECT_TRUE(are_intersecting(C1, tr1));

    EXPECT_TRUE(are_intersecting(D1, tr1));
    EXPECT_TRUE(are_intersecting(D2, tr1));
    EXPECT_TRUE(are_intersecting(D3, tr1));
    EXPECT_FALSE(are_intersecting(D4, tr1));
    EXPECT_FALSE(are_intersecting(D5, tr1));

    EXPECT_TRUE(are_intersecting(A2, tr2));
    EXPECT_TRUE(are_intersecting(B2, tr2));
    EXPECT_TRUE(are_intersecting(C2, tr2));

    EXPECT_TRUE(are_intersecting(D6, tr2));
    EXPECT_TRUE(are_intersecting(D7, tr2));
    EXPECT_FALSE(are_intersecting(D8, tr2));
    EXPECT_TRUE(are_intersecting(D9, tr2));
    EXPECT_FALSE(are_intersecting(D10, tr2));
}

TEST(Segment_, point_belong_segment_)
{
    Segment seg1 {Point {3.2}, Point {-5.7}};
    Point A1 {0.0}, B1 {3.7}, C1 {1.0, 0.2};

    Segment seg2 {Point {-8.0, -8.0}, Point {3.0, 3.0}};
    Point A2 {11.0, 2.0}, B2 {-3.6, -3.6}, C2 {-9.0, -9.0};

    Segment seg3 {Point {-9.0, -10.0}, Point {3.5, 2.5}};
    Point A3 {3.5, 2.5}, B3 {0.0, 0.0}, C3 {1.0, 0.0};

    EXPECT_TRUE(point_belong_segment(A1, seg1));
    EXPECT_FALSE(point_belong_segment(B1, seg1));
    EXPECT_FALSE(point_belong_segment(C1, seg1));

    EXPECT_FALSE(point_belong_segment(A2, seg2));
    EXPECT_TRUE(point_belong_segment(B2, seg2));
    EXPECT_FALSE(point_belong_segment(C2, seg2));

    EXPECT_TRUE(point_belong_segment(A3, seg3));
    EXPECT_FALSE(point_belong_segment(B3, seg3));
    EXPECT_TRUE(point_belong_segment(C3, seg3));
}

TEST(Segment_, are_intersecting)
{
    Segment seg1 {Point {0.0, 0.0}, Point {8.0, 8.0}};
    Segment seg2 {Point {1.0, 0.0}, Point {0.0, 1.0}};
    Segment seg3 {Point {0.0, 0.0, 1.0}, Point {2.0, 2.0, -4.0}};
    Segment seg4 {Point {7.0, 7.0}, Point {2.3, 3.4, 6.7}};
    Segment seg5 {Point {7.0, 7.0}, Point {11.0, 11.0}};
    Segment seg6 {Point {1.0, 0.0}, {9.0, 8.0}};
    Segment seg7 {Point {2.0}, Point {5.0}};
    Segment seg8 {Point {0.0}, Point {1.0}};
    Segment seg9 {Point {3.0, 1.0}, Point {3.0, 5.0}};
    Segment seg10 {Point {-2.0}, Point {-0.5}};
    Segment seg11 {Point {3.0}, Point {-1.0, 3.0}};

    EXPECT_TRUE(are_intersecting(seg1, seg2));
    EXPECT_TRUE(are_intersecting(seg2, seg1));
    EXPECT_TRUE(are_intersecting(seg1, seg3));
    EXPECT_FALSE(are_intersecting(seg2, seg3));
    EXPECT_TRUE(are_intersecting(seg1, seg4));
    EXPECT_TRUE(are_intersecting(seg1, seg5));
    EXPECT_FALSE(are_intersecting(seg1, seg6));
    EXPECT_FALSE(are_intersecting(seg7, seg8));
    EXPECT_FALSE(are_intersecting(seg7, seg9));
    EXPECT_FALSE(are_intersecting(seg10, seg11));
    EXPECT_FALSE(are_intersecting(seg11, seg10));
}

TEST(Segment_, seg_tr_intersecting_2D)
{
    Triangle tr {Point {-1.0, 3.0}, Point {0.0, 0.0}, Point {3.0, 0.0}};
    Segment seg1 {Point {-1.0, 2.0}, Point {0.5, 2.0}}, seg2 {Point {-2.0, 3.0}, Point {0.0, 3.0}};
    Segment seg3 {Point {3.0, 1.0}, Point {1.5, -1.0}}, seg4 {Point {0.5, -0.5}, Point {0.5, 0.5}};
    Segment seg5 {Point {0.0, 0.0}, Point {2.0, 0.0}}, seg6 {Point {-2.0, 0.0}, Point {-0.5, 0.0}};
    Segment seg7 {Point {2.0, 2.0}, Point {1.0, 3.0}}, seg8 {Point {2.0, 2.0}, Point {-1.5, 3.5}};
    Segment seg9 {Point {-0.5, 3.5}, Point {-1.5, 2.5}}, seg10 {Point {-4.0, 0.0}, Point {5.0, 0.0}};

    EXPECT_TRUE(Algorithm::seg_tr_intersecting_2D(seg1, tr));
    EXPECT_TRUE(Algorithm::seg_tr_intersecting_2D(seg2, tr));
    EXPECT_TRUE(Algorithm::seg_tr_intersecting_2D(seg3, tr));
    EXPECT_TRUE(Algorithm::seg_tr_intersecting_2D(seg4, tr));
    EXPECT_TRUE(Algorithm::seg_tr_intersecting_2D(seg5, tr));
    EXPECT_FALSE(Algorithm::seg_tr_intersecting_2D(seg6, tr));
    EXPECT_FALSE(Algorithm::seg_tr_intersecting_2D(seg7, tr));
    EXPECT_FALSE(Algorithm::seg_tr_intersecting_2D(seg8, tr));
    EXPECT_TRUE(Algorithm::seg_tr_intersecting_2D(seg9, tr));
    EXPECT_TRUE(Algorithm::seg_tr_intersecting_2D(seg10, tr));
}

TEST(Segment, seg_tr_intersection_3D)
{
    Triangle tr {Point {-3.0, 0.0}, Point {0.0, 4.0}, Point {2.0, 0.0}};

    Point A1 {0.0, 4.0}, A2 {0.0, 1.0}, A3 {1.0, 2.0}, A4 {2.0, 2.0};

    for (auto dx = 1.0; dx < 5.0; dx++)
        for (auto dy = 1.0; dy < 5.0; dy++)
            for (auto dz = 1.0; dz < 5.0; dz++)
            {
                Point F1 {A1.x_ + dx, A1.y_ + dy, A1.z_ + dz};
                Point S1 {A1.x_ - dx, A1.y_ - dy, A1.z_ - dz};

                Point F2 {A2.x_ + dx, A2.y_ + dy, A2.z_ + dz};
                Point S2 {A2.x_ - dx, A2.y_ - dy, A2.z_ - dz};

                Point F3 {A3.x_ + dx, A3.y_ + dy, A3.z_ + dz};
                Point S3 {A3.x_ - dx, A3.y_ - dy, A3.z_ - dz};

                Point F4 {A4.x_ + dx, A4.y_ + dy, A4.z_ + dz};
                Point S4 {A4.x_ - dx, A4.y_ - dy, A4.z_ - dz};
                
                Segment seg1 {F1, S1}, seg2 {F2, S2}, seg3 {F3, S3}, seg4 {F4, S4};
                EXPECT_TRUE(Algorithm::seg_tr_intersecting_3D(seg1, tr));
                EXPECT_TRUE(Algorithm::seg_tr_intersecting_3D(seg2, tr));
                EXPECT_TRUE(Algorithm::seg_tr_intersecting_3D(seg3, tr));
                EXPECT_FALSE(Algorithm::seg_tr_intersecting_3D(seg4, tr));
            }
}
TEST(Segment, are_intersecting_)
{
    Point P {12.0, 0.0}, Q {0.0, 13.0}, R {0.0, 0.0};
    Triangle tr {P, Q, R};

    Segment seg1 {P, Q}, seg2 {Q, P}, seg3 {Q, R};
    Segment seg4 {R, Q}, seg5 {R, P}, seg6 {P, R};

    std::vector<Segment<double>> vec1 {seg1, seg2, seg3, seg4, seg5, seg6};

    for (auto seg: vec1)
        EXPECT_TRUE(are_intersecting(seg, tr));
    
    Point A1 {1.0, 4.0, 1.0}, A2 {2.0, 3.0, 5.0}, A3 {6.0, 8.0, 4.0}, A4 {11.0, 11.0, 12.0};

    Segment seg7  {A1, A2}, seg8  {A1, A3}, seg9  {A1, A4};
    Segment seg10 {A2, A3}, seg11 {A2, A4}, seg12 {A3, A4};
    Segment seg13 {A2, A1}, seg14 {A3, A1}, seg15 {A4, A1};
    Segment seg16 {A3, A2}, seg17 {A4, A2}, seg18 {A4, A3};

    std::vector<Segment<double>> vec2 {seg7, seg8, seg9, seg10, seg11, seg12, seg13, seg14, seg15, seg16, seg17, seg18};

    for (auto seg: vec2)
        EXPECT_FALSE(are_intersecting(seg, tr));

    Point B1 {3.0, 3.0, -1.0}, B2 {1.0, 2.0, 5.0}, B3 {1'000'000.0, 1'000'000.0, 0.05}, B4 {3.0, -3.0, 1.0};

    Segment seg19 {B1, B2}, seg20 {B1, B4}, seg21 {B1, B3}, seg22 {B2, B3};

    EXPECT_TRUE(are_intersecting(seg19, tr));
    EXPECT_TRUE(are_intersecting(seg20, tr));
    EXPECT_FALSE(are_intersecting(seg21, tr));
    EXPECT_FALSE(are_intersecting(seg22, tr));
}
