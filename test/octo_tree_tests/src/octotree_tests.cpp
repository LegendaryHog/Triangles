#include <gtest/gtest.h>

#include "octo_tree.hpp"
#include <set>

using namespace Geometry;

struct PointDoubleCmp
{
    bool operator()(const Point<double>& p1, const Point<double>& p2) const
    {
        if (Compare::are_equal(p1.x_, p2.x_))
            if (Compare::are_equal(p1.y_, p2.y_))
                return p1.z_ < p2.z_;
            else
                return p1.y_ < p2.y_;
        else
            return p1.x_ < p2.x_;
    }
};


TEST(OctoTree, Constructor)
{
    OctoTree<double> tree_empty  (Point<double>{0.0, 0.0, 0.0}, 100.0, 0);
    OctoTree<double> tree_one_lv (Point<double>{0.0, 0.0, 0.0}, 100.0, 1);
    OctoTree<double> tree_two_lv (Point<double>{0.0, 0.0, 0.0}, 100.0, 2);
    std::set<Point<double>, PointDoubleCmp> centers_1_lv
    {Point<double>{-50, -50, -50}, Point<double>{-50, -50, 50}, Point<double>{-50, 50, -50}, Point<double>{50, -50, -50}, 
     Point<double>{50, 50, -50}, Point<double>{-50, 50, 50}, Point<double>{50, -50, 50}, Point<double>{50, 50, 50}};
    OctoTree<double> tree_three_lv (Point<double>{0.0, 0.0, 0.0}, 100.0, 3);

    EXPECT_TRUE(tree_empty.empty());
    EXPECT_EQ(tree_empty.depth(), 0);
    EXPECT_EQ(tree_empty.root(), nullptr);

    EXPECT_FALSE(tree_one_lv.empty());
    EXPECT_EQ(tree_one_lv.depth(), 1);
    EXPECT_NE(tree_one_lv.root(), nullptr);
    EXPECT_EQ(tree_one_lv.root()->half_width_, 100.0);
    EXPECT_EQ(tree_one_lv.root()->center_, (Point{0.0, 0.0, 0.0}));
    EXPECT_TRUE(tree_one_lv.root()->childless());

    EXPECT_FALSE(tree_two_lv.empty());
    EXPECT_EQ(tree_two_lv.depth(), 2);
    EXPECT_NE(tree_two_lv.root(), nullptr);
    EXPECT_EQ(tree_two_lv.root()->half_width_, 100.0);
    EXPECT_EQ(tree_two_lv.root()->center_, (Point{0.0, 0.0, 0.0}));
    EXPECT_FALSE(tree_two_lv.root()->childless());
    std::set<Point<double>, PointDoubleCmp> act_set_1_lv1 {};
    for (auto child: tree_two_lv.root()->children_)
    {
        act_set_1_lv1.insert(child->center_);
        EXPECT_EQ(child->half_width_, 50.0);
        EXPECT_TRUE(child->childless());
    }
    EXPECT_EQ(act_set_1_lv1, centers_1_lv);

    EXPECT_FALSE(tree_three_lv.empty());
    EXPECT_EQ(tree_three_lv.depth(), 3);
    EXPECT_NE(tree_three_lv.root(), nullptr);
    EXPECT_EQ(tree_three_lv.root()->half_width_, 100);
    EXPECT_EQ(tree_three_lv.root()->center_, (Point{0.0, 0.0, 0.0}));
    EXPECT_FALSE(tree_three_lv.root()->childless());
    std::set<Point<double>, PointDoubleCmp> act_set_1_lv2 {};
    for (auto child: tree_three_lv.root()->children_)
    {
        act_set_1_lv2.insert(child->center_);
        EXPECT_EQ(child->half_width_, 50.0);
        EXPECT_FALSE(child->childless());
        for (auto gr_child: child->children_)
        {
            EXPECT_EQ(gr_child->half_width_, 25.0);
            EXPECT_TRUE(gr_child->childless());
        }
    }
    EXPECT_EQ(act_set_1_lv2, centers_1_lv);
}

TEST(OctoTree, insert)
{
    OctoTree<double> tree(Point<double>{0.0, 0.0, 0.0}, 100.0, 3);
    auto root = tree.root();

    auto p1 = Shape<double>{Point{0.0, 0.0, 0.0}};
    tree.insert(p1, 0);
    EXPECT_EQ(root->bounds_.front().shape_index(), 0);
    EXPECT_EQ(std::addressof(root->bounds_.front().shape()), std::addressof(p1));
    
    auto p2 = Shape<double>{Point{50.0, 50.0, 50.0}};
    tree.insert(p2, 1);
    EXPECT_EQ(root->children_[7]->bounds_.front().shape_index(), 1);
    EXPECT_EQ(std::addressof(root->children_[7]->bounds_.front().shape()), std::addressof(p2));

    auto seg1 = Shape<double>{Segment{Point{50.0, 50.0, 50.0}, Point{0.0, 0.0, 0.0}}};
    tree.insert(seg1, 2);
    EXPECT_EQ(root->bounds_.back().shape_index(), 2);
    EXPECT_EQ(std::addressof(root->bounds_.back().shape()), std::addressof(seg1));
    
    auto tr1 = Shape<double>{Triangle{Point{2.0, 2.0, 2.0}, Point{21.0, 4.0, 2.3}, Point{21.0, 63.0, 6.0}}};
    tree.insert(tr1, 3);
    EXPECT_EQ(root->children_[7]->bounds_.back().shape_index(), 3);
    EXPECT_EQ(std::addressof(root->children_[7]->bounds_.back().shape()), std::addressof(tr1));
    
    auto tr2 = Shape<double>{Triangle{Point{2.0, 2.0, -2.0}, Point{21.0, 4.0, -2.3}, Point{21.0, 63.0, -6.0}}};
    tree.insert(tr2, 4);
    EXPECT_EQ(root->children_[3]->bounds_.back().shape_index(), 4);
    EXPECT_EQ(std::addressof(root->children_[3]->bounds_.back().shape()), std::addressof(tr2));

    auto tr3 = Shape<double>{Triangle{Point{-2.0, -2.0, -2.0}, Point{-21.0, -4.0, -2.3}, Point{-21.0, -63.0, -6.0}}};
    tree.insert(tr3, 5);
    EXPECT_EQ(root->children_[0]->bounds_.back().shape_index(), 5);
    EXPECT_EQ(std::addressof(root->children_[0]->bounds_.back().shape()), std::addressof(tr3));

    auto tr4 = Shape<double>{Triangle{Point{75.0, 25.0, -25.0}, Point{69.0, 28.0, -41.7}, Point{98.0, 12.0, -6.0}}};
    tree.insert(tr4, 6);
    EXPECT_EQ(root->children_[3]->children_[5]->bounds_.back().shape_index(), 6);
    EXPECT_EQ(std::addressof(root->children_[3]->children_[5]->bounds_.back().shape()), std::addressof(tr4));
}

