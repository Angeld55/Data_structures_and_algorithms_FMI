#ifndef Vector_HDR
#define Vector_HDR

#include <iostream>

template<typename T>
class Vector 
{

private:
	T* arr;
	size_t size;
	size_t capacity;

public:
	Vector();
	Vector(size_t capacity);
	Vector(const Vector<T>& other);
	Vector<T>& operator=(const Vector<T>& other);
	~Vector();

private:
	void copyFrom(const Vector<T>& other);
	void free();
	void resize(size_t newCap);

public:
	void pushBack(const T& newElem); //add a new element in the end
	void popBack(); //removes the last element
	
	size_t getSize() const;
	bool isEmpty() const;
	
	const T& operator[](size_t index) const;
	T& operator[](size_t index);
	
	class VectorIterator
	{
		T* currentElementPtr;

	public:

		typedef std::random_access_iterator_tag iterator_category;

		VectorIterator(T* currentElementPtr = nullptr) : currentElementPtr(currentElementPtr) {}

		T& operator*()
		{
			return *currentElementPtr;
		}

		T* operator->()
		{
			return currentElementPtr;
		}

		T& operator[](size_t i)
		{
			return *(currentElementPtr + i);
		}

		VectorIterator& operator++()
		{
			currentElementPtr++;
			return *this;
		}

		VectorIterator operator++(int)
		{
			VectorIterator copy(*this);
			++(*this);
			return copy;
		}

		VectorIterator& operator--()
		{
			currentElementPtr--;
			return *this;
		}

		VectorIterator operator--(int)
		{
			VectorIterator copy(*this);
			--(*this);
			return copy;
		}



		VectorIterator& operator+=(int s)
		{
			if (s >= 0)
			{
				while (s--)
					++(*this);
			}
			else
			{
				while (s++)
					--(*this);
			}

			return *this;
		}

		VectorIterator& operator-=(int s)
		{
			return *this += (-s);
		}

		VectorIterator operator+(int i) const
		{

			VectorIterator res(*this);
			return res += i;
		}

		VectorIterator operator-(int i) const
		{

			VectorIterator res(*this);
			return res -= i;
		}

		int operator-(const VectorIterator& rhs) const
		{
			return currentElementPtr - rhs.currentElementPtr;
		}

		bool operator==(const VectorIterator& rhs) const { return currentElementPtr == rhs.currentElementPtr; }
		bool operator!=(const VectorIterator& rhs) const { return !(rhs == *this); }
		bool operator<(const VectorIterator& rhs) const { return currentElementPtr < rhs.currentElementPtr; }
		bool operator>(const VectorIterator& rhs) const { return (rhs < *this); }
		bool operator<=(const VectorIterator& rhs) const { return !(*this > rhs); }
		bool operator>=(const VectorIterator& rhs) const { return !(*this < rhs); }

	};
	VectorIterator begin()
	{
		return VectorIterator(arr);
	}
	VectorIterator end()
	{
		return VectorIterator(arr + size);
	}
	
};

template<typename T>
Vector<T>::Vector() : size(0), capacity(4) 
{
	arr = new T[capacity];
}

template <typename T>
Vector<T>::Vector(size_t capacity) : size(0)
{
    auto closestPowerOfTwo = [](size_t n)
    {
       	n--;
	    
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	n |= n >> 32;
	    
	return n + 1;	
    };

	this->capacity = closestPowerOfTwo(capacity);
	arr = new T[capacity];
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	copyFrom(other);
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) 
{

	if (this != &other) 
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
Vector<T>::~Vector() 
{
	free();
}

template<typename T>
void Vector<T>::copyFrom(const Vector<T>& other) 
{
	
	arr = new T[other.capacity];

	for (size_t i = 0; i < other.size; i++)
		arr[i] = other.arr[i];

	size = other.size;
	capacity = other.capacity;
}

template<typename T>
void Vector<T>::free() 
{
	delete[] arr;
}

template<typename T>
void Vector<T>::resize(size_t newCap) 
{
	
	T* temp = arr;
	arr = new T[newCap];

	for (size_t i = 0; i < size; i++)
		arr[i] = temp[i];

	capacity = newCap;
	delete[] temp;
}


template<typename T>
void Vector<T>::pushBack(const T& newElem) 
{
	if (size >= capacity)
		resize(capacity * 2);

	arr[size++] = newElem;
}

template<typename T>
void Vector<T>::popBack() 
{
	if (size)
		size--;
	else
		throw std::length_error("Already empty!");

	if (size * 4 <= capacity && capacity > 1)
		resize(capacity / 2);
}

template<typename T>
size_t Vector<T>::getSize() const 
{
	return size;
}

template<typename T>
bool Vector<T>::isEmpty() const
{
	return size == 0;
}


template<typename T>
const T& Vector<T>::operator[](size_t index) const 
{
	if (index > size)
		throw std::out_of_range("Out of range!");
	return arr[index];
}


template<typename T>
T& Vector<T>::operator[](size_t index) 
{
	if (index > size)
		throw std::out_of_range("Out of range!");
	return arr[index];
}

#endif // !Vector_HDR
