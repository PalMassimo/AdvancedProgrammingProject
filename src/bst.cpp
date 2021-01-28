#include "../include/bst.h"

template <typename K, typename V>
bst<K, V>::bst() : _root{nullptr} {};
// bst<K, V>::bst() = default;

template <typename K, typename V>
bst<K, V>::bst(node &root) : _root{&root} {}

template <typename K, typename V>
void bst<K, V>::print_root()
{
    std::cout << "root key " << _root->_key << "\nroot value " << _root->_value << std::endl;
}

template <typename K, typename V>
std::pair<typename bst<K, V>::iterator, bool> bst<K, V>::insert(const std::pair<const K, V> &x)
{
    node *current = _root;
    if (current == nullptr)
    {
        _root = new node(x.first, x.second);
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
                    return std::make_pair(iterator{current->_left}, true);
                }
                current = current->_left;
            }
            else
            { //current->_key < x.first
                if (current->_right == nullptr)
                {
                    current->_right = new node(x.first, x.second);
                    return std::make_pair(iterator{current->_right}, true);
                }
                current = current->_right;
            }
        }
    }
    return std::make_pair(iterator{nullptr}, false);
}

template <typename K, typename V>
std::pair<typename bst<K, V>::iterator, bool> insert(std::pair<const K, V>&& x)
{
    node *current = _root;
    if (current == nullptr)
    {
        _root = new node(x.first, x.second);
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
                    return std::make_pair(iterator{current->_left}, true);
                }
                current = current->_left;
            }
            else
            { //current->_key < x.first
                if (current->_right == nullptr)
                {
                    current->_right = new node(x.first, x.second);
                    return std::make_pair(iterator{current->_right}, true);
                }
                current = current->_right;
            }
        }
    }
    return std::make_pair(iterator{nullptr}, false);
}

