#pragma once
#include <array>
#include <list>
#include <fstream>
#include "point.hpp"
#include "shape.hpp"

namespace Task
{

constexpr int Eight = 3;

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
    std::array<node_ptr, Eight> children_ {};
    std::list<ObjectSphere<Float>> objects_ {};

    bool childless() const
    {
        return (children_[0] == nullptr);
    }

    void dump(std::fstream& file)
    {
        file << "Node_" << this << "[color=brown, fillcolor=lightgreen, fontcolor=black" << ", label = \"{<_node_>ptr:\\n " << this
        << "| center: " << center_ << "| {";
        for (int i = 0; i < Eight - 1; i++)
            file << "<" << i << ">" << i << ": \\n " << children_[i] << "| ";
        file << "<" << Eight - 1 << ">" << Eight - 1 << ": \\n " << children_[Eight - 1]; 
        file << "}}\"];" << std::endl;
    }
};

template<std::floating_point Float>
class OctoTree
{
    using node_type = Node<Float>;
    using node_ptr  = Node<Float>*;
    using size_type = std::size_t;

    size_type depth_ = 0;
    node_ptr  root_  = nullptr;
private:
    static node_ptr build_octo_tree(const Geometry::Point<Float>& center, Float half_width, size_type stop_depth)
    {
        if (stop_depth == 0)
            return nullptr;

        node_ptr node = new node_type{center, half_width};

        Geometry::Point<Float> offset {};
        auto step = half_width * 0.5;

        for (int i = 0; i < Eight; i++)
        {
            offset.x_ = ((i & 1) ? step : -step);
            offset.y_ = ((i & 2) ? step : -step);
            offset.z_ = ((i & 4) ? step : -step);
            node->children_[i] = build_octo_tree(center + offset, step, stop_depth - 1);
        }
        return node;
    }
public:
    OctoTree(const Geometry::Point<Float>& center, Float half_width, size_type depth)
    :depth_ {depth}, root_ {build_octo_tree(center, half_width, depth)}
    {}

    bool empty() const
    {
        return (depth_ == 0);
    }

    void descriptor_dump(std::fstream& file) const
    {
        file << "\tTree [fillcolor=purple, label = \"{ OctoTree\\ndescriptor| depth: " << depth_ <<
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

        if (!node->childless())
            for (auto i = 0; i < Eight; i++)
                dump_node(file, node->children_[i]);
    }

    static void connect_nodes(std::fstream& file, node_ptr node)
    {
        if (node->childless())
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