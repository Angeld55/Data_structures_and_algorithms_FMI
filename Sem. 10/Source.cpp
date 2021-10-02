#include <iostream>
#include "BST.h"

int main()
{
	BST bst;

	bst.insert(2);
	bst.insert(1);
	bst.insert(4);
	bst.insert(3);
	bst.insert(5);

	bst.print();
	std::cout << "------------------------------\n";
	//std::cout << std::endl;

	bst.remove(2);
	std::cout << "After removing 2:\n\n";
	bst.print();
	std::cout << "------------------------------\n";

	bst.remove(4);
	std::cout << "After removing 4:\n\n";
	bst.print();
	std::cout << std::endl;

	BST bst2 = bst;
	std::cout << "------------------------------\n";
	std::cout << "After copy:\n";
	bst.print();

}
