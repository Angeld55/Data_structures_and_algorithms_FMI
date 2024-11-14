#pragma once

#include "../iterator/iterator.hpp"
#include <memory>

namespace Constants
{
constexpr unsigned GROWTH_FACTOR = 2;
}

template <class T, class Allocator = std::allocator<T>>
class vector
{
  public:
	using iterator = vector_iterator<T>;
	using const_iterator = const_vector_iterator<T>;
	using reverse_iterator = reverse_vector_iterator<T>;

	vector() = default;
	explicit vector(size_t count);
	vector(size_t count, const T& initial);

	vector(const vector& other);
	vector& operator=(const vector& other);

	vector(vector&& other);
	vector& operator=(vector&& other);

	void push_back(const T& element);
	void push_back(T&& element);
	void pop_back();

	void erase(const_iterator position);
	void erase(const_iterator first, const_iterator last);

	void clear();

	template <class... Args>
	void emplace_back(Args&&... args);

	T& operator[](size_t idx);
	const T& operator[](size_t idx) const;

	T* data();

	void resize(size_t n);
	void reserve(size_t n);
	void shrink_to_fit();

	size_t size() const;
	size_t capacity() const;
	bool empty() const;

	iterator begin()
	{
		return iterator(_data);
	}
	iterator end()
	{
		return iterator(&_data[size()]);
	}

	const_iterator c_begin() const
	{
		return const_iterator(_data);
	}
	const_iterator c_end() const
	{
		return const_iterator(&_data[size()]);
	}

	reverse_iterator rbegin()
	{
		return size() > 0 ? reverse_iterator(&_data[size() - 1]) : reverse_iterator(nullptr);
	}

	reverse_iterator rend()
	{
		return size() > 0 ? reverse_iterator(_data - 1) : reverse_iterator(nullptr);
	}

	const T& back() const
	{
		return _data[size() - 1];
	}
	T& back()
	{
		return _data[size() - 1];
	}

	const T& front() const
	{
		return _data[0];
	}
	T& front()
	{
		return _data[0];
	}

	~vector();

  private:
	void copy(const vector& other);
	void free();
	void move(vector&& other);
	size_t calculate_capacity() const;

	Allocator _allocator;

	T* _data = nullptr;
	size_t _size = 0;
	size_t _capacity = 0;
};

// Constructs the container with count copies of elements with default value.
template <class T, class Allocator>
vector<T, Allocator>::vector(size_t count)
	: _data(_allocator.allocate(count))
	, _size(count)
	, _capacity(count)
{
	// Default construct all elements.
	for (size_t i = 0; i < size(); i++)
		_allocator.construct(&_data[i]);
}

// Constructs the container with count copies of elements with value initial.
template <class T, class Allocator>
vector<T, Allocator>::vector(size_t count, const T& initial)
	: _data(_allocator.allocate(count))
	, _size(count)
	, _capacity(count)
{
	for (size_t i = 0; i < size(); i++)
		_allocator.construct(&_data[i], initial);
}

template <class T, class Allocator>
vector<T, Allocator>::vector(const vector& other)
{
	copy(other);
}

template <class T, class Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

template <class T, class Allocator>
vector<T, Allocator>::vector(vector&& other)
{
	move(std::move(other));
}

template <class T, class Allocator>
vector<T, Allocator>& vector<T, Allocator>::operator=(vector&& other)
{
	if (this != &other)
	{
		free();
		move(std::move(other));
	}
	return *this;
}

template <class T, class Allocator>
vector<T, Allocator>::~vector()
{
	free();
}

template <class T, class Allocator>
void vector<T, Allocator>::copy(const vector<T, Allocator>& other)
{
	_data = _allocator.allocate(other.capacity());
	
	// Copy construct the new memory
	for (size_t i = 0; i < other.size(); i++)
		_allocator.construct(&_data[i], other[i]);

	_size = other.size();
	_capacity = other.capacity();
}

template <class T, class Allocator>
void vector<T, Allocator>::free()
{
	for (size_t i = 0; i < size(); i++)
		_allocator.destroy(&_data[i]);
	
	_allocator.deallocate(_data, capacity());
}

template <class T, class Allocator>
void vector<T, Allocator>::move(vector<T, Allocator>&& other)
{
	_size = other.size();
	_capacity = other.capacity();
	_data = other._data;

	other._data = nullptr;
	other._size = other._capacity = 0;
}

template <class T, class Allocator>
size_t vector<T, Allocator>::size() const
{
	return _size;
}

template <class T, class Allocator>
size_t vector<T, Allocator>::capacity() const
{
	return _capacity;
}

template <class T, class Allocator>
size_t vector<T, Allocator>::calculate_capacity() const
{
	if (capacity() == 0)
		return 1;
	return capacity() * Constants::GROWTH_FACTOR;
}

// Resizes the container to contain `n` elements, does nothing if `n` == size(). 
// If the current size is greater than `n`, the container is reduced to its first count elements. 
// If the current size is less than `n`, then additional default-inserted elements are appended.
template <class T, class Allocator>
void vector<T, Allocator>::resize(size_t n)
{
	if (n < size())
	{
		for (size_t i = n; i < size(); i++)
			_allocator.destroy(&_data[i]);
		_size = n;
	}
	else if (n > size())
	{
		if (n <= capacity())
		{
			for (size_t i = size(); i < n; i++)
				_allocator.construct(&_data[i]);
			
			_size = n;
		}
		else
		{
			T* new_data = _allocator.allocate(n);

			for (size_t i = 0; i < size(); i++)
				_allocator.construct(new_data, std::move(_data[i]));
			
			for (size_t i = size(); i < n; i++)
				_allocator.construct(&new_data[i]);

			_allocator.deallocate(_data, capacity());

			_data = new_data;
			_capacity = n;
			_size = n;
		}
	}
}

// Increase the capacity of the vector (the total number 
// of elements that the vector can hold without requiring reallocation) 
// to a value that's greater or equal to `n`. If `n` is greater than
// the current capacity(), new storage is allocated, otherwise the function does nothing. 
template <class T, class Allocator>
void vector<T, Allocator>::reserve(size_t n)
{
	if (n <= capacity())
		return;

	T* new_data = _allocator.allocate(n);

	for (size_t i = 0; i < size(); i++)
		_allocator.construct(&new_data[i], std::move(_data[i]));

	_allocator.deallocate(_data, capacity());

	_data = new_data;
	_capacity = n;
}

// Requests the container to reduce its capacity to fit its size.
// This may cause a reallocation, but has no effect on the vector size and cannot alter its elements.
template <class T, class Allocator>
void vector<T, Allocator>::shrink_to_fit()
{
	if (capacity() == size())
		return;

	T* new_data = _allocator.allocate(size());
	for (size_t i = 0; i < size(); i++)
		_allocator.construct(new_data + i, std::move(_data[i]));
	_allocator.deallocate(_data, capacity());

	_capacity = _size;
	_data = new_data;
}

template <class T, class Allocator>
void vector<T, Allocator>::push_back(const T& element)
{
	if (size() == capacity())
		reserve(calculate_capacity());

	_allocator.construct(_data[_size++], element);
}

template <class T, class Allocator>
void vector<T, Allocator>::push_back(T&& element)
{
	if (size() == capacity())
		reserve(calculate_capacity());

	_allocator.construct(&_data[_size++], std::move(element));
}

// Erases the specified elements from the container.
template <class T, class Allocator>
void vector<T, Allocator>::erase(const_iterator position)
{
	erase(position, position + 1);
}

// Erases the specified range from the container.
template <class T, class Allocator>
void vector<T, Allocator>::erase(const_iterator first, const_iterator last)
{
	int deleted_count = last - first;

	if (deleted_count <= 0)
		return;

	int begin_offset = first - begin();
	int end_offset = last - begin();

	if (last != c_end())
	{
		size_t construct_idx = begin_offset;
		for (size_t i = end_offset; i < size(); i++)
		{
			_allocator.construct(&_data[construct_idx], std::move(_data[i]));
			++construct_idx;
		}
	}

	for (size_t i = end_offset; i < size(); i++)
		_allocator.destroy(&_data[i]);
	
	_size -= deleted_count;
}

// Removes the last element of the container.
// Exceptions: Throws nothing.
template <class T, class Allocator>
void vector<T, Allocator>::pop_back()
{
	if (empty())
		return;

	erase(--end());
}

// Appends a new element to the end of the container. 
// The element is constructed through placement-new in-place.
template <class T, class Allocator>
template <class... Args>
void vector<T, Allocator>::emplace_back(Args&&... args)
{
	if (size() == capacity())
		reserve(calculate_capacity());

	_allocator.construct(&_data[_size++], std::forward<Args>(args)...);
}

template <class T, class Allocator>
T& vector<T, Allocator>::operator[](size_t idx)
{
	return _data[idx];
}

template <class T, class Allocator>
const T& vector<T, Allocator>::operator[](size_t idx) const
{
	return _data[idx];
}

template <class T, class Allocator>
T* vector<T, Allocator>::data()
{
	return _data;
}

template <class T, class Allocator>
void vector<T, Allocator>::clear()
{
	for (size_t i = 0; i < size(); i++)
		_allocator.destroy(&_data[i]);
	
	_size = 0;
}

template <class T, class Allocator>
bool vector<T, Allocator>::empty() const
{
	return (size() == 0);
}