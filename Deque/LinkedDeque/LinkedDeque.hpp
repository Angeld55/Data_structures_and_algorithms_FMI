#pragma once
#include <cstddef>
#include <stdexcept>
#include <iterator>

template <typename T>
class LinkedDeque
{
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& d) : data(d), prev(nullptr), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    size_t count;
    void copyFrom(const LinkedDeque& other);
    void moveFrom(LinkedDeque&& other);
    void free();

public:
    class iterator;
    class const_iterator;

    LinkedDeque();
    LinkedDeque(const LinkedDeque<T>& other);
    LinkedDeque(LinkedDeque<T>&& other) noexcept;
    LinkedDeque<T>& operator=(const LinkedDeque<T>& other);
    LinkedDeque<T>& operator=(LinkedDeque<T>&& other) noexcept;
    ~LinkedDeque();

    bool empty() const noexcept;
    size_t size() const noexcept;
    void clear();
    T& front();
    T& back();
    const T& front() const;
    const T& back() const;
    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();

    void print() const; //for debuging

    class iterator
    {
        friend class LinkedDeque;
        LinkedDeque* dequePtr;
        Node* current;
        iterator(LinkedDeque* dq, Node* ptr);
    public:
        iterator();
        T& operator*() const;
        T* operator->() const;
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;
    };

    class const_iterator
    {
        friend class LinkedDeque;
        const LinkedDeque* dequePtr;
        const Node* current;
        const_iterator(const LinkedDeque* dq, const Node* ptr);
    public:
        const_iterator();
        const_iterator(const iterator& it);
        const T& operator*() const;
        const T* operator->() const;
        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator--();
        const_iterator operator--(int);
        bool operator==(const const_iterator& rhs) const;
        bool operator!=(const const_iterator& rhs) const;
    };

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    iterator insert(iterator pos, const T& value);
    iterator erase(iterator pos);
};

#ifndef LINKEDDEQUE_HPP
#define LINKEDDEQUE_HPP

template <typename T>
LinkedDeque<T>::iterator::iterator(LinkedDeque* dq, Node* ptr) : dequePtr(dq), current(ptr) {}

template <typename T>
LinkedDeque<T>::iterator::iterator() : dequePtr(nullptr), current(nullptr) {}

template <typename T>
T& LinkedDeque<T>::iterator::operator*() const 
{
    return current->data;
}

template <typename T>
T* LinkedDeque<T>::iterator::operator->() const 
{
    return &current->data;
}

template <typename T>
typename LinkedDeque<T>::iterator& LinkedDeque<T>::iterator::operator++() 
{
    if (current) current = current->next;
    return *this;
}

template <typename T>
typename LinkedDeque<T>::iterator LinkedDeque<T>::iterator::operator++(int) 
{
    iterator tmp = *this;
    ++(*this);
    return tmp;
}

template <typename T>
typename LinkedDeque<T>::iterator& LinkedDeque<T>::iterator::operator--() 
{
    if (!current) 
    {
        if (dequePtr && !dequePtr->empty()) 
            current = dequePtr->tail;
    }
    else 
    {
        current = current->prev;
    }
    return *this;
}

template <typename T>
typename LinkedDeque<T>::iterator LinkedDeque<T>::iterator::operator--(int)
{
    iterator tmp = *this;
    --(*this);
    return tmp;
}

template <typename T>
bool LinkedDeque<T>::iterator::operator==(const iterator& rhs) const 
{
    return current == rhs.current;
}

template <typename T>
bool LinkedDeque<T>::iterator::operator!=(const iterator& rhs) const 
{
    return current != rhs.current;
}

template <typename T>
LinkedDeque<T>::const_iterator::const_iterator(const LinkedDeque* dq, const Node* ptr)
    : dequePtr(dq), current(ptr) {}

template <typename T>
LinkedDeque<T>::const_iterator::const_iterator() : dequePtr(nullptr), current(nullptr) {}

template <typename T>
LinkedDeque<T>::const_iterator::const_iterator(const iterator& it)
    : dequePtr(it.dequePtr), current(it.current) {}

template <typename T>
const T& LinkedDeque<T>::const_iterator::operator*() const 
{
    return current->data;
}

template <typename T>
const T* LinkedDeque<T>::const_iterator::operator->() const 
{
    return &current->data;
}

template <typename T>
typename LinkedDeque<T>::const_iterator& LinkedDeque<T>::const_iterator::operator++() 
{
    if (current)
        current = current->next;
    return *this;
}

template <typename T>
typename LinkedDeque<T>::const_iterator LinkedDeque<T>::const_iterator::operator++(int) 
{
    const_iterator tmp = *this;
    ++(*this);
    return tmp;
}

template <typename T>
typename LinkedDeque<T>::const_iterator& LinkedDeque<T>::const_iterator::operator--() 
{
    if (!current) {
        if (dequePtr && !dequePtr->empty()) current = dequePtr->tail;
    }
    else {
        current = current->prev;
    }
    return *this;
}

template <typename T>
typename LinkedDeque<T>::const_iterator LinkedDeque<T>::const_iterator::operator--(int)
{
    const_iterator tmp = *this;
    --(*this);
    return tmp;
}

template <typename T>
bool LinkedDeque<T>::const_iterator::operator==(const const_iterator& rhs) const 
{
    return current == rhs.current;
}

template <typename T>
bool LinkedDeque<T>::const_iterator::operator!=(const const_iterator& rhs) const 
{
    return current != rhs.current;
}

template <typename T>
LinkedDeque<T>::LinkedDeque() : head(nullptr), tail(nullptr), count(0) {}

template <typename T>
LinkedDeque<T>::LinkedDeque(const LinkedDeque<T>& other) : head(nullptr), tail(nullptr), count(0) 
{
    copyFrom(other);
}

template <typename T>
LinkedDeque<T>::LinkedDeque(LinkedDeque<T>&& other) noexcept : head(nullptr), tail(nullptr), count(0) 
{
    moveFrom(std::move(other));
}

template <typename T>
LinkedDeque<T>& LinkedDeque<T>::operator=(const LinkedDeque<T>& other) 
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
LinkedDeque<T>& LinkedDeque<T>::operator=(LinkedDeque<T>&& other) noexcept
{
    if (this != &other) 
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template <typename T>
LinkedDeque<T>::~LinkedDeque() 
{
    free();
}

template <typename T>
bool LinkedDeque<T>::empty() const noexcept
{
    return count == 0;
}

template <typename T>
size_t LinkedDeque<T>::size() const noexcept 
{
    return count;
}

template <typename T>
void LinkedDeque<T>::clear() 
{
    free();
}

template <typename T>
T& LinkedDeque<T>::front() 
{
    if (empty()) throw std::runtime_error("Deque is empty");
    return head->data;
}

template <typename T>
const T& LinkedDeque<T>::front() const 
{
    if (empty()) throw std::runtime_error("Deque is empty");
    return head->data;
}

template <typename T>
T& LinkedDeque<T>::back() 
{
    if (empty()) throw std::runtime_error("Deque is empty");
    return tail->data;
}

template <typename T>
const T& LinkedDeque<T>::back() const 
{
    if (empty()) throw std::runtime_error("Deque is empty");
    return tail->data;
}

template <typename T>
void LinkedDeque<T>::push_front(const T& value) 
{
    Node* newNode = new Node(value);
    if (empty()) 
        head = tail = newNode;
    
    else 
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    ++count;
}

template <typename T>
void LinkedDeque<T>::push_back(const T& value) 
{
    Node* newNode = new Node(value);
    if (empty()) 
        head = tail = newNode;
    
    else 
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    ++count;
}

template <typename T>
void LinkedDeque<T>::pop_front()
{
    if (empty()) throw std::runtime_error("Deque is empty");
    Node* tmp = head;
    if (head == tail) 
        head = tail = nullptr;
    
    else 
    {
        head = head->next;
        head->prev = nullptr;
    }
    delete tmp;
    --count;
}

template <typename T>
void LinkedDeque<T>::pop_back() 
{
    if (empty()) throw std::runtime_error("Deque is empty");
    Node* tmp = tail;
    if (head == tail) 
        head = tail = nullptr;
 
    else 
    {
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete tmp;
    --count;
}

template <typename T>
typename LinkedDeque<T>::iterator LinkedDeque<T>::begin() 
{
    return iterator(this, head);
}

template <typename T>
typename LinkedDeque<T>::iterator LinkedDeque<T>::end() 
{
    return iterator(this, nullptr);
}

template <typename T>
typename LinkedDeque<T>::const_iterator LinkedDeque<T>::begin() const 
{
    return const_iterator(this, head);
}

template <typename T>
typename LinkedDeque<T>::const_iterator LinkedDeque<T>::end() const 
{
    return const_iterator(this, nullptr);
}

template <typename T>
typename LinkedDeque<T>::const_iterator LinkedDeque<T>::cbegin() const 
{
    return const_iterator(this, head);
}

template <typename T>
typename LinkedDeque<T>::const_iterator LinkedDeque<T>::cend() const 
{
    return const_iterator(this, nullptr);
}

template <typename T>
typename LinkedDeque<T>::iterator LinkedDeque<T>::insert(iterator pos, const T& value) 
{
    if (pos == begin()) 
    {
        push_front(value);
        return begin();
    }
    if (pos == end()) 
    {
        push_back(value);
        return iterator(this, tail);
    }
    Node* c = pos.current;
    Node* n = new Node(value);
    Node* b = c->prev;
    b->next = n;
    n->prev = b;
    n->next = c;
    c->prev = n;
    ++count;
    return iterator(this, n);
}

template <typename T>
typename LinkedDeque<T>::iterator LinkedDeque<T>::erase(iterator pos) 
{
    if (pos == end()) throw std::runtime_error("Cannot erase end");
    Node* del = pos.current;
    if (!del) throw std::runtime_error("Invalid iterator");
    Node* nxt = del->next;
    if (del == head) 
    {
        pop_front();
        return iterator(this, head);
    }
    else if (del == tail) 
    {
        pop_back();
        return end();
    }
    else 
    {
        Node* b = del->prev;
        Node* a = del->next;
        b->next = a;
        a->prev = b;
        delete del;
        --count;
        return iterator(this, a);
    }
}

template <typename T>
void LinkedDeque<T>::copyFrom(const LinkedDeque& other) 
{
    Node* tmp = other.head;
    while (tmp)
    {
        push_back(tmp->data);
        tmp = tmp->next;
    }
}

template <typename T>
void LinkedDeque<T>::moveFrom(LinkedDeque&& other)
{
    head = other.head;
    tail = other.tail;
    count = other.count;
    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;
}

template <typename T>
void LinkedDeque<T>::free()
{
    while (!empty()) 
        pop_front();
    
}

template <typename T>
void LinkedDeque<T>::print() const
{
    Node* curr = head;

    while (curr != nullptr)
    {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}


#endif

