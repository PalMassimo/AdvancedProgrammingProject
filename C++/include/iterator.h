#pragma once
/**
 * iterator class
*/

template <typename K, typename V, typename comparator>
template <typename O>
class bst<K, V, comparator>::_iterator
{
public:
    using Node = node<K, V>;
    /**
     * node pointer pointing the current tree node the iterator is iterator through
    */
    Node *current;

public:
    using value_type = O;
    using reference = value_type &;
    using pointer = value_type *;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    /**
     * Iterator constructor taking a node pointer. The iterator will point to this node. 
     */
    _iterator(Node *n) : current{n} {}

    /**
     * Dereference operator overloading
     */ 
    reference operator*() const { return current->_pair.first; }

    /**
     * Member accer operator overloading
     */ 
    pointer operator->() const { return &**this; }

    /**
     * Pre increment operator overloading 
    */
    _iterator &operator++()
    {

        if (current->_right.get() == nullptr)
        {
            while (current->_parent != nullptr && current == current->_parent->_right.get())
                current = current->_parent;
            current = current->_parent;
        }
        //se ci sono nodi a destra ci sono sicuramente altri nodi su cui iterare
        else
        {
            current = current->_right.get();
            while (current->_left.get() != nullptr)
                current = current->_left.get();
        }

        return *this;
    }

    /**
     * Post increment operator overloading
    */
    _iterator operator++(int)
    {
        auto tmp{*this};
        ++(*this);
        return tmp;
    }

    /**
     * Equality operator overloading. Both arguments are lvalues
    */
    friend bool operator==(_iterator &a, _iterator &b) { return a.current == b.current; }

    /**
     * Equality operator overloading. The first argument is an lvalue, the second a right value
    */
    friend bool operator==(_iterator &a, _iterator &&b) { return a.current == b.current; }

    /**
     * Inequality operator overloading. Both arguments are lvalues
    */
    friend bool operator!=(_iterator &a, _iterator &b) { return !(a == b); }

    /**
     * Inequality operator overloading. The first argument is an lvalue, the second a right value
    */
    friend bool operator!=(_iterator &a, _iterator &&b) { return !(a == b); }
};
