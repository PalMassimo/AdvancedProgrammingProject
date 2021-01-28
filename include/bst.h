#pragma once
#include <memory>
#include <iostream>
#include <iterator>
#include <utility>

//template<typename K, typename V, typename comparator = std::less<K>>
template <typename K, typename V>
class bst
{
public: //make it private
	struct node
	{
		node *_right;
		node *_left;
		K _key;
		V _value;

		node() = default;
		node(K key, V value) : _right{nullptr}, _left{nullptr}, _key{key}, _value{value} {};
		node(node &right_node, node &left_node, K key, V value) : _right{&right_node}, _left{&left_node}, _key{key}, _value{value} {};
	};

	template <typename O>
	class _iterator;
	using iterator = _iterator<K>;
	using const_iterator = _iterator<const K>;

	iterator begin() noexcept;// { return iterator{_root}; }
	const_iterator begin() const noexcept; //{ return const_iterator{_root}; }

	iterator end() noexcept;// { return iterator{nullptr}; }
	const_iterator end() const noexcept;// { return const_iterator{nullptr}; }

	node *_root;

public:
	bst();
	bst(node &root);
	void print_root();

	std::pair<iterator, bool> insert(const std::pair<const K, V> &x);
	std::pair<iterator, bool> insert(std::pair<const K, V>&& x);


};

template <typename K, typename V>
template <typename O>
class bst<K, V>::_iterator
{

	using node = typename bst<K, V>::node;
	node *current;

public:
	using value_type = O;
	using reference = value_type &;
	using pointer = value_type *;
	using difference_type = std::ptrdiff_t;
	using iterator_category = std::forward_iterator_tag;

	explicit _iterator(node *n) : current{n} {}

	reference operator*() const { return current->_key; }
	pointer operator->() const { return &**this; }

	_iterator &operator++()
	{
		

		current = current->_right;
		return *this;
	}

	_iterator operator++(int)
	{
		auto tmp{*this};
		++(*this);
		return tmp;
	}

friend bool operator==(_iterator &a, _iterator &b)
	{
		return a.current == b.current;
	}

	friend bool operator!=(_iterator &a, _iterator &b) { return !(a == b); }
};