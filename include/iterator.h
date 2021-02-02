template <typename K, typename V, typename comparator>
template <typename O>
class bst<K, V, comparator>::_iterator
{
public:
	using Node = node<K, V>;
	Node *current;

public:
	using value_type = O;
	using reference = value_type &;
	using pointer = value_type *;
	using difference_type = std::ptrdiff_t;
	using iterator_category = std::forward_iterator_tag;

	_iterator(Node *n) : current{n} {}

	reference operator*() const { return current->_pair.first; }
	pointer operator->() const { return &**this; }

	_iterator &operator++()
	{

		if (current->_right.get() == nullptr)
		{
			while (current->_parent != nullptr && current->_pair.first > current->_parent->_pair.first)
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