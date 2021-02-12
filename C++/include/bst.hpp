#pragma once
#include <memory>
#include <iostream>
#include <utility>
#include "node.hpp"

/**
 * class implementing templated binary search tree (BST)
*/
template <typename K, typename V, typename comparator = std::less<K>>
class bst
{

public:

	using Node = node<K, V>;

	/**
	 * unique pointer pointing the root node of the tree
	*/
	std::unique_ptr<Node> _root;

	/**
	 * comparator establishing the total order among key values
	 */
	comparator _cmp;

	/**
	 * iterator class for iterating through the tree
	*/
	template <typename O>
	class _iterator;
	using iterator = _iterator<K>;
	using const_iterator = _iterator<const K>;

	/**
	 * function returning the first element of the tree. It is the one having the lowest key value
	*/
	iterator begin() noexcept;

	/**
	 * as begin(), but const 
	*/
	const_iterator begin() const noexcept;

	/**
	 * as begin(), but const
	*/
	const_iterator cbegin() const noexcept;

	/**
	 * function returning the last element of the tree. It is the one having the highest key value
	*/
	iterator end() noexcept;

	/**
	 * as end(), but const 
	*/
	const_iterator end() const noexcept;

	/**
	 * as end(), but const 
	*/
	const_iterator cend() const noexcept;

public:

	/**
	 * default constructor
	*/
	bst() = default;

	/**
	 * constructor that changes the default comparator
	*/
	explicit bst(const comparator& _cmp);

	/**
	 * copy constructor
	*/
	bst(const bst &b);

	/**
	 * move constructor
	 */
	bst(bst &&b) = default;

	/**
	 * default deconstructor
	 */
	~bst() noexcept = default;

private:

	void copy(Node *n, Node *m);
	void divide_and_build(std::vector<std::pair<K, V>> values);
	void erase_root();

public:

	/**
 	* insert a node in the tree
 	*/
	std::pair<iterator, bool> insert(const std::pair<const K, V> &x);

	/**
 	* insert a node in the tree, but const
 	*/
	std::pair<iterator, bool> insert(std::pair<const K, V> &&x);

	/**
	*  as insert, but takes raw values instead of a pair
	*/
	template <class... Types>
	std::pair<iterator, bool> emplace(Types &&...args);

	/**
	 * return an iterator pointing the node holding x value. If such doesn't exist, returns nullptr
	*/
	iterator find(const K &x);

	/**
	 * as find, but const
	*/
	const_iterator find(const K &x) const;

	/**
	 * erase a node holding x value, if any.
	*/
	void erase(const K &x);

	void clear();

	/**
	 * move assignment
	*/
	bst &operator=(bst &&b) = default;

	/**
	 * copy assignment
	*/
	bst &operator=(const bst &b)
	{
		_root.reset();
		auto tmp = b;			  
		(*this) = std::move(tmp); 
		return *this;
	}

	/**
 	*  put to operator overloading
 	*/
	friend std::ostream &operator<<(std::ostream &os, const bst<K, V, comparator> &x)
	{
		os << "[";
		for (const auto &a : x)
			os << " " << a;
		os << " ]\n";
		return os;
	}

	/**
	 * subscripting operator overloading, taking l-value
	*/
	V &operator[](const K &x) { return find(x).current->_pair.second; }

	/**
	 * subscripting operator overloading, taking r-value
	*/
	V &operator[](K &&x) { return find(x)._current->_pair.second; }

	/**
	 * balance the tree
	*/
	void balance();
};
