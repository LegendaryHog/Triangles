#include <gtest/gtest.h>

#include "octo_tree.hpp"

TEST(OctoTree, Constructor)
{
    Task::OctoTree<double> tree1 (Geometry::Point{0.0, 0.0, 0.0}, 100, 1);
    Task::OctoTree<double> tree2 (Geometry::Point{0.0, 0.0, 0.0}, 100, 2);
    Task::OctoTree<double> tree3 (Geometry::Point{0.0, 0.0, 0.0}, 100, 3);

    tree1.debug_graph_dump("dump1");
    tree2.debug_graph_dump("dump2");
    tree3.debug_graph_dump("dump3");
}

TEST(OctoTree, insert)
{
    Task::OctoTree<double> tree1 (Geometry::Point{0.0, 0.0, 0.0}, 100, 3);
    tree1.insert(Geometry::Point{0.0, 0.0, 0.0});
    tree1.debug_graph_dump("dump4");
}