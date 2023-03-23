#include <gtest/gtest.h>
#include "bounding_box.hpp"

using namespace Geometry;

TEST(BoundingBox, Point_Bounding)
{
    Shape<double> p1 = Point<double>{0.0, 0.0, 0.0};
    auto p1_bbox     = make_bound (p1, 0);

    EXPECT_TRUE ((p1_bbox.center () == std::get<Point<double>> (p1)) &&
                 Compare::are_equal (p1_bbox.half_width_x (), Math::epsilon<double>) &&
                 Compare::are_equal (p1_bbox.half_width_y (), Math::epsilon<double>) &&
                 Compare::are_equal (p1_bbox.half_width_z (), Math::epsilon<double>));
}

TEST(BoundingBox, Segment_Bounding)
{
    Shape<double> seg_xOy = Segment<double> {Point{0.0, 0.0, 0.0}, Point{0.0, 1.0, 0.0}};
    auto seg_bbox         = make_bound (seg_xOy, 0);

    EXPECT_EQ(seg_bbox.center(), (Point{0.0, 0.5, 0.0}));
    EXPECT_TRUE(Compare::are_equal (seg_bbox.half_width_x (), Math::epsilon<double>));
    EXPECT_TRUE(Compare::are_equal (seg_bbox.half_width_y (), 0.5 + Math::epsilon<double>));
    EXPECT_TRUE(Compare::are_equal (seg_bbox.half_width_z (), Math::epsilon<double>));

    Shape<double> seg1 = Segment<double> {Point {0.0, 0.0, 0.0}, Point{1.0, 2.0, 4.0}};
    auto seg1_bbox     = make_bound (seg1, 0);

    EXPECT_EQ(seg1_bbox.center(), (Point{0.5, 1.0, 2.0}));
    EXPECT_TRUE(Compare::are_equal (seg1_bbox.half_width_x (), 0.5 + Math::epsilon<double>));
    EXPECT_TRUE(Compare::are_equal (seg1_bbox.half_width_y (), 1.0 + Math::epsilon<double>));
    EXPECT_TRUE(Compare::are_equal (seg1_bbox.half_width_z (), 2.0 + Math::epsilon<double>));
}

TEST(BoundingBox, Triangle_Bounding)
{
    Shape<double> tr_xOy = Triangle<double> {Point{0.0, 0.0, 0.0}, Point{1.0, 0.0, 0.0}, Point{0.0, 2.0, 0.0}};
    auto tr_xOy_bbox     = make_bound (tr_xOy, 0);

    EXPECT_EQ(tr_xOy_bbox.center(), (Point{0.5, 1.0, 0.0}));
    EXPECT_TRUE(Compare::are_equal (tr_xOy_bbox.half_width_x (), 0.5 + Math::epsilon<double>));
    EXPECT_TRUE(Compare::are_equal (tr_xOy_bbox.half_width_y (), 1.0 + Math::epsilon<double>));
    EXPECT_TRUE(Compare::are_equal (tr_xOy_bbox.half_width_z (), 0.0 + Math::epsilon<double>));

    Shape<double> tr1 = Triangle<double> {Point{0.0, 0.0, 0.0}, Point{11.0, 23.0, 10.0}, Point{15.0, 20.0, 4.0}};
    auto tr1_bbox     = make_bound (tr1, 0);

    EXPECT_EQ(tr1_bbox.center (), (Point{7.5, 11.5, 5.0}));
    EXPECT_TRUE(Compare::are_equal (tr1_bbox.half_width_x (), 7.5 + Math::epsilon<double>));
    EXPECT_TRUE(Compare::are_equal (tr1_bbox.half_width_y (), 11.5 + Math::epsilon<double>));
    EXPECT_TRUE(Compare::are_equal (tr1_bbox.half_width_z (), 5.0 + Math::epsilon<double>));
}
