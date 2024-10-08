#include <iostream>
using namespace std;

template <class T>
int binarySearch(const T* arr, int len, const T& searched)
{
	int leftIndex = 0;
	int rightIndex = len - 1;
	while (leftIndex <= rightIndex)
	{
		int midIndex = (leftIndex + (rightIndex - leftIndex) / 2;

		if (arr[midIndex] == searched)
			return midIndex;
		
		if (arr[midIndex] > searched)
			rightIndex = midIndex - 1;
		else
			leftIndex = midIndex + 1;
	}
	return -1;

}

template <typename Iterator, typename T>
Iterator binarySearch(Iterator begin, Iterator end, const T& value) 
{
    Iterator left = begin;
    Iterator right = end;

    while (left < right) 
    {
        Iterator middle = left + std::distance(left, right) / 2;

        if (*middle == value) 
            return middle;
        else if (*middle < value) 
            left = middle + 1;
        else 
            right = middle;
    }
    return end;  

int main()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7 };

	cout << binarySearch<int>(arr, 7, 10);
}
