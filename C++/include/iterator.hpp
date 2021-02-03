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
     * pointer pointing to the current tree node through the iteration
    */
    Node *_current;

public:
    using value_type = O;
    using reference = value_type &;
    using pointer = value_type *;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    /**
     * iterator constructor taking a node pointer. The iterator will point to this node
     */
    explicit _iterator(Node *n) noexcept: _current{n} {}

    /**
     * iterator destructor
     */
    ~_iterator() noexcept = default;

    /**
     * dereference operator overloading
     */ 
    reference operator*() const noexcept { return _current->_pair.first; }

    /**
     * member access operator overloading
     */ 
    pointer operator->() const noexcept { return &**this; }

    /**
     * pre increment operator overloading 
    */
    _iterator &operator++() noexcept
    {

        if (_current->_right.get() == nullptr)
        {
            while (_current->_parent != nullptr && _current == _current->_parent->_right.get())
                _current = _current->_parent;
            _current = _current->_parent;
        }
        else
        {
            _current = _current->_right.get();
            while (_current->_left.get() != nullptr)
                _current = _current->_left.get();
        }

        return *this;
    }

    /**
     * post increment operator overloading
    */
    _iterator operator++(int) noexcept
    {
        auto tmp{*this};
        ++(*this);
        return tmp;
    }

    /**
     * equality operator overloading. Both arguments are lvalues
    */
    friend bool operator==(_iterator &a, _iterator &b) noexcept { return a._current == b._current; }

    /**
     * equality operator overloading. The first argument is an lvalue, the second a rvalue
    */
    friend bool operator==(_iterator &a, _iterator &&b) noexcept { return a._current == b._current; }

    /**
     * inequality operator overloading. Both arguments are lvalues
    */
    friend bool operator!=(_iterator &a, _iterator &b) noexcept { return !(a == b); }

    /**
     * inequality operator overloading. The first argument is an lvalue, the second a rvalue
    */
    friend bool operator!=(_iterator &a, _iterator &&b) noexcept { return !(a == b); }
};
