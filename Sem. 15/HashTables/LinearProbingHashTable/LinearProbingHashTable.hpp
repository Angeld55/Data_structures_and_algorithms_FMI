#pragma once
#include "../HashTable.hpp"

template<typename KeyType, typename ValueType, typename HashFunc = std::hash<KeyType>>
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

template<typename KeyType, typename ValueType, typename HashFunc = std::hash<KeyType>>
LinearProbingHashTable<KeyType, ValueType, HashFunc>::LinearProbingHashTable() : deletedCells(capacity, false)
{

}

template<typename KeyType, typename ValueType, typename HashFunc = std::hash<KeyType>>
void LinearProbingHashTable<KeyType, ValueType, HashFunc>::put(KeyType key, ValueType value)
{
	size_t index = hasher(key) % capacity;

	while (data[index] != nullptr)
		(index += jump) %= capacity;
	Pair* temp = new Pair(key, value);
	data[index] = temp;

	//if (capacity * MAX_FILL_LEVEL <= elementsCount)
	//{
	//	resize(); //each element should be re-hashed
	//}
}

template<typename KeyType, typename ValueType, typename HashFunc = std::hash<KeyType>>
const ValueType& LinearProbingHashTable<KeyType, ValueType, HashFunc>::get(KeyType key)
{
	size_t index = hasher(key) % capacity;
	size_t startIndex = index;
	while (true)
	{
		Pair* currentCell = data[index];

		if (currentCell != nullptr && currentCell->key == key)
			return currentCell->value;
		if (currentCell == nullptr && !deletedCells[index])
			throw "No such element!";

		(index += jump) %= capacity;

		if (index == startIndex)
			throw "No such element!";

	}
}

template<typename KeyType, typename ValueType, typename HashFunc = std::hash<KeyType>>
bool LinearProbingHashTable<KeyType, ValueType, HashFunc>::remove(KeyType key)
{
	size_t index = hasher(key) % capacity;
	size_t startIndex = index;

	while (data[index] != nullptr || deletedCells[index])
	{
		Pair* currentCell = data[index];
		if (currentCell == nullptr)
			continue;

		if (currentCell->key == key)
		{
			delete currentCell;
			currentCell = nullptr;
			deletedCells[index] = true;
			return true;
		}

		(index += jump) %= capacity;

		if (index == startIndex)
			throw "Invalid key";
	}
	throw "Invalid key";
}