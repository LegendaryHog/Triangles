#include "intersection.hpp"
<<<<<<< HEAD
#include "location.hpp"
=======
>>>>>>> LegHog
#include <gtest/gtest.h>

using namespace Geometry;

<<<<<<< HEAD
TEST(CommonCase, Problem_Permutation_Point_Red)
=======
TEST(Common_Case, First)
>>>>>>> LegHog
{
    Triangle blue {Point{22.645042475962875, 82.1267687850731, 93.81962543017956},
                   Point{67.10824964048389, 15.16468924329465, 3.5737691907615887},
                   Point{7.314597187045968, 98.57960676681186, 30.923252914946588}};

    Triangle green {Point{12.150263502093317, 94.8745096696045, 15.597294942399898},
<<<<<<< HEAD
                    Point{56.786100746398546, 89.4356886265318, 20.91664333611487},
                    Point{90.67516258630724, 49.43657823665529, 48.221862781390236}};
=======
                    Point{90.67516258630724, 49.43657823665529, 48.221862781390236},
                    Point{56.786100746398546, 89.4356886265318, 20.91664333611487}};
>>>>>>> LegHog

    Triangle red {Point{42.81027758606856, 40.600322107771724, 99.25013614930288},
                  Point{11.560300543424184, 91.71630400669642, 67.98940077131682},
                  Point{61.01493605938193, 95.3730925554242, 16.257272342717933}};

    EXPECT_TRUE(are_intersecting(blue, red));
    EXPECT_TRUE(are_intersecting(red, blue));

    EXPECT_FALSE(are_intersecting(blue, green));
    EXPECT_FALSE(are_intersecting(green, blue));

<<<<<<< HEAD
    EXPECT_FALSE(are_intersecting(red, green));
    EXPECT_FALSE(are_intersecting(green, red));
}
=======
    // problem
#define FIXED
#ifdef FIXED
    EXPECT_FALSE(are_intersecting(red, green));
    EXPECT_FALSE(are_intersecting(green, red));
#endif

    Triangle tr1 {Point{0.0, 0.0, 0.0}, Point{0.0, 1.0, 0.0}, Point{0.5, 0.5, 0.0}};
    Triangle tr2 {Point{0.51, 0.51, 0.0}, Point{1.0, -1.0, 1.0}, Point{-1.0, 1.0, 0.1}};

    EXPECT_FALSE(are_intersecting(tr1, tr2));
    EXPECT_FALSE(are_intersecting(tr2, tr1));
}
>>>>>>> LegHog
