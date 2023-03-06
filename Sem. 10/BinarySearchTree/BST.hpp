#pragma once
#include <iostream>
#include <queue>

template <typename T>
class Bst;

template <typename T>
void printBst(const Bst<T>& bst);

template <class T>
class Bst
{
public:
    struct Node
    {
        T data;
        Node* left;
        Node* right;
        Node(const T& data, Node* left = nullptr, Node* right = nullptr) : data(data), left(left), right(right) {}
    };

    Node* root = nullptr;
    size_t size = 0;

    Node** findMinNode(Node** root);

    void free(Node* current);
    Node* copy(Node* current);

public:
    Bst() = default;

    Bst(const Bst<T>& other);
    Bst<T>& operator=(const Bst<T>& other);
    ~Bst();

    bool insert(const T& data);
    bool contains(const T& data) const;
    bool remove(const T& data);

    size_t getSize() const;
    bool isEmpty() const;
};


template <class T>
bool Bst<T>::insert(const T& data)
{
    Node** current = &root;

    while (*current)
    {
        if (data < ((*current)->data))
            current = &(*current)->left;
        else if (data > ((*current)->data))
            current = &(*current)->right;
        else
            return false;
    }
    *current = new Node(data);
    size++;
}

template <class T>
bool Bst<T>::contains(const T& data) const
{
    Node** current = &root;

    while (*current)
    {
        if (data < ((*current)->data))
            current = (*current)->left;
        else if (data > ((*current)->data))
            current = (*current)->right;
        else
            return true;
    }
    return false;
}

template <class T>
typename Bst<T>::Node** Bst<T>::findMinNode(Node** root)
{
    Node** current = root;

    while ((*current)->left)
    {
        current = &(*current)->left;
    }
    return current;
}


template <class T>
bool Bst<T>::remove(const T& data)
{
    Node** current = &root;

    while (*current)
    {
        if (data < (*current)->data)
            current = &(*current)->left;
        else if (data > (*current)->data)
            current = &(*current)->right;
        else
            break;
    }

    if (!(*current))
        return false;

    Node* toDelete = *current;

    if (!(*current) && !(*current))
        *current = nullptr;
    if (!(*current)->right)
        *current = (*current)->left;
    else if (!(*current)->left)
        *current = (*current)->right;
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
}

template <class T>
size_t Bst<T>::getSize() const
{
    return size;
}

template <class T>
bool Bst<T>::isEmpty() const
{
    return getSize() == 0;
}

template <class T>
typename Bst<T>::Node* Bst<T>::copy(Node* current)
{
    if (!current)
        return nullptr;
    Node* res = new Node(current->data);
    res->left = copy(current->left);
    res->right = copy(current->right);
    return res;
}

template <class T>
void Bst<T>::free(Node* current)
{
    if (!current)
        return;
    free(current->left);
    free(current->right);
    delete[] current;
}

template <class T>
Bst<T>::Bst(const Bst<T>& other)
{
    root = copy(other.root);
    size = other.size;
}

template <class T>
Bst<T>& Bst<T>::operator=(const Bst<T>& other)
{
    if (this != &other)
    {
        free(root);
        root = copy(other.root);
        size = other.size;
    }
    return *this;
}

template <class T>
Bst<T>::~Bst()
{
    free(root);
}
