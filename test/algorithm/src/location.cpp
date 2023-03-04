#include <gtest/gtest.h>
#include "location.hpp"

using namespace Geometry;

TEST (Location, Magic_Product_3D)
{
    Point pt_11 {1.0, 0.0, 0.0};
    Point pt_21 {0.0, 1.0, 0.0};
    Point pt_31 {0.0, 0.0, 0.0};

    EXPECT_EQ (Location::magic_product (pt_11, pt_21, pt_31, {802.82, -872.85, 48.14}),  Location::Loc3D::Above);
    EXPECT_EQ (Location::magic_product (pt_11, pt_21, pt_31, {802.82, -872.85, 0.0}),    Location::Loc3D::On);
    EXPECT_EQ (Location::magic_product (pt_11, pt_21, pt_31, {802.82, -872.85, -2.865}), Location::Loc3D::Below);

    EXPECT_EQ (Location::magic_product (pt_11, pt_31, pt_21, {802.82, -872.85, 48.14}),  Location::Loc3D::Below);
    EXPECT_EQ (Location::magic_product (pt_11, pt_31, pt_21, {802.82, -872.85, 0.0}),    Location::Loc3D::On);
    EXPECT_EQ (Location::magic_product (pt_11, pt_31, pt_21, {802.82, -872.85, -2.865}), Location::Loc3D::Above);
}