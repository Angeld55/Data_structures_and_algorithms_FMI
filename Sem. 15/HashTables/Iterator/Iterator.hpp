#pragma once

template <typename keyType, typename valueType>
class Iterator
{
public:
	virtual void operator++() = 0;
	virtual void operator--() = 0;
	virtual bool operator!=(const Iterator<keyType, valueType>& other) = 0;
};