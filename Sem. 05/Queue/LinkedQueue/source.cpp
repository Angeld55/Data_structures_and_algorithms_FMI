#include <iostream>
#include "LinkedQueue.hpp"

int main()
{
	LinkedQueue<int> q;

	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);

	std::cout << q.dequeue() << std::endl;
	std::cout << q.dequeue() << std::endl;
	std::cout << q.dequeue() << std::endl;
	std::cout << q.dequeue() << std::endl;
	std::cout << q.dequeue() << std::endl;

	std::cout << q.isEmpty() << std::endl;

	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);

	LinkedQueue<int> q2(q);
	std::cout << q2.dequeue() << std::endl;
	std::cout << q2.dequeue() << std::endl;
	std::cout << q2.dequeue() << std::endl;
	std::cout << q2.dequeue() << std::endl;
	std::cout << q2.dequeue() << std::endl;
}