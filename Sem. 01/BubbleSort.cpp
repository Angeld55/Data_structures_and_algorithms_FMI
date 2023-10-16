#include <iostream>

template <class T>
void swap(T& i, T& j)
{
    T temp = i;
    i = j;
    j = temp;
}

template <class T>
void bubbleSort(T* arr,int len)
{
    size_t right = len - 1;
    for(int j = 0; j < len; j++)
    {
        size_t lastSwappedIndex = 0;
        for(int i = 0; i < right; i++)
        {
            if(arr[i]>arr[i+1])
            {
                swap(arr[i], arr[i + 1]);
                lastSwappedIndex = i;
            }
        }

        right = lastSwappedIndex;
     }
}

int main()
{
    const size_t ARR_SIZE = 5;
    int arr[ARR_SIZE] = { 5,4,3,2,1 };

    bubbleSort<int>(arr, ARR_SIZE);

    for (size_t i = 0; i < ARR_SIZE; i++)
        std::cout << arr[i] << ' ';
    std::cout << std::endl;
}
