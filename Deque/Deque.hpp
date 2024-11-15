#pragma once

#include <algorithm>
#include <memory>
#include <stdexcept>

template <class T, class AllocatorType = std::allocator<T>>
class deque
{
public:
	deque();

	deque(const deque<T, AllocatorType>& other);
	deque& operator=(const deque<T, AllocatorType>& other);

	deque(deque<T, AllocatorType>&& other) noexcept;
	deque& operator=(deque<T, AllocatorType>&& other) noexcept;

	~deque() noexcept;

	void push_front(const T& obj);
	void push_front(T&& obj);

	void push_back(const T& obj);
	void push_back(T&& obj);

	void pop_front();
	void pop_back();

	template <typename... Args>
	void emplaceFront(Args&&... args);

	template <typename... Args>
	void emplaceBack(Args&&... args);

	const T& operator[](size_t ind) const;
	T& operator[](size_t ind);

	const T& front() const;
	const T& back() const;

	T& front();
	T& back();

	size_t getSize() const;
	bool empty() const;

	class DequeIterator
	{
	public:
		DequeIterator& operator++(int)
		{
			index++;
			return *this;
		}

		DequeIterator operator++()
		{
			DequeIterator old = *this;
			index++;
			return old;
		}

		DequeIterator& operator--(int)
		{
			index--;
			return *this;
		}

		DequeIterator operator--()
		{
			DequeIterator old = *this;
			index--;
			return old;
		}

		DequeIterator operator+(int n)
		{
			return DequeIterator(d, index + n);
		}

		DequeIterator operator-(int n)
		{
			return DequeIterator(d, index - n);
		}

		T& operator*()
		{
			return d[index];
		}

		bool operator==(const DequeIterator& other)
		{
			return index == other.index;
		}

		bool operator!=(const DequeIterator& other)
		{
			return index != other.index;
		}

	private:
		deque& d;
		size_t index; // semantic index (not in the physical array)
		DequeIterator(deque& d, int index) : d(d), index(index) {}

		friend class deque;
	};

	class ConstDequeIterator
	{
	public:
		ConstDequeIterator& operator++(int)
		{
			index++;
			return *this;
		}

		ConstDequeIterator operator++()
		{
			ConstDequeIterator old = *this;
			index++;
			return old;
		}

		ConstDequeIterator& operator--(int)
		{
			index--;
			return *this;
		}

		ConstDequeIterator operator--()
		{
			ConstDequeIterator old = *this;
			index--;
			return old;
		}

		ConstDequeIterator operator+(int n)
		{
			return ConstDequeIterator(d, index + n);
		}

		ConstDequeIterator operator-(int n)
		{
			return ConstDequeIterator(d, index - n);
		}

		const T& operator*() const
		{
			return d[index];
		}

		bool operator==(const ConstDequeIterator& other)
		{
			return index == other.index;
		}

		bool operator!=(const ConstDequeIterator& other)
		{
			return index != other.index;
		}

	private:
		const deque& d;
		size_t index; // semantic index (not in the physical array)
		ConstDequeIterator(const deque& d, int index) : d(d), index(index) {}

		friend class deque;
	};

	deque::DequeIterator begin()
	{
		return DequeIterator(*this, 0);
	}

	deque::DequeIterator end()
	{
		return DequeIterator(*this, getSize());
	}

	deque::ConstDequeIterator begin() const
	{
		return ConstDequeIterator(*this, 0);
	}

	deque::ConstDequeIterator end() const
	{
		return ConstDequeIterator(*this, getSize());
	}
	
private:
	T* data = nullptr;

	size_t size = 0;
	size_t capacity = 0;
	size_t head = 0;
	size_t tail = 0;

	AllocatorType myAlloc;

	void moveIndex(size_t& index, bool forward) const;

	void copyFrom(const deque<T, AllocatorType>& other);
	void moveFrom(deque<T, AllocatorType>&& other) noexcept;
	void free();

	void resize(size_t newCapacity = 0);

	size_t calculateCapacity() const;
};

template <class T, class AllocatorType>
void deque<T, AllocatorType>::push_front(const T& obj)
{
	if (size >= capacity)
	{
		resize();
	}
	moveIndex(head, false);
	std::construct_at(data + head, obj);
	size++;
}

template <class T, class AllocatorType>
void deque<T, AllocatorType>::push_front(T&& obj)
{
	if (size >= capacity)
	{
		resize();
	}
	moveIndex(head, false);
	std::construct_at(data + head, std::move(obj));
	size++;
}

template <class T, class AllocatorType>
void deque<T, AllocatorType>::push_back(const T& obj)
{
	if (size >= capacity)
	{
		resize();
	}
	std::construct_at(data + tail, obj);
	moveIndex(tail, true);
	size++;
}

template <class T, class AllocatorType>
void deque<T, AllocatorType>::push_back(T&& obj)
{
	if (size >= capacity)
	{
		resize();
	}
	std::construct_at(data + tail, std::move(obj));
	moveIndex(tail, true);
	size++;
}

template <class T, class AllocatorType>
void deque<T, AllocatorType>::pop_front()
{
	if (empty())
	{
		throw std::out_of_range("deque is empty");
	}
	std::destroy_at(data + head);
	moveIndex(head, true);
	size--;
}

template <class T, class AllocatorType>
void deque<T, AllocatorType>::pop_back()
{
	if (empty())
	{
		throw std::out_of_range("deque is empty");
	}
	moveIndex(tail, false);
	std::destroy_at(data + tail);
	size--;
}

template <class T, class AllocatorType>
template <typename... Args>
void deque<T, AllocatorType>::emplaceFront(Args&&... args)
{
	if (size >= capacity)
	{
		resize();
	}
	moveIndex(head, false);
	std::construct_at(data + head, std::forward<Args>(args)...);
	size++;
}

template <class T, class AllocatorType>
template <typename... Args>
void deque<T, AllocatorType>::emplaceBack(Args&&... args)
{
	if (size >= capacity)
	{
		resize();
	}
	std::construct_at(data + tail, std::forward<Args>(args)...);
	moveIndex(tail, true);
	size++;
}

template <class T, class AllocatorType>
const T& deque<T, AllocatorType>::operator[](size_t ind) const
{
	return data[(head + ind) % capacity];
}

template <class T, class AllocatorType>
T& deque<T, AllocatorType>::operator[](size_t ind)
{
	return data[(head + ind) % capacity];
}

template <class T, class AllocatorType>
const T& deque<T, AllocatorType>::front() const
{
	return data[head];
}

template <class T, class AllocatorType>
const T& deque<T, AllocatorType>::back() const
{
	return data[(tail == 0 ? capacity : tail) - 1];
}

template <class T, class AllocatorType>
T& deque<T, AllocatorType>::front()
{
	return data[head];
}

template <class T, class AllocatorType>
T& deque<T, AllocatorType>::back()
{
	return data[(tail == 0 ? capacity : tail) - 1];
}

template <class T, class AllocatorType>
size_t deque<T, AllocatorType>::getSize() const
{
	return size;
}

template <class T, class AllocatorType>
bool deque<T, AllocatorType>::empty() const
{
	return size == 0;
}

template <class T, class AllocatorType>
void deque<T, AllocatorType>::moveIndex(size_t& index, bool forward) const
{
	if (capacity == 0)
	{
		throw std::runtime_error("Trying to move index on deque with no capacity");
	}
	if (forward)
	{
		(++index) %= capacity;
	}
	else
	{
		index = (index == 0) ? capacity - 1 : index - 1;
	}
}

template <class T, class AllocatorType>
deque<T, AllocatorType>::deque() : size(0), capacity(8), head(0), tail(0)
{
	data = myAlloc.allocate(capacity);
}

template <class T, class AllocatorType>
deque<T, AllocatorType>::deque(const deque<T, AllocatorType>& other)
{
	copyFrom(other);
}

template <class T, class AllocatorType>
deque<T, AllocatorType>& deque<T, AllocatorType>::operator=(const deque<T, AllocatorType>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <class T, class AllocatorType>
deque<T, AllocatorType>::deque(deque<T, AllocatorType>&& other) noexcept
{
	moveFrom(std::move(other));
}

template <class T, class AllocatorType>
deque<T, AllocatorType>& deque<T, AllocatorType>::operator=(deque<T, AllocatorType>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <class T, class AllocatorType>
deque<T, AllocatorType>::~deque() noexcept
{
	free();
}

template <class T, class AllocatorType>
void deque<T, AllocatorType>::copyFrom(const deque<T, AllocatorType>& other)
{
	capacity = other.capacity;
	data = myAlloc.allocate(capacity);
	for (size_t i = 0; i < other.getSize(); i++)
	{
		push_back(other[i]);
	}
}

template <class T, class AllocatorType>
void deque<T, AllocatorType>::moveFrom(deque<T, AllocatorType>&& other) noexcept
{
	data = other.data;
	size = other.size;
	capacity = other.capacity;
	head = other.head;
	tail = other.tail;

	other.data = nullptr;
	other.size = other.capacity = other.head = other.tail = 0;
}

template <class T, class AllocatorType>
void deque<T, AllocatorType>::free()
{
	// this check is needed in the case of full deque (when size == capacity)
    	// because then head == tail and elements won't be destroyed
    	if (head == tail && size >= 1)
    	{
        	std::destroy_at(data + head);
		moveIndex(head, true);
    	}
	while (head != tail)
	{
		std::destroy_at(data + head);
		moveIndex(head, true);
	}
	myAlloc.deallocate(data, capacity);
	data = nullptr;
	size = capacity = head = tail = 0;
}

template <class T, class AllocatorType>
void deque<T, AllocatorType>::resize(size_t newCapacity)
{
	if (newCapacity == 0)
	{
		newCapacity = calculateCapacity();
	}

	T* newData = myAlloc.allocate(newCapacity);
	
	size_t includedElementsCount = std::min(size, newCapacity);
	for (size_t i = 0; i < includedElementsCount; i++)
	{
		std::construct_at(newData + i, std::move(operator[](i)));
		std::destroy_at(data + ((head + i) % capacity));
	}
	myAlloc.deallocate(data, capacity);
	data = newData;

	head = 0;
	tail = size;
	capacity = newCapacity;
}

template<class T, class AllocatorType>
size_t deque<T, AllocatorType>::calculateCapacity() const
{
	return capacity ? capacity * 2 : 1;
}
