#include <iostream>

template <typename T>
class Collection
{
	virtual void push_back(const T& el) = 0;
	virtual void push_front(const T& el) = 0;
	virtual void insert_At(const T& el, int index) = 0;
	virtual T peek(int index) = 0;

	virtual T pop_back() = 0;
	virtual T pop_front() = 0;
	virtual T remove_At(int index) = 0;

	virtual void print() const = 0;
};