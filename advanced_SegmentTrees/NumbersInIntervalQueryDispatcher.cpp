#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;


class NumbersInIntervalQueryDispatcher
{
	std::vector<int> arr;
	std::vector<std::vector<int>> segmentTree; //for update queries consider using SET

	size_t leftChild(size_t current)
	{
		return current * 2 + 1;
	}

	size_t rightChild(size_t current)
	{
		return current * 2 + 2;
	}

	void build(size_t currentVertex, size_t currentLeftBound, size_t currentRightBound)
	{
		if (currentLeftBound == currentRightBound)
			segmentTree[currentVertex].push_back(arr[currentLeftBound]);

		else
		{
			size_t mid = currentLeftBound + (currentRightBound - currentLeftBound) / 2;

			build(leftChild(currentVertex), currentLeftBound, mid);
			build(rightChild(currentVertex), mid + 1, currentRightBound);

			std::merge(segmentTree[leftChild(currentVertex)].begin(), segmentTree[leftChild(currentVertex)].end(), segmentTree[rightChild(currentVertex)].begin(), segmentTree[rightChild(currentVertex)].end(), back_inserter(segmentTree[currentVertex]));
		}
	}

	size_t countNumberInIntervalFromArray(const std::vector<int> v, int L, int R)
	{
		auto it1 = lower_bound(v.begin(), v.end(), L);
		auto it2 = upper_bound(v.begin(), v.end(), R);

		return distance(it1, it2);
	}

	size_t getNumbersFromSubarrayInInteraval_rec(size_t currentVertex, size_t currentLeftBound, size_t currentRightBound, size_t subarrayStart, size_t subarrayEnd, size_t L, size_t R)
	{
		if (subarrayStart > subarrayEnd)
			return 0;

		if (currentLeftBound == subarrayStart && currentRightBound == subarrayEnd)
			return countNumberInIntervalFromArray(segmentTree[currentVertex], L, R);

		size_t mid = currentLeftBound + (currentRightBound - currentLeftBound) / 2;
		return getNumbersFromSubarrayInInteraval_rec(leftChild(currentVertex), currentLeftBound, mid, subarrayStart, std::min(subarrayEnd, mid), L, R) +
			getNumbersFromSubarrayInInteraval_rec(rightChild(currentVertex), mid + 1, currentRightBound, std::max(subarrayStart, mid + 1), subarrayEnd, L, R);
	}

public:
	NumbersInIntervalQueryDispatcher(const std::vector<int>& arr) : segmentTree(4 * arr.size()), arr(arr)
	{
		build(0, 0, arr.size() - 1);
	}

	size_t getNumbersFromSubarrayInInteravl(size_t subarrayStart, size_t subarrayEnd, size_t L, size_t R)
	{
		return getNumbersFromSubarrayInInteraval_rec(0, 0, arr.size() - 1, subarrayStart, subarrayEnd, L, R);
	}
};


int main()
{

	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };

	NumbersInIntervalQueryDispatcher disp(v);
	cout << disp.getNumbersFromSubarrayInInteravl(0, 9, -1, 11);
}
