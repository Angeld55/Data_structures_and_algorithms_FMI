#include "SinglyLinkedList.hpp"

int main()
{
	SinglyLinkedList<int> l;
	SinglyLinkedList<int> l2;

	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);

	l.push_front(0);
	l.push_front(-1);
	l.push_front(-2);

	l.print();
	cout << endl;

	l.pop_front();
	l.pop_front();
	l.pop_front();

	l.print();
	cout << endl;

	cout << l.front() << endl;
	cout << l.back() << endl;

	l2.push_back(6);
	l2.push_back(7);
	l2.push_back(8);

	SinglyLinkedList<int> res = concat(l, l2);
	res.print();
}
