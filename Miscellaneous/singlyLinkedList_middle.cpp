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

const Node* middleNode(const Node* head) 
{
    const Node* slow = head;
    const Node* fast = head;

    while (fast && fast->next) 
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

int main()
{
    Node* list = new Node(20, new Node(14, new Node(7)));

    std::cout << middleNode(list)->data << std::endl;

    free(list);

}