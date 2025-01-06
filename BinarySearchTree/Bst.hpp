#pragma once
#include <iostream>
#include <functional>
#include <stack>
#include <vector>

template <class T, typename Compare = std::less<T>>
class Bst
{
private:
    struct Node
    {
        T data;
        size_t subtreeSize = 1;
        Node* left;
        Node* right;
        static size_t getSubtreeSize(const Node* ptr)
        {
            if (!ptr)
                return 0;
            else
                return ptr->subtreeSize;
        }
        Node(const T& data, Node* left = nullptr, Node* right = nullptr) : data(data), left(left), right(right) {}
    };

    Node* root = nullptr;
    size_t size = 0;
    Compare comp; // comparator instance

    Node** findMinNode(Node** root);
    void free(Node* current);
    Node* copy(Node* current);

    const Node& getNodeByIndexRec(const Node& curr, size_t index) const
    {
        size_t leftSubtreeSize = Node::getSubtreeSize(curr.left);
        if (leftSubtreeSize == index)
            return curr;
        else if (leftSubtreeSize > index)
            return getNodeByIndexRec(*curr.left, index);
        else
            return getNodeByIndexRec(*curr.right, index - leftSubtreeSize - 1);
    }

public:
    Bst() = default;
    explicit Bst(const Compare& comparator) : comp(comparator) {}
    Bst(const Bst<T, Compare>& other);
    Bst<T, Compare>& operator=(const Bst<T, Compare>& other);
    ~Bst();

    const T& operator[](size_t index) const
    {
        return getNodeByIndexRec(*root, index).data;
    }

    bool insert(const T& data);
    bool contains(const T& data) const;
    bool remove(const T& data);

    size_t getSize() const;
    bool isEmpty() const;

    class ForwardIterator
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
        ForwardIterator(Node* root = nullptr) 
        {
            pushLeft(root);
        }

        T& operator*() const 
        {
            return nodeStack.top()->data;
        }

        ForwardIterator& operator++() 
        {
            Node* node = nodeStack.top();
            nodeStack.pop();
            if (node->right) {
                pushLeft(node->right);
            }
            return *this;
        }
        ForwardIterator operator++(int)
        {
            ForwardIterator old = *this;
            ++(*this);
            return old;
        }

        bool operator!=(const ForwardIterator& other) const 
        {
            return nodeStack != other.nodeStack;
        }

        bool operator==(const ForwardIterator& other) const 
        {
            return nodeStack == other.nodeStack;
        }
    };

    ForwardIterator begin() const 
    {
        return ForwardIterator(root);
    }

    ForwardIterator end() const 
    {
        return ForwardIterator(nullptr);
    }
};

template <class T, typename Compare>
bool Bst<T, Compare>::insert(const T& data)
{
    Node** current = &root;

    while (*current)
    {
        (*current)->subtreeSize++;
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

void treeSort(std::vector<int>& v)
{
    Bst<int> bst;
    for (int i = 0; i < v.size(); i++)
        bst.insert(v.at(i));

    unsigned index = 0;
    for (auto it = bst.begin(); it != bst.end(); it++)
        v.at(index++) = *it;
}