#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class SumQueryDispatcher
{
	std::vector<int> arr;
	std::vector<int> segmentTree;

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
			segmentTree[currentVertex] = arr[leftBound];
		else
		{
			size_t mid = leftBound + (rightBound - leftBound) / 2;
			build(leftChild(currentVertex), leftBound, mid);
			build(rightChild(currentVertex), mid + 1, rightBound);

			segmentTree[currentVertex] = segmentTree[leftChild(currentVertex)] + segmentTree[rightChild(currentVertex)];
		}
	}

	int getSumRec(size_t currentVertex, size_t currentLeftBound, size_t currentRightBound, size_t searchedLeftBound, size_t searchedRightBound)
	{
		if (searchedLeftBound > searchedRightBound)
			return 0;

		if (currentLeftBound == searchedLeftBound && currentRightBound == searchedRightBound)
			return segmentTree[currentVertex];

		size_t mid = currentLeftBound + (currentRightBound - currentLeftBound) / 2;
		return getSumRec(leftChild(currentVertex), currentLeftBound, mid, searchedLeftBound, std::min(searchedRightBound, mid)) +
			getSumRec(rightChild(currentVertex), mid + 1, currentRightBound, std::max(searchedLeftBound, mid + 1), searchedRightBound);

	}

	void update_rec(size_t currentVertex, size_t currentLeftBound, size_t currentRightBound, size_t index, size_t newValue)
	{
		if (currentLeftBound == currentRightBound)
			segmentTree[currentVertex] = newValue;
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
	SumQueryDispatcher(const std::vector<int>& arr) : arr(arr), segmentTree(4 * arr.size(), 0)
	{
		build(0, 0, arr.size() - 1);
	}

	int getSum(size_t leftBound, size_t rightBound)
	{
		return getSumRec(0, 0, arr.size() - 1, leftBound, rightBound);
	}
	void update(size_t index, size_t value)
	{
		update_rec(0, 0, arr.size() - 1, index, value);
		arr[index] = value;
	}
};

int main()
{
	std::vector<int> v = { 1, 3, -2, 8, -7 };

	SumQueryDispatcher disp(v);

	disp.update(0, 1);
	disp.update(1, 2);
	disp.update(2, 3);
	disp.update(3, 4);
	disp.update(4, 5);

	cout << disp.getSum(0, 4);
}
