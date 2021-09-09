#include <iostream>

template <class T> void mergeSort(T* arr, int len);

template <class T> void merge(T* arr1, size_t len1,T* arr2, size_t len2);

template <class T>
void mergeSort(T* arr, int len)
{  
    if(len<=1)
        return;
        
    size_t mid = len/2;

    mergeSort(arr, mid);
    mergeSort(arr + mid, len - mid);
  
    merge<T>(arr, mid, arr+mid, len-mid);
 
}
template <class T>
void merge(T* arr1, size_t arr1len,T* arr2, size_t arr2len)
{
    T* result = new T[arr1len + arr2len];

    size_t cursor1 = 0, cursor2 = 0, resultCursor = 0;

    while(cursor1 < arr1len && cursor2 < arr2len)
    {
        if(arr1[cursor1] <= arr2[cursor2])
            result[resultCursor++] = arr1[cursor1++];
        else  
            result[resultCursor++] = arr2[cursor2++];
    }

    while(cursor1 < arr1len)
        result[resultCursor++]=arr1[cursor1++];

    while(cursor2 < arr2len)
        result[resultCursor++]=arr2[cursor2++];
        
   //Въпреки,че arr1 е с по-малка големина, можем да си ползволим това да излезем извън масива, понеже знаем, че arr1 с arr2 са слепени     
    for(size_t i = 0; i < (arr1len + arr2len); i++)
        arr1[i] = result[i];
    delete[] result;
}

int main()
{
    const size_t SIZE = 9;
    int arr[SIZE] = { 9,8,7,6,5,4,3,2,1 };

    mergeSort<int>(arr, SIZE);

    for (int i = 0; i < SIZE; i++)
        std::cout << arr[i] << ' ';
    std::cout << std::endl;

}