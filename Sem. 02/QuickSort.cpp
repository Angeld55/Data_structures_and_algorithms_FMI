#include <iostream>
using namespace std;

template <typename T>
int Partition(T* arr, int len)
{

	T pivot = arr[len/2];
	int i = 0, j = len-1;

	while (true)
	{
		while (arr[j] > pivot)
			j--;
		
		while (arr[i] < pivot)
			i++;

		if (i < j)
			std::swap(arr[i], arr[j]);
		else
			return j;
	}
}


template <typename T>
void QuickSort(T* arr, int len)
{
	if (len <= 1)
		return;

	int pivotIndex = Partition(arr, len);
	QuickSort(arr, pivotIndex);
	QuickSort(arr + pivotIndex, len - pivotIndex-1);
}
// Best case: T(n) = 2T(n/2) + n
// Worst case : T(n) = T(n-1) + n;
int main()
{
	int arr1[] = {1,2,3,4,5,6,7,8,9,10};
	QuickSort(arr1, 10);

	for (int i = 0; i < 10; i++)
		cout << arr1[i] << " ";
}
