#include "Vector.hpp"

template <typename T>
class StackVector : private Vector<T>
{
public:
	void push(const T& el);
	T pop();
	T peek();
};

template <typename T>
void StackVector<T>::push(const T& el)
{
	pushBack(el);
}
template <typename T>
T StackVector<T>::pop()
{
	return popBack();
}

template <typename T>
T StackVector<T>::peek()
{
	return getAt(count - 1);
}