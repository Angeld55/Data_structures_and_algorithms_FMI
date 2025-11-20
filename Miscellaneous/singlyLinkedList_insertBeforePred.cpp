#include <iostream>

struct Node {
    Node(int data, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

void print(const Node* list) {
    while (list) {
        std::cout << list->data;
        if (list->next)
            std::cout << " -> ";
        list = list->next;
    }
    std::cout << '\n';
}

void freeList(Node* list) {
    while (list) {
        Node* toDel = list;
        list = list->next;
        delete toDel;
    }
}

template <class PredType, class FuncType>
Node* insertBeforeNodes(Node* list, 
                        const PredType& predicate, 
                        const FuncType& createNodeValueFunc) 
{
    Node** curr = &list;   // pointer to pointer to current node

    while (*curr)
    {
        if (predicate((*curr)->data))
        {
            Node* newNode = new Node(createNodeValueFunc((*curr)->data));

            newNode->next = *curr;
            *curr = newNode;

            curr = &((*curr)->next->next);
        }
        else
        {
            curr = &((*curr)->next);
        }
    }

    return list;
}

int main() {
    Node* list = new Node(8, new Node(2, new Node(10, new Node(4, nullptr))));

    //insert before each even the cooresponding odd.
    list = insertBeforeNodes(list,
                             [](int x) {return x % 2 == 0; },
                             [](int x) {return x - 1; });
   
    print(list);
    freeList(list);
}
