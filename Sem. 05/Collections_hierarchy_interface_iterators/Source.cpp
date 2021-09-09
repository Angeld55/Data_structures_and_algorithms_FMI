#include "DoublyLinkedList/DoublyLinkedList.hpp"
#include "Vector/Vector.hpp"
#include "Algorithms/Algorithms.hpp"
using namespace std;

int main()
{
	Vector<int> v;
	v.pushBack(3);
	v.pushBack(14);

	DoublyLinkedList<int> v2;
	v2.pushBack(110);
	v2.pushBack(555);

	cout << Search<int>(v.begin(), v.end(), 14) <<endl;
	cout << Search<int>(v2.begin(), v2.end(), 14) << endl;

}