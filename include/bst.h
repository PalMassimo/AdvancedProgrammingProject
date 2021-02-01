#pragma once
#include <memory>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <array>

//template<typename K, typename V, typename comparator = std::less<K>>
template <typename K, typename V>
class bst
{
public: //make it private
	struct node
	{
		node *_parent;
		std::unique_ptr<node> _right;
		std::unique_ptr<node> _left;

		std::pair<K, V> _pair;

		node() = default;

		node(std::pair<K, V> a_pair) : _parent{nullptr}, _pair{a_pair} {}

		node(K key, V value) : _parent{nullptr}, _pair{std::make_pair(key, value)}
		{
			_left.reset();
			_right.reset();
		}

		node(node &parent, K key, V value) : _parent{&parent}, _pair{std::make_pair(key, value)}
		{
			_left.reset();
			_right.reset();
		}
		node(node *parent, K key, V value) : _parent{parent}, _pair{std::make_pair(key, value)}
		{
			_left.reset();
			_right.reset();
		}
		~node() = default;
	};

	std::unique_ptr<node> _root;

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
	bst(node &root);
	bst(const bst &b);
	~bst() = default;

	bst& operator=(const bst& b){
        _root.reset();
        auto tmp = b; // copy ctor
        (*this) = std::move(tmp); // move assignment
        return *this;
    }

	void copy(node *n, node *m);

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

	void balance()
	{
		//count the number of nodes
		std::size_t number_of_elements = 0;
		for (auto a : *this)
			number_of_elements++;
		std::pair<K, V> arr[number_of_elements];

		//populate the array of node pointers
		std::size_t index = 0;
		for (_iterator<int> it = (*this).begin(); it != (*this).end(); it++)
		{
			arr[index++] = it.current._pair;
		}
		//build another tree
		bst<K, V> another_tree{};

		another_tree._root.reset(new node(arr[number_of_elements / 2]));
		divide_and_build(arr, number_of_elements);
		// (*this).clear();
		*this = another_tree;
	}

	void divide_and_build(node arr[], std::size_t arr_size)
	{
		if (arr_size == 1)
			return;
		else
		{
			node *parent = new node{arr[arr_size / 2]._pair.first, arr[arr_size / 2]._value};
			node *left_child = new node{arr[arr_size / 4]._pair.first, arr[arr_size / 4]._value};
			node *right_child = new node{arr[arr_size / 2 + arr_size / 4]._pair.first, arr[arr_size / 2 + arr_size / 4]._value};

			parent->_left.reset(left_child);
			parent->_right.reset(right_child);

			node left_arr[arr_size / 2];
			for (std::size_t i = 0; i < arr_size / 2; i++)
				left_arr[i] = arr[i];
			divide_and_build(left_arr, arr_size / 2);

			node right_arr[arr_size / 2];
			for (int i = arr_size / 2 + 1; i < arr_size; i++)
				right_arr[i] = arr[i];
			divide_and_build(right_arr, arr_size / 2);
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

	_iterator(node *n) : current{n} {}

	reference operator*() const { return current->_pair.first; }
	pointer operator->() const { return &**this; }

	_iterator &operator++()
	{

		if (current->_right.get() == nullptr)
		{
			while (current->_parent != nullptr && current->_pair.first > current->_parent->_pair.first)
			{
				current = current->_parent;
			}
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