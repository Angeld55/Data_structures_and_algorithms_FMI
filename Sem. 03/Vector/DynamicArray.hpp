#ifndef DYNAMICARRAY_HDR
#define DYNAMICARRAY_HDR

#include <iostream>

template<typename T>
class DynamicArray {

private:
	T* arr;
	size_t curSize;
	size_t capacity;

public:
	DynamicArray();
	DynamicArray(int size);
	DynamicArray(const DynamicArray<T>& other);
	DynamicArray<T>& operator=(const DynamicArray<T>& other);
	~DynamicArray();

private:
	void CopyFrom(const DynamicArray<T>& other);
	void Free();
	void Resize(size_t newCap);
	void swap(int i, int j);
	int Partition(int low, int high);
	void QuickSort(int low, int high);
public:
	void PushBack(const T& newElem); //add a new element in the end
	T PopBack(); //removes the last element
	
	void InsertAt(size_t index, const T& newElem); //add a new element on random position
	void RemoveAt(size_t index); //removes an element on random position
	
	int IndexOf(const T& el);
	int getSize() const;
	
	const T& operator[](size_t index) const;
	T& operator[](size_t index);
	
	void Sort();
};

template<typename T>
DynamicArray<T>::DynamicArray() : curSize(0), capacity(4) 
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
DynamicArray<T>::DynamicArray(int size) : curSize(0)
{
	capacity = closestPowerOfTwo(size);
	arr = new T[capacity];
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other) {
	CopyFrom(other);
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) 
{

	if (this != &other) 
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}

template<typename T>
DynamicArray<T>::~DynamicArray() 
{
	Free();
}

template<typename T>
void DynamicArray<T>::CopyFrom(const DynamicArray<T>& other) 
{
	
	arr = new T[other.capacity];

	for (size_t i = 0; i < other.curSize; i++)
		arr[i] = other.arr[i];

	curSize = other.curSize;
	capacity = other.capacity;
}

template<typename T>
void DynamicArray<T>::Free() 
{
	delete[] arr;
}

template<typename T>
void DynamicArray<T>::Resize(size_t newCap) 
{
	
	T* temp = arr;
	arr = new T[newCap];
	for (size_t i = 0; i < curSize; i++)
		arr[i] = temp[i];

	capacity = newCap;
	delete[] temp;
}



template <typename T>
void DynamicArray<T>::swap(int i, int j)
{
	T temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

template <typename T>
int DynamicArray<T>::Partition(int low, int high)
{
	T pivot = arr[high];  
	int i = (low - 1); 
	for (int j = low; j <= high - 1; j++)
	{
		
		if (arr[j] < pivot)
		{
			i++;  
			swap(i,j);
		}
	}
	swap(i+1, high);
	return (i + 1);
}

template <typename T>
void DynamicArray<T>::QuickSort(int low, int high)
{
	if (low >= high)
		return;
	int pi = Partition( low, high);
	QuickSort( low, pi - 1);
	QuickSort(pi + 1, high);
}

template<typename T>
void DynamicArray<T>::PushBack(const T& newElem) 
{

	if (curSize >= capacity)
		Resize(capacity * 2);

	arr[curSize++] = newElem;
}

template<typename T>
T DynamicArray<T>::PopBack() 
{

	T el = arr[curSize - 1];
	if (curSize)
		curSize--;
	else
		throw std::length_error("Already empty!");

	if (curSize * 2 <= capacity && capacity > 1)
		Resize(capacity / 2);
	return el;
}

template<typename T>
void DynamicArray<T>::InsertAt(size_t index, const T& newElem) 
{

	PushBack(newElem); //put the new element on last position

	if (index >= curSize) //the element should be the last one
		return;

	for (size_t i = curSize - 1; i > index; i--)
		std::swap(arr[i], arr[i - 1]);
}

template<typename T>
void DynamicArray<T>::RemoveAt(size_t index) 
{

	if (index >= curSize || curSize == 1) { //removes the last element
		PopBack();
		return;
	}

	for (size_t i = index; i < curSize-1; i++)
		std::swap(arr[i], arr[i + 1]);
	PopBack();
}

template <typename T>
int DynamicArray<T>::IndexOf(const T& el)
{
	for (int i = 0; i < curSize; ++i)
	{
		if (arr[i] == el)
			return i;
	}
	return -1;
}

template<typename T>
int DynamicArray<T>::getSize() const 
{
	return curSize;
}


template<typename T>
const T& DynamicArray<T>::operator[](size_t index) const 
{

	if (index > curSize)
		throw std::out_of_range("Out of range!");
	return arr[index];
}


template<typename T>
T& DynamicArray<T>::operator[](size_t index) {
	if (index > curSize)
		throw std::out_of_range("Out of range!");
	return arr[index];
}

template <typename T>
void DynamicArray<T>::Sort()
{
	QuickSort(0, curSize - 1);
}
#endif // !DYNAMICARRAY_HDR
