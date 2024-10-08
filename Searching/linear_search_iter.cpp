#include <iostream>

template <class T>
int linearSearch(const T* arr, unsigned len, const T& searched)
{
	for (int i = 0; i < len; i++)
	{
		if (arr[i] == searched)
			return i;
	}
	return -1;
}

//with iterators
template <typename Iterator, typename T>
Iterator linearSearch(Iterator begin, Iterator end, const T& value) {
    for (Iterator it = begin; it != end; ++it) 
    {
        if (*it == value) 
	{
            return it;  
        }
    }
    return end;
}

int main()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7 };

	std::cout << linearSearch<int>(arr, 7, 10);
}
