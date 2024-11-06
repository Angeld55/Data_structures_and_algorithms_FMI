#pragma once

#include <memory>
#include <stdexcept>

template <class T, class AllocatorType = std::allocator<T>>
class Deque
{
	T* data = nullptr;
	size_t currentSize = 0;
	size_t currentCapacity = 0;
	size_t head = 0;
	size_t tail = 0;
	AllocatorType myAlloc;

	void moveIndex(size_t& index, bool forward) const;
	void copyFrom(const Deque<T, AllocatorType>& other);
	void moveFrom(Deque<T, AllocatorType>&& other) noexcept;
	void free();
	void resize(size_t newCapacity = 0);

	size_t calculateCapacity() const;

public:
	Deque();
	Deque(const Deque<T, AllocatorType>& other);
	Deque(Deque<T, AllocatorType>&& other) noexcept;
	Deque& operator=(const Deque<T, AllocatorType>& other);
	Deque& operator=(Deque<T, AllocatorType>&& other) noexcept;
	~Deque();

	void pushFront(const T& obj);
	void pushFront(T&& obj);
	void pushBack(const T& obj);
	void pushBack(T&& obj);
	void popFront();
	void popBack();

	template <typename... Args>
	void emplaceFront(Args&&... args);

	template <typename... Args>
	void emplaceBack(Args&&... args);

	void shrinkToFit();

	T& operator[](size_t ind);
	const T& operator[](size_t ind) const;

	T& back();
	const T& back() const;
	T& front();
	const T& front() const;
	bool isEmpty() const;
	size_t size() const;
	size_t capacity() const;

	class Iterator
	{
		friend class Deque;
		Deque& deque;
		size_t index; //(not in the physical array)

		Iterator(Deque& deque, int index) : deque(deque), index(index) {}

	public:

		Iterator& operator++(int)
		{
			index++;
			return *this;
		}

		Iterator operator++()
		{
			Iterator old = *this;
			index++;
			return old;
		}

		Iterator& operator--(int)
		{
			index--;
			return *this;
		}

		Iterator operator--()
		{
			Iterator old = *this;
			index--;
			return old;
		}

		Iterator operator+(int n)
		{
			return Iterator(deque, index + n);
		}

		Iterator operator-(int n)
		{
			return Iterator(deque, index - n);
		}

		T& operator*()
		{
			return deque[index];
		}

		bool operator==(const Iterator& other)
		{
			return index == other.index;
		}
		bool operator!=(const Iterator& other)
		{
			return index != other.index;
		}
	};

	class ConstIterator
	{
		friend class Deque;
		const Deque& deque;
		size_t index; //semantic index (not in the physical array)

		ConstIterator(const Deque& deque, int index) : deque(deque), index(index) {}

	public:

		ConstIterator& operator++(int)
		{
			index++;
			return *this;
		}

		ConstIterator operator++()
		{
			ConstIterator old = *this;
			index++;
			return old;
		}

		ConstIterator& operator--(int)
		{
			index--;
			return *this;
		}

		ConstIterator operator--()
		{
			ConstIterator old = *this;
			index--;
			return old;
		}

		ConstIterator operator+(int n)
		{
			return ConstIterator(deque, index + n);
		}

		ConstIterator operator-(int n)
		{
			return ConstIterator(deque, index - n);
		}

		const T& operator*() const
		{
			return deque[index];
		}

		bool operator==(const ConstIterator& other)
		{
			return index == other.index;
		}
		bool operator!=(const ConstIterator& other)
		{
			return index != other.index;
		}
	};

	Deque::Iterator begin()
	{
		return Iterator(*this, 0);
	}

	Deque::Iterator end()
	{
		return Iterator(*this, size());
	}

	Deque::ConstIterator begin() const
	{
		return ConstIterator(*this, 0);
	}

	Deque::ConstIterator end() const
	{
		return ConstIterator(*this, size());
	}
};

// Implementation of member functions
template <class T, class AllocatorType>
Deque<T, AllocatorType>::Deque() : currentCapacity(8), currentSize(0), head(0), tail(0)
{
	data = myAlloc.allocate(currentCapacity);
}

template <class T, class AllocatorType>
void Deque<T, AllocatorType>::moveIndex(size_t& index, bool forward) const
{
	if(currentCapacity == 0)
		throw std::runtime_error("Trying to move index on deque with no capacity");
	
	if (forward)
	{
		(++index) %= currentCapacity;
	}
	else
	{
		index = (index == 0) ? currentCapacity - 1 : index - 1;
	}
}

template <class T, class AllocatorType>
void Deque<T, AllocatorType>::copyFrom(const Deque<T, AllocatorType>& other)
{
	currentCapacity = other.currentCapacity;
	data = myAlloc.allocate(currentCapacity);

	for (size_t i = 0; i < other.size(); i++)
	{
		pushBack(other[i]);
	}
}

template <class T, class AllocatorType>
void Deque<T, AllocatorType>::moveFrom(Deque<T, AllocatorType>&& other) noexcept
{
	data = other.data;
	currentSize = other.currentSize;
	currentCapacity = other.currentCapacity;
	head = other.head;
	tail = other.tail;

	other.data = nullptr;
	// Destructor might fail otherwise.
	other.head = other.tail = 0;
	other.currentSize = other.currentCapacity = 0;
}

template <class T, class AllocatorType>
void Deque<T, AllocatorType>::free()
{
	while (head != tail)
	{
		myAlloc.destroy(data + head);
		moveIndex(head, true);
	}
	myAlloc.deallocate(data, currentCapacity);
	data = nullptr;
	currentSize = head = tail = currentCapacity = 0;
}

template <class T, class AllocatorType>
void Deque<T, AllocatorType>::resize(size_t newCapacity)
{
	if (newCapacity == 0) 
	{
		newCapacity = calculateCapacity();
	}

	T* newData = myAlloc.allocate(newCapacity);
	for (size_t i = 0; i < currentSize; i++)
	{
		myAlloc.construct(newData + i, std::move(operator[](i)));
		myAlloc.destroy(data + ((head + i) % currentCapacity));
	}
	myAlloc.deallocate(data, currentCapacity);

	head = 0;
	tail = currentSize % newCapacity;
	currentCapacity = newCapacity;
	data = newData;
}

template <class T, class AllocatorType>
Deque<T, AllocatorType>::~Deque()
{
	free();
}

template <class T, class AllocatorType>
Deque<T, AllocatorType>::Deque(const Deque<T, AllocatorType>& other)
{
	copyFrom(other);
}

template <class T, class AllocatorType>
Deque<T, AllocatorType>::Deque(Deque<T, AllocatorType>&& other) noexcept
{
	moveFrom(std::move(other));
}

template <class T, class AllocatorType>
Deque<T, AllocatorType>& Deque<T, AllocatorType>::operator=(const Deque<T, AllocatorType>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <class T, class AllocatorType>
Deque<T, AllocatorType>& Deque<T, AllocatorType>::operator=(Deque<T, AllocatorType>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <class T, class AllocatorType>
void Deque<T, AllocatorType>::pushFront(const T& obj)
{
	if (currentSize >= currentCapacity)
		resize();
	moveIndex(head, false);
	myAlloc.construct(data + head, obj);
	currentSize++;
}

template <class T, class AllocatorType>
void Deque<T, AllocatorType>::pushFront(T&& obj)
{
	if (currentSize >= currentCapacity)
		resize();
	moveIndex(head, false);
	myAlloc.construct(data + head, std::move(obj));
	currentSize++;
}

template <class T, class AllocatorType>
void Deque<T, AllocatorType>::pushBack(const T& obj)
{
	if (currentSize >= currentCapacity)
		resize();
	myAlloc.construct(data + tail, obj);
	moveIndex(tail, true);
	currentSize++;
}

template <class T, class AllocatorType>
void Deque<T, AllocatorType>::pushBack(T&& obj)
{
	if (currentSize >= currentCapacity)
		resize();
	myAlloc.construct(data + tail, std::move(obj));
	moveIndex(tail, true);
	currentSize++;
}

template <class T, class AllocatorType>
void Deque<T, AllocatorType>::popFront()
{
	if (isEmpty())
		throw std::out_of_range("Deque is empty");
	myAlloc.destroy(data + head);
	moveIndex(head, true);
	currentSize--;
}

template <class T, class AllocatorType>
void Deque<T, AllocatorType>::popBack()
{
	if (isEmpty())
		throw std::out_of_range("Deque is empty");
	moveIndex(tail, false);
	myAlloc.destroy(data + tail);
	currentSize--;
}

template <class T, class AllocatorType>
template <typename... Args>
void Deque<T, AllocatorType>::emplaceFront(Args&&... args)
{
	if (currentSize >= currentCapacity)
		resize();
	moveIndex(head, false);
	myAlloc.construct(data + head, std::forward<Args>(args)...);
	currentSize++;
}

template <class T, class AllocatorType>
template <typename... Args>
void Deque<T, AllocatorType>::emplaceBack(Args&&... args)
{
	if (currentSize >= currentCapacity)
		resize();
	myAlloc.construct(data + tail, std::forward<Args>(args)...);
	moveIndex(tail, true);
	currentSize++;
}

template<class T, class AllocatorType>
void Deque<T, AllocatorType>::shrinkToFit()
{
	if (currentCapacity > currentSize)
	{
		// If size is 0 then we double up the memory.
		if(currentSize == 0)
		{
			free();
			return;
		}
		
		resize(currentSize);
	}
}

template <class T, class AllocatorType>
T& Deque<T, AllocatorType>::operator[](size_t ind)
{
	return data[(head + ind) % currentCapacity];
}

template <class T, class AllocatorType>
const T& Deque<T, AllocatorType>::operator[](size_t ind) const
{
	return data[(head + ind) % currentCapacity];
}

template <class T, class AllocatorType>
T& Deque<T, AllocatorType>::back()
{
	return data[(tail == 0 ? currentCapacity : tail) - 1];
}

template <class T, class AllocatorType>
const T& Deque<T, AllocatorType>::back() const
{
	return data[(tail == 0 ? currentCapacity : tail) - 1];
}

template <class T, class AllocatorType>
T& Deque<T, AllocatorType>::front()
{
	return data[head];
}

template <class T, class AllocatorType>
const T& Deque<T, AllocatorType>::front() const
{
	return data[head];
}

template <class T, class AllocatorType>
bool Deque<T, AllocatorType>::isEmpty() const
{
	return currentSize == 0;
}

template <class T, class AllocatorType>
size_t Deque<T, AllocatorType>::size() const
{
	return currentSize;
}

template<class T, class AllocatorType>
size_t Deque<T, AllocatorType>::capacity() const
{
	return currentCapacity;
}

template<class T, class AllocatorType>
size_t Deque<T, AllocatorType>::calculateCapacity() const
{
	return currentCapacity ? currentCapacity * 2 : 1;
}
