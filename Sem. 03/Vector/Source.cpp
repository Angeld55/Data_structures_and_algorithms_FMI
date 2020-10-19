#include "Vector.hpp"

int main()
{
	Vector<int> v;

	v.push_back(4);
	v.push_back(10);
	v.push_back(15);
	v.push_back(16);
	v.print();

	v.push_back(33);
	v.print();

	v.insert_At(999, 1);
	v.print();

	v.pop_front();
	v.remove_At(1);
	v.remove_At(0);

	v.print();


	while (1){}
}