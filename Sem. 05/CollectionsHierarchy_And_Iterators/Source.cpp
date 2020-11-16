#include "DoublyLinkedList.hpp"
#include "Vector.hpp"
#include "Algorithms.hpp"
using namespace std;

int main()
{

	DoublyLinkedList<int> v2;
	v2.pushBack(33);
	v2.pushFront(44);

	v2[1] = 999;
	cout << v2[1] << endl;
	v2.print();

}