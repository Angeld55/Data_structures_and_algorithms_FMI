#include <iostream>
using namespace std;

struct Node
{
    int data = 0;
    Node* next = nullptr;
    
    Node(int data, Node* next = nullptr) : data(data), next(next){}
};

void print(const Node* root)
{
    while(root)
    {
        std::cout << root->data;
        if(root->next)
            std::cout << "->";
        root = root->next;
    }
    std::cout << std::endl;
}

void freeList(Node* root)
{
    Node* current = root;
    while(current)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void pushBack(Node*& resultBegin, Node*& resultEnd, Node* toAdd)
{
	if (!resultBegin)
	{
		resultBegin = resultEnd = toAdd;
	}
	else
	{
		resultEnd->next = toAdd;
		resultEnd = toAdd;
	}
}

Node* mergeLists(Node* first, Node* second)
{
	Node* resultBegin = nullptr, *resultEnd = nullptr;

	while (first && second)
	{
		if (first->data < second->data)
		{
			pushBack(resultBegin, resultEnd, first);
			first = first->next;
		}
		else
		{
			pushBack(resultBegin, resultEnd, second);
			second = second->next;
		}
	}
	if (!first)
	{
		pushBack(resultBegin, resultEnd, second);
	}
	else
	{
		pushBack(resultBegin, resultEnd, first);
	}
	return resultBegin;
}


Node* getMid(Node* list)
{
    if(!list)
        return nullptr;
    Node* slow = list;
    Node* fast = list->next; //not the first, so in the even case we chose the first mid (needed due to spliting logic in MS)  
    
    while(fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Node* mergeSort(Node* list)
{
    
    if(!list || !list->next) 
        return list;
        
    Node* mid = getMid(list);

        
    Node* left = list;
    Node* right = mid->next;
    mid->next = nullptr;
    
    left = mergeSort(left);
    right = mergeSort(right);
    
    return mergeLists(left, right);
}


int main()
{
    Node* list = new Node(20, new Node(14, new Node(7, new Node(3))));
    list = mergeSort(list);
    print(list);
    freeList(list);
}
