#include "double_comparison.hpp"
#include "vector.hpp"

#include <gtest/gtest.h>

using namespace Geometry;

TEST (Vectors, Equality)
{
    Vector vec_1 {1.0, 2.0, 3.0};
    Vector vec_2 {2.0, 3.0, 4.0};
    Vector vec_3 {1.000001, 2.000002, 3.000003};

    EXPECT_TRUE (vec_1 == vec_1);

    EXPECT_FALSE (vec_1 == vec_2);
    EXPECT_FALSE (vec_2 == vec_1);

    EXPECT_TRUE (vec_1 == vec_3);
    EXPECT_TRUE (vec_3 == vec_1);
}

TEST (Vectors, Inequality)
{
    Vector vec_1 {1.0, 2.0, 3.0};
    Vector vec_2 {2.0, 3.0, 4.0};
    Vector vec_3 {1.000001, 2.000002, 3.000003};

    EXPECT_FALSE (vec_1 != vec_1);

    EXPECT_TRUE (vec_1 != vec_2);
    EXPECT_TRUE (vec_2 != vec_1);

    EXPECT_FALSE (vec_1 != vec_3);
    EXPECT_FALSE (vec_3 != vec_1);
}

TEST (Vectors, Addition)
{
    Vector vec_1 {1.0, 2.0, 3.0};
    Vector vec_2 {2.0, 3.0, 4.0};
    Vector vec_3 {3.0, 4.0, 5.0};
    Vector<double> null {};

    EXPECT_TRUE (vec_1 + vec_2 == vec_2 + vec_1);
    EXPECT_TRUE ((vec_1 + vec_2) + vec_3 == vec_1 + (vec_2 + vec_3));
    EXPECT_TRUE (vec_1 + (-vec_1) == null);
    EXPECT_TRUE (vec_1 + null == vec_1);

    EXPECT_TRUE ((vec_1 + vec_2 == Vector {3.0, 5.0, 7.0}));

    /* Edge case: two vectors are approximately opposite *
     *            but their sum doesn't belong to        *
     *            epsilon-neighborhood of 0.0            */
    Vector long_long_vec_1 = Vector {100000000.0};
    Vector long_long_vec_2 = Vector {-100000001.0};
    EXPECT_TRUE (long_long_vec_1 + long_long_vec_2 == null);
}

TEST (Vectors, Subtraction)
{
    Vector vec_1 {1.0, 2.0, 3.0};
    Vector vec_2 {2.0, 3.0, 4.0};
    Vector<double> null {};

    EXPECT_FALSE (vec_1 - vec_2 == vec_2 - vec_1);

    EXPECT_TRUE ((vec_1 - vec_2 == Vector {-1.0, -1.0, -1.0}));
    EXPECT_TRUE ((vec_2 - vec_1 == Vector {1.0, 1.0, 1.0}));

    /* Edge case: two vectors are approximately equal *
     *            but their difference doesn't belong *
     *            to epsilon-neighborhood of 0.0      */
    Vector long_long_vec_1 = Vector {100000000.0};
    Vector long_long_vec_2 = Vector {100000001.0};
    EXPECT_TRUE (long_long_vec_1 - long_long_vec_2 == null);
}

TEST (Vectors, Multiplication)
{
    Vector vec_1 {1.0, 2.0, 3.0};
    Vector vec_2 {2.0, 3.0, 4.0};
    Vector<double> null {};
    const double num_1 = 4.0;
    const double num_2 = 5.0;

    EXPECT_TRUE (vec_1 * num_1 == num_1 * vec_1);

    EXPECT_TRUE (num_1 * (num_2 * vec_1) == (num_1 * num_2) * vec_1);
    EXPECT_TRUE (1.0 * vec_1 == vec_1);
    EXPECT_TRUE ((num_1 + num_2) * vec_1 == num_1 * vec_1 + num_2 * vec_1);
    EXPECT_TRUE (num_1 * (vec_1 + vec_2) == num_1 * vec_1 + num_1 * vec_2);

    EXPECT_TRUE (vec_1 * 0.0 == null);
    EXPECT_TRUE (num_1 * null == null);

    EXPECT_TRUE ((-num_1) * vec_1 == num_1 * (-vec_1));
}

TEST (Vectors, Inversion)
{
    Vector vec {1.0, 2.0, 3.0};

    EXPECT_TRUE ((-vec == Vector {-1.0, -2.0, -3.0}));
    EXPECT_TRUE (-vec == -1.0 * vec);

    EXPECT_TRUE (-(-vec) == vec);
}

TEST (Vectors, Module)
{
    Vector<double> null {};
    EXPECT_TRUE (Compare::are_equal (null.module (), 0.0));

    Vector vec_1 {1.0, 2.0, 3.0};
    EXPECT_TRUE (Compare::are_equal (vec_1.module (), 3.74165738));

    Vector vec_2 {1.0, 1.0, 1.0};
    EXPECT_TRUE (Compare::are_equal (vec_2.module (), 1.73205081));

    double really_big_number = 1563413432.2;
    Vector vec_3 {1.0, 1.0, really_big_number};
    EXPECT_TRUE (Compare::are_equal (vec_3.module (), really_big_number));

    Vector vec_4 {-2.0, -3.0, 6.0};
    EXPECT_TRUE (Compare::are_equal (vec_4.module (), 7.0));

    Vector vec_5 {12.0, 16.0, 21.0};
    EXPECT_TRUE (Compare::are_equal (vec_5.module (), 29.0));
}

TEST (Vectors, Normalize)
{
    Vector<double> vec_1 {3, 0, 0};
    Vector<double> vec_1_norm {1, 0, 0};

    EXPECT_TRUE (vec_1.normalize() == vec_1_norm);

    Vector<double> null {};
    EXPECT_TRUE (null.normalize() == null);
}

TEST (Vectors, Is_Zero)
{
    Vector<double> null {};
    EXPECT_TRUE (null.is_zero ());

    Vector approx_null {-0.00000001, 0.0000009, 0.000000000008};
    EXPECT_TRUE (approx_null.is_zero ());

    Vector non_null {24.356, 72.4517, -32256574.1};
    EXPECT_FALSE (non_null.is_zero ());
}

TEST (Vectors, Scalar_Product)
{
    Vector vec_1 {39840329.2, -24532.895, 8734.12353};
    Vector vec_2 {-13767891.3, 12653.09862, 34912749.1233};
    EXPECT_DOUBLE_EQ (scalar_product (vec_1, vec_2), scalar_product (vec_2, vec_1));

    Vector vec_3 {1.0, 0.0, 4.0};
    Vector vec_4 {0.0, -6.0, 0.0};
    EXPECT_TRUE (Compare::are_equal (scalar_product (vec_3, vec_4), 0.0));

    Vector vec_5 {876325.1357, 79812.234412, -7671.122};
    Vector<double> null {};
    EXPECT_TRUE (Compare::are_equal (scalar_product (vec_5, null), 0.0));

    Vector vec_6 {34.354, 1088.12, -882.0231};
    Vector vec_7 {78989.0, -414.177, 972.13};
    EXPECT_TRUE (Compare::are_equal (scalar_product (vec_6, vec_7), 1'405'472.0 ));

    Vector vec_8 {6712.98213, -0.000014145, 72653.45};
    Vector vec_9 {0.0000007862, -0.0000094781, 21.7532};
    EXPECT_TRUE (Compare::are_equal (scalar_product (vec_8, vec_9), 1'580'445.0));

    // Edge cases: two vectors are orthogonal
    Vector vec_10 {8583.23098, 14712.30};
    Vector vec_11 {22500.0 * 14712.30, -8583.23098 * 22500.0};
    EXPECT_TRUE (Compare::are_equal (scalar_product (vec_10, vec_11), 0.0));

    Vector vec_12 {12840854.3457, 78648714912.235};
    Vector vec_13 {78648714912.235 * 0.000006, -12840854.3457 * 0.000006};
    EXPECT_TRUE (Compare::are_equal (scalar_product (vec_12, vec_13), 0.0));
}

TEST (Vectors, Vector_Product)
{
    Vector e_1 {1.0, 0.0, 0.0};
    Vector e_2 {0.0, 1.0, 0.0};
    Vector e_3 {0.0, 0.0, 1.0};
    EXPECT_TRUE (vector_product (e_1, e_2) == e_3);
    EXPECT_TRUE (vector_product (e_1, e_3) == -e_2);
    EXPECT_TRUE (vector_product (e_2, e_3) == e_1);

    // Edge cases: two vectors are collinear
    Vector vec_1 {125390.241, 398124.14, 0.14122};
    auto product = vector_product (vec_1, vec_1 * 22500.0);
    EXPECT_TRUE (product.is_zero ());
}

TEST (Vectors, Ctor_From_Points)
{
    // Edge case: constructing vector from 2 approximately matching points
    Point remote_pt_1 {100000001.0};
    Point remote_pt_2 {100000000.0};
    Vector vec {remote_pt_1, remote_pt_2};
    Vector<double> null {};
    EXPECT_TRUE (vec == null);
}
