#pragma once

#include "../List_interface/List.h"
#include "../Iterators/Iterator.hpp"



using namespace std;

template <typename T>
class Vector : public List<T>
{
	T* data;
	int count;
	int capacity;
	void CopyFrom(const Vector<T>& other);
	void Free();
	void Resize(int newCap);
	int closestPowerOfTwo(int n);
public:
	Vector();
	Vector(int capacity);

	Vector(const Vector<T>& other);
	Vector<T>& operator=(const Vector<T>& other);
	~Vector();

	void pushBack(const T& el); // O(1)
	void pushFront(const T& el); // O(n)
	void insertAt(const T& el, int index); // O(n)

	T getAt(int index); // O(1)

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

	T popBack(); // O(1)
	T popFront(); // O(n)
	T removeAt(int index); //O(n)

	size_t getSize() const;
	void print() const;

	class VectorIterator : public Iterator<T>
	{
		T* currentElement;
		int index;
		int size;

	public:
		VectorIterator(T* currentElement, int index, int size) : currentElement(currentElement), index(index), size(size){}
		T& operator*()
		{
			return *currentElement;
		}
		void operator++()
		{
			if (index < size-1)
			{
				index++;
				currentElement++;
			}
			else
			{
				index++;
				currentElement = nullptr;
			}
		}
		void operator--()
		{
			if (index > 0)
			{
				index--;
				currentElement--;
			}
		}
		bool operator!=( Iterator& other)
		{
			VectorIterator*  ptr2 = (VectorIterator*)&other;
			return currentElement != ptr2->currentElement;
		}
	};
	VectorIterator begin()
	{
		return VectorIterator(&data[0], 0, count);
	}
	VectorIterator end()
	{
		return VectorIterator(nullptr, count, count);
	}
};
template <typename T>
int Vector<T>::closestPowerOfTwo(int n)
{
	n--;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	return n + 1;
}
template <typename T>
Vector<T>::Vector() : Vector(4)
{
}
template <typename T>
Vector<T>::Vector(int capacity)
{
	this->capacity = closestPowerOfTwo(capacity);
	data = new T[this->capacity];
	count = 0;
}

template <typename T>
void Vector<T>::Resize(int newCap)
{
	T* temp = new T[newCap];
	for (int i = 0; i < count; i++)
		temp[i] = data[i];
	capacity = newCap;
	delete[] data;
	data = temp;
}

template <typename T>
void Vector<T>::pushBack(const T& el)
{
	if (count == capacity)
		Resize(count * 2);
	data[count++] = el;
}
template <typename T>
void Vector<T>::pushFront(const T& el)
{
	if (count == capacity)
		Resize(count * 2);
	for (int i = count; i >= 1; i--)
		data[i] = data[i - 1];
	data[0] = el;
	count++;
}

template <typename T>
void Vector<T>::insertAt(const T& el, int index)
{
	if (index > count)
		throw std::out_of_range("Out of range!");
	if (count == capacity)
		Resize(capacity * 2);

	for (int i = count; i > index; i--)
		data[i] = data[i - 1];
	data[index] = el;
	count++;

}
template <typename T>
T Vector<T>::getAt(int index)
{
	if (index < 0 || index >= count)
		throw std::out_of_range("Out of range!");
	return data[index];
}
template <typename T>
T Vector<T>::popBack()
{
	if (count == 0)
		throw std::out_of_range("Empty!");
	T el = data[--count];
	if (count < capacity / 2)
		Resize(capacity / 2);
	return el;

}
template <typename T>
T Vector<T>::popFront()
{
	if (count == 0)
		throw std::out_of_range("Empty!");
	T el = data[0];
	for (int i = 1; i < count; i++)
		data[i - 1] = data[i];
	if (--count < capacity / 2)
		Resize(capacity / 2);
	return el;
}

template <typename T>
T Vector<T>::removeAt(int index)
{
	if (index < 0 || index >= count)
		throw std::out_of_range("Out of range!");
	T el = data[index];

	for (int i = index; i < count - 1; i++)
		data[i] = data[i + 1];
	if (--count < capacity / 2)
		Resize(capacity / 2);
	return el;
}
template<typename T>
inline size_t Vector<T>::getSize() const
{
	return count;
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const
{

	if (index > count)
		throw std::out_of_range("Out of range!");
	return data[index];
}


template<typename T>
T& Vector<T>::operator[](size_t index)
{
	if (index > count)
		throw std::out_of_range("Out of range!");
	return data[index];
}

template <typename T>
void Vector<T>::print() const
{
	for (int i = 0; i < count; i++)
	{
		cout << data[i] << " ";
	}
	for (int i = count; i < capacity; i++)
		cout << "_ ";
	cout << endl;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	CopyFrom(other);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}
template <typename T>
Vector<T>::~Vector()
{
	Free();
}

template <typename T>
void Vector<T>::CopyFrom(const Vector<T>& other)
{
	data = new T[other.capacity];
	for (int i = 0; i < other.count; i++)
		data[i] = other.data[i];
	count = other.count;
}
template <typename T>
void Vector<T>::Free()
{
	delete[] data;
}