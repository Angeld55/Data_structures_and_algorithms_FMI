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
std::pair<Node*, Node*> partition(Node* list, const PredicateType& pred)
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
	{
		trueListEnd->next = nullptr;
	}
	if (falseListEnd)
	{
		falseListEnd->next = nullptr;
	}

	return std::make_pair(trueListBegin, falseListBegin);
}

// <begin, end>
std::pair<Node*, Node*> concatLists(Node* leftBegin, Node* leftEnd, Node* rightBegin, Node* rightEnd) 
{
	if (leftBegin == nullptr) return std::make_pair(rightBegin, rightEnd); 
	if (rightBegin == nullptr) return std::make_pair(leftBegin, leftEnd);

	leftEnd->next = rightBegin;
	return std::make_pair(leftBegin, rightEnd);
}


std::pair<Node*, Node*> quickSort(Node* list)
{
	if (!list || !list->next)
		return std::make_pair(list, list);

	int pivot = list->data;
	auto partitionResults = partition(list, [pivot](int el) {return el < pivot; });

	Node* pivotPtr = partitionResults.second;

	auto leftToConcat = quickSort(partitionResults.first);
	auto rightToConcat = quickSort(partitionResults.second->next); //skip the pivot

	pivotPtr->next = rightToConcat.first; //attach the pivot to the begin of right
	rightToConcat.first = pivotPtr;
	if (!rightToConcat.second) //the right was empty list, we should concat only the pivot
		rightToConcat.second = pivotPtr;

	return concatLists(leftToConcat.first, 
					   leftToConcat.second,
		               rightToConcat.first,
		               rightToConcat.second);
}

void printList(Node* iter)
{
	while (iter != nullptr)
	{
		std::cout << iter->data;
		if (iter->next)
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
	Node* list = new Node{ 31, new Node{4, new Node{53, new Node{2}}} };
	
	auto res = quickSort(list);
	list = res.first;
	printList(list);
	freeList(list);
}
