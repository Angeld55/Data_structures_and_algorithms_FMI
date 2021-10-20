#ifndef DYNAMICARRAY_HDR
#define DYNAMICARRAY_HDR

#include <iostream>

template<typename T>
class DynamicArray {

private:
	T* arr;
	size_t size;
	size_t capacity;

public:
	DynamicArray();
	DynamicArray(size_t capacity);
	DynamicArray(const DynamicArray<T>& other);
	DynamicArray<T>& operator=(const DynamicArray<T>& other);
	~DynamicArray();

private:
	void copyFrom(const DynamicArray<T>& other);
	void free();
	void resize(size_t newCap);

public:
	void pushBack(const T& newElem); //add a new element in the end
	T popBack(); //removes the last element
	int indexOf(const T& el);
	size_t getSize() const;
	bool isEmpty() const;
	
	const T& operator[](size_t index) const;
	T& operator[](size_t index);
};

template<typename T>
DynamicArray<T>::DynamicArray() : size(0), capacity(4) 
{
	arr = new T[capacity];
}


unsigned closestPowerOfTwo(unsigned n)
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
DynamicArray<T>::DynamicArray(size_t capacity) : size(0)
{
	capacity = closestPowerOfTwo(capacity);
	arr = new T[capacity];
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
{
	copyFrom(other);
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) 
{

	if (this != &other) 
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
DynamicArray<T>::~DynamicArray() 
{
	free();
}

template<typename T>
void DynamicArray<T>::copyFrom(const DynamicArray<T>& other) 
{
	
	arr = new T[other.capacity];

	for (size_t i = 0; i < other.size; i++)
		arr[i] = other.arr[i];

	size = other.size;
	capacity = other.capacity;
}

template<typename T>
void DynamicArray<T>::free() 
{
	delete[] arr;
}

template<typename T>
void DynamicArray<T>::resize(size_t newCap) 
{
	
	T* temp = arr;
	arr = new T[newCap];

	for (size_t i = 0; i < size; i++)
		arr[i] = temp[i];

	capacity = newCap;
	delete[] temp;
}


template<typename T>
void DynamicArray<T>::pushBack(const T& newElem) 
{
	if (size >= capacity)
		resize(capacity * 2);

	arr[size++] = newElem;
}

template<typename T>
T DynamicArray<T>::popBack() 
{

	T el = arr[size - 1];
	if (size)
		size--;
	else
		throw std::length_error("Already empty!");

	if (size * 2 <= capacity && capacity > 1)
		resize(capacity / 2);
	
	return el;
}



template <typename T>
int DynamicArray<T>::indexOf(const T& el)
{
	for (int i = 0; i < size; ++i)
	{
		if (arr[i] == el)
			return i;
	}
	return -1;
}

template<typename T>
size_t DynamicArray<T>::getSize() const 
{
	return size;
}

template<typename T>
bool DynamicArray<T>::isEmpty() const
{
	return size == 0;
}


template<typename T>
const T& DynamicArray<T>::operator[](size_t index) const 
{
	if (index > size)
		throw std::out_of_range("Out of range!");
	return arr[index];
}


template<typename T>
T& DynamicArray<T>::operator[](size_t index) 
{
	if (index > size)
		throw std::out_of_range("Out of range!");
	return arr[index];
}

#endif // !DYNAMICARRAY_HDR
