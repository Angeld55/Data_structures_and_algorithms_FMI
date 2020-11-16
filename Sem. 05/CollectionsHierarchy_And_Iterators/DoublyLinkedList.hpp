#pragma once
#include "List.h"
#include "Iterator.hpp"

template <typename T> 
class DoublyLinkedList : public List<T>
{
	size_t count = 0;
	struct Node
	{
		Node(T data) : data(data) {}
		T data;
		Node* next = nullptr;
		Node* prev = nullptr;
	};

	Node* head = nullptr;
	Node* tail = nullptr;
	bool isEmpty() const;

	void getAtIndex(size_t index, Node*& ptr);

	void CopyFrom(const DoublyLinkedList& other);
	void Free();

public:
	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList<T>& other);
	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);
	~DoublyLinkedList();

	void pushBack(const T& el); //O(1)
	void pushFront(const T& el); //O(1)
	void insertAt(const T& el, int index); // O(n)

	T getAt(int index); // O(n)

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

	T popBack(); // O(1)
	T popFront(); // O(1)
	T removeAt(int index); // O(n)

	void print() const;
	size_t getSize() const;

	class LinkedListIterator : public Iterator<T>
	{
		Node* currentNode;
	public:
		LinkedListIterator(Node* n) : currentNode(n)
		{}
		T& operator*()
		{
			return currentNode->data;
		}
		void operator++()
		{
			if (currentNode != nullptr)
				currentNode = currentNode->next;
		}
		void operator--()
		{
			if (currentNode->prev != nullptr)
				currentNode = currentNode->prev;
		}
		bool operator!=(Iterator& other)
		{
			LinkedListIterator*  ptr2 = (LinkedListIterator*)&other;
			return currentNode != ptr2->currentNode;
		}
	};
	LinkedListIterator begin()
	{
		return LinkedListIterator(head);
	}
	LinkedListIterator end()
	{
		return LinkedListIterator(nullptr);
	}

};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), count(0)
{}

template <typename T>
bool DoublyLinkedList<T>::isEmpty() const
{
	return head == nullptr && tail == nullptr;
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
template <typename T>
void DoublyLinkedList<T>::insertAt(const T& el, int index)
{
	if (index > count)
		throw "invalid index";
	if (index == 0)
		pushFront(el);
	else if (index == count)
		pushBack(el);
	else
	{
		Node* ptr;
		getAtIndex(index, ptr);
		Node* added = new Node(el);
		added->next = ptr;
		added->prev = ptr->prev;
		ptr->prev->next = added;
		ptr->prev = added;
		count++;
	}
}

template <typename T>
void DoublyLinkedList<T>::getAtIndex(size_t index, Node*& ptr)
{
	Node* iter = head;
	for (size_t i = 0; i < index; i++)
		iter = iter->next;
	ptr = iter;
}

template <typename T>
T DoublyLinkedList<T>::getAt(int index)
{
	if (index < 0 || index >= count)
		throw "Invalid index";
	Node* result;
	getAtIndex(index, result);
	return result->data;
}

template<typename T>
T DoublyLinkedList<T>::popBack()
{
	if (isEmpty())
		throw "Empty!";
	else if (head == tail)
	{
		T data = head->data;
		delete head;
		head = tail = nullptr;
		return data;
	}
	else
	{
		T data = tail->data;
		tail->prev->next = nullptr;

		Node* toDelete = tail;
		tail = tail->prev;

		delete toDelete;

		count--;
		return data;
	}
}

template<typename T>
T DoublyLinkedList<T>::popFront()
{
	if (isEmpty())
		throw "Empty!";
	else if (head == tail)
	{
		T data = head->data;
		delete head;

		head = tail = nullptr;
		
		count--;
		return data;
	}
	else
	{
		T data = head->data;
		head->next->prev = nullptr;

		Node* toDelete = head;
		head = head->next;
		
		delete toDelete;
		
		count--;
		return data;
	}
}

template<typename T>
T DoublyLinkedList<T>::removeAt(int index)
{
	if (isEmpty())
		throw "Empty!";
	if (index == 0)
		return popFront();
	if(index == count-1)
		return popBack();
	Node* toRemove;
	getAtIndex(index, toRemove);

	T data = toRemove->data;
	toRemove->prev->next = toRemove->next;
	toRemove->next->prev = toRemove->prev;
	delete toRemove;
	
	count--;
	return data;

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
const T& DoublyLinkedList<T>::operator[](size_t index) const
{

	if (index > count)
		throw std::out_of_range("Out of range!");
	Node* ptr = nullptr;
	getAtIndex(index, ptr);
	return ptr->data;
}

template<typename T>
T& DoublyLinkedList<T>::operator[](size_t index)
{

	if (index > count)
		throw std::out_of_range("Out of range!");
	Node* ptr;
	getAtIndex(index, ptr);
	return ptr->data;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other)
{
	CopyFrom(other);
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	Free();
}

template <typename T>
void DoublyLinkedList<T>::CopyFrom(const DoublyLinkedList<T>& other)
{
	Node* otherIter = other.head;
	while (otherIter != nullptr)
	{
		pushBack(otherIter->data);
		otherIter = otherIter->next;
	}
}

template<typename T>
void DoublyLinkedList<T>::Free()
{
	Node* iter = head;
	while (iter != nullptr)
	{
		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}
}