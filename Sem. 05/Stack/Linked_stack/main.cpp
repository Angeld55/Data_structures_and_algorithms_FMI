#include <iostream>
#include "LinkedStack.hpp"

int main() 
{
	LinkedStack<int> list;
	list.push(15);
	list.push(20);
	std::cout << list.peek() << std::endl;
	std::cout << list.pop() << std::endl;
	std::cout << list.isEmpty() << std::endl;
	std::cout << list.peek() << std::endl;

	LinkedStack<int> newList = list;
	std::cout << newList.peek() << std::endl;

	return 0;
}