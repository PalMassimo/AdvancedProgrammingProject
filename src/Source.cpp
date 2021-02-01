#include <iostream>
#include "bst.cpp"
#include <utility>
#include <memory>

int main()
{
	std::cout << "----- Start Program -----" << std::endl;

	bst<int, int> tree{};
	std::cout << "Tree: " << tree << std::endl;

	// tree.insert(std::make_pair(8, 8));
	// tree.insert(std::make_pair(10, 10));
	// tree.insert(std::make_pair(6, 6));

	std::vector<int> v{8, 3, 10, 6, 1, 14, 7, 4, 13};
	for (std::size_t i = 0; i < v.size(); ++i)
	{
		tree.insert(std::make_pair(v.at(i), v.at(i)));
	}
	std::cout << "Tree: " << tree << std::endl;

	// bst<int, int> tree_copy=tree;

	// std::cout << "Tree_copy: " << tree_copy << std::endl;

	// tree.clear();

	// std::cout << "Tree_copy: " << tree_copy << std::endl;

	// std::cout << "Tree: " << tree << std::endl;

	bst<int, int> a_tree{};
	a_tree.insert(std::make_pair(1, 1));
	a_tree.insert(std::make_pair(10, 10));
	a_tree.insert(std::make_pair(15, 15));

	std::cout << "Tree a_tree before balance: " << a_tree << std::endl;
	a_tree.balance();
	std::cout << "Tree a_tree after balance: " << a_tree << std::endl;

	std::cout << "----- End Program -----" << std::endl;
	return 0;
};
