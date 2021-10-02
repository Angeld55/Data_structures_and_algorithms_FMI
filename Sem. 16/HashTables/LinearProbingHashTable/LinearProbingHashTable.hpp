#include "../HashTable.hpp"

template <typename keyType, typename valueType, typename hashFunc = hash<keyType>>
class LinearProbingHashTable : public HashTable<keyType, valueType, hashFunc>
{
private:
	size_t jump;
	double maxFillLevel;
	int elementsCount;

	vector<bool> deletedCells;

	void copyFrom(const LinearProbingHashTable<keyType, valueType, hashFunc>& other);

public:
	void put(const keyType& key, const valueType& value);
	const valueType& get(const keyType& key);
	void remove(const keyType& key);

	LinearProbingHashTable();
	LinearProbingHashTable(const LinearProbingHashTable<keyType, valueType, hashFunc>& other);
	const LinearProbingHashTable<keyType, valueType, hashFunc>& operator= (const LinearProbingHashTable<keyType, valueType, hashFunc>& other);
};

template <typename keyType, typename valueType, typename hashFunc>
void LinearProbingHashTable<keyType, valueType, hashFunc>::put(const keyType& key, const valueType& value)
{
	this->addElInTableAndSeq(key, value, jump, true);
	elementsCount++;

	if (elementsCount >= maxFillLevel * this->hashTable.capacity())
	{
		this->resize();
		deletedCells.resize(this->hashTable.capacity());
	}
}
template <typename keyType, typename valueType, typename hashFunc>
const valueType& LinearProbingHashTable<keyType, valueType, hashFunc>::get(const keyType& key)
{
	size_t index = this->hasher(key) % this->hashTable.capacity();
	int startIndex = index;

	// An optimisation we do: replace the earliest tombstone encountered with the value we did a lookup for. The next time we lookup the key,
	// it will be found much faster!
	size_t firstTombstoneIndex = -1;
	bool foundFirstTombstoneIndex = false;

	do
	{
		if (!this->hashTable[index] && !deletedCells[index])
			throw "No such element";

		if (!foundFirstTombstoneIndex && deletedCells[index])
		{
			foundFirstTombstoneIndex = true;
			firstTombstoneIndex = index;
		}

		if ((!this->hashTable[index] && deletedCells[index]) || (this->hashTable[index]->key != key))
		{
			(index += jump) %= this->hashTable.capacity();
			continue;
		}

		if (foundFirstTombstoneIndex)
		{
			deletedCells[firstTombstoneIndex] = false;
			this->hashTable[firstTombstoneIndex] = this->hashTable[index];

			this->hashTable[index] = nullptr;
			return this->hashTable[firstTombstoneIndex]->value;
		}

		return this->hashTable[index]->value;

	} while (index != startIndex);

	throw "No such element";
}
template <typename keyType, typename valueType, typename hashFunc>
void LinearProbingHashTable<keyType, valueType, hashFunc>::remove(const keyType& key)
{
	size_t index = this->hasher(key) % this->hashTable.capacity();
	int startIndex = index;

	do
	{
		if (!this->hashTable[index] && !deletedCells[index])
			throw "No such element";

		if ((!this->hashTable[index] && deletedCells[index]) || (this->hashTable[index]->key != key))
		{
			(index += jump) %= this->hashTable.capacity();
			continue;
		}

		// removing searched value from the ordered sequence
		this->handleRemoveInSeq(this->hashTable[index]);

		// removing searched value from the hash table
		delete this->hashTable[index];
		this->hashTable[index] = nullptr;
		elementsCount--;
		deletedCells[index] = true;

		return;

	} while (index != startIndex);

	throw "No such element";
}

template <typename keyType, typename valueType, typename hashFunc>
void LinearProbingHashTable<keyType, valueType, hashFunc>::copyFrom(const LinearProbingHashTable<keyType, valueType, hashFunc>& other)
{
	this->jump = other.jump;
	this->maxFillLevel = other.maxFillLevel;
	this->deletedCells = other.deletedCells;

	typename HashTable<keyType, valueType, hashFunc>::Pair* iter = other.first;
	while (iter)
	{
		put(iter->key, iter->value);
		iter = iter->nextInSeq;
	}
}

template <typename keyType, typename valueType, typename hashFunc>
LinearProbingHashTable<keyType, valueType, hashFunc>::LinearProbingHashTable() : jump(1), maxFillLevel(0.8), elementsCount(0), deletedCells(this->hashTable.capacity(), false)
{}
template <typename keyType, typename valueType, typename hashFunc>
LinearProbingHashTable<keyType, valueType, hashFunc>::LinearProbingHashTable(const LinearProbingHashTable<keyType, valueType, hashFunc>& other)
{
	copyFrom(other);
}
template <typename keyType, typename valueType, typename hashFunc>
const LinearProbingHashTable<keyType, valueType, hashFunc>& LinearProbingHashTable<keyType, valueType, hashFunc>::operator= (const LinearProbingHashTable<keyType, valueType, hashFunc>& other)
{
	if (this != &other)
	{
		this->free();
		copyFrom(other);
	}

	return *this;
}