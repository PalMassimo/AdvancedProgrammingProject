#pragma once
#include <memory>

/**
 * 
 * The struct node implementing the concept of tree node.
 * It consists of a pair of a key and a value.
 * */

template <typename K, typename V>
struct node
{
public:
    /**
     * raw pointer pointing his parent node. The only node without a parent is the root node
    */
    node *_parent;

    /**
     * unique pointer pointing the left child of node
     */
    std::unique_ptr<node> _right;
    /**
     * unique pointer pointing the right child of node
     */
    std::unique_ptr<node> _left;

    /**
     * content of the node
     */
    std::pair<K, V> _pair;

public:
    /**
     * node constructor without argument
    */
    node() noexcept = default;

    /**
     * node constructor taking a pair as argument. A node linked to no other node is initialized with content passed as argument
     */ 
    explicit node(const std::pair<K, V>& a_pair) : _parent{nullptr}, _right{}, _left{}, _pair{a_pair} {}

    /**
     * node constructor having as content the one passed to parameter, and having as parent the pointer passed as argument
     */ 
    explicit node(node *parent, const std::pair<K, V>& a_pair) : _parent{parent}, _right{}, _left{}, _pair{a_pair} {}

    /**
     * node deconstructor 
     */ 
    ~node() noexcept = default;
};
