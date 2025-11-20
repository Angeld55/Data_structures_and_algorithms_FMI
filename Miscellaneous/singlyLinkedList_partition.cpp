#include <iostream>

struct Node
{
	int data;
	Node* next = nullptr;
	Node(int value, Node* ptr = nullptr) : data(value), next(ptr) {}
};

void push_back(Node*& begin, Node*& end, Node* toAdd)
{
	if (begin == nullptr)
	{
		begin = end = toAdd;
	}
	else
	{
		end->next = toAdd;
		end = toAdd;
		///toAdd->next = nullptr !!! NO! You need this pointer in the next iteration of the partition func
	}
}

template <class PredicateType>
Node* partition(Node* list, const PredicateType& pred)
{
	Node* trueListBegin = nullptr;
	Node* trueListEnd = nullptr;

	Node* falseListBegin = nullptr;
	Node* falseListEnd = nullptr;

	while (list != nullptr)
	{
		if (pred(list->data))
			push_back(trueListBegin, trueListEnd, list);
		else
			push_back(falseListBegin, falseListEnd, list);
		list = list->next;
	}
	if (trueListEnd)
		trueListEnd->next = falseListBegin;
	if(falseListEnd)
		falseListEnd->next = nullptr;

	return trueListBegin != nullptr ? trueListBegin : falseListBegin;
}

void printList(Node* iter)
{
	while (iter != nullptr)
	{
	    
		std::cout << iter->data;
		if(iter->next)
		   std::cout << " -> ";
		iter = iter->next;
	}
}
void freeList(Node* iter)
{
	while (iter != nullptr)
	{
		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}
}

int main()
{
	Node* list = new Node{ 3, new Node{4, new Node{5, new Node{6}}} };
	Node* newBegin = partition(list, [](int x) {return x % 2 == 0; });
	printList(newBegin);
	freeList(newBegin);
}

