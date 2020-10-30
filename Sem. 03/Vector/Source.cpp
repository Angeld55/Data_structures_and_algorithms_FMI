#include "Vector.hpp"

int main()
{
	Vector<int> v;

	v.pushBack(4);
	v.insertAt(0, 44);
	v.insertAt(2, 55);
	v.print();
}