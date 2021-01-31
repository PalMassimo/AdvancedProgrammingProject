#include <iostream>
#include "bst.cpp"
#include <utility>
#include <memory>

int main()
{
	std::cout << "----- Start Program -----" << std::endl;

	bst<int, int> tree{};
	tree.insert(std::make_pair(8, 8));
	tree.insert(std::make_pair(3, 3));

	std::vector<int> v{8, 3, 10, 6, 1, 14, 7, 4, 13};
	for (int i = 0; i < v.size(); ++i){
		tree.insert(std::make_pair(v.at(i), v.at(i)));
	}
	std::cout << "Tree: " << tree << std::endl;

	// tree.erase(8);
	// tree.clear();

	std::cout << "Tree: " << tree << std::endl;
	std::cout << "----- End Program -----" << std::endl;

	// tree.balance();
	return 0;
};
