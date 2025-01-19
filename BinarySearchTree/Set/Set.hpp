#pragma once
#include <iostream>
#include <functional>
#include <stack>
#include <vector>

template <class T, typename Compare = std::less<T>>
class Set
{
private:
    struct Node
    {
        T data;
        Node* left;
        Node* right;

        Node(const T& data, Node* left = nullptr, Node* right = nullptr)
            : data(data), left(left), right(right) {}
    };

    Node* root = nullptr;
    size_t size = 0;
    Compare comp; 

    Node** findMinNode(Node** root);
    void free(Node* current);
    Node* copy(Node* current);

public:
    Set() = default;
    explicit Set(const Compare& comparator) : comp(comparator) {}
    Set(const Set<T, Compare>& other);
    Set<T, Compare>& operator=(const Set<T, Compare>& other);
    ~Set();

    bool insert(const T& data);
    bool contains(const T& data) const;
    bool remove(const T& data);

    size_t getSize() const;
    bool isEmpty() const;

    class ConstIterator
    {
    private:
        std::stack<Node*> nodeStack;

        void pushLeft(Node* node)
        {
            while (node)
            {
                nodeStack.push(node);
                node = node->left;
            }
        }

    public:
        ConstIterator(Node* root = nullptr)
        {
            pushLeft(root);
        }

        const T& operator*() const
        {
            return nodeStack.top()->data;
        }

        ConstIterator& operator++()
        {
            Node* node = nodeStack.top();
            nodeStack.pop();
            if (node->right) {
                pushLeft(node->right);
            }
            return *this;
        }
        ConstIterator operator++(int)
        {
            ConstIterator old = *this;
            ++(*this);
            return old;
        }

        bool operator!=(const ConstIterator& other) const
        {
            return nodeStack != other.nodeStack;
        }

        bool operator==(const ConstIterator& other) const
        {
            return nodeStack == other.nodeStack;
        }
    };

    ConstIterator cbegin() const
    {
        return ConstIterator(root);
    }

    ConstIterator cend() const
    {
        return ConstIterator(nullptr);
    }
};

template <class T, typename Compare>
bool Set<T, Compare>::insert(const T& data)
{
    Node** current = &root;

    while (*current)
    {
        if (comp(data, (*current)->data))
            current = &(*current)->left;
        else if (comp((*current)->data, data))
            current = &(*current)->right;
        else
            return false; 
    }
    *current = new Node(data);
    size++;
    return true;
}

template <class T, typename Compare>
bool Set<T, Compare>::contains(const T& data) const
{
    Node* current = root;

    while (current)
    {
        if (comp(data, current->data))
            current = current->left;
        else if (comp(current->data, data))
            current = current->right;
        else
            return true;
    }
    return false;
}

template <class T, typename Compare>
typename Set<T, Compare>::Node** Set<T, Compare>::findMinNode(Node** root)
{
    Node** current = root;

    while ((*current)->left)
    {
        current = &(*current)->left;
    }
    return current;
}

template <class T, typename Compare>
bool Set<T, Compare>::remove(const T& data)
{
    Node** current = &root;

    while (*current)
    {
        if (comp(data, (*current)->data))
            current = &(*current)->left;
        else if (comp((*current)->data, data))
            current = &(*current)->right;
        else
            break;
    }

    if (!(*current))
        return false; // Data not found

    Node* toDelete = *current;

    // No children
    if (!(*current)->left && !(*current)->right)
        *current = nullptr;
    // Only left child
    else if (!(*current)->right)
        *current = (*current)->left;
    // Only right child
    else if (!(*current)->left)
        *current = (*current)->right;
    // Two children
    else
    {
        Node** rightMin = findMinNode(&(*current)->right);
        *current = *rightMin;
        *rightMin = (*rightMin)->right;

        (*current)->left = toDelete->left;
        (*current)->right = toDelete->right;
    }
    delete toDelete;
    size--;
    return true;
}

template <class T, typename Compare>
size_t Set<T, Compare>::getSize() const
{
    return size;
}

template <class T, typename Compare>
bool Set<T, Compare>::isEmpty() const
{
    return getSize() == 0;
}

template <class T, typename Compare>
typename Set<T, Compare>::Node* Set<T, Compare>::copy(Node* current)
{
    if (!current)
        return nullptr;
    Node* res = new Node(current->data);
    res->left = copy(current->left);
    res->right = copy(current->right);
    return res;
}

template <class T, typename Compare>
void Set<T, Compare>::free(Node* current)
{
    if (!current)
        return;
    free(current->left);
    free(current->right);
    delete current;
}

template <class T, typename Compare>
Set<T, Compare>::Set(const Set<T, Compare>& other) : comp(other.comp)
{
    root = copy(other.root);
    size = other.size;
}

template <class T, typename Compare>
Set<T, Compare>& Set<T, Compare>::operator=(const Set<T, Compare>& other)
{
    if (this != &other)
    {
        free(root);
        root = copy(other.root);
        size = other.size;
        comp = other.comp;
    }
    return *this;
}

template <class T, typename Compare>
Set<T, Compare>::~Set()
{
    free(root);
}
