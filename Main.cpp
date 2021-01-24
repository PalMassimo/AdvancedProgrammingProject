#include <iostream>
#include "bst.h"


int main() {

	std::cout << "-- Start Program --" << std::endl;

	//Node<std::string, int> node{ nullptr, nullptr, std::string{"Massimo"}, 10 };
	//bst<std::string, int> bst{};

	Node<std::string, int> head{ "Tibor", 24 };
	Node<std::string, int> leaf{ "Ugo", 24 };


	bst<std::string, int> bst{ };
	bst.insert(std::pair<std::string, int>{head.key, head.value});

	bst.printTree();

	bst.insert(std::pair<std::string, int>{leaf.key, leaf.value});
	bst.printTree();


	std::cout << "-- End Program --" << std::endl;
}