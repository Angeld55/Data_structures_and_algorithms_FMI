#pragma once
#include "../HashTable.hpp"

template<class KeyType, class ValueType, class HashFunc>
class LinearProbingHashTable : public HashTable<KeyType, ValueType, HashFunc>
{
	const size_t jump = 1;
	const double MAX_FILL_LEVEL = 0.8;

	std::vector<bool> deletedCells;

public:
	LinearProbingHashTable();

	void put(KeyType key, ValueType value);
	const ValueType& get(KeyType key);
	bool remove(KeyType key);

};

template<class KeyType, class ValueType, class HashFunc>
LinearProbingHashTable<KeyType, ValueType, HashFunc>::LinearProbingHashTable() : deletedCells(this->capacity, false)
{

}

template<class KeyType, class ValueType, class HashFunc>
void LinearProbingHashTable<KeyType, ValueType, HashFunc>::put(KeyType key, ValueType value)
{
	size_t index = this->hasher(key) % this->capacity;

	while (this->data[index] != nullptr)
		(index += jump) %= this->capacity;
	typename HashTable<KeyType, ValueType, HashFunc>::Pair* temp = new typename HashTable<KeyType, ValueType, HashFunc>::Pair(key, value);
	this->data[index] = temp;

	//if (capacity * MAX_FILL_LEVEL <= elementsCount)
	//{
	//	resize(); //each element should be re-hashed
	//}
}

template<class KeyType, class ValueType, class HashFunc>
const ValueType& LinearProbingHashTable<KeyType, ValueType, HashFunc>::get(KeyType key)
{
	size_t index = this->hasher(key) % this->capacity;
	size_t startIndex = index;
	while (true)
	{
		typename HashTable<KeyType, ValueType, HashFunc>::Pair* currentCell = this->data[index];

		if (currentCell != nullptr && currentCell->key == key)
			return currentCell->value;
		if (currentCell == nullptr && !deletedCells[index])
			throw "No such element!";

		(index += jump) %= this->capacity;

		if (index == startIndex)
			throw "No such element!";
	}
}

template<class KeyType, class ValueType, class HashFunc>
bool LinearProbingHashTable<KeyType, ValueType, HashFunc>::remove(KeyType key)
{
	size_t index = this->hasher(key) % this->capacity;
	size_t startIndex = index;

	while (this->data[index] != nullptr || deletedCells[index])
	{
		typename HashTable<KeyType, ValueType, HashFunc>::Pair* currentCell = this->data[index];
		if (currentCell == nullptr)
			continue;

		if (currentCell->key == key)
		{
			delete currentCell;
			currentCell = nullptr;
			deletedCells[index] = true;
			return true;
		}

		(index += jump) %= this->capacity;

		if (index == startIndex)
			throw "Invalid key";
	}
	throw "Invalid key";
}