#include <iostream>
using namespace std;

int max(int a, int b)
{
	return a > b ? a : b;
}

int getMax(const int* arr, int len)
{
	if (len == 1)
		return arr[0];
	return max(arr[0], getMax(arr + 1, len - 1));
}
// T(n) = T(n-1) + 1  -> O(n)

int main()
{
	const size_t SIZE = 7;
	int arr[] = { 1, 2, 3, 4, 5, 3, 2 };

	std::cout << getMax(arr, SIZE);
}