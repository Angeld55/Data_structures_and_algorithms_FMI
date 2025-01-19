#include <iostream>
#include "LinkedStack.hpp"

int main() 
{
	LinkedStack<int> list;
	list.push(15);
	list.push(20);
	std::cout << list.peek() << std::endl;
	list.pop();
	std::cout << list.isEmpty() << std::endl;
	std::cout << list.peek() << std::endl;
	list.pop();

	list.push(100);

	LinkedStack<int> newList = list;
	std::cout << newList.peek() << std::endl;

	return 0;
}