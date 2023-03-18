#pragma once
#include <array>
#include <list>
#include <fstream>
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

    Geometry::Point<Float> center_ {};
    Float half_width_ = 0;
    node_ptr parent_ = 0;
    int which_child_ = 0;
    std::array<node_ptr, Eight> children_ {};
    std::list<ObjectSphere<Float>> objects_ {};

    bool empty() const
    {
        return (children_[0] == nullptr);
    }

    void dump(std::fstream& file)
    {
        file << "Node_" << this << "[fillcolor=white" << ", label = \"{<_node_>ptr:\\n " << this
        << "| parent:\\n " << parent_ << "| which child: " << which_child_ << "| center: " << center_ << "| {";
        for (int i; i < Eight; i++)
            file << "<" << i << ">" << i << ": \\n " << children_[i] << "| ";
        file << "| }}\"];" << std::endl;
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

    bool empty() const
    {
        return (depth_ == 0);
    }

    void descriptor_dump(std::fstream& file) const
    {
        file << "\tTree [fillcolor=purple, label = \"{ OcvtoTree\\ndescriptor| depth: " << depth_ <<
        "| <root> root:\\n " << root_ << "}\"];" << std::endl;
    }

    void debug_graph_dump(const std::string& filename) const
    {   
        std::fstream file {filename + ".dot", std::ofstream::out | std::ofstream::trunc};

        file << "digraph G {" << std::endl;
        file << "\trankdir=\"TB\"" << std::endl;
        file << "\tnode[shape=record, penwidth=3.0, style=filled, color=black, fontcolor=white];" << std::endl;
        descriptor_dump(file);
        tree_dump(file);
        file << "}" << std::endl;
        file.close();

        std::system(("dot -T svg " + filename + ".dot -o " + filename + ".svg").c_str());
        std::system(("rm " + filename + ".dot").c_str());
    }

    static void dump_node(std::fstream& file, node_ptr node)
    {
        node->dump(file);

        if (!node->empty())
            for (auto i = 0; i < Eight; i++)
                dump_node(file, node->children_[i]);
    }

    static void connect_nodes(std::fstream& file, node_ptr node)
    {
        if (node->empty())
            return;

        for (auto i = 0; i < Eight; i++)
            file << "Node_" << node << ":" << i << ":s -> Node_" << node->children_[i] << ":_node_:n;" << std::endl;

        for (auto i = 0; i < Eight; i++)
            connect_nodes(file, node->children_[i]);
    }

    void tree_dump(std::fstream& file) const
    {
        if (empty())
            return;

        dump_node(file, root_);
    
        file << "edge[penwidth=3, color=black];" << std::endl;
        connect_nodes(file, root_);
    }
};

} // namespace Container