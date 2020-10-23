#include <iostream>

template <typename T>
class List
{
	virtual void pushBack(const T& el) = 0;
	virtual void pushFront(const T& el) = 0;
	virtual void insertAt(const T& el, int index) = 0;
	virtual T getAt(int index) = 0;

	virtual T popBack() = 0;
	virtual T popFront() = 0;
	virtual T removeAt(int index) = 0;

	virtual void print() const = 0;
};