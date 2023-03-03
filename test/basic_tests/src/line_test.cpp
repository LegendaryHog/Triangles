#include "double_comparison.hpp"
#include "line.hpp"

#include <gtest/gtest.h>

using namespace Geometry;

TEST (Lines, operator_equal)
{
    Point pt1 {1.0, 1.0, 1.0};
    Point pt2 {0.0, 0.0, 0.0};

    Vector vec1 {1.0, 1.0, 1.0};
    Vector vec2 {33.1, 78.4, 96.7};

    Line line1 {pt1, pt2};
    Line line2 {pt1, vec1};
    EXPECT_TRUE (line1 == line2);

    Line line3 {pt1, vec1};
    Line line4 {pt1, -vec1};
    EXPECT_TRUE (line3 == line4);

    Line line5 {pt2, vec1};
    Line line6 {pt2, vec2};
    EXPECT_TRUE (line5 != line6);
}

TEST (Lines, _are_parallel)
{
    Point pt1 {0.0, 0.0, 0.0};
    Point pt2 {0.0, 0.0, 1.0};

    Vector vec1 {1.0, 2.0, 3.0};
    Vector vec2 {37.8, 767.6, -39.7};

    Line line1 {pt1, vec1};
    Line line2 {pt2, vec1};
    EXPECT_TRUE (are_parallel (line1, line2));

    EXPECT_TRUE (are_parallel (line1, line1)); //basic logic

    Line line3 {pt1, vec1};
    Line line4 {pt1, vec2};
    EXPECT_FALSE (are_parallel (line3, line4));

    Line line5 {pt1, vec1};
    Line line6 {pt2, -vec1};
    EXPECT_TRUE (are_parallel (line5, line6));

    Line line7 {pt2, vec2};
    EXPECT_FALSE (are_parallel (line3, line7));
}

TEST (Lines, distance_btw_line_n_pt)
{
    Point pt1 {0.0, 0.0, 0.0};
    Point pt2 {1.0, 0.0, 0.0};
    Point pt3 {0.0, 1.0, 0.0};

    Vector vec1 {0.0, 0.0, 1.0};

    Line line {pt1, vec1};

    EXPECT_TRUE (Compare::are_equal (distance (line, pt1), 0.0));
    EXPECT_TRUE (Compare::are_equal (distance (line, pt2), 1.0));
    EXPECT_TRUE (Compare::are_equal (distance (line, pt3), 1.0));
}

TEST (Lines, distance_btw_lines)
{
    Point pt1 {0.0, 0.0, 0.0};
    Point pt2 {1.0, 1.0, 1.0};
    Point pt3 {1.0, 0.0, 0.0};

    Vector vec1 {0.0, 0.0, 1.0};
    Vector vec2 {1.0, 0.0, 1.0};
    Vector vec3 {1.0, -1.0, 0.0};

    Line line1 {pt1, vec1};
    Line line2 {pt2, vec2};
    EXPECT_TRUE (Compare::are_equal (distance (line1, line2), 1.0));

    Line line3 {pt3, vec1};
    EXPECT_TRUE (Compare::are_equal (distance (line1, line3), 1.0));

    Line line4 {pt1, vec2};
    Line line5 {pt3, vec2};
    EXPECT_TRUE (Compare::are_equal (distance (line4, line5), 1.0 / std::sqrt (2.0)));

    Line line6 {pt2, vec3};
    EXPECT_TRUE (Compare::are_equal (distance (line1, line6), std::sqrt (2.0)));

    EXPECT_TRUE (Compare::are_equal (distance (line1, line4), 0.0));
    EXPECT_TRUE (Compare::are_equal (distance (line2, line6), 0.0));
}
