#include <iostream>
using namespace std;

template <class T>
bool linearSearch(const T* arr, unsigned len, const T& searched)
{
	if (len == 0)
		return false;
	
	return  *arr == searched || linearSearch(++arr, --len, searched);
}

template <typename Iterator, typename T>
Iterator linearSearch(Iterator begin, Iterator end, const T& value)
{
    if (begin == end)
        return end;
    
    if (*begin == value) 
        return begin;
    
    return linearSearch(++begin, end, value);
}

int main()
{
	int arr[5] = { 1, 2, 3, 4, 5 };
	cout << linearSearch<int>(arr, 5, 9);
}
