#include <iostream>
using namespace std;


template <class T>
size_t Merge(T* firstArr, size_t firstSize, T* secondArr, size_t secondSize, T* resultArr)
{
    size_t invCount = 0;
    
	size_t resultIter = 0; 
	size_t firstIter = 0;
	size_t secondIter = 0;

	while(firstIter < firstSize && secondIter < secondSize)
	{
	    if(firstArr[firstIter] < secondArr[secondIter])
	    {
	        resultArr[resultIter++] =  firstArr[firstIter++];
	    }
	    else
	    {
	         resultArr[resultIter++] =  secondArr[secondIter++];
	         invCount += firstSize - firstIter; 
	    }
	}
	
	while(firstIter < firstSize)
		resultArr[resultIter++] = firstArr[firstIter++];

	while(secondIter < secondSize)
		resultArr[resultIter++] = secondArr[secondIter++];
	return invCount;
}

template <class T>
size_t MergeSortStep(T* pArr, size_t Size, T* pBuffer)
{
	if(Size <= 1)
		return 0;

	size_t middle = Size / 2;

	size_t first = MergeSortStep(pArr, middle, pBuffer);

	size_t second = MergeSortStep(pArr + middle, Size - middle, pBuffer + middle);

	size_t third = Merge(pArr, middle, pArr + middle, Size - middle, pBuffer);

	for(size_t i = 0; i < Size; i++)
		pArr[i] = pBuffer[i];
	
	return first + second + third;
}

template <class T>
size_t MergeSortInversionCount(T* pArr, size_t Size)
{
	if (!pArr || Size == 0)
		return 0;

	T* pBuffer = new T[Size];

	size_t res = MergeSortStep(pArr, Size, pBuffer);

	delete[]  pBuffer;
	return res;
}


const int SIZE = 15;
int main()
{
	int arr1[] = { 90, 30, 15,14,13,12,11,8,7,6,5,4,3,2,1};
	size_t inversionCount = MergeSortInversionCount(arr1, SIZE);

	for (int i = 0; i < SIZE; i++)
		cout << arr1[i] << " ";
	cout << endl << "Inversion count: " << inversionCount << endl;
}
