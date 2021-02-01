#pragma once
#include <memory>

namespace node
{
    template <typename K, typename V>
    struct node
    {
    private:
        node *_parent;
        std::unique_ptr<node> _right;
        std::unique_ptr<node> _left;

        std::pair<K, V> _pair;

    public:
        node() = default;

        node(std::pair<K, V> a_pair) : _parent{nullptr}, _right{}, _left{}, _pair{a_pair} {}

        node(node *parent, std::pair<K, V> a_pair) : _parent{parent}, _right{}, _left{}, _pair{a_pair} {}

        ~node() = default;
    };

} // namespace node