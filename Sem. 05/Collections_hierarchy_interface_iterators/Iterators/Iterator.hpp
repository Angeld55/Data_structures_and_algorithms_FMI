#pragma once

template <typename T>
class Iterator
{
public:
	virtual T& operator*() = 0;
	virtual void operator++() = 0;
	virtual void operator--() = 0;
	virtual bool operator!=(Iterator&) = 0;
};