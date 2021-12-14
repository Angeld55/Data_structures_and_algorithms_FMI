#include <iostream>
#include <vector>
#include "Algorithms.hpp"
#include "PriorityQueue.hpp"


int main()
{
	PriorityQueue<int> pq({ 1, 2, 3, 4, 4, 5, 7, 8 });
	pq.print();
	std::cout << "----------------------------------------------\n";

	pq.insert(100000);
	pq.insert(-4);
	pq.insert(55);
	std::cout << "After inserting 100000, -4, 55:\n";
	pq.print();
	std::cout << "----------------------------------------------\n";

	std::cout << "Remove the biggest element:\n";
	pq.pop();
	pq.print();


	std::cout << "\nHeap Sort:\n";
	std::vector<int> v = { 15, 4, 8, 12, 54 ,2, 10 };
	HeapSort(v);
	for (int i = 0; i < v.size(); i++)
	{
		std::cout << v[i] << ' ';
	}

}
