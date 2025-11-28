#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <queue>
#include <list>

class Browser
{
    struct Node
    {
        std::string url;
        Node* prev = nullptr;
        Node* next = nullptr;

        Node(const std::string& str) : url(str) { }
    };

public:
    Browser(const std::string& homePage)
    {
        head = currNode = new Node(homePage);
    }

    void visit(const std::string& url)
    {
        if (currNode->next)
        {
            free(currNode->next);
        }
        
        currNode->next = new Node(url);
        currNode->next->prev = currNode;
        currNode = currNode->next;
    }

    const std::string& back(unsigned int steps)
    {
        while (currNode->prev != nullptr && steps != 0)
        {
            currNode = currNode->prev;
            steps--;
        }

        return currNode->url;
    }

    const std::string& forward(unsigned int steps)
    {
        while (currNode->next != nullptr && steps != 0)
        {
            currNode = currNode->next;
            steps--;
        }

        return currNode->url;
    }

    void reset()
    {
        currNode = head;
        free(head->next);
        head->next = nullptr;
    }

    const std::string& getCurrent() const
    {
        return currNode->url;
    }

    // Disable copying so we have exception safety
    // Alternatively - we have to manually make copy of the linked list
    Browser(const Browser&) = delete;
    Browser& operator=(const Browser&) = delete;

    ~Browser() noexcept
    {
        free(head);
    }

private:
    void free(Node* nodePtr)
    {
        while (nodePtr)
        {
            Node* temp = nodePtr->next;
            delete nodePtr;
            nodePtr = temp;
        }
    }

    // If we don't want to use our own Node and manage memory:
    // We can use std::list<std::string> for the doubly linked list (or forward_list for SLL)
    // We can use std::list<std::string>::iterator for the currNode pointer that moves back and forward
    Node* head = nullptr;
    Node* currNode = nullptr;
};

int main()
{

}
