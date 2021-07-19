#include <iostream>
#include <vector>
#include "PriorityQueue.h"

void HeapSort(std::vector<int>& v)
{
	PriorityQueue q(v); // Ñòðîè ïèðàìèäà îò ìàñèâ - O(n)

	for (int i = v.size() - 1; i >= 0; i--)
		v[i] = q.get(); //log(n)
}

int main()
{
	PriorityQueue v({ 1, 2, 3, 4, 4, 5, 7, 8 });
	v.print();


	v.insert(100000);
	v.insert(-4);
	v.get();
	v.insert(55);

	v.print();

}
