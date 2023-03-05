#include <iostream>
using namespace std;


template <class T>
void Merge(T* firstArr, size_t firstSize, T* secondArr, size_t secondSize, T* resultArr)
{
	size_t resultIter = 0; 
	size_t firstIter = 0;
	size_t secondIter = 0;

	while(firstIter < firstSize && secondIter < secondSize)
		resultArr[resultIter++] = (firstArr[firstIter] < secondArr[secondIter] ? firstArr[firstIter++] : secondArr[secondIter++]);

	while(firstIter < firstSize)
		resultArr[resultIter++] = firstArr[firstIter++];

	while(secondIter < secondSize)
		resultArr[resultIter++] = secondArr[secondIter++];
}

template <class T>
void MergeSortStep(T* pArr, size_t Size, T* pBuffer)
{
	if(Size <= 1)
		return;

	size_t middle = Size / 2;

	MergeSortStep(pArr, middle, pBuffer);

	MergeSortStep(pArr + middle, Size - middle, pBuffer + middle);

	Merge(pArr, middle, pArr + middle, Size - middle, pBuffer);

	for(size_t i = 0; i < Size; i++)
		pArr[i] = pBuffer[i];
}

template <class T>
void MergeSort(T* pArr, size_t Size)
{
	if (!pArr || Size == 0)
		return;

	T* pBuffer = new T[Size];

	MergeSortStep(pArr, Size, pBuffer);

	delete[]  pBuffer;
}


const int SIZE = 15;
int main()
{
	int arr1[] = { 15,14,13,12,11,30,90,8,7,6,5,4,3,2,1};
	MergeSort(arr1, SIZE);

	for (int i = 0; i < SIZE; i++)
		cout << arr1[i] << " ";
}
