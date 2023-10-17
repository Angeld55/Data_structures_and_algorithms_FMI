#include <iostream>

template <class T>
void swap(T& i, T& j)
{
    T temp = i;
    i = j;
    j = temp;
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
                minIndex = j;
        }

        if(i != minIndex)
          swap(arr[i], arr[minIndex]);
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
