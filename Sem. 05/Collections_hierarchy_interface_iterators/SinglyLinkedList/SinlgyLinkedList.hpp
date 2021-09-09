#pragma once
#include "../List_interface/List.h"
#include "../Iterators/Iterator.hpp"


template <typename T>
class SinglyLinkedList : public List<T>
{
	size_t count;
	struct Node
	{
		Node(T data) : data(data) {}
		T data;
		Node* next = nullptr;
	};

	Node* head;
	Node* tail;

	bool isEmpty() const;
	void getAtIndex(size_t index, Node*& ptr);

	void CopyFrom(const SinglyLinkedList& other);
	void Free();
public:
	SinglyLinkedList();
	SinglyLinkedList(const SinglyLinkedList<T>& other);
	SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& other);
	~SinglyLinkedList();

	void pushBack(const T& el); //O(1)
	void pushFront(const T& el); // O(1)
	void insertAt(const T& el, int index); // O(n)

	T getAt(int index); // O(n)

	T popBack(); // O(n)
	T popFront(); // O(1)
	T removeAt(int index); // O(n)

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

	void print() const;

	size_t getSize() const;


};

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), tail(nullptr), count(0)
{}

template <typename T>
bool SinglyLinkedList<T>::isEmpty() const
{
	return head == nullptr && tail == nullptr;
}

template <typename T>
void SinglyLinkedList<T>::pushBack(const T& el)
{
	Node* added = new Node(el);
	count++;
	if (isEmpty())
		head = tail = added;
	else
	{
		tail->next = added;
		tail = added;
	}
}

template <typename T>
void SinglyLinkedList<T> ::pushFront(const T& el)
{
	Node* added = new Node(el);
	count++;
	if (isEmpty())
		head = tail = added;
	else
	{
		added->next = head;
		head = added;
	}
}

template <typename T>
void SinglyLinkedList<T>::insertAt(const T& el, int index)
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
		getAtIndex(index - 1, ptr);
		
		Node* added = new Node(el);
		added->next = ptr->next;
		
		ptr->next = added;
		count++;
	}
}

template <typename T>
void SinglyLinkedList<T>::getAtIndex(size_t index, Node*& ptr)
{
	Node* iter = head;
	for (size_t i = 0; i < index; i++)
		iter = iter->next;
	ptr = iter;
}

template <typename T>
T SinglyLinkedList<T>::getAt(int index)
{
	if (index < 0 || index >= count)
		throw "Invalid index";
	Node* result;
	getAtIndex(index, result);
	return result->data;
}

template<typename T>
 T SinglyLinkedList<T>::popBack()
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
		 Node* prevLast;
		 getAtIndex(count - 2, prevLast);

		 T data = prevLast->next->data;
		 delete prevLast->next;
		 
		 prevLast->next = nullptr;
		 tail = prevLast;
		 
		 count--;
		 return data;
	 }
}

 template<typename T>
T SinglyLinkedList<T>::popFront()
 {
	if (isEmpty())
		throw "Empty!";
	if (head == tail)
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
		Node* toDelete = head;

		head = head->next;
		delete toDelete;
		
		count--;
		return data;
	}
 }

template<typename T>
T SinglyLinkedList<T>::removeAt(int index)
{
	if (isEmpty())
		throw "Empty!";
	if (index == 0)
		return popFront();
	if (index == count - 1)
		return popBack();
	Node* ptr;
	getAtIndex(index - 1, ptr);

	Node* toDelete = ptr->next;
	T data = toDelete->data;
	ptr->next = toDelete->next;
	
	delete toDelete;
	count--;
	
	return data;
}

template<typename T>
 void SinglyLinkedList<T>::print() const
{
	 Node* iter = head;
	 while (iter != nullptr)
	 {
		 std::cout << iter->data;
		 if (iter != tail)
			 std::cout << "->";
		 iter = iter->next;
	 }
	 std::cout << std::endl;
}

 template<typename T>
size_t SinglyLinkedList<T>::getSize() const
 {
	return count;
 }

template<typename T>
const T& SinglyLinkedList<T>::operator[](size_t index) const
{

	if (index > count)
		throw std::out_of_range("Out of range!");
	Node* ptr = head;
	for (int i = 0; i < index; i++)
		ptr = ptr->next;
	return ptr->data;
}

template<typename T>
T& SinglyLinkedList<T>::operator[](size_t index) 
{

	if (index > count)
		throw std::out_of_range("Out of range!");
	Node* ptr;
	getAtIndex(index, ptr);
	return ptr->data;
}

template<typename T>
void SinglyLinkedList<T>::CopyFrom(const SinglyLinkedList<T>& other)
{
	Node* otherIter = other.head;
	while (otherIter != nullptr)
	{
		pushBack(otherIter->data);
		otherIter = otherIter->next;
	}
}

template<typename T>
void SinglyLinkedList<T>::Free()
{
	Node* iter = head;
	while (iter != nullptr)
	{
		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other)
{
	CopyFrom(other);
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}
template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
	Free();
}