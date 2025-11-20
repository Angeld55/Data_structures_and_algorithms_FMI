
#include <iostream>

struct Node
{
    Node(int data, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

void freeList(Node* list)
{
    while (list) {
        Node* toDel = list;
        list = list->next;
        delete toDel;
    }
}

void printList(const Node* list)
{
    while (list)
    {
        std::cout << list->data;
        if (list->next)
            std::cout << "->";
        list = list->next;
    }
    std::cout << std::endl;
}


Node* reverseIter(Node* llist) 
{

    if (llist == nullptr || llist->next == nullptr)
        return llist;

    Node* curr = llist;
    Node* prev = nullptr;

    while (curr != nullptr) 
    {
        Node* temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    return prev;
}

Node* reverseRec(Node* llist)
{
    if (!llist || !llist->next)
        return llist;
    
    Node* next = llist->next;
    llist->next = nullptr;

    Node* reversedFromNext = reverseRec(next);
    
    next->next = llist;
    return reversedFromNext;
}

int main()
{
    Node* list = new Node(20, new Node(14, new Node(7)));

    list = reverseIter(list);
    printList(list);

    list = reverseRec(list);

    printList(list);

    free(list);
}

