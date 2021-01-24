#pragma once
#include <iostream>
#include <utility>

template<typename K, typename V>
struct Node {
	Node* left;
	Node* right;
	K key;
	V value;

	Node() { std::cout << "default Node constructor invoked" << std::endl; }

	Node(Node* left, Node* right, K key, V value) :left{ left }, right{ right }, key{ key }, value{ value }{
		std::cout << "custom Node constructor invoked" << std::endl;
	}

	Node(K key, V value) : left{ nullptr }, right{ nullptr }, key{ key }, value{ value } {std::cout << "custom Node constructor invoked" << std::endl;}

};

template<typename K, typename V>
class bst {
public:
	Node<K, V>* root;
	size_t size;

public:
	bst() : root(nullptr), size{ 0 } { std::cout << "default bst constructor invoked" << std::endl; }
	bst(Node<K, V>& root) : root{ &root }, size{ 1 }{std::cout << "custom bst constructor invoked" << std::endl; };
	//insert functions
	bool insert(const std::pair<K, V>& x)
	{
		if (root == nullptr) {
			root = new Node<K, V>{ x.first, x.second };
			std::cout << "Now the bst has a root node" << std::endl;
			return true;
		}
		else {
			if (x.first > root->key) {
				root->right = new Node<K, V>{ x.first, x.second };
			}
			else {
				root->left = new Node<K, V>{ x.first, x.second };
			}
			return true;
		}

	}

	void printTree() {
		std::cout << "The root is " << root->key << " with the value " << root->value << std::endl;

		if (root->left == nullptr) {
			std::cout << "The root has not left leaf" << std::endl;
		}
		else {
			std::cout << "The left leaf is " << root->left->key << " with the value " << root->left->value << std::endl;
		}

		if (root->right == nullptr) {
			std::cout << "The root has not right leaf" << std::endl;
		}
		
		else {
			std::cout << "The right leaf is " << root->right->key << " with the value " << root->right->value << std::endl;
		}


	}

	~bst() {
		delete root;
		std::cout << "Deconstructor invoked" << std::endl;
	}

	//std::pair<iterator, bool> insert(const std::pair<K key, V value>& x);
	//std::pair<iterator, bool> insert(std::pair<K key, V value>& x);

	//emplace function
	//template<class... Types>
	//std::pair<iterator, bool> emplace(Types&&... args);

	////clear function
	//void clear();

	////begin function
	//iterator begin();
	//const_iterator begin() const;
	//const_iterator end() const;

};
