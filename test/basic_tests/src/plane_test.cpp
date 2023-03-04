#include "double_comparison.hpp"
#include "plane.hpp"

#include <gtest/gtest.h>
#include <iostream>

using namespace Geometry;

TEST (PlaneTest, Constructors)
{
    Vector norm_bad {0.0, 0.0, 0.0};
    Point orig {0.0, 0.0, 0.0};

    Vector norm_1 {1.0, 0.0, 0.0};
    Vector norm_2 {0.0, 1.0, 0.0};
    Vector norm_3 {0.0, 0.0, 1.0};

    //  Test for bad constructors
    EXPECT_THROW ({ Plane (orig, norm_bad); }, std::invalid_argument);
    EXPECT_THROW ({ Plane (0.0, 0.0, 0.0, 42.0); }, std::invalid_argument);

    //  Test for good constructor
    EXPECT_NO_THROW ({ Plane (orig, norm_1); });
    EXPECT_NO_THROW ({ Plane (orig, norm_2); });
    EXPECT_NO_THROW ({ Plane (orig, norm_3); });

    //  Test normal creation of a plane
    Point check_point {-42.0, 0.0, 0.0};
    Plane pl {1.0, 0.0, 0.0, 42.0};
    EXPECT_TRUE (check_point == pl.origin ());                    //  check origin
    EXPECT_TRUE (Compare::are_equal (pl.norm_vec ().module (), 1.0)); //  check module of unit vector
}

TEST (PlaneTest, PlanePoint)
{
    Plane pl {0.0, 0.0, 1.0, 5.0};
    Point p {0.0, 0.0, 0.0};
    Point p_in {-1.0, -2.0, -5.0};
    Point p_out {-1.0, -2.0, 0.0};

    EXPECT_TRUE (Compare::are_equal (distance (p, pl), 5.0));

    EXPECT_TRUE (is_belong (p_in, pl));
    EXPECT_FALSE (is_belong (p_out, pl));
}

TEST (PlaneTest, PlaneLine)
{
    Plane pl {0.0, 0.0, 1.0, 0.0};

    Point p1 {0.0, 0.0, 0.0};
    Point p2 {1.0, 1.0, 1.0};
    Point p3 {1.0, 1.0, 0.0};
    Point p4 {1.0, 1.0, 5.0};
    Point p5 {0.0, 0.0, 5.0};

    Line line_inter {p1, p2};
    Line line_con {p1, p3};
    Line line_par {p5, p4};

    EXPECT_TRUE (are_intersect (line_inter, pl));
    EXPECT_FALSE (are_intersect (line_par, pl));

    EXPECT_TRUE (are_parallel (line_con, pl));
    EXPECT_TRUE (are_parallel (pl, line_con));
    EXPECT_FALSE (are_parallel (line_inter, pl));

    EXPECT_TRUE (is_belong (line_con, pl));
    EXPECT_FALSE (is_belong (line_par, pl));
    EXPECT_FALSE (is_belong (line_inter, pl));

    EXPECT_TRUE (Compare::are_equal (distance (line_par, pl), 5.0));
    EXPECT_TRUE (Compare::are_equal (distance (line_con, pl), 0.0));
    EXPECT_THROW ({ distance (line_inter, pl); }, std::logic_error);
}

TEST (PlaneTest, PlanePlane)
{
    Plane pl_back {1.0, 0.0, 0.0, 0.0};
    Plane pl_front {1.0, 0.0, 0.0, -2.0};
    Plane pl_inter {1.0, 1.0, 0.0, 0.0};
    Plane pl_inter_2 {1.0, 1.0, 0.0, 0.0};

    EXPECT_TRUE (are_parallel (pl_back, pl_front));
    EXPECT_FALSE (are_parallel (pl_inter, pl_back));

    EXPECT_TRUE (are_intersect (pl_inter, pl_front));

    EXPECT_FALSE (are_equal (pl_back, pl_inter));
    EXPECT_TRUE (are_equal (pl_inter, pl_inter_2));

    EXPECT_TRUE (Compare::are_equal (distance (pl_back, pl_front), 2.0));
    EXPECT_TRUE (Compare::are_equal (distance (pl_inter, pl_inter_2), 0.0));
    EXPECT_THROW ({ distance (pl_back, pl_inter); }, std::logic_error);
}
