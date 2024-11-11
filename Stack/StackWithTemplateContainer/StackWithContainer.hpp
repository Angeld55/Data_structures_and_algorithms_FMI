#pragma once
#include <deque>

template <class T, class Container = std::deque<T>>
class Stack
{
private:
	Container _c;

public:
	T& top()
	{
		return _c.back();
	}
	const T& top() const
	{
		return _c.back();
	}

	bool empty() const
	{
		return _c.empty();
	}
	size_t size() const
	{
		return _c.size();
	}

	void push(const T& el)
	{
		_c.push_back(el);
	}
	void pop()
	{
		_c.pop_back();
	}
};