#include <iostream>
using namespace std;

template <class T>
size_t partition(T* pArr, size_t len)
{
    if(pArr[0] > pArr[len - 1])
        std::swap(pArr[0],  pArr[len - 1]);

	T& partitioningElement = pArr[len-1];
    
    size_t left = 0;
    size_t right = len - 1;

	while(true)
	{
		while(pArr[++left] < partitioningElement)
			;

		while(pArr[--right] > partitioningElement)
		{
			if(left == right)
				break;
		}

		if(left >= right)
			break;

		std::swap(pArr[left], pArr[right]);
	}

	std::swap(pArr[left], partitioningElement);

	return left;
}



template <typename T>
void QuickSort(T* arr, size_t len)
{
	if (len <= 1)
		return;
	
	size_t pivotIndex = partition(arr, len);

	QuickSort(arr, pivotIndex);
	QuickSort(arr + pivotIndex + 1, len - pivotIndex-1);
}


const int SIZE = 15;
int main()
{
	int arr1[] = { 15,14,13,12,11,30,90,8,7,6,5,4,3,2,1};
	QuickSort(arr1, SIZE);

	for (int i = 0; i < SIZE; i++)
		cout << arr1[i] << " ";
}
