#include <iostream>
#include <utility>
using namespace std;

template <class T>
void bubbleSort(T* arr, unsigned len)
{
    unsigned end = len - 1;
    for (int i = 0; i < len; i++)
    {
        unsigned lastSwappedIndex = 0;

        for (int j = 0; j < end; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
                lastSwappedIndex = j;
            }
        }

        end = lastSwappedIndex;
        if (lastSwappedIndex == 0) // Is the array already sorted?
            return;
    }
}

int main()
{
    int arr[] = { 7, 6, 5, 4, 3, 2, 1 };

    bubbleSort<int>(arr, 7);

    for (int i = 0; i < 7; i++)
        cout << arr[i] << " ";

    return 0;
}
