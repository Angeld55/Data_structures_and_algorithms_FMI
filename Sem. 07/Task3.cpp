#include <iostream>
#include <string>
using namespace std;

struct Node
{
	Node(int value, Node* next) : value(value), next(next){}
	int value;
	Node* next;
};

void print(Node* list)
{
	Node* iter = list;
	while (iter != nullptr)
	{
		cout << iter->value <<" ";
		iter = iter->next;
	}
}

void freeList(Node* list)
{
	Node* iter = list;
	while(iter)
	{
		Node* next = iter->next;
		delete iter;
		iter = next;
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
	Node* list = new Node(1, new Node(8, nullptr));
	print(rearrange(list));
	freeList(list);

}
