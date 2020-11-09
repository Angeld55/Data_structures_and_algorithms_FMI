#include "DoublyLinkedList.hpp"
#include "Vector.hpp"
#include "Algorithms.hpp"
using namespace std;

int main()
{
	Vector<char> v;
	v.pushBack('d');
	v.pushBack('m');
	v.pushBack('a');
	v.pushBack('t');

	cout << Search<char>(v.begin(), v.end(), 'm') << endl;

	DoublyLinkedList<int> v2;
	v2.pushBack(33);
	v2.pushFront(44);

	cout << Search<int>(v2.begin(), v2.end(), 55) << endl;;

}