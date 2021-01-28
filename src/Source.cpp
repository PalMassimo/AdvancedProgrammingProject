#include <iostream>
#include "bst.cpp"
#include <utility>
#include <memory>

int main()
{
	std::cout << "----- Start Program -----" << std::endl;

	 
	bst<int, int>::node head{1, 1};
	bst<int, int> tree{head};

	auto pairTest1 = tree.insert(std::make_pair(2, 2));
	auto pairTest2 = tree.insert(std::make_pair(3, 3));
	auto pairTest3 = tree.insert(std::make_pair(4, 4));
	
	 for (auto a : tree)
	{
		std::cout << "node key : " << a << "\n"
				  << std::endl;
	} 
	 

	std::cout << "----- End Program -----" << std::endl;
	return 0;
};
