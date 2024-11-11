#include <iostream>
#include "ArrayStack.hpp"

int main()
{

	ArrayStack<int> arrStack;
	arrStack.push(3);
	arrStack.push(5);
	arrStack.push(7);
	std::cout << arrStack.size() << std::endl;
	std::cout << arrStack.peek() << std::endl;
	arrStack.pop();
	std::cout << arrStack.peek() << std::endl;

	ArrayStack<int> newArrStack = arrStack;
	std::cout << newArrStack.size() << std::endl;


	return 0;
}