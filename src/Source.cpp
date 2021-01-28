#include <iostream>
#include "bst.cpp"
#include <utility>
#include <memory>

int main()
{
	std::cout << "----- Start Program -----" << std::endl;

	bst<int, int>::node head{8, 8};
	bst<int, int> tree{head};

	tree.insert(std::make_pair(6, 6));
	tree.insert(std::make_pair(10, 10));
	tree.insert(std::make_pair(7, 7));
	tree.insert(std::make_pair(14, 14));
	tree.insert(std::make_pair(13, 13));
	tree.insert(std::make_pair(4, 4));
	tree.insert(std::make_pair(3, 3));
	tree.insert(std::make_pair(1, 1));



	for (auto a : tree)
	{
		std::cout << a << " ";
	}

	std::cout << std::endl;


	// test find
	int qualcosa = *(tree.find(10));
	std::cout<<"qualcosa " << qualcosa<<std::endl;

	std::cout << "----- End Program -----" << std::endl;
	return 0;
};
