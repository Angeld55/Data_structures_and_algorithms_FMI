#include <iostream>
#include <memory>

template <class T, class AllocatorType = std::allocator<T>>
class Deque
{
	T* data = nullptr;
	size_t currentSize = 0;
	size_t currCapacity = 0;
	size_t head = 0;
	size_t tail = 0;
	AllocatorType myAlloc;

	void moveIndex(size_t& index, bool forward);
	void copyFrom(const Deque<T, AllocatorType>& other);
	void moveFrom(Deque<T, AllocatorType>&& other);
	void free();
	void resize(size_t newCapacity = 0);

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

	public:
		Iterator(Deque& deque, int index) : deque(deque), index(index) {}

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
			return deque.data[index];
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

	public:
		ConstIterator(const Deque& deque, int index) : deque(deque), index(index) {}

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
			return deque.data[index];
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
Deque<T, AllocatorType>::Deque() : currCapacity(8), currentSize(0), head(0), tail(0)
{
	data = myAlloc.allocate(currCapacity);
}

template <class T, class AllocatorType>
void Deque<T, AllocatorType>::moveIndex(size_t& index, bool forward)
{
	if (forward)
	{
		(++index) %= currCapacity;
	}
	else
	{
		index = (index == 0) ? currCapacity - 1 : index - 1;
	}
}

template <class T, class AllocatorType>
void Deque<T, AllocatorType>::copyFrom(const Deque<T, AllocatorType>& other)
{
	currCapacity = other.currCapacity;
	currentSize = other.currentSize;
	head = other.head;
	tail = other.tail;
	data = myAlloc.allocate(currCapacity);

	for (size_t i = 0; i < other.size(); i++)
	{
		pushBack(other[i]);
	}
}

template <class T, class AllocatorType>
void Deque<T, AllocatorType>::moveFrom(Deque<T, AllocatorType>&& other)
{
	free();
	data = other.data;
	currentSize = other.currentSize;
	currCapacity = other.currCapacity;
	head = other.head;
	tail = other.tail;

	other.data = nullptr;
	other.currentSize = other.currCapacity = 0;
}

template <class T, class AllocatorType>
void Deque<T, AllocatorType>::free()
{
	while (head != tail)
	{
		myAlloc.destroy(data + head);
		moveIndex(head, true);
	}
	myAlloc.deallocate(data, currCapacity);
	data = nullptr;
	currentSize = head = tail = currCapacity = 0;
}

template <class T, class AllocatorType>
void Deque<T, AllocatorType>::resize(size_t newCapacity)
{
	if (newCapacity == 0) newCapacity = currCapacity * 2;

	T* newData = myAlloc.allocate(newCapacity);
	for (size_t i = 0; i < currentSize; i++)
	{
		myAlloc.construct(newData + i, std::move(operator[](i)));
		myAlloc.destroy(data + ((head + i) % currCapacity));
	}
	myAlloc.deallocate(data, currCapacity);

	head = 0;
	tail = currentSize % newCapacity;
	currCapacity = newCapacity;
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
	if (currentSize >= currCapacity)
		resize();
	moveIndex(head, false);
	myAlloc.construct(data + head, obj);
	currentSize++;
}

template <class T, class AllocatorType>
void Deque<T, AllocatorType>::pushFront(T&& obj)
{
	if (currentSize >= currCapacity)
		resize();
	moveIndex(head, false);
	myAlloc.construct(data + head, std::move(obj));
	currentSize++;
}

template <class T, class AllocatorType>
void Deque<T, AllocatorType>::pushBack(const T& obj)
{
	if (currentSize >= currCapacity)
		resize();
	myAlloc.construct(data + tail, obj);
	moveIndex(tail, true);
	currentSize++;
}

template <class T, class AllocatorType>
void Deque<T, AllocatorType>::pushBack(T&& obj)
{
	if (currentSize >= currCapacity)
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
	if (currentSize >= currCapacity)
		resize();
	moveIndex(head, false);
	myAlloc.construct(data + head, std::forward<Args>(args)...);
	currentSize++;
}

template <class T, class AllocatorType>
template <typename... Args>
void Deque<T, AllocatorType>::emplaceBack(Args&&... args)
{
	if (currentSize >= currCapacity)
		resize();
	myAlloc.construct(data + tail, std::forward<Args>(args)...);
	moveIndex(tail, true);
	currentSize++;
}

template<class T, class AllocatorType>
void Deque<T, AllocatorType>::shrinkToFit()
{
	if (currCapacity > currentSize)
	{
		resize(currentSize); 
	}
}

template <class T, class AllocatorType>
T& Deque<T, AllocatorType>::operator[](size_t ind)
{
	return data[(head + ind) % currCapacity];
}

template <class T, class AllocatorType>
const T& Deque<T, AllocatorType>::operator[](size_t ind) const
{
	return data[(head + ind) % currCapacity];
}

template <class T, class AllocatorType>
T& Deque<T, AllocatorType>::back()
{
	return data[(tail == 0 ? currCapacity : tail) - 1];
}

template <class T, class AllocatorType>
const T& Deque<T, AllocatorType>::back() const
{
	return data[(tail == 0 ? currCapacity : tail) - 1];
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
	return currCapacity;
}
