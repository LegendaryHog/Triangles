#include <gtest/gtest.h>

#include "octo_tree.hpp"

using namespace Geometry;

TEST(OctoTree, Constructor)
{
    OctoTree<double> tree_empty  (Point<double>{0.0, 0.0, 0.0}, 100, 0);
    OctoTree<double> tree_one_lv (Point<double>{0.0, 0.0, 0.0}, 100, 1);
    OctoTree<double> tree_two_lv (Point<double>{0.0, 0.0, 0.0}, 100, 2);

    EXPECT_TRUE(tree_empty.empty());
    EXPECT_EQ(tree_empty.depth(), 0);

}

TEST(OctoTree, insert)
{
    OctoTree<double> tree1 (Point<double>{0.0, 0.0, 0.0}, 100, 3);
    tree1.insert(Point{0.0, 0.0, 0.0}, 0);
}