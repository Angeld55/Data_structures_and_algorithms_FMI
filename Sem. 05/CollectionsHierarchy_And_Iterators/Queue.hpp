#include "SinlgyLinkedList.hpp"

template <typename T>
class Queue : private SinglyLinkedList<T>
{
public:
	void enqueue(const T& el); 
	T dequeue();
	T peek();
};
template <typename T>
void Queue<T>::enqueue(const T& el)
{
	pushBack(el);
}
 template <typename T>
T Queue<T>::dequeue()
{
	return popFront();
}
template <typename T>
T Queue<T>::peek()
{
	return getAt(size - 1);
}