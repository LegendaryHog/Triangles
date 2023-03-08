#include <gtest/gtest.h>
#include "intersection.hpp"
using namespace Geometry;

#define COMMON_PART                                                                         \
do                                                                                          \
{                                                                                           \
    Algorithm::transform_triangle (tr_1, Location::magic_product (tr_2.P_, tr_2.Q_, tr_2.R_, tr_1.P_),           \
                              Location::magic_product (tr_2.P_, tr_2.Q_, tr_2.R_, tr_1.Q_),           \
                              Location::magic_product (tr_2.P_, tr_2.Q_, tr_2.R_, tr_1.R_), tr_2);    \
                                                                                            \
    EXPECT_TRUE (new_tr_1 == tr_1);                                                         \
    EXPECT_TRUE (new_tr_2 == tr_2);                                                         \
}                                                                                           \
while (0)

// P_loc == Loc_3D::Above
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TEST (Transform_Triangle, P_Above__Q_Above__R_On)
{
    Triangle<double> tr_1 {{-12.0, 13.0, 4.0}, {8.0, -5.0, 3.0}, {5.0, -7.0, 0.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 {tr_1.R_, tr_1.P_, tr_1.Q_};
    Triangle<double> new_tr_2 {tr_2.P_, tr_2.R_, tr_2.Q_};

    COMMON_PART;
}

TEST (Transform_Triangle, P_Above__Q_Above__R_Below)
{
    Triangle<double> tr_1 {{71.0, 5.0, 10.0}, {-2.0, 1.0, 14.0}, {8.0, -20.0, -9.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 {tr_1.R_, tr_1.P_, tr_1.Q_};
    Triangle<double> new_tr_2 {tr_2.P_, tr_2.R_, tr_2.Q_};

    COMMON_PART;
}

TEST (Transform_Triangle, P_Above__Q_On__R_Above)
{
    Triangle<double> tr_1 {{7.0, -9.0, 11.0}, {-34.0, 16.0, 0.0}, {-28.0, 3.0, 8.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 {tr_1.Q_, tr_1.R_, tr_1.P_};
    Triangle<double> new_tr_2 {tr_2.P_, tr_2.R_, tr_2.Q_};

    COMMON_PART;
}

TEST (Transform_Triangle, P_Above__Q_On__R_On)
{
    Triangle<double> tr_1 {{-1.0, 7.0, 5.0}, {-22.0, 15.0, 0.0}, {18.0, 6.0, 0.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 = tr_1;
    Triangle<double> new_tr_2 = tr_2;

    COMMON_PART;
}

TEST (Transform_Triangle, P_Above__Q_On__R_Below)
{
    Triangle<double> tr_1 {{17.0, -2.0, 37.0}, {4.0, 12.0, 0.0}, {0.0, 10.0, -56.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 = tr_1;
    Triangle<double> new_tr_2 = tr_2;

    COMMON_PART;
}

TEST (Transform_Triangle, P_Above__Q_Below__R_Above)
{
    Triangle<double> tr_1 {{13.0, -24.0, 11.0}, {3.0, -46.0, -25.0}, {9.0, -4.0, 8.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 {tr_1.Q_, tr_1.R_, tr_1.P_};
    Triangle<double> new_tr_2 {tr_2.P_, tr_2.R_, tr_2.Q_};

    COMMON_PART;
}

TEST (Transform_Triangle, P_Above__Q_Below__R_On)
{
    Triangle<double> tr_1 {{-38.0, 41.0, 67.0}, {-1.0, -8.0, -31.0}, {5.0, 9.0, 0.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 = tr_1;
    Triangle<double> new_tr_2 = tr_2;

    COMMON_PART;
}

TEST (Transform_Triagle, P_Above__Q_Below__R_Below)
{
    Triangle<double> tr_1 {{4.0, 14.0, 13.0}, {71.0, -35.0, -15.0}, {-16.0, 23.0, -18.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 = tr_1;
    Triangle<double> new_tr_2 = tr_2;

    COMMON_PART;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// P_loc == Loc_3D::On
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TEST (Transform_Triangle, P_On__Q_Above__R_Above)
{
    Triangle<double> tr_1 {{-18.0, 71.0, 0.0}, {1.0, 5.0, 35.0}, {9.0, -43.0, 11.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 = tr_1;
    Triangle<double> new_tr_2 {tr_2.P_, tr_2.R_, tr_2.Q_};

    COMMON_PART;
}

TEST (Transform_Triangle, P_On__Q_Above__R_On)
{
    Triangle<double> tr_1 {{4.0, -6.0, 0.0}, {52.0, -37.0, 15.0}, {91.0, -21.0, 0.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 {tr_1.Q_, tr_1.R_, tr_1.P_};
    Triangle<double> new_tr_2 = tr_2;

    COMMON_PART;
}

TEST (Transform_Triangle, P_On__Q_Above__R_Below)
{
    Triangle<double> tr_1 {{44.0, 55.0, 0.0}, {-13.0, 42.0, 12.0}, {66.0, -74.0, -33.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 {tr_1.Q_, tr_1.R_, tr_1.P_};
    Triangle<double> new_tr_2 = tr_2;

    COMMON_PART;
}

TEST (Transform_Triangle, P_On__Q_On__R_Above)
{
    Triangle<double> tr_1 {{31.0, -26.0, 0.0}, {83.0, -38.0, 0.0}, {-22.0, 74.0, 37.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 {tr_1.R_, tr_1.P_, tr_1.Q_};
    Triangle<double> new_tr_2 = tr_2;

    COMMON_PART;
}

TEST (Transform_Triangle, P_On__Q_On__R_Below)
{
    Triangle<double> tr_1 {{41.0, -62.0, 0.0}, {-59.0, 41.0, 0.0}, {73.0, 26.0, -29.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 {tr_1.R_, tr_1.P_, tr_1.Q_};
    Triangle<double> new_tr_2 {tr_2.P_, tr_2.R_, tr_2.Q_};

    COMMON_PART;
}

TEST (Transform_Triangle, P_On__Q_Below__R_Above)
{
    Triangle<double> tr_1 {{37.0, 20.0, 0.0}, {-12.0, 77.0, -49.0}, {40.0, -31.0, 16.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 {tr_1.R_, tr_1.P_, tr_1.Q_};
    Triangle<double> new_tr_2 = tr_2;

    COMMON_PART;
}

TEST (Transform_Triangle, P_On__Q_Below__R_On)
{
    Triangle<double> tr_1 {{76.0, -38.0, 0.0}, {92.0, 17.0, -50.0}, {5.0, -6.0, 0.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 {tr_1.Q_, tr_1.R_, tr_1.P_};
    Triangle<double> new_tr_2 {tr_2.P_, tr_2.R_, tr_2.Q_};

    COMMON_PART;
}

TEST (Transform_Triagle, P_On__Q_Below__R_Below)
{
    Triangle<double> tr_1 {{24.0, -53.0, 0.0}, {10.0, 35.0, -23.0}, {73.0, -27.0, -61.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 = tr_1;
    Triangle<double> new_tr_2 = tr_2;

    COMMON_PART;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// P_loc == Loc_3D::Below
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TEST (Transform_Triangle, P_Below__Q_Above__R_Above)
{
    Triangle<double> tr_1 {{14.0, -63.0, -39.0}, {95.0, 88.0, 18.0}, {2.0, 8.0, 1.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 = tr_1;
    Triangle<double> new_tr_2 {tr_2.P_, tr_2.R_, tr_2.Q_};

    COMMON_PART;
}

TEST (Transform_Triangle, P_Below__Q_Above__R_On)
{
    Triangle<double> tr_1 {{67.0, -32.0, -56.0}, {0.0, -14.0, 26.0}, {19.0, -21.0, 0.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 = tr_1;
    Triangle<double> new_tr_2 {tr_2.P_, tr_2.R_, tr_2.Q_};

    COMMON_PART;
}

TEST (Transform_Triangle, P_Below__Q_Above__R_Below)
{
    Triangle<double> tr_1 {{64.0, -24.0, -23.0}, {11.0, 15.0, 55.0}, {-83.0, 43.0, -73.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 {tr_1.Q_, tr_1.R_, tr_1.P_};
    Triangle<double> new_tr_2 = tr_2;

    COMMON_PART;
}

TEST (Transform_Triangle, P_Below__Q_On__R_Above)
{
    Triangle<double> tr_1 {{13.0, 53.0, -56.0}, {-94.0, 26.0, 0.0}, {82.0, -74.0, 81.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 = tr_1;
    Triangle<double> new_tr_2 {tr_2.P_, tr_2.R_, tr_2.Q_};

    COMMON_PART;
}

TEST (Transform_Triangle, P_Below__Q_On__R_On)
{
    Triangle<double> tr_1 {{23.0, 74.0, -59.0}, {-25.0, 63.0, 0.0}, {-86.0, 61.0, 0.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 = tr_1;
    Triangle<double> new_tr_2 {tr_2.P_, tr_2.R_, tr_2.Q_};

    COMMON_PART;
}

TEST (Transform_Triangle, P_Below__Q_On__R_Below)
{
    Triangle<double> tr_1 {{24.0, 60.0, -73.0}, {34.0, -73.0, 0.0}, {-92.0, 10.0, -20.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 {tr_1.Q_, tr_1.R_, tr_1.P_};
    Triangle<double> new_tr_2 = tr_2;

    COMMON_PART;
}

TEST (Transform_Triangle, P_Below__Q_Below__R_Above)
{
    Triangle<double> tr_1 {{61.0, 93.0, -27.0}, {14.0, 25.0, -80.0}, {7.0, -2.0, 23.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 {tr_1.R_, tr_1.P_, tr_1.Q_};
    Triangle<double> new_tr_2 = tr_2;

    COMMON_PART;
}

TEST (Transform_Triangle, P_Below__Q_Below__R_On)
{
    Triangle<double> tr_1 {{75.0, 12.0, -27.0}, {-9.0, 32.0, -80.0}, {75.0, -1.0, 0.0}};
    Triangle<double> tr_2 {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}};

    Triangle<double> new_tr_1 {tr_1.R_, tr_1.P_, tr_1.Q_};
    Triangle<double> new_tr_2 = tr_2;

    COMMON_PART;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
