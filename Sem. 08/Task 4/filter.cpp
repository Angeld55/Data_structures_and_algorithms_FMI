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

void free(Node* list)
{
	Node* iter = list;

	while (iter != nullptr)
	{
		Node* toRemove = iter;
		iter = iter->next;
		delete toRemove;
	}
}

bool isEven(int number)
{
	return number % 2 == 0;
}

Node* filter(Node* list, function<bool(int)> func)
{
	Node* iter = list;
	Node* newList = nullptr, * first = nullptr;

	while (true)
	{
		if (func(iter->number))
		{
			if (first == nullptr)
				first = newList = iter;
			else
			{
				newList->next = iter;
				newList = newList->next;
			}
			iter = iter->next;
		}
		else
		{
			Node* toRemove = iter;
			iter = iter->next;
			delete toRemove;
		}

		if (iter == nullptr)
		{
			if (newList)
				newList->next = nullptr;
			break;
		}
	}
	return first;
}

int main()
{
	Node* n = new Node(3, new Node(7, new Node(9, new Node(10, new Node(11)))));

	Node* newNode = filter(n, isEven);
	print(newNode);
	free(newNode);
}
