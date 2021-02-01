#include "../include/bst.h"

// template <typename K, typename V>
// bst<K, V>::bst() { _root.reset(); }

template <typename K, typename V>
bst<K, V>::bst(node &root)
{
    _root.reset(&root);
}

template <typename K, typename V>
bst<K, V>::bst(const bst &b)
{ //copy ctor - deepcopy
    if (b._root == nullptr)
    {
        _root.reset(nullptr);
    }
    else
    {
        _root.reset(new node(b._root->_pair));
        copy(_root.get(), b._root.get());
    }
}

template <typename K, typename V>
void bst<K, V>::copy(node *n, node *m)
{
    if (m->_right != nullptr)
    {
        n->_right.reset(new node(n, m->_right->_pair));
        copy(n->_right.get(), m->_right.get());
    }
    if (m->_left != nullptr)
    {
        n->_left.reset(new node(n, m->_left->_pair));
        copy(n->_left.get(), m->_left.get());
    }
}

template <typename K, typename V>
typename bst<K, V>::iterator bst<K, V>::begin() noexcept
{
    if (_root == nullptr)
        return iterator{nullptr};

    node *current = _root.get();
    while (current->_left != nullptr)
        current = current->_left.get();

    return iterator{current};
}

template <typename K, typename V>
typename bst<K, V>::const_iterator bst<K, V>::begin() const noexcept
{
    if (_root == nullptr)
        return const_iterator{nullptr};

    node *current = _root.get();
    while (current->_left != nullptr)
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
        _root.reset(new node(x));
        return std::make_pair(iterator{_root.get()}, true);
    }
    else
    {
        while (current != nullptr)
        {
            if (current->_pair.first == x.first)
            {
                return std::make_pair(iterator{current}, false);
            }
            else if (current->_pair.first > x.first)
            {
                if (current->_left == nullptr)
                {
                    current->_left.reset(new node(x));
                    current->_left->_parent = current;
                    return std::make_pair(iterator{current->_left.get()}, true);
                }
                current = current->_left.get();
            }
            else
            { //current->_key < x.first
                if (current->_right == nullptr)
                {
                    current->_right.reset(new node(x));
                    current->_right->_parent = current;
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
        _root.reset(new node(x));
        return std::make_pair(iterator{_root.get()}, true);
    }
    else
    {
        while (current != nullptr)
        {
            if (current->_pair.first == x.first)
            {
                return std::make_pair(iterator{current}, false);
            }
            else if (current->_pair.first > x.first)
            {
                if (current->_left == nullptr)
                {
                    current->_left.reset(new node(x));
                    current->_left->_parent = current;
                    return std::make_pair(iterator{current->_left.get()}, true);
                }
                current = current->_left.get();
            }
            else
            { //current->_key < x.first
                if (current->_right == nullptr)
                {
                    current->_right.reset(new node(x));
                    current->_right->_parent = current;
                    return std::make_pair(iterator{current->_right.get()}, true);
                }
                current = current->_right.get();
            }
        }
    }
    return std::make_pair(iterator{nullptr}, false);
}

template <typename K, typename V>
void bst<K, V>::erase_root()
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
        node *rightest_child = _root->_left.get();
        while (rightest_child->_right != nullptr)
            rightest_child = rightest_child->_right.get();
        rightest_child->_right.reset(_root->_right.get());

        _root->_right->_parent = rightest_child;
        _root->_left->_parent = nullptr;
        // _root.reset(_root->_right.get());
    }
}

template <typename K, typename V>
void bst<K, V>::erase(const K &x)
{

    iterator it = find(x);

    if (it == end()) // doesn't exist a node with key value x
        return;
    else
    {
        if (it.current->_parent == nullptr) //node is the root
        {
            erase_root();
            return;
        }

        //node has no children
        if (it.current->_right == nullptr && it.current->_left == nullptr)
        {
            (it.current == it.current->_parent->_right.get()) ? it.current->_parent->_right.reset() : it.current->_parent->_left.reset();
            // delete it.current;
            return;
        }

        //node having only left child and it is the left child of the parent
        if (it.current->_left != nullptr && it.current->_right == nullptr && it.current == it.current->_parent->_left.get())
        {
            it.current->_left->_parent = it.current->_parent;
            it.current->_parent->_left.swap(it.current->_left);
            it.current->_left.reset(nullptr); //TODO: memory leak if not present?
            // delete it.current;
            return;
        }

        //node having only right child and it is the left child of the parent
        if (it.current->_left == nullptr && it.current->_right != nullptr && it.current == it.current->_parent->_left.get())
        {
            it.current->_right->_parent = it.current->_parent;
            it.current->_parent->_left.swap(it.current->_right);
            it.current->_right.reset(nullptr); //TODO: memory leak if not present?
            // delete it.current;
            return;
        }

        //node having only right child and it is the right child of the parent
        if (it.current->_left == nullptr && it.current->_right != nullptr && it.current == it.current->_parent->_right.get())
        {

            it.current->_right->_parent = it.current->_parent;
            it.current->_parent->_right.swap(it.current->_right);
            it.current->_right.reset(nullptr); //TODO: memory leak if not present?
            // delete it.current;
            return;
        }

        //node having only left child and it is the right child of the parent
        if (it.current->_left != nullptr && it.current->_right == nullptr && it.current == it.current->_parent->_right.get())
        {
            it.current->_left->_parent = it.current->_parent;
            it.current->_parent->_right.swap(it.current->_left);
            it.current->_left.reset(nullptr); //TODO: memory leak if not present?
            // delete it.current;
            return;
        }

        //the node has two child and it is the right child of parent
        if (it.current->_right != nullptr && it.current->_left != nullptr && it.current == it.current->_parent->_right.get())
        {
            node *rightest_child = it.current->_left.get();

            while (rightest_child->_right != nullptr)
                rightest_child = rightest_child->_right.get();
            rightest_child->_right.reset(it.current->_right.get());

            it.current->_right->_parent = rightest_child;

            //colleghiamo il figlio di destra del parent al figlio di sinistra del nodo corrente
            it.current->_left->_parent = it.current->_parent;
            it.current->_parent->_right.swap(it.current->_left);
            // it.current->_right.swap(it.current->_left->_right);
            // it.current->_right.reset(nullptr);
            // it.current->_left.reset(nullptr); //TODO: memory leak if not present?
            // delete it.current;
            return;
        }

        //the node has two child and it is the left child of parent
        if (it.current->_right != nullptr && it.current->_left != nullptr && it.current == it.current->_parent->_left.get())
        {
            //colleghiamo il figlio di destra del parent al figlio di sinistra del nodo corrente
            it.current->_left->_parent = it.current->_parent;
            it.current->_parent->_left.swap(it.current->_left);
            it.current->_left.reset(nullptr); //TODO: memory leak if not present?

            node *rightest_child = it.current->_left.get();

            while (rightest_child->_right != nullptr)
                rightest_child = rightest_child->_right.get();
            rightest_child->_right.reset(it.current->_right.get());

            it.current->_right->_parent = rightest_child;

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

template <typename K, typename V>
void bst<K, V>::divide_and_build(std::vector<std::pair<K, V>> values)
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

template <typename K, typename V>
void bst<K, V>::balance()
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
        values.push_back(it.current->_pair);
    }

    //delete the tree
    (*this).clear();

    divide_and_build(values);
}
