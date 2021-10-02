#include <iostream>
#include <functional>
using namespace std;

struct Node
{
	int number;
	Node* next;

	Node(int number, Node* next = nullptr) : number(number), next(next) {}
};

void print(Node* list)
{
	Node* iter = list;

	while (iter != nullptr)
	{
		cout << iter->number;
		if (iter->next != nullptr)
			cout << "->";
		iter = iter->next;
	}
}

void Free(Node* list)
{
	Node* iter = list;

	while (iter != nullptr)
	{
		Node* toRemove = iter;
		iter = iter->next;
		delete toRemove;
	}
}

int addOne(int number)
{
	return number + 1;
}

void map(Node* list, function<int(int)> func)
{
	Node* iter = list;

	while (iter != nullptr)
	{
		iter->number = func(iter->number);
		iter = iter->next;
	}
}

int main()
{
	Node* n = new Node(3, new Node(7, new Node(9, new Node(10, new Node(11)))));

	map(n, addOne);
	print(n);
	Free(n);
}