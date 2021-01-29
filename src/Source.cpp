#include <iostream>
#include "bst.cpp"
#include <utility>
#include <memory>

int main()
{
	std::cout << "----- Start Program -----" << std::endl;

	bst<int, int>::node head{8, 8};
	bst<int, int> tree{head};

	tree.insert(std::make_pair(3, 3));
	tree.insert(std::make_pair(10, 10));

	tree.insert(std::make_pair(6, 6));
	tree.insert(std::make_pair(1, 1));
	tree.insert(std::make_pair(14, 14));

	tree.insert(std::make_pair(7, 7));
	tree.insert(std::make_pair(13, 102));
	tree.insert(std::make_pair(4, 4));

	std::cout << tree[13] << std::endl;

/* 	for (auto a : tree)
	{
		std::cout << a << " ";
	}

	std::cout << std::endl;

	
	tree.erase(8);
	for (auto a : tree)
	{
		std::cout << a << " ";
	}

	std::cout << std::endl;

	tree.clear();
	std::cout << "empty tree" << std::endl;
	for (auto a : tree)
	{
		std::cout << a << " ";
	}
	std::cout << std::endl;
 */
	std::cout << "----- End Program -----" << std::endl;
	return 0;
};
