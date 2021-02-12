#include <iostream>
#include <utility>
#include <memory>
#include "bst.cpp"
#include "../include/iterator.hpp"


int main()
{
	std::cout << "----- Start Program ----- \n";
	
	bst<int, int> tree{};
	std::cout << "\nTree is initialized \n";
	std::cout << "--------------------------- \n" << std::endl;


	std::vector<int> v{8, 3, 10, 6, 1, 14, 7, 4, 13};
	for (std::size_t i = 0; i < v.size(); ++i)
		tree.insert({v.at(i), v.at(i)});
	
	std::cout << "Tree after inserting some values. \n" << tree;
	std::cout << "---------------------------- \n" << std::endl;

	tree.emplace(2,5);
	
	std::cout << "Tree after emplace(2,5) function. \n" << tree;
	std::cout << "---------------------------- \n" << std::endl;

	std::cout << "Key " << *tree.find(2) << " was found inside the tree ";
	std::cout << "with value " << tree[2] << ".\n";
	std::cout << "---------------------------- \n" << std::endl;

	tree.erase(2);
	std::cout << "Tree after erase(2) function. \n" << tree;
	std::cout << "---------------------------- \n" << std::endl;

	tree.balance();
	std::cout << "Tree after balance() \n" << tree;
	std::cout << "---------------------------- \n" << std::endl;

	tree.clear();
	std::cout << "Tree after clear() \n" << tree;

	std::cout << "----- End Program -----" << std::endl;
	return 0;
}
