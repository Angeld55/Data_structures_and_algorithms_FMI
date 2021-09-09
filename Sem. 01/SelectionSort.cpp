#include <iostream>

template <class T>
void swap(T* arr,size_t i ,size_t j)
{
    T temp = arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}

template <class T>
void selectionSort(T* arr,size_t size)
{
    for(size_t i = 0; i < size - 1; i++)
    {
        size_t minIndex = i;

        for(int j = i + 1; j < size; j++)
        {
            if(arr[j] < arr[minIndex])
                minIndex=j;
        }

        if(i != minIndex)
          swap(arr,i,minIndex);
    }
}

int main()
{
    const size_t ARR_SIZE = 5;
    int arr[ARR_SIZE] = { 5,4,3,2,1 };

    selectionSort<int>(arr, ARR_SIZE);

    for (size_t i = 0; i < ARR_SIZE; i++)
        std::cout << arr[i] << ' ';
    std::cout << std::endl;
}
