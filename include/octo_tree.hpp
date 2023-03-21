#pragma once
#include <array>
#include <list>
#include <fstream>
#include <unordered_set>
#include <vector>
#include "bounding_sphere.hpp"

namespace Task
{

using IndexsContainer = std::unordered_set<std::size_t>;

constexpr int Eight = 8;
namespace detail
{
template<std::floating_point Float>
struct Node
{
    using node_ptr = Node*;

    Geometry::Point<Float> center_ {};
    Float half_width_ = 0;
    std::array<node_ptr, Eight> children_ {};
    std::vector<Geometry::BoundingSphere<Float>> bounds_ {};

    bool childless() const
    {
        return (children_[0] == nullptr);
    }

    void dump(std::fstream& file)
    {
        file << "Node_" << this << "[color=brown, fillcolor=lightgreen, fontcolor=black" << ", label = \"{<_node_>ptr:\\n " << this
        << "| center: " << center_ << "| half width: " << half_width_<< "| bounds: ";
        for (auto x: bounds_)
            file << x << "\\n";
        file << "| {";
        for (int i = 0; i < Eight - 1; i++)
            file << "<" << i << ">" << i << ": \\n " << children_[i] << "| ";
        file << "<" << Eight - 1 << ">" << Eight - 1 << ": \\n " << children_[Eight - 1]; 
        file << "}}\"];" << std::endl;
    }
};

} // namespace detail

template<std::floating_point Float>
class OctoTree final
{
    using node_type  = detail::Node<Float>;
    using node_ptr   = detail::Node<Float>*;
    using size_type  = std::size_t;
    using value_type = Geometry::BoundingSphere<Float>;
    using reference  = value_type&;
    using const_reference = const value_type&;
    
    size_type depth_ = 0;
    node_ptr  root_  = nullptr;
public:
    OctoTree() = default;
private:
    void swap(OctoTree& other)
    {
        std::swap(depth_, other.depth_);
        std::swap(root_, other.root_);
    }
public:
    OctoTree(OctoTree&& other) noexcept
    {
        swap(other);
    }

    OctoTree& operator=(OctoTree&& rhs) noexcept
    {
        swap(rhs);
        return *this;
    }

private:
    static void destruct(node_ptr node)
    {
        if (node == nullptr)
            return;

        for (auto child: node->children_)
            destruct(child);

        delete node;
    }

public:
    ~OctoTree() {destruct(root_);}

private:
    static node_ptr build_octo_tree(const Geometry::Point<Float>& center, Float half_width, size_type stop_depth)
    {
        if (stop_depth == 0)
            return nullptr;

        node_ptr node = new node_type{center, half_width};

        Geometry::Point<Float> offset {};
        auto step = half_width * 0.5;

        for (auto i = 0; i < Eight; i++)
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
    :depth_ {depth}
    {
        OctoTree tmp {};
        tmp.depth_ = depth;
        tmp.root_  = build_octo_tree(center, half_width, depth);
        swap(tmp);
    }

    bool empty() const
    {
        return (depth_ == 0);
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

private:
    static std::pair<bool, int> straddle_compute(node_ptr node, const_reference bound)
    {
        Float delta = 0.0;
        int index = 0;

        delta = bound.center().x_ - node->center_.x_;
        if (std::abs(delta) < bound.radius())
            return {true, index};
        if (delta > 0.0)
            index |= (1 << 0);

        delta = bound.center().y_ - node->center_.y_;
        if (std::abs(delta) < bound.radius())
            return {true, index};
        if (delta > 0.0)
            index |= (1 << 1);

        delta = bound.center().z_ - node->center_.z_;
        if (std::abs(delta) < bound.radius())
            return {true, index};
        if (delta > 0.0)
            index |= (1 << 2);

        return {false, index};
    }

    void insert_bound(node_ptr node, const_reference bound)
    {
        auto [straddle, index] = straddle_compute(node, bound);

        if (!straddle && node->children_[index])
            insert_bound(node->children_[index], bound);
        else
            node->bounds_.push_back(bound);
    }
public:
    void insert(const Geometry::Shape<Float>& shape, std::size_t shape_index)
    {
        insert_bound(root_, make_bound(shape, shape_index));
    }

    template<std::forward_iterator FwdIt>
    void insert(FwdIt first, FwdIt last)
    {
        std::size_t index = 0;
        while (first != last)
            insert(*first++, index++);
    }
private:
    void recursive_intersection(node_ptr node, IndexsContainer& indexs) const
    {
        static std::vector<node_ptr> ancestors {};

        ancestors.push_back(node);

        for (auto ancestor: ancestors)
            for (const auto& bound_a: ancestor->bounds_)
                for (const auto& bound_b: node->bounds_)
                    if (bound_a.shape_index() != bound_b.shape_index() && Geometry::are_intersecting(bound_a.shape(), bound_b.shape()))
                        indexs.insert({bound_a.shape_index(), bound_b.shape_index()});

        if (!node->childless())
            for (auto child: node->children_)
                recursive_intersection(child, indexs);

        ancestors.pop_back();
    }

public:
    IndexsContainer intersect_all() const
    {
        IndexsContainer indexs {};
        recursive_intersection(root_, indexs);
        return indexs;
    }

private:
    void descriptor_dump(std::fstream& file) const
    {
        file << "\tTree [fillcolor=purple, label = \"{ OctoTree\\ndescriptor| depth: " << depth_ <<
        "| <root> root:\\n " << root_ << "}\"];" << std::endl;
    }

    static void dump_node(std::fstream& file, node_ptr node)
    {
        node->dump(file);

        if (node->childless())
            return;

        for (auto child: node->children_)
            dump_node(file, child);
    }

    static void connect_nodes(std::fstream& file, node_ptr node)
    {
        if (node->childless())
            return;

        auto i = 0;
        for (auto child: node->children_)
            file << "Node_" << node << ":" << i++ << ":s -> Node_" << child << ":_node_:n;" << std::endl;

        for (auto child: node->children_)
            connect_nodes(file, child);
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