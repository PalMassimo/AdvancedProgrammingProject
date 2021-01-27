#include "../include/bst.h"

template<typename K, typename V>
bst<K, V>::bst() : _root{nullptr} {} ;
// bst<K, V>::bst() = default;


template<typename K, typename V>
bst<K,V>::bst(node& root) : _root{ &root } {}

template<typename K, typename V>
void bst<K, V>::print_root()
{
std::cout << "root key " << _root->_key << "\nroot value " << _root->_value << std::endl;
}

//template<typename K, typename V>
//_iterator<K> bst<K,V>::begin() noexcept { return iterator{ head } };