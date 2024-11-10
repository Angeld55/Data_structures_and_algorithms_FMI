#include <iostream>
#include <functional>

struct Node
{
    Node* next;
    int data;
};

template <typename Predicate>
Node* removeNodes(Node* head, Predicate predicate) 
{
    Node** current = &head;
    while (*current != nullptr) 
    {
        if (predicate((*current)->data))
        {
            Node* temp = *current;
            *current = (*current)->next;
            delete temp;
        } 
        else
        {
            current = &(*current)->next;
        }
    }
    return head;
}

void printList(Node* head) 
{
    Node* current = head;
    while (current != nullptr) 
    {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void freeList(Node* list)
{
    Node* curr = list;
    
    while(curr)
    {
        Node* toDelete = curr;
        curr = curr->next;
        delete toDelete;
    }
}

int main() {
    // Create a sample list: 1 -> 2 -> 3 -> 4 -> 5
    Node* head = new Node{nullptr, 1};
    head->next = new Node{nullptr, 2};
    head->next->next = new Node{nullptr, 3};
    head->next->next->next = new Node{nullptr, 4};
    head->next->next->next->next = new Node{nullptr, 5};

    std::cout << "Original list: ";
    printList(head);

    head = removeNodes(head, [](int data) { return data % 2 == 0; });

    std::cout << "List after removing even values: ";
    printList(head);

    head = removeNodes(head, [](int) { return true; });

    freeList(head);
    return 0;
}
