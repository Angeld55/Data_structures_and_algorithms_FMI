#include <iostream>
#include "DoublyLinkedList.hpp"

int main()
{
	DoublyLinkedList<int> l;

	l.pushBack(3);
	l.pushBack(4);
	l.pushFront(2);
	l.pushFront(1);
	l.pushFront(99);
	l.pushBack(100);

	l.popBack();
	l.popFront();

	l.print();
}