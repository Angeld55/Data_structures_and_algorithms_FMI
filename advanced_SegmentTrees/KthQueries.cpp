#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class KthQueriesDispatcher
{
	std::vector<int> arr;
	std::vector<int> segmentTree;
	int elementForQueries;

	size_t leftChild(size_t current)
	{
		return current * 2 + 1;
	}

	size_t rightChild(size_t current)
	{
		return current * 2 + 2;
	}

	void build(size_t currentVertex, size_t leftBound, size_t rightBound)
	{
		if (leftBound == rightBound)
		{
			segmentTree[currentVertex] = arr[leftBound] == elementForQueries;
		}
		else
		{
			size_t mid = leftBound + (rightBound - leftBound) / 2;
			build(leftChild(currentVertex), leftBound, mid);
			build(rightChild(currentVertex), mid + 1, rightBound);

			segmentTree[currentVertex] = segmentTree[leftChild(currentVertex)] + segmentTree[rightChild(currentVertex)];
		}
	}

	int getKth_rec(size_t currentVertex, size_t currentLeftBound, size_t currentRightBound, size_t k) const
	{
		if (k > segmentTree[currentVertex])
			return -1;
		if (currentLeftBound == currentRightBound)
			return currentLeftBound;

		size_t mid = currentLeftBound + (currentRightBound - currentLeftBound) / 2;

		if (segmentTree[leftChild(currentVertex)] >= k)
			return getKth_rec(leftChild(currentVertex), currentLeftBound, mid, k);
		else
			return getKth_rec(rightChild(currentVertex), mid + 1, currentRightBound, k - segmentTree[leftChild(currentVertex)]);
	}


	void update_rec(size_t currentVertex, size_t currentLeftBound, size_t currentRightBound, size_t index, size_t newValue)
	{
		if (currentLeftBound == currentRightBound)
			segmentTree[currentVertex] = arr[currentLeftBound] == elementForQueries;
		else
		{
			size_t mid = currentLeftBound + (currentRightBound - currentLeftBound) / 2;
			if (index <= mid)
				update_rec(leftChild(currentVertex), currentLeftBound, mid, index, newValue);
			else
				update_rec(rightChild(currentVertex), mid + 1, currentRightBound, index, newValue);

			segmentTree[currentVertex] = segmentTree[leftChild(currentVertex)] + segmentTree[rightChild(currentVertex)];
		}
	}

public:
	KthQueriesDispatcher(const std::vector<int>& arr, int elementForQueries) : arr(arr), segmentTree(4 * arr.size(), 0), elementForQueries(elementForQueries)
	{
		build(0, 0, arr.size() - 1);
	}

	int getKth(size_t k) const
	{
		return getKth_rec(0, 0, arr.size() - 1, k);
	}

	void update(size_t index, size_t value)
	{
		update_rec(0, 0, arr.size() - 1, index, value);
		arr[index] = value;
	}
};

int main()
{
	std::vector<int> v = { 1, 2, 3, 2, 2, 2, 2 };

	KthQueriesDispatcher disp(v, 2);

	cout << disp.getKth(3);
}
