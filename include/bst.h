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
		node *_parent;
		node *_right;
		node *_left;
		K _key;
		V _value;

		node() = default;
		node(K key, V value) : _parent{nullptr}, _right{nullptr}, _left{nullptr}, _key{key}, _value{value} {};
		node(node &parent_node, node &right_node, node &left_node, K key, V value) : _parent{parent_node}, _right{&right_node}, _left{&left_node}, _key{key}, _value{value} {};
	};

	template <typename O>
	class _iterator;
	using iterator = _iterator<K>;
	using const_iterator = _iterator<const K>;

	iterator begin() noexcept;			   // { return iterator{_root}; }
	const_iterator begin() const noexcept; //{ return const_iterator{_root}; }

	iterator end() noexcept;			 // { return iterator{nullptr}; }
	const_iterator end() const noexcept; // { return const_iterator{nullptr}; }

	node *_root;

public:
	bst();
	bst(node &root);
	void print_root();

	std::pair<iterator, bool> insert(const std::pair<const K, V> &x);
	std::pair<iterator, bool> insert(std::pair<const K, V> &&x);
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
		node *head = current;
		while (head->_parent != nullptr)
			head = head->_parent;

		//check if the node is the greatest one
		if (current->_right == nullptr && head->_key < current->_key)
		{
			current = nullptr;
			return *this;
		}

		if (current->_right == nullptr)
		{
			if (current->_key > current->_parent->_key)
			{
				while (current->_parent != nullptr && current->_key > current->_parent->_key)
					current = current->_parent;
				current=current->_parent;//check
			}
			else
			{
				current = current->_parent;
			}
		}
		else
		{
			current = current->_right;
			while (current->_left != nullptr)
				current = current->_left;
		}

		// current = current->_right;
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