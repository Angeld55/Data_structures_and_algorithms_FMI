#pragma once
#include <iostream>

// Implementation without a sentinel node and without circular linkage.

template <typename T> 
class DoublyLinkedList 
{
    size_t count = 0;

    struct Node
    {
        Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}
        T data;
        Node* next;
        Node* prev;
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    void copyFrom(const DoublyLinkedList& other);
    void moveFrom(DoublyLinkedList&& other);
    void free();

public:
    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList<T>& other);
    DoublyLinkedList(DoublyLinkedList<T>&& other);
	
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);
    DoublyLinkedList<T>& operator=(DoublyLinkedList<T>&& other);
    ~DoublyLinkedList();

    void pushBack(const T& el);  //todo: add emplace. todo: add move semantics (also for insert)
    void pushFront(const T& el); 
    void popBack(); 
    void popFront(); 
    
    const T& front() const;
    const T& back() const;
    
    T& front();
    T& back();

    void print() const;
    size_t getSize() const;

    bool isEmpty() const;
    
    void clear();

    class DllIterator;
    class ConstDllIterator;

    DllIterator insert(const T& element, const ConstDllIterator& it);
    DllIterator remove(const DllIterator& it);
    
    DllIterator begin() { return DllIterator(*this, head); }
    DllIterator end() { return DllIterator(*this, nullptr); }
    ConstDllIterator cbegin() const { return ConstDllIterator(*this, head); }
    ConstDllIterator cend() const { return ConstDllIterator(*this, nullptr); }

    class DllIterator
    {
        friend class DoublyLinkedList;
        Node* currentElementPtr;
        DoublyLinkedList& list;

    public:
        typedef std::bidirectional_iterator_tag iterator_category;

        DllIterator(DoublyLinkedList& list, Node* currentElementPtr = nullptr) : list(list), currentElementPtr(currentElementPtr) {}

        T& operator*() { return currentElementPtr->data; }
        T* operator->() { return &currentElementPtr->data; }

        DllIterator& operator++() {
            if(currentElementPtr)
                currentElementPtr = currentElementPtr->next;
            return *this;
        }

        DllIterator operator++(int) {
            DllIterator copy(*this);
            ++(*this);
            return copy;
        }

        DllIterator& operator--() {
            if(currentElementPtr)
                currentElementPtr = currentElementPtr->prev;
            else
                currentElementPtr = list.tail;
            return *this;
        }

        DllIterator operator--(int) {
            DllIterator copy(*this);
            --(*this);
            return copy;
        }

        bool operator==(const DllIterator& rhs) const { return currentElementPtr == rhs.currentElementPtr; }
        bool operator!=(const DllIterator& rhs) const { return !(rhs == *this); }
    };

    class ConstDllIterator
    {
        Node* currentElementPtr;
        const DoublyLinkedList& list; // Modified to const DoublyLinkedList

        friend class DoublyLinkedList;

    public:
        typedef std::bidirectional_iterator_tag iterator_category;

        ConstDllIterator(const DoublyLinkedList& list, Node* currentElementPtr = nullptr) : list(list), currentElementPtr(currentElementPtr) {}
        ConstDllIterator(const DllIterator& iter) : list(iter.list), currentElementPtr(iter.currentElementPtr){} //convert constructor
        
        const T& operator*() const { return currentElementPtr->data; }
        const T* operator->() const { return &currentElementPtr->data; }

        ConstDllIterator& operator++() {
            if(currentElementPtr)
                currentElementPtr = currentElementPtr->next;
            return *this;
        }

        ConstDllIterator operator++(int) {
            ConstDllIterator copy(*this);
            ++(*this);
            return copy;
        }

        ConstDllIterator& operator--() {
            if(currentElementPtr)
                currentElementPtr = currentElementPtr->prev;
            else
                currentElementPtr = list.tail;
            return *this;
        }

        ConstDllIterator operator--(int) {
            ConstDllIterator copy(*this);
            --(*this);
            return copy;
        }

        bool operator==(const ConstDllIterator& rhs) const { return currentElementPtr == rhs.currentElementPtr; }
        bool operator!=(const ConstDllIterator& rhs) const { return !(rhs == *this); }
    };
};
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), count(0)
{}

template <typename T>
bool DoublyLinkedList<T>::isEmpty() const
{
	return head == nullptr;
}

template <typename T>
void DoublyLinkedList<T>::pushBack(const T& el)
{
	Node* added = new Node(el);
	count++;
	if (isEmpty())
		head = tail = added;
	else
	{
		tail->next = added;
		added->prev = tail;
		tail = added;
	}
}
template <typename T>
void DoublyLinkedList<T>::pushFront(const T& el)
{
	Node* added = new Node(el);
	if (isEmpty())
	{
		head = tail = added;
	}
	else
	{
		added->next = head;
		head->prev = added;
		head = added;
	}
	count++;
}

template<typename T>
void DoublyLinkedList<T>::popBack()
{
	if (isEmpty())
		throw std::runtime_error("The list is empty!");
	
	if (head == tail)
	{
		delete head;
		head = tail = nullptr;
	}
	else
	{
		tail->prev->next = nullptr;

		Node* toDelete = tail;
		tail = tail->prev;

		delete toDelete;

	}

	count--;
}

template<typename T>
void DoublyLinkedList<T>::popFront()
{
	if (isEmpty())
		throw std::runtime_error("The list is empty!");

	
	if (head == tail)
	{
		delete head;
		head = tail = nullptr;
	}
	else
	{
		head->next->prev = nullptr;

		Node* toDelete = head;
		head = head->next;
		
		delete toDelete;
	}

	count--;
}

template <typename T>
typename DoublyLinkedList<T>::DllIterator DoublyLinkedList<T>::insert(const T& element, const ConstDllIterator& it)
{
    if (it == cbegin())
    {
        pushFront(element);
        return begin();
    }
    else if (it == cend())
    {
        pushBack(element);
        return DllIterator(*this, tail);
    }
    else 
    {
        Node* current = it.currentElementPtr;
        Node* newNode = new Node(element);
        
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
        count++;

        return DllIterator(*this, newNode);
    }
}

template <typename T>
typename DoublyLinkedList<T>::DllIterator DoublyLinkedList<T>::remove(const DllIterator& it)
{
    Node* toDelete = it.currentElementPtr;
    if (!toDelete)
        throw std::runtime_error("Cannot remove end iterator");

    if (toDelete == head)
    {
        popFront();
        return begin();
    }
    else if (toDelete == tail)
    {
        popBack();
        return end();
    }
    else
    {
        toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;
        Node* nextNode = toDelete->next;

        delete toDelete;
        count--;

        return DllIterator(*this, nextNode);
    }
}

template<typename T>
const T& DoublyLinkedList<T>::front() const
{
	if (isEmpty())
		throw std::runtime_error("The list is empty!");

	return head->data;
}

template<typename T>
const T& DoublyLinkedList<T>::back() const
{
	if (isEmpty())
		throw std::runtime_error("The list is empty!");

	return tail->data;
}


template<typename T>
T& DoublyLinkedList<T>::front()
{
	if (isEmpty())
		throw std::runtime_error("The list is empty!");

	return head->data;
}

template<typename T>
T& DoublyLinkedList<T>::back()
{
	if (isEmpty())
		throw std::runtime_error("The list is empty!");

	return tail->data;
}

template<typename T>
void DoublyLinkedList<T>::print() const
{
	Node* iter = head;
	while (iter != nullptr)
	{
		std::cout << iter->data;
		if (iter != tail)
			std::cout << "<->";
		iter = iter->next;
	}
	std::cout << std::endl;
}
template<typename T>
size_t DoublyLinkedList<T>::getSize() const
{
	return count;
}

template<typename T>
void DoublyLinkedList<T>::clear()
{
    free();
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other) : head(nullptr), tail(nullptr)
{
	copyFrom(other);
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>&& other)
{
	moveFrom(std::move(other));
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	free();
}

template <typename T>
void DoublyLinkedList<T>::copyFrom(const DoublyLinkedList<T>& other)
{
	Node* otherIter = other.head;
	while (otherIter != nullptr)
	{
		pushBack(otherIter->data);
		otherIter = otherIter->next;
	}
}

template <typename T>
void DoublyLinkedList<T>::moveFrom(DoublyLinkedList<T>&& other)
{
	head = other.head;
	tail = other.tail;
	count = other.count;
	other.head = other.tail = nullptr;
	other.count = 0;
}


template<typename T>
void DoublyLinkedList<T>::free()
{
	Node* iter = head;
	while (iter != nullptr)
	{
		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}
	
	head = tail = nullptr;
	count = 0;
}
