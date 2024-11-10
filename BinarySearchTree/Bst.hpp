#pragma once
#include <iostream>
#include <queue>
#include <functional>

template <class T, typename Compare = std::less<T>>
class Bst
{
private:
    struct Node
    {
        T data;
        Node* left;
        Node* right;
        Node(const T& data, Node* left = nullptr, Node* right = nullptr) : data(data), left(left), right(right) {}
    };

    Node* root = nullptr;
    size_t size = 0;
    Compare comp; // comparator instance

    Node** findMinNode(Node** root);
    void free(Node* current);
    Node* copy(Node* current);

public:
    Bst() = default;
    explicit Bst(const Compare& comparator) : comp(comparator) {}
    Bst(const Bst<T, Compare>& other);
    Bst<T, Compare>& operator=(const Bst<T, Compare>& other);
    ~Bst();

    bool insert(const T& data);
    bool contains(const T& data) const;
    bool remove(const T& data);

    size_t getSize() const;
    bool isEmpty() const;
};

template <class T, typename Compare>
bool Bst<T, Compare>::insert(const T& data)
{
    Node** current = &root;

    while (*current)
    {
        if (comp(data, (*current)->data))
            current = &(*current)->left;
        else if (comp((*current)->data, data))
            current = &(*current)->right;
        else
            return false; // Data already exists
    }
    *current = new Node(data);
    size++;
    return true;
}

template <class T, typename Compare>
bool Bst<T, Compare>::contains(const T& data) const
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
typename Bst<T, Compare>::Node** Bst<T, Compare>::findMinNode(Node** root)
{
    Node** current = root;

    while ((*current)->left)
    {
        current = &(*current)->left;
    }
    return current;
}

template <class T, typename Compare>
bool Bst<T, Compare>::remove(const T& data)
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

    if (!(*current)->left && !(*current)->right)
        *current = nullptr; // Node has no children
    else if (!(*current)->right)
        *current = (*current)->left; // Node has only left child
    else if (!(*current)->left)
        *current = (*current)->right; // Node has only right child
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
size_t Bst<T, Compare>::getSize() const
{
    return size;
}

template <class T, typename Compare>
bool Bst<T, Compare>::isEmpty() const
{
    return getSize() == 0;
}

template <class T, typename Compare>
typename Bst<T, Compare>::Node* Bst<T, Compare>::copy(Node* current)
{
    if (!current)
        return nullptr;
    Node* res = new Node(current->data);
    res->left = copy(current->left);
    res->right = copy(current->right);
    return res;
}

template <class T, typename Compare>
void Bst<T, Compare>::free(Node* current)
{
    if (!current)
        return;
    free(current->left);
    free(current->right);
    delete current;
}

template <class T, typename Compare>
Bst<T, Compare>::Bst(const Bst<T, Compare>& other) : comp(other.comp)
{
    root = copy(other.root);
    size = other.size;
}

template <class T, typename Compare>
Bst<T, Compare>& Bst<T, Compare>::operator=(const Bst<T, Compare>& other)
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
Bst<T, Compare>::~Bst()
{
    free(root);
}
