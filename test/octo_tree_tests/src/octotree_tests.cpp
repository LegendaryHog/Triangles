#include <gtest/gtest.h>

#include "octo_tree.hpp"

TEST(OctoTree, Constructor)
{
    Task::OctoTree<double> tree_empty  (Geometry::Point<double>{0.0, 0.0, 0.0}, 100, 0);
    Task::OctoTree<double> tree_one_lv (Geometry::Point<double>{0.0, 0.0, 0.0}, 100, 1);
    Task::OctoTree<double> tree_two_lv (Geometry::Point<double>{0.0, 0.0, 0.0}, 100, 2);

    EXPECT_TRUE (tree_empty.empty());

    auto tree_one_lv_root = tree_one_lv.root ();
    EXPECT_TRUE (!tree_one_lv.empty() && 
                 (tree_one_lv_root->half_width_ == 100) &&
                  tree_one_lv_root->childless() &&
                 (tree_one_lv_root->center_ == Geometry::Point{0.0, 0.0, 0.0}));

    auto tree_two_lv_root = tree_two_lv.root ();
    EXPECT_TRUE (!tree_two_lv.empty() && 
                 (tree_two_lv_root->half_width_ == 100) &&
                 !tree_two_lv_root->childless() &&
                 (tree_two_lv_root->center_ == Geometry::Point{0.0, 0.0, 0.0}));


    EXPECT_TRUE (tree_two_lv_root->children_[0] != nullptr && 
                (tree_two_lv_root->children_[0]->half_width_ == 50) &&
                 tree_two_lv_root->children_[0]->childless() &&
                (tree_two_lv_root->children_[0]->center_ == Geometry::Point{-50.0, -50.0, -50.0}));

    EXPECT_TRUE (tree_two_lv_root->children_[1] != nullptr && 
                (tree_two_lv_root->children_[1]->half_width_ == 50) &&
                 tree_two_lv_root->children_[1]->childless() &&
                (tree_two_lv_root->children_[1]->center_ == Geometry::Point{50.0, -50.0, -50.0}));

    EXPECT_TRUE (tree_two_lv_root->children_[2] != nullptr && 
                (tree_two_lv_root->children_[2]->half_width_ == 50) &&
                 tree_two_lv_root->children_[2]->childless() &&
                (tree_two_lv_root->children_[2]->center_ == Geometry::Point{-50.0, 50.0, -50.0}));

    EXPECT_TRUE (tree_two_lv_root->children_[3] != nullptr && 
                (tree_two_lv_root->children_[3]->half_width_ == 50) &&
                 tree_two_lv_root->children_[3]->childless() &&
                (tree_two_lv_root->children_[3]->center_ == Geometry::Point{50.0, 50.0, -50.0}));

    EXPECT_TRUE (tree_two_lv_root->children_[4] != nullptr && 
                (tree_two_lv_root->children_[4]->half_width_ == 50) &&
                 tree_two_lv_root->children_[4]->childless() &&
                (tree_two_lv_root->children_[4]->center_ == Geometry::Point{-50.0, -50.0, 50.0}));

    EXPECT_TRUE (tree_two_lv_root->children_[5] != nullptr && 
                (tree_two_lv_root->children_[5]->half_width_ == 50) &&
                 tree_two_lv_root->children_[5]->childless() &&
                (tree_two_lv_root->children_[5]->center_ == Geometry::Point{50.0, -50.0, 50.0}));

    EXPECT_TRUE (tree_two_lv_root->children_[6] != nullptr && 
                (tree_two_lv_root->children_[6]->half_width_ == 50) &&
                 tree_two_lv_root->children_[6]->childless() &&
                (tree_two_lv_root->children_[6]->center_ == Geometry::Point{-50.0, 50.0, 50.0}));

    EXPECT_TRUE (tree_two_lv_root->children_[7] != nullptr && 
                (tree_two_lv_root->children_[7]->half_width_ == 50) &&
                 tree_two_lv_root->children_[7]->childless() &&
                (tree_two_lv_root->children_[7]->center_ == Geometry::Point{50.0, 50.0, 50.0}));            

}

TEST(OctoTree, insert)
{
    Task::OctoTree<double> tree1 (Geometry::Point<double>{0.0, 0.0, 0.0}, 100, 3);
    tree1.insert(Geometry::Point{0.0, 0.0, 0.0}, 0);
}