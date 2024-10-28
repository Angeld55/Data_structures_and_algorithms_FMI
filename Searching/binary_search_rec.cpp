#include <iostream>
using namespace std;

template <class T>
int binarySearch(const int* arr, int len, const T& searched)
{
	if (len == 0)
		return -1;

	int midIndex = len / 2;

	if (arr[midIndex] == searched)
		return midIndex;
	
	if (arr[midIndex] < searched)
	{
		int result = binarySearch(arr + midIndex + 1, len - midIndex - 1, searched);
		return (result == -1) ? -1 : result + midIndex + 1;
	}
	else
		return binarySearch(arr, midIndex, searched);
}

template <typename Iterator, typename T>
Iterator binarySearchIterators(Iterator left, Iterator right, const T& value) 
{
    if (left >= right) 
        return right;  
    
    Iterator middle = left + std::distance(left, right) / 2;

    if (*middle == value) 
        return middle;
    else if (*middle < value) 
        return binarySearchIterators(middle + 1, right, value);
    else 
        return binarySearchIterators(left, middle, value);
}

int main()
{
	int arr[] = { 1, 2, 2, 6, 19, 55 };
	cout << binarySearch(arr, 6, 19);
}
