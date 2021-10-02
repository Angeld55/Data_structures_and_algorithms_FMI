#include <iostream>
#include <algorithm>
#include "Vector/Vector.hpp"
#include "DoublyLinkedList/DoublyLinkedList.hpp"
#include "SinglyLinkedList/SinglyLinkedList.hpp"

#include "CollectionAlgorithms/Algorithms.hpp"
using namespace std;

int main()
{

	{ //simple example for vector
		Vector<int> v1;

		v1.pushBack(13);
		v1.pushBack(3);
		v1.pushBack(10);

		std::cout << CustomAlgorithms::containsElement(v1.begin(), v1.end(), 10) << std::endl;
		std::cout << CustomAlgorithms::isSorted(v1.begin(), v1.end()) << std::endl;
	}

	{ //simple example for SLL
		SinglyLinkedList<int> sll;

		sll.pushBack(1);
		sll.pushBack(2);
		sll.pushBack(3);
		sll.pushBack(4);

		std::cout << CustomAlgorithms::containsElement(sll.begin(), sll.end(), 3) << std::endl;
		std::cout << CustomAlgorithms::isSorted(sll.begin(), sll.end()) << std::endl;

		sll.print();

		auto it = sll.begin();

		it++; it++;

		auto res = sll.insertAfter(99, it);
		std::cout << (*res) << std::endl;
		sll.print();

		sll.removeAfter(res);
		sll.print();
	}

	{ //simple example for DLL
		DoublyLinkedList<int> dll;

		dll.pushBack(1);
		dll.pushBack(2);
		dll.pushBack(3);
		dll.pushBack(4);

		auto it = dll.begin();
		auto res = dll.remove(it);

		dll.print();

		dll.insertAfter(999, res);

		dll.print();
	}



}