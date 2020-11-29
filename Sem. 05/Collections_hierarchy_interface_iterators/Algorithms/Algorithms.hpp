#pragma once

#include "../Iterators/Iterator.hpp"

template <typename T>
bool Search(Iterator<T>& begin, Iterator<T>& end, T el)
{
	for (auto& it = begin; it != end; it++)
	{
		if (el == *it)
			return true;
	}
	return false;
}