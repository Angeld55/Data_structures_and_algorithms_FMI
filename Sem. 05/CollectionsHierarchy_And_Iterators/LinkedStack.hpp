#include "SinlgyLinkedList.hpp"


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
	pushBack(el);
}
template <typename T>
T LinkedStack<T>::pop()
{
	return popBack();
}

template <typename T>
T LinkedStack<T>::peek()
{
	return getAt(count - 1);
}
