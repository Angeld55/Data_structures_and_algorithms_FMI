#include <iostream>
#include "Bst.hpp"
#include "printer/BST_printer.hpp"

int main()
{
	Bst<int> bst;

	printBst<int>(bst);

	bst.insert(2);
	bst.insert(1);
	bst.insert(4);
	bst.insert(3);
	bst.insert(5);


	printBst<int>(bst);
	std::cout << "------------------------------\n";
	//std::cout << std::endl;

	bst.remove(2);
	std::cout << "After removing 2:\n\n";
	printBst<int>(bst);
	std::cout << "------------------------------\n";

	bst.remove(4);
	std::cout << "After removing 4:\n\n";
	printBst<int>(bst);
	std::cout << std::endl;

	std::cout << "------------------------------\n";

	bst.insert(9);
	std::cout << "After inserting 9:\n\n";
	printBst<int>(bst);
	std::cout << std::endl;

	std::cout << "------------------------------\n";

	bst.insert(0);
	std::cout << "After inserting 0:\n\n";
	printBst<int>(bst);
	std::cout << std::endl;


	std::cout << "------------------------------\n";

	bst.remove(5);
	std::cout << "After removing 5:\n\n";
	printBst<int>(bst);
	std::cout << std::endl;

	std::cout << "------------------------------\n";


	bst.remove(3);
	std::cout << "After removing 3:\n\n";
	printBst<int>(bst);
	std::cout << std::endl;

	Bst<int> bst2 = bst;
	std::cout << "------------------------------\n";
	std::cout << "After copy:\n";
	printBst<int>(bst);

}
