#include "SinlgyLinkedList.hpp"
#include "DoublyLinkedList.hpp"


void testFunction(List<int>& l);
int main()
{

	DoublyLinkedList<int> dl;

	dl.pushFront(1);
	dl[0] = 99;
	dl.print();


	SinglyLinkedList<int> sl;
	sl.pushBack(3);
	sl.pushFront(10);
	sl.print();

	testFunction(dl);
	testFunction(sl);
}


 void exampleFunction(List<int>& l) //this list cloud be: Vector, SinglyLinkedList, DoublyLinkedList ... 
{
	l.pushBack(3);
	l.popBack();
	l.print();
}