#include "Vector.hpp"

int main()
{
	Vector<int> v;

	v.pushBack(4);
	
	Vector<int> v2(v);

	v.print();

	while (1){}
}