#pragma once
#include "PriorityQueue.hpp"

void HeapSortExtraMemory(std::vector<int>& v)
{
	PriorityQueue<int> q(v); // Building heap - O(n)

	for (int i = v.size() - 1; i >= 0; i--)
	{
		v[i] = q.peek(); //log(n)
		q.pop();
	}

}


template <typename T>
void heapify(T* arr, size_t elIndex, size_t size)
{
    while(true)
    {
        size_t leftChildInd = 2 * elIndex + 1;
        size_t rightChildInd = 2 * elIndex + 2;
        
        bool shouldGoLeft = leftChildInd < size && arr[leftChildInd] > arr[elIndex];
        bool shouldGoRight = rightChildInd < size && arr[rightChildInd] > arr[elIndex];
        
        if(shouldGoLeft && !shouldGoRight)
        {
            std::swap(arr[elIndex], arr[leftChildInd]);
            elIndex = leftChildInd;
        }
        else if(!shouldGoLeft && shouldGoRight)
        {
            std::swap(arr[elIndex], arr[rightChildInd]);
            elIndex = rightChildInd;
        }
        else if(shouldGoLeft && shouldGoRight)
        {
            if(arr[leftChildInd] > arr[rightChildInd])
            {
                std::swap(arr[elIndex], arr[leftChildInd]);
                elIndex = leftChildInd;

            }
            else
            {
                std::swap(arr[elIndex], arr[rightChildInd]);
                elIndex = rightChildInd;
            }
        }
        else
            break;
    }
}

template <typename T>
void heapSort(T* arr, size_t size)
{
    size_t mid = size / 2;
    
    for(int i = mid; i >= 0; i--)
        heapify(arr, i, size);
        
    for(int i = size - 1; i >= 0; i--)
    {
        std::swap(arr[0], arr[i]);
        heapify(arr, 0, i);
    }
}

int main()
{
    int arr[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1};
    
    heapSort(arr, 9);
    
    for(int i = 0; i < 9; i++)
        std::cout << arr[i] << " ";

    return 0;
}
