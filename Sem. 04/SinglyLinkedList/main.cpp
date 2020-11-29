#include "SinglyLinkedList.hpp"
#include <iostream>


int main()
{
	LinkedList<int> l;

	l.AddFirst(3);
	l.AddLast(5);
	l.AddFirst(1);
	l.AddLast(44);
	l.Print();
	l.RemoveFirst();
	l.RemoveLast();
	l.Print();


}
