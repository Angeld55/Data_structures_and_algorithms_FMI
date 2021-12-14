#pragma once
#include "PriorityQueue.hpp"

void HeapSort(std::vector<int>& v)
{
	PriorityQueue<int> q(v); // Building heap - O(n)

	for (int i = v.size() - 1; i >= 0; i--)
	{
		v[i] = q.peek(); //log(n)
		q.pop();
	}

}