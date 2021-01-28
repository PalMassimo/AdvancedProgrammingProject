#include "../include/bst.h"

template <typename K, typename V>
bst<K, V>::bst() : _root{nullptr} {};

template <typename K, typename V>
bst<K, V>::bst(node &root) : _root{&root} {}

template <typename K, typename V>
void bst<K, V>::print_root()
{
    std::cout << "root key " << _root->_key << "\nroot value " << _root->_value << std::endl;
}

template <typename K, typename V>
typename bst<K, V>::iterator bst<K, V>::begin() noexcept
{
    node *current = _root;
    while (current->_left != nullptr)
        current = current->_left;

    return iterator{current};
}

template <typename K, typename V>
typename bst<K, V>::const_iterator bst<K, V>::begin() const noexcept
{
    node *current = _root;
    while (current->_left != nullptr)
        current = current->_left;

    return const_iterator{current};
}

template <typename K, typename V>
typename bst<K, V>::iterator bst<K, V>::end() noexcept { return iterator{nullptr}; }

template <typename K, typename V>
typename bst<K, V>::const_iterator bst<K, V>::end() const noexcept { return const_iterator{nullptr}; }

template <typename K, typename V>
std::pair<typename bst<K, V>::iterator, bool> bst<K, V>::insert(const std::pair<const K, V> &x)
{
    node *current = _root;
    if (current == nullptr)
    {
        _root = new node(x.first, x.second);
        _root->_parent = nullptr;
        return std::make_pair(iterator{_root}, true);
    }
    else
    {
        while (current != nullptr)
        {
            if (current->_key == x.first)
            {
                return std::make_pair(iterator{current}, false);
            }
            else if (current->_key > x.first)
            {
                if (current->_left == nullptr)
                {
                    current->_left = new node(x.first, x.second);
                    current->_left->_parent=current;
                    return std::make_pair(iterator{current->_left}, true);
                }
                current = current->_left;
            }
            else
            { //current->_key < x.first
                if (current->_right == nullptr)
                {
                    current->_right = new node(x.first, x.second);
                    current->_right->_parent=current;
                    return std::make_pair(iterator{current->_right}, true);
                }
                current = current->_right;
            }
        }
    }
    return std::make_pair(iterator{nullptr}, false);
}

template <typename K, typename V>
std::pair<typename bst<K, V>::iterator, bool> bst<K, V>::insert(std::pair<const K, V> &&x)
{
   node *current = _root;
    if (current == nullptr)
    {
        _root = new node(x.first, x.second);
        _root->_parent = nullptr;
        return std::make_pair(iterator{_root}, true);
    }
    else
    {
        while (current != nullptr)
        {
            if (current->_key == x.first)
            {
                return std::make_pair(iterator{current}, false);
            }
            else if (current->_key > x.first)
            {
                if (current->_left == nullptr)
                {
                    current->_left = new node(x.first, x.second);
                    current->_left->_parent=current;
                    return std::make_pair(iterator{current->_left}, true);
                }
                current = current->_left;
            }
            else
            { //current->_key < x.first
                if (current->_right == nullptr)
                {
                    current->_right = new node(x.first, x.second);
                    current->_right->_parent=current;
                    return std::make_pair(iterator{current->_right}, true);
                }
                current = current->_right;
            }
        }
    }
    return std::make_pair(iterator{nullptr}, false);
}

