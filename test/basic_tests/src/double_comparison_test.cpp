#include "double_comparison.hpp"
#include <gtest/gtest.h>

using namespace Compare;

TEST (Double_Comparison, Normalized)
{
    EXPECT_TRUE (are_equal (0.0, 0.0));
    EXPECT_TRUE (are_equal (0.0, -0.0));

    EXPECT_FALSE (are_equal (1.0, 0.0));
    EXPECT_FALSE (are_equal (1.0, -0.0));
    EXPECT_FALSE (are_equal (-1.0, 0.0));
    EXPECT_FALSE (are_equal (-1.0, -0.0));

    EXPECT_FALSE (are_equal (83745.2, 0.0));
    EXPECT_FALSE (are_equal (83745.2, -0.0));
    EXPECT_FALSE (are_equal (-83745.2, 0.0));
    EXPECT_FALSE (are_equal (-83745.2, -0.0));
}

TEST (Double_Comparison, Subnormal)
{
    EXPECT_TRUE (are_equal (Math::epsilon<double> / 2.0, 0.0));
    EXPECT_TRUE (are_equal (Math::epsilon<double> / 2.0, -0.0));
    EXPECT_TRUE (are_equal (-Math::epsilon<double> / 2.0, 0.0));
    EXPECT_TRUE (are_equal (-Math::epsilon<double> / 2.0, -0.0));

    EXPECT_TRUE (are_equal (1e-10, 0.0));
    EXPECT_TRUE (are_equal (1e-10, -0.0));
    EXPECT_TRUE (are_equal (-1e-10, 0.0));
    EXPECT_TRUE (are_equal (-1e-10, -0.0));
}
