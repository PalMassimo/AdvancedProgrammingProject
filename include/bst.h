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
		~node() = default;
	};

	template <typename O>
	class _iterator;
	using iterator = _iterator<K>;
	using const_iterator = _iterator<const K>;

	iterator begin() noexcept;			   // { return iterator{_root}; }
	const_iterator begin() const noexcept; //{ return const_iterator{_root}; }
	//const_iterator cbegin() const noexcept;

	iterator end() noexcept;			 // { return iterator{nullptr}; }
	const_iterator end() const noexcept; // { return const_iterator{nullptr}; }
	//const_iterator cend() const noexcept;

	node *_root;

public:
	bst();
	bst(node &root);
	void print_root();

	std::pair<iterator, bool> insert(const std::pair<const K, V> &x);
	std::pair<iterator, bool> insert(std::pair<const K, V> &&x);
	iterator find(const K &x)
	{
		for (_iterator<int> it = (*this).begin(); it != (*this).end(); it++)
		{
			if ((*it) == x)
				return it;
		}

		return _iterator<K>{nullptr};
	}

	template <class... Types>
	std::pair<iterator, bool> emplace(Types &&...args)
	{
		return (*this).insert(std::forward<Types>(args)...);
	}

	void erase(const K &x)
	{

		iterator it = find(x);

		if (it == end())
			return;
		else
		{
			//node is the root
			if (it.current->_parent == nullptr)
			{

				if (it.current->_left == nullptr && it.current->_right == nullptr)
				{
					//delete
				}
				else if (it.current->_left == nullptr)
				{
					it.current->_right->_parent = nullptr;
				}
				else if (it.current->_right == nullptr)
				{
					it.current->_left->_parent = nullptr;
				}
				else
				{
					node *rightest_child = it.current->_left;

					while (rightest_child->_right != nullptr)
						rightest_child = rightest_child->_right;
					rightest_child->_right = it.current->_right;

					it.current->_right->_parent = rightest_child;
					it.current->_left->_parent = nullptr;
				}
				return;
			}

			//node has no children
			if (it.current->_right == nullptr && it.current->_left == nullptr)
			{
				(it.current == it.current->_parent->_right) ? it.current->_parent->_right = nullptr : it.current->_parent->_left = nullptr;
				delete it.current;
				return;
			}

			//node having only left child and it is the left child of the parent
			if (it.current->_left != nullptr && it.current->_right == nullptr && it.current == it.current->_parent->_left)
			{
				it.current->_parent->_left = it.current->_left;
				it.current->_left->_parent = it.current->_parent;
				delete it.current;
				return;
			}

			//node having only right child and it is the left child of the parent
			if (it.current->_left == nullptr && it.current->_right != nullptr && it.current == it.current->_parent->_left)
			{
				it.current->_parent->_left = it.current->_right;
				it.current->_right->_parent = it.current->_parent;
				delete it.current;
				return;
			}

			//node having only right child and it is the right child of the parent
			if (it.current->_left == nullptr && it.current->_right != nullptr && it.current == it.current->_parent->_right)
			{
				it.current->_parent->_right = it.current->_right;
				it.current->_right->_parent = it.current->_parent;
				delete it.current;
				return;
			}

			//node having only left child and it is the right child of the parent
			if (it.current->_left != nullptr && it.current->_right == nullptr && it.current == it.current->_parent->_right)
			{
				it.current->_parent->_right = it.current->_left;
				it.current->_left->_parent = it.current->_parent;
				delete it.current;
				return;
			}

			//the node has two child and it is the right child of parent
			if (it.current->_right != nullptr && it.current->_left != nullptr && it.current == it.current->_parent->_right)
			{
				//colleghiamo il figlio di destra del parent al figlio di sinistra del nodo corrente
				it.current->_parent->_right = it.current->_left;
				it.current->_left->_parent = it.current->_parent;

				node *rightest_child = it.current->_left;

				while (rightest_child->_right != nullptr)
					rightest_child = rightest_child->_right;
				rightest_child->_right = it.current->_right;

				it.current->_right->_parent = rightest_child;

				delete it.current;
				return;
			}

			//the node has two child and it is the left child of parent
			if (it.current->_right != nullptr && it.current->_left != nullptr && it.current == it.current->_parent->_left)
			{
				//colleghiamo il figlio di destra del parent al figlio di sinistra del nodo corrente
				it.current->_parent->_left = it.current->_left;
				it.current->_left->_parent = it.current->_parent;

				node *rightest_child = it.current->_left;

				while (rightest_child->_right != nullptr)
					rightest_child = rightest_child->_right;
				rightest_child->_right = it.current->_right;

				it.current->_right->_parent = rightest_child;

				delete it.current;
				return;
			}

			std::cout << "if this point is reached at least one case is missing" << std::endl;
			return;
		}
	}

	void clear()
	{

		for (_iterator<int> it = (*this).begin(); it != (*this).end();)
		{
			auto a = *it;
			++it;
			std::cout << "node deleted with key " << a << std::endl;
			erase(a);
		}
	}
};

template <typename K, typename V>
template <typename O>
class bst<K, V>::_iterator
{
public:
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

		if (current->_right == nullptr)
		{
			while (current->_parent != nullptr && current->_key > current->_parent->_key)
			{
				current = current->_parent;
			}
			current = current->_parent;
		}
		//se ci sono nodi a destra ci sono sicuramente altri nodi su cui iterare
		else
		{
			current = current->_right;
			while (current->_left != nullptr)
				current = current->_left;
		}

		return *this;
	}

	_iterator operator++(int)
	{
		auto tmp{*this};
		++(*this);
		return tmp;
	}

	friend bool operator==(_iterator &a, _iterator &b) { return a.current == b.current; }
	friend bool operator==(_iterator &a, _iterator &&b) { return a.current == b.current; }

	friend bool operator!=(_iterator &a, _iterator &b) { return !(a == b); }
	friend bool operator!=(_iterator &a, _iterator &&b) { return !(a == b); }
};