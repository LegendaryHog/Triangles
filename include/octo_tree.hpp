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
    Geometry::Shape<Float> shape_ {};
    Geometry::Point<Float> center_ {};
    Float radius_ = 0;
};

template<std::floating_point Float>
std::ostream& operator<<(std::ostream& out, const ObjectSphere<Float>& obj)
{
    return std::visit([&out](const auto& sh) -> std::ostream& {return (out << sh);}, obj.shape_);
}

namespace detail
{
template<std::floating_point Float>
ObjectSphere<Float> make_object(const Geometry::Point<Float>& p)
{
    return {p, p, 1e-6};
}

template<std::floating_point Float>
ObjectSphere<Float> make_object(const Geometry::Segment<Float>& seg)
{
    return {seg, (seg.F_ + seg.S_) * 0.5, Geometry::distance(seg.F_, seg.S_) * 0.5 + 1e-6};
}

template<std::floating_point Float>
ObjectSphere<Float> make_object(const Geometry::Triangle<Float>& tr)
{
    auto PQ = Geometry::distance(tr.P_, tr.Q_);
    auto QR = Geometry::distance(tr.Q_, tr.R_);
    auto RP = Geometry::distance(tr.R_, tr.P_);

    if (PQ > QR)
        if (PQ > RP)
            return {tr, tr.R_, std::max(QR, RP)};
        else
            return {tr, tr.Q_, std::max(PQ, QR)};
    else
        if (QR > RP)
            return {tr, tr.P_, std::max(RP, PQ)};
        else
            return {tr, tr.Q_, std::max(PQ, QR)};
}

}

template<std::floating_point Float>
ObjectSphere<Float> make_object(const Geometry::Shape<Float>& shape)
{
    return std::visit([](const auto& sh){return detail::make_object(sh);}, shape);
}

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
        << "| center: " << center_ << "| half width: " << half_width_<< "| objects: ";
        for (auto x: objects_)
            file << x << ", ";
        file << "| {";
        for (int i = 0; i < Eight - 1; i++)
            file << "<" << i << ">" << i << ": \\n " << children_[i] << "| ";
        file << "<" << Eight - 1 << ">" << Eight - 1 << ": \\n " << children_[Eight - 1]; 
        file << "}}\"];" << std::endl;
    }
};

template<std::floating_point Float>
class OctoTree final
{
    using node_type  = Node<Float>;
    using node_ptr   = Node<Float>*;
    using size_type  = std::size_t;
    using value_type = ObjectSphere<Float>;
    using pointer    = value_type*;
    using reference  = value_type&;
    using const_reference = const value_type&;
    using const_pointer   = const value_type*;

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
#if 0
    OctoTree(const OctoTree& other)
    :OctoTree(other.root_->center_, other.root_->half_width_, other.depth_)
    {

    }

    OctoTree& operator=(const OctoTree& rhs)
    {
        OctoTree tmp {rhs};
        swap(tmp);
        return *this;
    }
#endif
private:
    static void destruct(node_ptr node)
    {
        if (node == nullptr)
            return;

        for (auto i = 0; i < Eight; i++)
            destruct(node->children_[i]);

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

        for (int i = 0; i < Eight; i++)
        {
            offset.x_ = ((i & 1) ? step : -step);
            offset.y_ = ((i & 2) ? step : -step);
            offset.z_ = ((i & 4) ? step : -step);
            node->children_[i] = build_octo_tree(center + offset, step, stop_depth - 1);
        }
        return node;
    }
private:
    template<std::input_iterator InpIt>
    static std::tuple<Geometry::Point<Float>, Float, size_type>
    calculate_octo_tree(InpIt first, InpIt last)
    {
        Float min_coord = 0.0, max_coord = 0.0;
        size_type size = 0;
        while (first != last)
        {
            size++;
            
        }
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

    template<std::input_iterator InpIt>
    OctoTree(InpIt first, InpIt last)
    {

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
    std::pair<bool, int> straddle_compute(node_ptr node, const_reference obj)
    {
        Float delta = 0;
        int index = 0;

        delta = obj.center_.x_ - node->center_.x_;
        if (std::abs(delta) < node->half_width_ + obj.radius_)
            return {true, index};
        if (delta > 0.0)
            index |= (1 << 0);

        delta = obj.center_.y_ - node->center_.y_;
        if (std::abs(delta) < node->half_width_ + obj.radius_)
            return {true, index};
        if (delta > 0.0)
            index |= (1 << 1);

        delta = obj.center_.z_ - node->center_.z_;
        if (std::abs(delta) < node->half_width_ + obj.radius_)
            return {true, index};
        if (delta > 0.0)
            index |= (1 << 2);

        return {false, index};
    }

    void insert_object(node_ptr node, const_reference obj)
    {
        auto [straddle, index] = straddle_compute(node, obj);

        if (!straddle && node->children_[index])
            insert_object(node->children_[index], obj);
        else
            node->objects_.push_back(obj);
    }
public:
    void insert(const Geometry::Shape<Float>& shape)
    {
        insert_object(root_, make_object(shape));
    }

    template<std::forward_iterator FwdIt>
    void insert(FwdIt first, FwdIt last)
    {
        while (first != last)
            insert(*first++);
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