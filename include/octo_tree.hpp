#pragma once
#include <array>
#include <list>
#include "point.hpp"
#include "shape.hpp"

namespace Task
{

constexpr int Eight = 8;

template<std::floating_point Float>
struct ObjectSphere
{
    Geometry::Point<Float> center_ {};
    Float radius;
};

template<std::floating_point Float>
struct Node
{
    using node_ptr = Node*;

    Geometry::Point<Float> ceneter_ {};
    Float half_width_ = 0;
    node_ptr parent_ = 0;
    int which_child_ = 0;
    std::array<node_ptr, Eight> children_ {};
    std::list<ObjectSphere<Float>> objects_ {};

    bool empty() const
    {
        return (children_[0] == nullptr);
    }
};

template<std::floating_point Float>
class OctoTree
{
    using node_type = Node<Float>;
    using node_ptr  = Node<Float>*;
    using size_type = std::size_t;

    node_ptr  root_  = nullptr;
    size_type depth_ = 0;
public:
    OctoTree(const Geometry::Point<Float>& center, Float half_width, size_type depth)
    :depth_ {depth}
    {
        if (depth_ == 0)
            return;
        
        root_ = new node_type{center, half_width};

        if (depth_ == 1)
            return;

        size_type lvl = 0;
        node_ptr node = root_;
        for(;;)
        {
            if (node->empty())
            {
                Geometry::Point<Float> offset {};
                auto step = half_width * 0.5;

                for (int i = 0; i < Eight; i++)
                {
                    offset.x_ = ((i & 1) ? step : -step);
                    offset.y_ = ((i & 2) ? step : -step);
                    offset.z_ = ((i & 4) ? step : -step);
                    node->children_[i] = new node_type{center + offset, step, node, i};
                }                
            }
            
            if (node->which_child_ != Eight - 1)
                node = node->parent_->children_[node->which_child_ + 1];
            else if (lvl == depth_ - 1)
                node = node->parent_;
            else
                node = node->children_[0];
        }
    }

    void debug_graph_dump() const
    {
        
    }
};

} // namespace Container