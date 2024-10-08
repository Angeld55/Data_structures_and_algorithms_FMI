#include <iostream>
#include <utility>
using namespace std;

template <class T>
void naiveInsertionSort(T* arr, int len) 
{
    for (int i = 1; i < len; i++)
    {
        int elIndex = i; 
        while (elIndex > 0 && arr[elIndex] < arr[elIndex - 1])
        {
            std::swap(arr[elIndex], arr[elIndex - 1]); 
            elIndex--;
        }
    }
}

template <class T>
void insertionSort(T* arr, int len)
{
    for (int i = 1; i < len; i++)
    {
        T element = arr[i];
        int index = i - 1;
        while (index >= 0 && arr[index] > element)
        {
            arr[index + 1] = arr[index];
            index--;
        }
        arr[index + 1] = element; // Inserting the element at the correct position
    }
}

int main()
{
    int arr[] = { 7, 6, 5, 4, 3, 2, 1 };
    int len = sizeof(arr) / sizeof(arr[0]);

    // Using Naive Insertion Sort
    NaiveInsertionSort<int>(arr, len);
    cout << "Sorted using Naive Insertion Sort: ";
    for (int i = 0; i < len; i++)
        cout << arr[i] << " ";
    cout << endl;

    // Resetting the array for the next sort
    int arr2[] = { 7, 6, 5, 4, 3, 2, 1 };

    // Using Insertion Sort
    InsertionSort<int>(arr2, len);
    cout << "Sorted using Insertion Sort: ";
    for (int i = 0; i < len; i++)
        cout << arr2[i] << " ";
    cout << endl;

    return 0;
}
