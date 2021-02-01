#include <iostream>
#include "bst.cpp"
#include <utility>
#include <memory>

int main()
{
	std::cout << "----- Start Program -----" << std::endl;

	bst<int, int> tree{};
	std::cout << "Tree: " << tree << std::endl;

	std::vector<int> v{8, 3, 10, 6, 1, 14, 7, 4, 13};
	for (std::size_t i = 0; i < v.size(); ++i)
		tree.insert({v.at(i), v.at(i)});

	std::cout << "Tree: " << tree << std::endl;

	std::cout << "Tree before balance: " << tree << std::endl;
	tree.balance();
	std::cout << "Tree after balance: " << tree << std::endl;

	std::cout << "----- End Program -----" << std::endl;
	return 0;
};
