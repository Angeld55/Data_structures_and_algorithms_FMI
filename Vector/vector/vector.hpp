#pragma once
#include "../iterator/iterator.hpp"
#include <utility>
#include <algorithm>
namespace Constants
{
constexpr unsigned GROWTH_FACTOR = 2;
}

//It uses the default allocator. Could be done with template allocator.
template <class T>
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
		return iterator(_data + size());
	}

	const_iterator c_begin() const
	{
		return const_iterator(_data);
	}
	const_iterator c_end() const
	{
		return const_iterator(_data + size());
	}

	reverse_iterator rbegin()
	{
    		return size() > 0 ? reverse_iterator(_data + size() - 1) : reverse_iterator(nullptr);
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

	T* _data = nullptr;
	size_t _size = 0;
	size_t _capacity = 0;
};

// Constructs the container with count copies of elements with default value.
// Why dont we call `new` here?
// When you choose a memory managment strategy
// to stick with it for concistency.
template <class T>
vector<T>::vector(size_t count)
	: _data(static_cast<T*>(operator new(count * sizeof(T))))
	, _size(count)
	, _capacity(count)
{
	// default construct all elements
	for (size_t i = 0; i < count; i++)
		new (&_data[i]) T();
}

// Constructs the container with count copies of elements with value initial.
template <class T>
vector<T>::vector(size_t count, const T& initial)
	: _data(static_cast<T*>(operator new(count * sizeof(T))))
	, _size(count)
	, _capacity(count)
{
	// construct all elements copying initial
	for (size_t i = 0; i < count; i++)
		new (&_data[i]) T(initial);
}

template <class T>
vector<T>::vector(const vector& other)
{
	copy(other);
}

template <class T>
vector<T>& vector<T>::operator=(const vector& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

template <class T>
vector<T>::vector(vector&& other)
{
	move(std::move(other));
}

template <class T>
vector<T>& vector<T>::operator=(vector&& other)
{
	if (this != &other)
	{
		free();
		move(std::move(other));
	}
	return *this;
}

template <class T>
vector<T>::~vector()
{
	free();
}

template <class T>
void vector<T>::copy(const vector<T>& other)
{
	// allocate enough memoty
	_data = static_cast<T*>(operator new(other.capacity() * sizeof(T)));

	// copy construct elements
	for (size_t i = 0; i < other.size(); i++)
		new (&_data[i]) T(other[i]);

	_size = other.size();
	_capacity = other.capacity();
}

template <class T>
void vector<T>::free()
{
	// call destructor on constructed elements
	for (size_t i = 0; i < size(); i++)
		_data[i].~T();

	// deallocate memory
	operator delete(_data, capacity() * sizeof(T));
}

template <class T>
void vector<T>::move(vector<T>&& other)
{
	_size = other.size();
	_capacity = other.capacity();
	_data = other._data;

	other._data = nullptr;
	other._size = other._capacity = 0;
}

template <class T>
size_t vector<T>::size() const
{
	return _size;
}

template <class T>
size_t vector<T>::capacity() const
{
	return _capacity;
}

template <class T>
size_t vector<T>::calculate_capacity() const
{
	if (capacity() == 0)
		return 1;
	return capacity() * Constants::GROWTH_FACTOR;
}

// Resizes the container to contain `n` elements, does nothing if `n` == size(). 
// If the current size is greater than `n`, the container is reduced to its first count elements. 
// If the current size is less than `n`, then additional default-inserted elements are appended.
template <class T>
void vector<T>::resize(size_t n)
{
	if (n < size())
	{
		// call destructor on constructed elements
		for (size_t i = n; i < size(); i++)
			(_data + i)->~T();

		_size = n;
	}
	else if (n > size())
	{
		if (n <= capacity())
		{
			// default construct elements in range [size(), n)
			for (size_t i = size(); i < n; i++)
				new (&_data[i]) T();

			_size = n;
		}
		else
		{
			T* new_data = static_cast<T*>(operator new(n * sizeof(T)));

			for (size_t i = 0; i < size(); i++)
				new (&new_data[i]) T(std::move(_data[i]));

			for (size_t i = size(); i < n; i++)
				new (&new_data[i]) T();

			operator delete(_data, capacity() * sizeof(T));

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
template <class T>
void vector<T>::reserve(size_t n)
{
	if (n <= capacity())
		return;

	T* new_data = static_cast<T*>(operator new(n * sizeof(T)));

	for (size_t i = 0; i < size(); i++)
        {
		new (&new_data[i]) T(std::move(_data[i]));
                _data[i].~T();
	}
	operator delete(_data, capacity() * sizeof(T));

	_data = new_data;
	_capacity = n;
}

// Requests the container to reduce its capacity to fit its size.
// This may cause a reallocation, but has no effect on the vector size and cannot alter its elements.
template <class T>
void vector<T>::shrink_to_fit()
{
	if (capacity() == size())
		return;

	T* new_data = static_cast<T*>(operator new(size() * sizeof(T)));

	for (size_t i = 0; i < size(); i++)
	{
		new (&new_data[i]) T(std::move(_data[i]));
		_data[i].~T();
	}
	operator delete(_data, capacity() * sizeof(T));

	_capacity = _size;
	_data = new_data;
}

template <class T>
void vector<T>::push_back(const T& element)
{
	if (size() == capacity())
		reserve(calculate_capacity());

	new (&_data[_size++]) T(element);
}

template <class T>
void vector<T>::push_back(T&& element)
{
	if (size() == capacity())
		reserve(calculate_capacity());

	new (&_data[_size++]) T(std::move(element));
}

// Erases the specified elements from the container.
template <class T>
void vector<T>::erase(const_iterator position)
{
	erase(position, position + 1);
}

// Erases the specified range from the container.
template <class T>
void vector<T>::erase(const_iterator first, const_iterator last)
{
	int deleted_count = last - first;

	if (deleted_count <= 0)
		return;

	int begin_offset = first - begin();
	int end_offset = last - begin();

	if (last != c_end())
	{
		for (size_t i = end_offset; i < size(); i++)
			new (&_data[begin_offset++]) T(std::move(_data[i]));
	}

	for (size_t i = end_offset; i < size(); i++)
		(_data + i)->~T();

	_size -= deleted_count;
}

// Removes the last element of the container.
// Exceptions: Throws nothing.
template <class T>
void vector<T>::pop_back()
{
	if (empty())
		return;

	erase(--end());
}

// Appends a new element to the end of the container. 
// The element is constructed through placement-new in-place.
template <class T>
template <class... Args>
void vector<T>::emplace_back(Args&&... args)
{
	if (size() == capacity())
		reserve(calculate_capacity());

	new (&_data[_size++]) T(std::forward<Args>(args)...);
}

template <class T>
T& vector<T>::operator[](size_t idx)
{
	return _data[idx];
}

template <class T>
const T& vector<T>::operator[](size_t idx) const
{
	return _data[idx];
}

template <class T>
T* vector<T>::data()
{
	return _data;
}

template <class T>
void vector<T>::clear()
{
	for (size_t i = 0; i < size(); i++)
		(_data + i)->~T();

	_size = 0;
}

template <class T>
bool vector<T>::empty() const
{
	return (size() == 0);
}
