#pragma once
#include <iostream>

template <typename T>
class List
{
public:
	virtual void pushBack(const T& el) = 0;
	virtual void pushFront(const T& el) = 0;
	virtual void insertAt(const T& el, int index) = 0;
	virtual T getAt(int index) = 0;

	virtual const T& operator[](size_t index) const = 0;
	virtual T& operator[](size_t index) = 0;

	virtual T popBack() = 0;
	virtual T popFront() = 0;
	virtual T removeAt(int index) = 0;

	virtual size_t getSize() const = 0;
	virtual void print() const = 0;
};