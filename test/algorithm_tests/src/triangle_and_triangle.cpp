#include "intersection.hpp"
#include "location.hpp"
#include <gtest/gtest.h>

using namespace Geometry;

TEST(CommonCase, Problem_Permutation_Point_Red)
{
    Triangle blue {Point{22.645042475962875, 82.1267687850731, 93.81962543017956},
                   Point{67.10824964048389, 15.16468924329465, 3.5737691907615887},
                   Point{7.314597187045968, 98.57960676681186, 30.923252914946588}};

    Triangle green {Point{12.150263502093317, 94.8745096696045, 15.597294942399898},
                    Point{56.786100746398546, 89.4356886265318, 20.91664333611487},
                    Point{90.67516258630724, 49.43657823665529, 48.221862781390236}};

    Triangle red {Point{42.81027758606856, 40.600322107771724, 99.25013614930288},
                  Point{11.560300543424184, 91.71630400669642, 67.98940077131682},
                  Point{61.01493605938193, 95.3730925554242, 16.257272342717933}};

    EXPECT_TRUE(are_intersecting(blue, red));
    EXPECT_TRUE(are_intersecting(red, blue));

    EXPECT_FALSE(are_intersecting(blue, green));
    EXPECT_FALSE(are_intersecting(green, blue));

    EXPECT_FALSE(are_intersecting(red, green));
    EXPECT_FALSE(are_intersecting(green, red));
}

TEST(PartialCase, Intersecgtion_By_A_Point)
{
    Triangle T2   {Point{0.0, 0.0, 0.0}, Point{2.0, 0.0, 0.0}, Point{0.0, 2.0, 0.0}};

    Triangle T1_1 {Point{0.0, 0.0, 0.0}, Point{0.0, 0.0, 2.0}, Point{1.0, 2.0, 2.0}};
    Triangle T1_2 {Point{0.0, 0.0, 2.0}, Point{0.0, 0.0, 0.0}, Point{1.0, 2.0, 2.0}};
    Triangle T1_3 {Point{0.0, 0.0, 2.0}, Point{1.0, 2.0, 2.0}, Point{0.0, 0.0, 0.0}};

    EXPECT_TRUE (are_intersecting(T1_1, T2));
    EXPECT_TRUE (are_intersecting(T2, T1_1));

    EXPECT_TRUE (are_intersecting(T1_2, T2));
    EXPECT_TRUE (are_intersecting(T2, T1_2));

    EXPECT_TRUE (are_intersecting(T1_3, T2));
    EXPECT_TRUE (are_intersecting(T2, T1_3));
}

TEST(PartialCase, Intersecgtion_By_A_Side)
{
    Triangle T2   {Point{ 0.0, 0.0, 0.0}, Point{2.0, 0.0, 0.0}, Point{0.0, 2.0, 0.0}};
 
    Triangle T1_1 {Point{ 1.0, 1.0, 0.0}, Point{ 0.5, 1.5, 0.0}, Point{0.0, 0.0, 1.0}};
    Triangle T1_2 {Point{ 1.0, 1.0, 0.0}, Point{-1.0, 3.0, 0.0}, Point{0.0, 0.0, 1.0}};
    Triangle T1_3 {Point{ 3.0,-1.0, 0.0}, Point{-1.0, 3.0, 0.0}, Point{0.0, 0.0, 1.0}};

    Triangle T1_4 {Point{-0.5, 2.5, 0.0}, Point{-1.0, 3.0, 0.0}, Point{0.0, 0.0, 1.0}};

    EXPECT_TRUE (are_intersecting(T2, T1_1));
    EXPECT_TRUE (are_intersecting(T1_1, T2));

    EXPECT_TRUE (are_intersecting(T2, T1_2));
    EXPECT_TRUE (are_intersecting(T1_2, T2));

    EXPECT_TRUE (are_intersecting(T2, T1_3));
    EXPECT_TRUE (are_intersecting(T1_3, T2));

    EXPECT_FALSE (are_intersecting(T2, T1_4));
    EXPECT_FALSE (are_intersecting(T1_4, T2));
}
