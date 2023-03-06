#include <iostream>
using namespace std;

struct Node
{
    Node* next = nullptr;
    int data;
    
    Node(int data, Node* next = nullptr) : data(data), next(next){}
};

void print(const Node* root)
{
    while(root)
    {
        std::cout << root->data << " ";
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

Node* mergeLists(Node* firstIter, Node* secondIter)
{
    if(firstIter == nullptr)
        return secondIter;
    if(secondIter == nullptr)
        return firstIter;
        
    Node* resultRoot;
    Node* resultIter;
    
    if(firstIter->data < secondIter->data)
    {
        resultRoot = firstIter;
        resultIter = firstIter;
        firstIter = firstIter->next;
    }   
    else
    {
        resultRoot = secondIter;
        resultIter = secondIter;
        secondIter = secondIter->next;
    }
    
    while(firstIter && secondIter)
    {
        if(firstIter->data <= secondIter->data)
        {
            resultIter->next = firstIter;
            firstIter = firstIter->next;
        }
        else
        {
            resultIter->next = secondIter;
            secondIter = secondIter->next;
        }
        resultIter = resultIter->next;
    }
    
    resultIter->next = firstIter ? firstIter : secondIter;
    return resultRoot;
}

Node* getMid(Node* list)
{
    Node* slow = list;
    Node* fast = list ->next;
    
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
    Node* list = new Node(20, new Node(14, new Node(7)));
    list = mergeSort(list);
    print(list);
    freeList(list);
    list = nullptr;
}
