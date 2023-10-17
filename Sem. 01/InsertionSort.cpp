#include <iostream>

template <class T>
void swap(T& i, T& j)
{
    T temp = i;
    j = i;
    i = temp;
}

template <class T>
void naiveInsertionSort(T* arr,size_t len) 
{
    for(size_t i = 1; i < len; i++)
    {
        T elIndex = i;
        while(elIndex > 0 && arr[elIndex] < arr[elIndex - 1])
        {
            swap(arr, elIndex, elIndex - 1);
            elIndex--;
        }
    }
}

template <class T>
void insertionSort(T* arr, size_t len)
{
    for(size_t i = 1; i < len; i++)
    {
        T element = arr[i];
        int index = i - 1;
        while(index >= 0 && arr[index] > element)
        {
            arr[index + 1] = arr[index];
            index--;
        }
        arr[index + 1] = element;
    }
}

int main()
{
    const size_t ARR_SIZE = 5;
    int arr[ARR_SIZE] = { 5,4,3,2,1 };

    insertionSort<int>(arr, ARR_SIZE);

    for (size_t i = 0; i < ARR_SIZE; i++)
        std::cout << arr[i] << ' ';
    std::cout << std::endl;
}
