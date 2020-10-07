#include <iostream>
#include <ctime>

using namespace std;

//b.c: O(n), a.c: O(n), w.c: O(n)
int sum(const int* arr, int len)
{
	int sum = 0;
	for (int i = 0; i < len; i++)
		sum += arr[i];
	
	return sum;
}

//b.c: O(1), a.c: O(n), w.c: O(n)
bool contains(const int* arr, int len, int el)
{
	for (int i = 0; i < len; i++)
	{
		if (arr[i] == el)
			return true;
	}
	return false;
}

//b.c: O(1), a.c: O(1), w.c: O(1)
int f1(const int* arr, int len)
{
	return arr[0] + arr[len - 1];
}


// 2^0 + 2^1 ... + 2^n = 2^(n+1) - 1
//b.c: O(n), a.c: O(n), w.c: O(n)
int f2(int n)
{
	int res = 0;
	int iter = 1;
	for (int i = 0; i <= n; i++)
	{
		res += iter * 2;
	}
}

//b.c: O(1), a.c: O(1), w.c: O(1)
int f2_better(int n)
{
	return (1 << (n + 1)) - 1;
	
}

//b.c: O(n), a.c: O(n), w.c: O(n)
int f3(int n) 
{
	int sum = 0;
	for (int i = 0; i <= n; i++)
		sum += i;
	return sum;
}
//b.c: O(n), a.c: O(1), w.c: O(1)
int f3_better(int n)
{
	return n*(n + 1) / 2;
}

//b.c: O(log(n)), a.c: O(log(n)), w.c: O(log(n))
bool isPowerOfTwo(int n)
{
	while (n > 1)
	{
		if (n % 2 == 1)
			return false;
		n /= 2;
	}
	return true;
}
//b.c: O(1), a.c: O(1), w.c: O(1)
bool isPowerOfTwo2_better(int n)
{
	if (n != 0)
		return n & (n - 1);
	return false;
}

int main()
{	

}
