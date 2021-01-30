#include "../include/bst.h"

template <typename K, typename V>
bst<K, V>::bst() {_root.reset(nullptr);}

// template <typename K, typename V>
// bst<K, V>::bst(node &root) : _root{&root} {}

template <typename K, typename V>
//bst<K, V>::bst(node &root) : _root{new node(root)} {}
bst<K, V>::bst(node &root) { _root=std::make_unique<node>(root); }


template <typename K, typename V>
void bst<K, V>::print_root()
{
    std::cout << "root key " << _root.get()->_key << "\nroot value " << _root.get()->_value << std::endl;
}

template <typename K, typename V>
typename bst<K, V>::iterator bst<K, V>::begin() noexcept
{
    node *current = _root.get();
    while (current->_left != nullptr)
        current = current->_left;

    return iterator{current};
}

template <typename K, typename V>
typename bst<K, V>::const_iterator bst<K, V>::begin() const noexcept
{
    node *current = _root.get();
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
    node *current = _root.get();
    if (current == nullptr)
    {
        _root.reset(new node(x.first, x.second));
        _root.get()->_parent = nullptr;
        return std::make_pair(iterator{_root.get()}, true);
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
                    current->_left->_parent = current;
                    return std::make_pair(iterator{current->_left}, true);
                }
                current = current->_left;
            }
            else
            { //current->_key < x.first
                if (current->_right == nullptr)
                {
                    current->_right = new node(x.first, x.second);
                    current->_right->_parent = current;
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
    node *current = _root.get();
    if (current == nullptr)
    {
        _root.reset(new node(x.first, x.second));
        _root.get()->_parent = nullptr;
        return std::make_pair(iterator{_root.get()}, true);
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
                    current->_left->_parent = current;
                    return std::make_pair(iterator{current->_left}, true);
                }
                current = current->_left;
            }
            else
            { //current->_key < x.first
                if (current->_right == nullptr)
                {
                    current->_right = new node(x.first, x.second);
                    current->_right->_parent = current;
                    return std::make_pair(iterator{current->_right}, true);
                }
                current = current->_right;
            }
        }
    }
    return std::make_pair(iterator{nullptr}, false);
}

template <typename K, typename V>
void bst<K, V>::erase(const K &x)
{

    iterator it = find(x);

    if (it == end())
        return;
    else
    {
        //node is the root
        if (it.current->_parent == nullptr)
        {

            if (it.current->_left == nullptr && it.current->_right == nullptr)
            {
                _root.reset(nullptr);
            }
            else if (it.current->_left == nullptr)
            {
                it.current->_right->_parent = nullptr;
                _root.reset(it.current->_right);
            }
            else if (it.current->_right == nullptr)
            {
                it.current->_left->_parent = nullptr;
                _root.reset(it.current->_left);
            }
            else
            {
                node *rightest_child = it.current->_left;

                while (rightest_child->_right != nullptr)
                    rightest_child = rightest_child->_right;
                rightest_child->_right = it.current->_right;

                it.current->_right->_parent = rightest_child;
                it.current->_left->_parent = nullptr;
            }
            return;
        }

        //node has no children
        if (it.current->_right == nullptr && it.current->_left == nullptr)
        {
            (it.current == it.current->_parent->_right) ? it.current->_parent->_right = nullptr : it.current->_parent->_left = nullptr;
            delete it.current;
            return;
        }

        //node having only left child and it is the left child of the parent
        if (it.current->_left != nullptr && it.current->_right == nullptr && it.current == it.current->_parent->_left)
        {
            it.current->_parent->_left = it.current->_left;
            it.current->_left->_parent = it.current->_parent;
            delete it.current;
            return;
        }

        //node having only right child and it is the left child of the parent
        if (it.current->_left == nullptr && it.current->_right != nullptr && it.current == it.current->_parent->_left)
        {
            it.current->_parent->_left = it.current->_right;
            it.current->_right->_parent = it.current->_parent;
            delete it.current;
            return;
        }

        //node having only right child and it is the right child of the parent
        if (it.current->_left == nullptr && it.current->_right != nullptr && it.current == it.current->_parent->_right)
        {
            it.current->_parent->_right = it.current->_right;
            it.current->_right->_parent = it.current->_parent;
            delete it.current;
            return;
        }

        //node having only left child and it is the right child of the parent
        if (it.current->_left != nullptr && it.current->_right == nullptr && it.current == it.current->_parent->_right)
        {
            it.current->_parent->_right = it.current->_left;
            it.current->_left->_parent = it.current->_parent;
            delete it.current;
            return;
        }

        //the node has two child and it is the right child of parent
        if (it.current->_right != nullptr && it.current->_left != nullptr && it.current == it.current->_parent->_right)
        {
            //colleghiamo il figlio di destra del parent al figlio di sinistra del nodo corrente
            it.current->_parent->_right = it.current->_left;
            it.current->_left->_parent = it.current->_parent;

            node *rightest_child = it.current->_left;

            while (rightest_child->_right != nullptr)
                rightest_child = rightest_child->_right;
            rightest_child->_right = it.current->_right;

            it.current->_right->_parent = rightest_child;

            delete it.current;
            return;
        }

        //the node has two child and it is the left child of parent
        if (it.current->_right != nullptr && it.current->_left != nullptr && it.current == it.current->_parent->_left)
        {
            //colleghiamo il figlio di destra del parent al figlio di sinistra del nodo corrente
            it.current->_parent->_left = it.current->_left;
            it.current->_left->_parent = it.current->_parent;

            node *rightest_child = it.current->_left;

            while (rightest_child->_right != nullptr)
                rightest_child = rightest_child->_right;
            rightest_child->_right = it.current->_right;

            it.current->_right->_parent = rightest_child;

            delete it.current;
            return;
        }

        std::cout << "if this point is reached at least one case is missing" << std::endl;
        return;
    }
}
template <typename K, typename V>
void bst<K, V>::clear()
{
    for (_iterator<int> it = (*this).begin(); it != (*this).end();)
    {
        auto a = *it;
        ++it;
        erase(a);
    }
}

template <typename K, typename V>
typename bst<K, V>::iterator bst<K, V>::find(const K &x)
{
    for (_iterator<int> it = (*this).begin(); it != (*this).end(); it++)
    {
        if ((*it) == x)
            return it;
    }

    return _iterator<K>{nullptr};
}
