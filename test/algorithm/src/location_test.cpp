#include <gtest/gtest.h>
#include "location.hpp"
#include "triangle.hpp"

using namespace Geometry;

TEST(Location, laying_in_same_half)
{
    Point A1 {2.0, 2.0}, A2 {2.0, 0.0}, A3 {0.0, 0.0}, A4 {0.0, 2.0};

    EXPECT_EQ(Location::laying_in_same_half(A1, A2, A3, A4), Location::LocPoints::InSame);
    EXPECT_EQ(Location::laying_in_same_half(A1, A3, A2, A4), Location::LocPoints::InDifferent);
    EXPECT_EQ(Location::laying_in_same_half(A1, A2, A1, A4), Location::LocPoints::Undefined);
    EXPECT_EQ(Location::laying_in_same_half(A4, A2, A1, A4), Location::LocPoints::Undefined);
    EXPECT_EQ(Location::laying_in_same_half(A3, A2, A1, A4), Location::LocPoints::InSame);
}

TEST(Location, Magic_Product_3D)
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

TEST(Location, Magic_Product_2D)
{
    Triangle T1 {Point {0.0, 0.0, 0.0}, Point {1.0, 0.0, 0.0}, Point {0.0, 1.0, 0.0}};
    Triangle T2 {Point {0.0, 0.0, 0.0}, Point {1.0, 0.0, 0.0}, Point {2.0, 0.0, 0.0}};
    Triangle T3 {Point {0.0, 0.0, 0.0}, Point {0.0, 0.0, 0.0}, Point {0.0, 0.0, 0.0}};

    EXPECT_TRUE (Location::magic_product (T1.P(), T1.Q(), T1.R()) == Location::Loc2D::Positive &&
                 Location::magic_product (T1.R(), T1.P(), T1.Q()) == Location::Loc2D::Positive &&
                 Location::magic_product (T1.Q(), T1.R(), T1.P()) == Location::Loc2D::Positive);

    EXPECT_TRUE (Location::magic_product (T1.Q(), T1.P(), T1.R()) == Location::Loc2D::Negative &&
                 Location::magic_product (T1.P(), T1.R(), T1.Q()) == Location::Loc2D::Negative &&
                 Location::magic_product (T1.R(), T1.Q(), T1.P()) == Location::Loc2D::Negative);

    EXPECT_TRUE (Location::magic_product (T2.P(), T2.Q(), T2.R()) == Location::Loc2D::Neutral &&
                 Location::magic_product (T2.R(), T2.P(), T2.Q()) == Location::Loc2D::Neutral &&
                 Location::magic_product (T2.Q(), T2.R(), T2.P()) == Location::Loc2D::Neutral);

    EXPECT_TRUE (Location::magic_product (T3.P(), T3.Q(), T3.R()) == Location::Loc2D::Neutral &&
                 Location::magic_product (T3.R(), T3.P(), T3.Q()) == Location::Loc2D::Neutral &&
                 Location::magic_product (T3.Q(), T3.R(), T3.P()) == Location::Loc2D::Neutral);
}
