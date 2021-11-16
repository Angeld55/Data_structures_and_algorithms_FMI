#include <iostream>
using namespace std;

template <typename T>
struct Node
{
	T data;

	Node<T>* prev;
	Node<T>* next;
	Node<T>* child;

	Node(const T& data) : data(data), prev(nullptr), next(nullptr), child(nullptr)
	{}
};

template <typename T>
void free(Node<T>* iter)
{
	while (iter)
	{
		Node<T>* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}
}
template <typename T>
void print(Node<T>* iter)
{
	while (iter)
	{
		cout << iter->data;
		if (iter->next)
			cout << "->";
		iter = iter->next;
	}
}

template <typename T>
Node<T>* getMiddle(Node<T>* list)
{
	Node<T>* slowIter = list;
	Node<T>* fastIter = list;

	while (fastIter)
	{
		slowIter = slowIter->next;
		fastIter = fastIter->next->next;
	}

	return slowIter;
}

template <typename T>
void flatten(Node<T>* list)
{
	Node<T>* iter = getMiddle(list);

	while (iter)
	{
		if (iter->child)
		{
			Node<T>* tempNext = iter->next;
			Node<T>* tempChildIter = iter->child;

			iter->next = tempChildIter;
			tempChildIter->prev = iter;
			iter->child = nullptr;

			while (tempChildIter->next)
				tempChildIter = tempChildIter->next;
			
			if (tempNext)
			{
				tempChildIter->next = tempNext;
				tempNext->prev = tempChildIter;
			}
		}

		iter = iter->next;
	}

	print(list);
	free(list);
}

int main()
{
	Node<int>* n1 = new Node<int>(1);
	Node<int>* n2 = new Node<int>(2);
	Node<int>* n3 = new Node<int>(3);
	Node<int>* n4 = new Node<int>(4);
	Node<int>* n7 = new Node<int>(7);
	Node<int>* n8 = new Node<int>(8);
	Node<int>* n9 = new Node<int>(9);
	Node<int>* n10 = new Node<int>(10);
	Node<int>* n11 = new Node<int>(11);
	Node<int>* n12 = new Node<int>(12);

	n1->next = n2;
	n2->prev = n1;
	n2->next = n3;
	n3->prev = n2;
	n3->next = n4;
	n4->prev = n3;

	n3->child = n7;
	n7->next = n8;
	n8->prev = n7;
	n8->next = n9;
	n9->prev = n8;
	n9->next = n10;
	n10->prev = n9;

	n8->child = n11;
	n11->next = n12;
	n12->prev = n11;

	flatten(n1);
}