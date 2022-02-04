
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <list>
#include <unordered_map>
#include <iterator>
#include <algorithm>

struct Node
{
    Node* next;
    int data;

    Node(int data, Node* next = nullptr) : data(data), next(next) {}
};

Node* getMid(Node* list)
{
    Node* fast = list;
    Node* slow = list;

    while (fast != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}


int getAccumNumber(Node* begin, Node* end)
{
    int number = 0;

    while (begin != end)
    {
        (number *= 10) += begin->data;
        begin = begin->next;
    }

    return number;
}

void free(Node* list)
{
    if (list == nullptr)
        return;

    free(list->next);
    delete list;
}

Node* createList(int n, Node*& lastOfList)
{
    Node* last = nullptr;

    bool isFirst = true;
    while (n != 0)
    {
        int lastDigit = n % 10;
        Node* current = new Node(lastDigit);
        current->next = last;
        last = current;

        if (isFirst)
        {
            lastOfList = current;
            isFirst = false;
        }
        n /= 10;
    }
    return last;
}

void task(Node*& list)
{
    Node* secondNumberBegin = getMid(list);

    int first = getAccumNumber(list, secondNumberBegin);
    int second = getAccumNumber(secondNumberBegin, nullptr);
    
    Node* firstLast, *secondLast;
    Node* firstList = createList(first - 1, firstLast);
    Node* secondList = createList(second + 1, secondLast);

    firstLast->next = secondList;
    free(list);
    list = firstList;
}


void print(const Node* list)
{
    while (list != nullptr)
    {
        std::cout << list->data << " ";
        list = list->next;
    }
}

int main()
{
    Node* f = new Node(1, new Node(9, new Node(0, new Node(0, new Node(9, new Node(9, new Node(9, new Node(9))))))));

    task(f);

    print(f);

    free(f);

}
