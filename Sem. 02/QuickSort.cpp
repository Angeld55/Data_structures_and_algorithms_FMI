#include <iostream>
using namespace std;

template <typename T>
int partition(T* arr, int len)
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
void quickSort(T* arr, size_t len)
{
	if (len <= 1)
		return;

	size_t pivotIndex = partition(arr, len);
	quickSort(arr, pivotIndex);
	quickSort(arr + pivotIndex + 1, len - pivotIndex - 1);
}
// Best case: T(n) = 2*T(n/2) + 1 easy solved with Master theorem
// Worst case :T(n) = T(n-1) + 1

const size_t SIZE = 15;
int main()
{
	int arr1[] = { 15,14,13,12,11,30,90,8,7,6,5,4,3,2,1};
	quickSort(arr1, SIZE);

	for (int i = 0; i < SIZE; i++)
		cout << arr1[i] << ' ';



}
