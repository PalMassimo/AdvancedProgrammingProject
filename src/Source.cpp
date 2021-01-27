#include <iostream>
#include "bst.cpp"
#include <utility>

int main()
{
	std::cout << "----- Start Program -----" << std::endl;

	// bst<int, int>::node dx{5, 5};
	// bst<int, int>::node sx{5, 5};

	// bst<int, int>::node head{dx, sx, 3, 3};
	// bst<int, int> tree{head};

	// tree._root->_right = &dx;
	// tree._root->_left = &sx;

	bst<int, int>::node head{3, 3};
	bst<int, int> tree{head};
	std::pair<int,int> input{4,4};

	//tree.print_root();
	auto pairTest = tree.insert(input);
	// std::cout << pairTest.first << "/n" << pairTest.second << std::endl;
	std::cout << pairTest.second << std::endl;


	 for (auto a : tree)
	{
		std::cout << a << std::endl;
	} 

	std::cout << "----- End Program -----" << std::endl;
	return 0;
}
