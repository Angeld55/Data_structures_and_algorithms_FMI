#include <iostream>
#include "CircularQueue.hpp"

int main()
{
	Queue<int> q;

	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);

	std::cout << q.peek() << std::endl;
	q.dequeue();
	std::cout << q.peek() << std::endl;
	q.dequeue();
	std::cout << q.peek() << std::endl;
	q.dequeue();
	std::cout << q.peek() << std::endl;
	q.dequeue();
	std::cout << q.peek() << std::endl;
	q.dequeue();

	std::cout << q.isEmpty() << std::endl;

	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);

	Queue<int> q2(q);
	std::cout << q.peek() << std::endl;
	q.dequeue();
	std::cout << q.peek() << std::endl;
	q.dequeue();
	std::cout << q.peek() << std::endl;
	q.dequeue();
	std::cout << q.peek() << std::endl;
	q.dequeue();
	std::cout << q.peek() << std::endl;
	q.dequeue();
}