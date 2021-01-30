#include "../include/bst.h"

template <typename K, typename V>
bst<K, V>::bst() { _root.reset(nullptr); }

// template <typename K, typename V>
// bst<K, V>::bst(node &root) : _root{&root} {}

template <typename K, typename V>
bst<K, V>::bst(node root) : _root{new node(root._key, root._value)} {}
// bst<K, V>::bst(node root) : _root{std::make_unique<node>(root)}
// {
// }

template <typename K, typename V>
typename bst<K, V>::iterator bst<K, V>::begin() noexcept
{
    node *current = _root.get();
    while (current->_left.get() != nullptr)
        current = current->_left.get();

    return iterator{current};
}

template <typename K, typename V>
typename bst<K, V>::const_iterator bst<K, V>::begin() const noexcept
{
    node *current = _root.get();
    while (current->_left.get() != nullptr)
        current = current->_left.get();

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
        _root.get()->_parent.reset(nullptr);
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
                if (current->_left.get() == nullptr)
                {
                    current->_left.reset(new node(x.first, x.second));
                    current->_left.get()->_parent.reset(current);
                    return std::make_pair(iterator{current->_left.get()}, true);
                }
                current = current->_left.get();
            }
            else
            { //current->_key < x.first
                if (current->_right.get() == nullptr)
                {
                    current->_right.reset(new node(x.first, x.second));
                    current->_right.get()->_parent.reset(current);
                    return std::make_pair(iterator{current->_right.get()}, true);
                }
                current = current->_right.get();
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
        _root.get()->_parent.reset(nullptr);
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
                if (current->_left.get() == nullptr)
                {
                    current->_left.reset(new node(x.first, x.second));
                    current->_left.get()->_parent.reset(current);
                    return std::make_pair(iterator{current->_left.get()}, true);
                }
                current = current->_left.get();
            }
            else
            { //current->_key < x.first
                if (current->_right.get() == nullptr)
                {
                    current->_right.reset(new node(x.first, x.second));
                    current->_right.get()->_parent.reset(current);
                    return std::make_pair(iterator{current->_right.get()}, true);
                }
                current = current->_right.get();
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
        if (it.current->_parent.get() == nullptr)
        {

            if (it.current->_left.get() == nullptr && it.current->_right.get() == nullptr)
            {
                _root.reset(nullptr);
            }
            else if (it.current->_left.get() == nullptr)
            {
                it.current->_right.get()->_parent.reset(nullptr);
                _root.reset(it.current->_right.get());
            }
            else if (it.current->_right.get() == nullptr)
            {
                it.current->_left.get()->_parent.reset(nullptr);
                _root.reset(it.current->_left.get());
            }
            else
            {
                node *rightest_child = it.current->_left.get();

                while (rightest_child->_right.get() != nullptr)
                    rightest_child = rightest_child->_right.get();
                rightest_child->_right.reset(it.current->_right.get());

                it.current->_right.get()->_parent.reset(rightest_child);
                it.current->_left.get()->_parent.reset(nullptr);
            }
            return;
        }

        //node has no children
        if (it.current->_right.get() == nullptr && it.current->_left.get() == nullptr)
        {
            (it.current == it.current->_parent.get()->_right) ? it.current->_parent.get()->_right.reset(nullptr) : it.current->_parent.get()->_left.reset(nullptr);
            // delete it.current;
            return;
        }

        //node having only left child and it is the left child of the parent
        if (it.current->_left.get() != nullptr && it.current->_right.get() == nullptr && it.current == it.current->_parent.get()->_left)
        {
            it.current->_parent.get()->_left.reset(it.current->_left.get());
            it.current->_left.get()->_parent.reset(it.current->_parent.get());
            // delete it.current;
            return;
        }

        //node having only right child and it is the left child of the parent
        if (it.current->_left.get() == nullptr && it.current->_right.get() != nullptr && it.current == it.current->_parent.get()->_left)
        {
            it.current->_parent.get()->_left.reset(it.current->_right.get());
            it.current->_right.get()->_parent.reset(it.current->_parent.get());
            // delete it.current;
            return;
        }

        //node having only right child and it is the right child of the parent
        if (it.current->_left.get() == nullptr && it.current->_right.get() != nullptr && it.current == it.current->_parent.get()->_right)
        {
            it.current->_parent.get()->_right.reset(it.current->_right.get());
            it.current->_right.get()->_parent.reset(it.current->_parent.get());
            // delete it.current;
            return;
        }

        //node having only left child and it is the right child of the parent
        if (it.current->_left.get() != nullptr && it.current->_right.get() == nullptr && it.current == it.current->_parent.get()->_right)
        {
            it.current->_parent.get()->_right.reset(it.current->_left.get());
            it.current->_left.get()->_parent.reset(it.current->_parent.get());
            // delete it.current;
            return;
        }

        //the node has two child and it is the right child of parent
        if (it.current->_right.get() != nullptr && it.current->_left.get() != nullptr && it.current == it.current->_parent.get()->_right)
        {
            //colleghiamo il figlio di destra del parent al figlio di sinistra del nodo corrente
            it.current->_parent.get()->_right.reset(it.current->_left.get());
            it.current->_left.get()->_parent.reset(it.current->_parent.get());

            node *rightest_child = it.current->_left.get();

            while (rightest_child->_right.get() != nullptr)
                rightest_child = rightest_child->_right.get();
            rightest_child->_right.reset(it.current->_right.get());

            it.current->_right.get()->_parent.reset(rightest_child);

            // delete it.current;
            return;
        }

        //the node has two child and it is the left child of parent
        if (it.current->_right.get() != nullptr && it.current->_left.get() != nullptr && it.current == it.current->_parent.get()->_left)
        {
            //colleghiamo il figlio di destra del parent al figlio di sinistra del nodo corrente
            it.current->_parent.get()->_left.reset(it.current->_left.get());
            it.current->_left.get()->_parent.reset(it.current->_parent.get());

            node *rightest_child = it.current->_left.get();

            while (rightest_child->_right.get() != nullptr)
                rightest_child = rightest_child->_right.get();
            rightest_child->_right.reset(it.current->_right.get());

            it.current->_right.get()->_parent.reset(rightest_child);

            // delete it.current;
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
