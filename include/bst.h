#pragma once
#include <memory>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <array>
#include "node.h"

/**
 * class implementing template binary search tree (BST)
*/
template <typename K, typename V, typename comparator = std::less<K>>
class bst
{

public:
	/**
	 * alias of template class node<K,V>
	 * 
	*/
	using Node = node<K, V>;

	/**
	 * unique pointer pointing the root node of bst
	*/
	std::unique_ptr<Node> _root;

	/**
	 * comparator establishing the total order among key values
	 */
	comparator cmp;

	/**
	 * iterator class for iterating through bst class
	 */
	template <typename O>
	class _iterator;
	using iterator = _iterator<K>;
	using const_iterator = _iterator<const K>;

	/**
	 * function returning the first element of the tree. It is the one having the lowest key value
	 */
	iterator begin() noexcept;
	const_iterator begin() const noexcept;
	const_iterator cbegin() const noexcept;

	/**
	 * function returning the last element of the tree. It is the one having the highest key value
	 */
	iterator end() noexcept;
	const_iterator end() const noexcept;
	const_iterator cend() const noexcept;

public:
	/**
	 * default constructor
	*/
	bst() = default;
	/**
	 * constructor that build a tree consisting of only a node passed to it
	*/
	bst(Node &root);

	/**
	 * copy constructor
	*/
	bst(const bst &b);

	/**
	 * move constructor (default one)
	 */
	bst(bst &&b) = default;

	/**
	 * default deconstructor
	 */
	~bst() = default;

private:
	void copy(Node *n, Node *m);
	void divide_and_build(std::vector<std::pair<K, V>> values);
	void erase_root();

public:
	std::pair<iterator, bool> insert(const std::pair<const K, V> &x);
	std::pair<iterator, bool> insert(std::pair<const K, V> &&x);

	template <class... Types>
	std::pair<iterator, bool> emplace(Types &&...args);

	iterator find(const K &x);
	const_iterator find(const K &x) const;

	void erase(const K &x);

	void clear();

	/**
	 * Move assignment, set to default
	 */
	bst &operator=(bst &&b) = default;

	/**
	 * Copy assignment.
	*/
	bst &operator=(const bst &b)
	{
		_root.reset();
		auto tmp = b;			  // copy ctor
		(*this) = std::move(tmp); // move assignment
		return *this;
	}

	/**
 	* put to operator overloading implemented
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
	 * Subscripting operator.
	*/
	V &operator[](const K &x) { return find(x).current->_pair.second; }
	V &operator[](K &&x) { return find(x).current->_pair.second; }

	//value_type& operator[](key_type&& x); //TODO

	/**
	 * Function balancing the tree, not in place.
	 */
	void balance();
};

#include "iterator.h"
