#include "SinglyLinkedList.hpp"
#include <iostream>


int main()
{
	LinkedList<int> l;

	l.addFirst(3);
	l.addLast(5);
	l.addFirst(1);
	l.addLast(44);
	l.print();
	l.removeFirst();
	l.removeLast();
	l.print();


}
