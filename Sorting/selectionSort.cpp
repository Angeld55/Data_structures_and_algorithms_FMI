#include <iostream>
#include <utility> 
using namespace std;

template <class T>
void SelectionSort(T* arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int minElementIndex = i;

        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[minElementIndex])
                minElementIndex = j;
        }

        if (i != minElementIndex)
            std::swap(arr[i], arr[minElementIndex]); // Using std::swap
    }
}

int main()
{
    int arr[] = { 7, 6, 5, 4, 3, 2, 1 };
    int size = sizeof(arr) / sizeof(arr[0]);

    SelectionSort<int>(arr, size);

    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";

    return 0;
}
