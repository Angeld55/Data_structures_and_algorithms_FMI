#include <iostream>
using namespace std;

int Max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}
int getMax(const int* arr, int len)
{
	if (len == 1)
		return arr[0];
	return Max(arr[0], getMax(arr + 1, len - 1));
}
// T(n) = T(n-1) + 1  -> O(n)
int main()
{
	
}