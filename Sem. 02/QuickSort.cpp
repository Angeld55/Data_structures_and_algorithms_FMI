#include <iostream>
using namespace std;

template <typename T>
int Partition(T* arr, int len)
{

	T pivot = arr[len / 2];
	int i = 0, j = len-1 ;

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
