#pragma once
#include <array>
#include <fstream>
#include <vector>
#include "bounding_box.hpp"

namespace Geometry
{
template<std::floating_point Float>
using Bound = BoundingBox<Float>;

constexpr int Eight = 8;
namespace detail
{
template<std::floating_point Float>
struct Node
{
    using node_ptr = Node*;

    Point<Float> center_ {};
    Float half_width_ = 0;
    std::array<node_ptr, Eight> children_ {};
    std::vector<Bound<Float>> bounds_ {};

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
    using node_type = detail::Node<Float>;
    using node_ptr       = detail::Node<Float>*;
    using const_node_ptr = const detail::Node<Float>*;
    using size_type  = std::size_t;
    using value_type = Bound<Float>;
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

    OctoTree(const Point<Float>& center, Float half_width, size_type depth)
    :depth_ {depth}
    {
        OctoTree tmp {};
        tmp.depth_ = depth;
        tmp.root_  = build_octo_tree(center, half_width, depth);
        swap(tmp);
    }

    template<std::input_iterator InpIt>
    OctoTree(InpIt begin, InpIt end)
    {
        auto [space_box, num_of_shapes] = compute_space_box_and_size(begin, end);
        auto depth = calculate_depth(num_of_shapes);
        OctoTree tmp (space_box.first, space_box.second, depth);
        tmp.insert(begin, end);
        swap(tmp);
    }

private:
    static node_ptr build_octo_tree(const Point<Float>& center, Float half_width, size_type stop_depth)
    {
        if (stop_depth == 0)
            return nullptr;

        node_ptr node = new node_type{center, half_width};

        Point<Float> offset {};
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

    using SpaceBox = std::pair<Point<Float>, Float>;

    template<std::input_iterator InpIt>
    static std::pair<SpaceBox, size_type> compute_space_box_and_size(InpIt first, InpIt last)
    {
        if (first == last)
            return {};
        size_type num_of_shapes = 1;
        auto [center_box, hw_box_x, hw_box_y, hw_box_z] = compute_box(*first++);
        auto min_x = center_box.x_ - hw_box_x, max_x = center_box.x_ + hw_box_x;
        auto min_y = center_box.y_ - hw_box_y, max_y = center_box.y_ + hw_box_y;
        auto min_z = center_box.z_ - hw_box_z, max_z = center_box.z_ + hw_box_z;

        while (first != last)
        {
            auto [center, hw_x, hw_y, hw_z] = compute_box(*first++);
            num_of_shapes++;
            const auto& act_min_x = center.x_ - hw_x, act_max_x = center.x_ + hw_x;
            const auto& act_min_y = center.y_ - hw_y, act_max_y = center.y_ + hw_y;
            const auto& act_min_z = center.z_ - hw_z, act_max_z = center.z_ + hw_z;
            
            if (act_min_x < min_x) min_x = act_min_x;
            if (act_min_y < min_y) min_y = act_min_y;
            if (act_min_z < min_z) min_z = act_min_z;

            if (act_max_x > max_x) max_x = act_max_x;
            if (act_max_y > max_y) max_y = act_max_y;
            if (act_max_z > max_z) max_z = act_max_z;
        }

        return {{Point{(max_x + min_x) * 0.5, (max_y + min_y) * 0.5, (max_z + min_z) * 0.5},
                std::max({max_x - min_x, max_y - min_y, max_z - min_z}) * 0.5}, num_of_shapes};
    }

    static size_type calculate_depth(size_type num_of_shapes)
    {
        if (num_of_shapes == 0)
            return 0;
        constexpr size_type MAX_SIZE = 6;
        return std::min(static_cast<size_type>(log2(static_cast<double>(num_of_shapes)) / 3.0 + 1.0), MAX_SIZE);
    }

public:
    bool empty() const {return (depth_ == 0);}
    size_type depth() const {return depth_;}
    const_node_ptr root() const {return root_;}

    void insert(const Shape<Float>& shape, ShapeIndT shape_index)
    {
        insert_bound(root_, make_bound(shape, shape_index));
    }

private:
    template<std::input_iterator InpIt>
    void insert(InpIt first, InpIt last)
    {
        ShapeIndT index = 0;
        while (first != last)
            insert(*first++, index++);
    }

    static std::pair<bool, int> straddle_compute(node_ptr node, const_reference bound)
    {
        Float delta = 0.0;
        int index = 0;

        delta = bound.center().x_ - node->center_.x_;
        if (std::abs(delta) < bound.half_width_x())
            return {true, index};
        if (delta > 0.0)
            index |= (1 << 0);

        delta = bound.center().y_ - node->center_.y_;
        if (std::abs(delta) < bound.half_width_y())
            return {true, index};
        if (delta > 0.0)
            index |= (1 << 1);

        delta = bound.center().z_ - node->center_.z_;
        if (std::abs(delta) < bound.half_width_z())
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

    void recursive_intersection(node_ptr node, IndexesContainer& indexes) const
    {
        static std::vector<node_ptr> ancestors {};

        ancestors.push_back(node);

        for (auto ancestor: ancestors)
            for (const auto& bound_a: ancestor->bounds_)
                for (const auto& bound_b: node->bounds_)
                    if (bound_a.shape_index() != bound_b.shape_index() && are_intersecting(bound_a, bound_b))
                        indexes.insert({bound_a.shape_index(), bound_b.shape_index()});

        if (!node->childless())
            for (auto child: node->children_)
                recursive_intersection(child, indexes);

        ancestors.pop_back();
    }

public:
    IndexesContainer find_all_intersections() const
    {
        IndexesContainer indexes {};
        recursive_intersection(root_, indexes);
        return indexes;
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