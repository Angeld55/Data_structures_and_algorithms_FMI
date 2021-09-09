#include "DynamicArray.hpp"

int main()
{
	DynamicArray<int> d;
	d.pushBack(3);
	d.pushBack(1);
	d.pushBack(11);

	d[1] = 4;

	std::cout << d.popBack()<<std::endl;
	std::cout << d.popBack() << std::endl;
	std::cout << d.popBack() << std::endl;
	
	std::cout << d.isEmpty() << std::endl;

	d.pushBack(9);
	d.pushBack(8);
	d.pushBack(7);
	d.pushBack(6);
	d.pushBack(5);

	std::cout << d.popBack() << std::endl;
	std::cout << d.popBack() << std::endl;
	std::cout << d.popBack() << std::endl;

	std::cout << d[1] << std::endl;
	std::cout << d[0] << std::endl;

}
