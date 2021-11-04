#include "SinglyLinkedList.hpp"

int main()
{
	SinglyLinkedList<int> l;
	SinglyLinkedList<int> l2;

	l.pushBack(1);
	l.pushBack(2);
	l.pushBack(3);
	l.pushBack(4);
	l.pushBack(5);

	l.pushFront(0);
	l.pushFront(-1);
	l.pushFront(-2);

	l.print();
	cout << endl;

	l.popFront();
	l.popFront();
	l.popFront();

	l.print();
	cout << endl;

	cout << l.front() << endl;
	cout << l.back() << endl;

	l2.pushBack(6);
	l2.pushBack(7);
	l2.pushBack(8);

	SinglyLinkedList<int> res = concat(l, l2);
	res.print();
}
