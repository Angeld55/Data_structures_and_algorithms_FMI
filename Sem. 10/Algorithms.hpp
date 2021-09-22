#include "PriorityQueue.h"

void HeapSort(std::vector<int>& v)
{
	PriorityQueue q(v); // Building heap - O(n)

	for (int i = v.size() - 1; i >= 0; i--)
		v[i] = q.get(); //log(n)
}