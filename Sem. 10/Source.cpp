#include <iostream>
#include "BST.hpp"

int main()
{
	BST<int> bst;

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

	std::cout << "------------------------------\n";

	bst.insert(9);
	std::cout << "After inserting 9:\n\n";
	bst.print();
	std::cout << std::endl;

	std::cout << "------------------------------\n";

	bst.insert(0);
	std::cout << "After inserting 0:\n\n";
	bst.print();
	std::cout << std::endl;


	std::cout << "------------------------------\n";

	bst.remove(5);
	std::cout << "After removing 5:\n\n";
	bst.print();
	std::cout << std::endl;

	std::cout << "------------------------------\n";


	bst.remove(3);
	std::cout << "After removing 3:\n\n";
	bst.print();
	std::cout << std::endl;

	BST<int> bst2 = bst;
	std::cout << "------------------------------\n";
	std::cout << "After copy:\n";
	bst.print();

}
