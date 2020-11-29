#include "../SinglyLinkedList/SinlgyLinkedList.hpp"


template <typename T>
class LinkedStack : private SinglyLinkedList<T>
{
public:
	void push(const T& el);
	T pop();
	T peek();
};

template <typename T>
void LinkedStack<T>::push(const T& el)
{
	pushFront(el);
}
template <typename T>
T LinkedStack<T>::pop()
{
	return popFront();
}

template <typename T>
T LinkedStack<T>::peek()
{
	return getAt(0);
}
