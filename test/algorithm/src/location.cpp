#include <gtest/gtest.h>
#include "location.hpp"

TEST (Location, Magic_Product_3D)
{
    Point pt_11 {1.0, 0.0, 0.0};
    Point pt_21 {0.0, 1.0, 0.0};
    Point pt_31 {0.0, 0.0, 0.0};

    EXPECT_EQ (magic_product (pt_11, pt_21, pt_31, {802.82, -872.85, 48.14}),  Loc_3D::Above);
    EXPECT_EQ (magic_product (pt_11, pt_21, pt_31, {802.82, -872.85, 0.0}),    Loc_3D::On);
    EXPECT_EQ (magic_product (pt_11, pt_21, pt_31, {802.82, -872.85, -2.865}), Loc_3D::Below);

    EXPECT_EQ (magic_product (pt_11, pt_31, pt_21, {802.82, -872.85, 48.14}),  Loc_3D::Below);
    EXPECT_EQ (magic_product (pt_11, pt_31, pt_21, {802.82, -872.85, 0.0}),    Loc_3D::On);
    EXPECT_EQ (magic_product (pt_11, pt_31, pt_21, {802.82, -872.85, -2.865}), Loc_3D::Above);
}