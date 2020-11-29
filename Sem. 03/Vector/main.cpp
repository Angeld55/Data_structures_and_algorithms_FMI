#include "DynamicArray.hpp"

int main()
{
	DynamicArray<int> d;
	d.PushBack(3);
	d.PushBack(1);
	d.PushBack(11);
	d[1] = 4;
	d.InsertAt(0, 7);
	std::cout << d.PopBack()<<std::endl;
	std::cout << d.PopBack() << std::endl;
	std::cout << d.PopBack() << std::endl;
	std::cout << d.PopBack() << std::endl;
}
