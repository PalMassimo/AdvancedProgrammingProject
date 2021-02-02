#pragma once
#include <memory>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <array>
#include "node.h"

// namespace bst
// {

template <typename K, typename V, typename comparator = std::less<K>>
class bst
{

public: //make it private
	// struct node
	// {
	// 	node *_parent;
	// 	std::unique_ptr<node> _right;
	// 	std::unique_ptr<node> _left;

	// 	std::pair<K, V> _pair;

	// 	node() = default;

	// 	node(std::pair<K, V> a_pair) : _parent{}, _right{}, _left{}, _pair{a_pair} {}

	// 	node(node *parent, std::pair<K, V> a_pair) : _parent{parent}, _right{}, _left{}, _pair{a_pair} {}

	// 	~node() = default;
	// };
	using Node = node<K, V>;

	std::unique_ptr<Node> _root;
	comparator cmp;

	template <typename O>
	class _iterator;
	using iterator = _iterator<K>;
	using const_iterator = _iterator<const K>;

	iterator begin() noexcept;
	const_iterator begin() const noexcept;
	//const_iterator cbegin() const noexcept;

	iterator end() noexcept;
	const_iterator end() const noexcept;
	//const_iterator cend() const noexcept;

public:
	bst() = default;
	bst(Node &root);
	bst(const bst &b);
	~bst() = default;

	bst &operator=(const bst &b)
	{
		_root.reset();
		auto tmp = b;			  // copy ctor
		(*this) = std::move(tmp); // move assignment
		return *this;
	}

	void copy(Node *n, Node *m);

	bst(bst &&b) = default;			   //: _root{std::move(b._root)}; // move ctor
	bst &operator=(bst &&b) = default; //move assignment

	std::pair<iterator, bool> insert(const std::pair<const K, V> &x);
	std::pair<iterator, bool> insert(std::pair<const K, V> &&x);

	template <class... Types>
	std::pair<iterator, bool> emplace(Types &&...args)
	{
		return (*this).insert(std::forward<Types>(args)...);
	}

	iterator find(const K &x);

	void erase(const K &x);

	void clear();

	V &operator[](const K &x) { return find(x).current->_value; }

	friend std::ostream &operator<<(std::ostream &os, const bst &x)
	{
		os << "[";
		for (auto a : x)
			os << " " << a;
		os << " ]\n";
		return os;
	}

	//value_type& operator[](key_type&& x); //TODO

	void erase_root();

	void divide_and_build(std::vector<std::pair<K, V>> values);

	void balance();
};

//} //namespace bst

#include "iterator.h"