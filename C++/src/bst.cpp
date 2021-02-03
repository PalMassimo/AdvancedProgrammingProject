#include <vector>
#include "../include/bst.hpp"

template <typename K, typename V, typename comparator>
bst<K, V, comparator>::bst(const bst &b)
{
    if (b._root == nullptr)
    {
        _root.reset(nullptr);
    }
    else
    {
        _root.reset(new Node(b._root->_pair));
        copy(_root.get(), b._root.get());
    }
}

template <typename K, typename V, typename comparator>
bst<K, V, comparator>::bst(const comparator &cmp): _cmp{cmp} {}

template <typename K, typename V, typename comparator>
void bst<K, V, comparator>::copy(Node *n, Node *m)
{
    if (m->_right != nullptr)
    {
        n->_right.reset(new Node(n, m->_right->_pair));
        copy(n->_right.get(), m->_right.get());
    }
    if (m->_left != nullptr)
    {
        n->_left.reset(new Node(n, m->_left->_pair));
        copy(n->_left.get(), m->_left.get());
    }
}

template <typename K, typename V, typename comparator>
typename bst<K, V, comparator>::iterator bst<K, V, comparator>::begin() noexcept
{
    if (_root == nullptr)
        return iterator{nullptr};

    Node *_current = _root.get();
    while (_current->_left != nullptr)
        _current = _current->_left.get();

    return iterator{_current};
}

template <typename K, typename V, typename comparator>
typename bst<K, V, comparator>::const_iterator bst<K, V, comparator>::begin() const noexcept
{
    if (_root == nullptr)
        return const_iterator{nullptr};

    Node *_current = _root.get();
    while (_current->_left != nullptr)
        _current = _current->_left.get();

    return const_iterator{_current};
}

template <typename K, typename V, typename comparator>
typename bst<K, V, comparator>::const_iterator bst<K, V, comparator>::cbegin() const noexcept
{
    if (_root == nullptr)
        return const_iterator{nullptr};

    Node *_current = _root.get();
    while (_current->_left != nullptr)
        _current = _current->_left.get();

    return const_iterator{_current};
}

template <typename K, typename V, typename comparator>
typename bst<K, V, comparator>::iterator bst<K, V, comparator>::end() noexcept { return iterator{nullptr}; }

template <typename K, typename V, typename comparator>
typename bst<K, V, comparator>::const_iterator bst<K, V, comparator>::end() const noexcept { return const_iterator{nullptr}; }

template <typename K, typename V, typename comparator>
typename bst<K, V, comparator>::const_iterator bst<K, V, comparator>::cend() const noexcept { return const_iterator{nullptr}; }

template <typename K, typename V, typename comparator>
std::pair<typename bst<K, V, comparator>::iterator, bool> bst<K, V, comparator>::insert(const std::pair<const K, V> &x)
{
    Node *_current = _root.get();
    if (_current == nullptr)
    {
        _root.reset(new Node(x));
        return std::make_pair(iterator{_root.get()}, true);
    }
    else
    {
        while (_current != nullptr)
        {
            if (!cmd(_current->_pair.first,x.first) && !cmd(x.first, _current->_pair.first))
            {
                return std::make_pair(iterator{_current}, false);
            }
            else if (_cmp(x.first, _current->_pair.first))
            {
                if (_current->_left == nullptr)
                {
                    _current->_left.reset(new Node(_current, x));
                    return std::make_pair(iterator{_current->_left.get()}, true);
                }
                _current = _current->_left.get();
            }
            else
            { //_current->_key < x.first
                if (_current->_right == nullptr)
                {
                    _current->_right.reset(new Node(_current, x));
                    return std::make_pair(iterator{_current->_right.get()}, true);
                }
                _current = _current->_right.get();
            }
        }
    }
    return std::make_pair(iterator{nullptr}, false);
}

template <typename K, typename V, typename comparator>
std::pair<typename bst<K, V, comparator>::iterator, bool> bst<K, V, comparator>::insert(std::pair<const K, V> &&x)
{
    Node *_current = _root.get();
    if (_current == nullptr)
    {
        _root.reset(new Node(x));
        return std::make_pair(iterator{_root.get()}, true);
    }
    else
    {
        while (_current != nullptr)
        {
            if (!_cmp(_current->_pair.first, x.first) && !_cmp(x.first, _current->_pair.first))
            {
                return std::make_pair(iterator{_current}, false);
            }
            else if (_cmp(x.first, _current->_pair.first))
            {
                if (_current->_left == nullptr)
                {
                    _current->_left.reset(new Node(_current, x));
                    return std::make_pair(iterator{_current->_left.get()}, true);
                }
                _current = _current->_left.get();
            }
            else //_current->_key < x.first
            {
                if (_current->_right == nullptr)
                {
                    _current->_right.reset(new Node(_current, x));
                    return std::make_pair(iterator{_current->_right.get()}, true);
                }
                _current = _current->_right.get();
            }
        }
    }
    return std::make_pair(iterator{nullptr}, false);
}

template <typename K, typename V, typename comparator>
template <class... Types>
std::pair<typename bst<K, V, comparator>::iterator, bool> bst<K, V, comparator>::emplace(Types &&...args)
{
    return (*this).insert({std::forward<Types>(args)...});
}

template <typename K, typename V, typename comparator>
void bst<K, V, comparator>::erase_root()
{

    if (_root->_right == nullptr && _root->_left == nullptr) // root has no children
    {
        _root.reset(nullptr);
        return;
    }
    else if (_root->_right != nullptr && _root->_left == nullptr)
    {
        _root.swap(_root->_right);
        _root->_parent->_right.reset(nullptr);
        _root->_parent = nullptr;
    }
    else if (_root->_right == nullptr && _root->_left != nullptr)
    {
        _root.swap(_root->_left);
        _root->_parent->_left.reset(nullptr);
        _root->_parent = nullptr;
    }
    else //the root has both right child and left child
    {
        Node *rightest_child = _root->_left.get();
        while (rightest_child->_right != nullptr)
            rightest_child = rightest_child->_right.get();
        rightest_child->_right.reset(_root->_right.get());

        _root->_right->_parent = rightest_child;
        _root->_left->_parent = nullptr;
        // _root.reset(_root->_right.get());
    }
}

template <typename K, typename V, typename comparator>
void bst<K, V, comparator>::erase(const K &x)
{

    iterator it = find(x);

    if (it == end()) // doesn't exist a node with key value x
        return;
    else
    {
        if (it._current->_parent == nullptr) //node is the root
        {
            erase_root();
            return;
        }

        //node has no children
        if (it._current->_right == nullptr && it._current->_left == nullptr)
        {
            (it._current == it._current->_parent->_right.get()) ? it._current->_parent->_right.reset() : it._current->_parent->_left.reset();
            return;
        }

        //node having only left child and it is the left child of the parent
        if (it._current->_left != nullptr && it._current->_right == nullptr && it._current == it._current->_parent->_left.get())
        {
            it._current->_left->_parent = it._current->_parent;
            it._current->_parent->_left.swap(it._current->_left);
            it._current->_left.reset(nullptr);
            return;
        }

        //node having only right child and it is the left child of the parent
        if (it._current->_left == nullptr && it._current->_right != nullptr && it._current == it._current->_parent->_left.get())
        {
            it._current->_right->_parent = it._current->_parent;
            it._current->_parent->_left.swap(it._current->_right);
            it._current->_right.reset(nullptr);
            return;
        }

        //node having only right child and it is the right child of the parent
        if (it._current->_left == nullptr && it._current->_right != nullptr && it._current == it._current->_parent->_right.get())
        {

            it._current->_right->_parent = it._current->_parent;
            it._current->_parent->_right.swap(it._current->_right);
            it._current->_right.reset(nullptr);
            return;
        }

        //node having only left child and it is the right child of the parent
        if (it._current->_left != nullptr && it._current->_right == nullptr && it._current == it._current->_parent->_right.get())
        {
            it._current->_left->_parent = it._current->_parent;
            it._current->_parent->_right.swap(it._current->_left);
            it._current->_left.reset(nullptr);
            return;
        }

        //the node has two child and it is the right child of parent
        if (it._current->_right != nullptr && it._current->_left != nullptr && it._current == it._current->_parent->_right.get())
        {
            Node *rightest_child = it._current->_left.get();

            while (rightest_child->_right != nullptr)
                rightest_child = rightest_child->_right.get();
            rightest_child->_right.reset(it._current->_right.get());

            it._current->_right->_parent = rightest_child;

            //link parents's right node to the current's left child 
            it._current->_left->_parent = it._current->_parent;
            it._current->_parent->_right.swap(it._current->_left);
            return;
        }

        //the node has two child and it is the left child of parent
        if (it._current->_right != nullptr && it._current->_left != nullptr && it._current == it._current->_parent->_left.get())
        {
            it._current->_left->_parent = it._current->_parent;
            it._current->_parent->_left.swap(it._current->_left);
            it._current->_left.reset(nullptr);

            Node *rightest_child = it._current->_left.get();

            while (rightest_child->_right != nullptr)
                rightest_child = rightest_child->_right.get();
            rightest_child->_right.reset(it._current->_right.get());

            it._current->_right->_parent = rightest_child;

            return;
        }

        return;
    }
}

template <typename K, typename V, typename comparator>
void bst<K, V, comparator>::clear()
{
    for (_iterator<int> it = (*this).begin(); it != (*this).end();)
    {
        auto a = *it;
        ++it;
        erase(a);
    }
}

template <typename K, typename V, typename comparator>
typename bst<K, V, comparator>::iterator bst<K, V, comparator>::find(const K &x)
{
    for (_iterator<int> it = (*this).begin(); it != (*this).end(); it++)
    {
        if ((*it) == x)
            return it;
    }

    return _iterator<K>{nullptr};
}

template <typename K, typename V, typename comparator>
typename bst<K, V, comparator>::const_iterator bst<K, V, comparator>::find(const K &x) const
{
    for (const_iterator it = (*this).begin(); it != (*this).end(); it++)
    {
        if ((*it) == x)
            return it;
    }

    return const_iterator{nullptr};
}

template <typename K, typename V, typename comparator>
void bst<K, V, comparator>::divide_and_build(std::vector<std::pair<K, V>> values)
{
    if (values.size() == 1)
    {
        insert(values.at(0));
        return;
    }
    else
    {
        std::size_t half = values.size() / 2;
        insert(values.at(half));

        std::vector<std::pair<K, V>> left_values{}, right_values{};
        for (std::size_t i = 0; i < half; i++)
        {
            left_values.push_back(values.at(i));
            right_values.push_back(values.at(values.size() - 1 - i));
        }

        divide_and_build(left_values);
        divide_and_build(right_values);
    }
}

template <typename K, typename V, typename comparator>
void bst<K, V, comparator>::balance()
{

    // tree is empty
    if (_root == nullptr)
    {
        return;
    }

    std::vector<std::pair<K, V>> values{};

    //populate the array of node pointers
    for (_iterator<int> it = (*this).begin(); it != (*this).end(); it++)
    {
        values.push_back(it._current->_pair);
    }

    //delete the tree
    (*this).clear();

    divide_and_build(values);
}
