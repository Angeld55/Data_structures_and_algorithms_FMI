
#include <iostream>
#include <string>
using namespace std;

// Едносвързан списък.
// 0->5->7->1->4->6->9->2
// Пренаредим, така че първо да са четните, после да са начетните.
// Трябва да запазим относителната наредба!!!
// 0->4->6->2->5->7->1->9
// O(n)

struct Node
{
	Node(int value, Node* next) : value(value), next(next){}
	int value;
	Node* next;
};
void Print(Node* list)
{
	Node* iter = list;
	while (iter != nullptr)
	{
		cout << iter->value <<" ";
		iter = iter->next;
	}
}
Node* rearrange(Node* list)
{
	Node* firstEven;
	Node* lastEven;

	Node* firstOdd;
	Node* lastOdd;
	firstEven = lastEven = firstOdd = lastOdd = nullptr;

	Node* iter = list;

	while (iter != nullptr)
	{
		if (iter->value % 2 == 0)
		{
			if (firstEven == nullptr)
				firstEven = lastEven = iter;
			else
			{
				lastEven->next = iter;
				lastEven = iter;
			}
		}
		else
		{
			if (firstOdd == nullptr)
				firstOdd = lastOdd = iter;
			else
			{
				lastOdd->next = iter;
				lastOdd = iter;
			}

		}

		iter = iter->next;
	}
	if (lastEven)
		lastEven->next = firstOdd;
		
	if (lastOdd)
		lastOdd->next = nullptr;
	return lastEven != nullptr ? firstEven : firstOdd;
}
int main()
{
	Node* list = new Node(1, new Node(8,nullptr));
	Print(rearrange(list));
	

}