#include "../HashTable.hpp"

template <typename keyType, typename valueType, typename hashFunc = hash<keyType>>
class DoubleHashingHashTable : public HashTable<keyType, valueType, hashFunc>
{
private:
	double maxFillLevel;
	int elementsCount;

	vector<bool> deletedCells;

	void copyFrom(const DoubleHashingHashTable<keyType, valueType, hashFunc>& other);

public:
	void put(const keyType& key, const valueType& value);
	const valueType& get(const keyType& key);
	void remove(const keyType& key);

	DoubleHashingHashTable();
	DoubleHashingHashTable(const DoubleHashingHashTable<keyType, valueType, hashFunc>& other);
	const DoubleHashingHashTable<keyType, valueType, hashFunc>& operator= (const DoubleHashingHashTable<keyType, valueType, hashFunc>& other);
};

template <typename keyType, typename valueType, typename hashFunc>
void DoubleHashingHashTable<keyType, valueType, hashFunc>::put(const keyType& key, const valueType& value)
{
	this->addElInTableAndSeq(key, value);
	elementsCount++;

	if (elementsCount >= maxFillLevel * this->hashTable.capacity())
	{
		deletedCells = vector<bool>(this->hashTable.capacity() * 2, false);
		this->resize();
	}
}
template <typename keyType, typename valueType, typename hashFunc>
const valueType& DoubleHashingHashTable<keyType, valueType, hashFunc>::get(const keyType& key)
{
	size_t index = this->hasher(key) % this->hashTable.capacity();

	int count = 0;
	int i = 1;

	// An optimisation we do: replace the earliest tombstone encountered with the value we did a lookup for. The next time we lookup the key,
	// it will be found much faster!
	size_t firstTombstoneIndex = -1;
	bool foundFirstTombstoneIndex = false;

	while ((!this->hashTable[index] && deletedCells[index]) || (this->hashTable[index]->key != key))
	{
		if (!foundFirstTombstoneIndex && deletedCells[index])
		{
			foundFirstTombstoneIndex = true;
			firstTombstoneIndex = index;
		}

		if (hash<size_t>{}(index) % this->hashTable.capacity())
			(index += (i * hash<size_t>{}(index))) %= this->hashTable.capacity();
		else
			(index += (i * (hash<size_t>{}(index)+1))) %= this->hashTable.capacity();
		i++;
		count++;

		if (count >= this->hashTable.capacity())
			throw "No such element!";
	}

	if (foundFirstTombstoneIndex)
	{
		deletedCells[firstTombstoneIndex] = false;
		this->hashTable[firstTombstoneIndex] = this->hashTable[index];

		this->hashTable[index] = nullptr;

		return this->hashTable[firstTombstoneIndex]->value;
	}

	return this->hashTable[index]->value;
}
template <typename keyType, typename valueType, typename hashFunc>
void DoubleHashingHashTable<keyType, valueType, hashFunc>::remove(const keyType& key)
{
	size_t index = this->hasher(key) % this->hashTable.capacity();

	int count = 0;
	int i = 1;
	while ((!this->hashTable[index] && deletedCells[index]) || (this->hashTable[index]->key != key))
	{
		if (hash<size_t>{}(index) % this->hashTable.capacity())
			(index += (i * hash<size_t>{}(index))) %= this->hashTable.capacity();
		else
			(index += (i * (hash<size_t>{}(index)+1))) %= this->hashTable.capacity();
		i++;
		count++;

		if (count >= this->hashTable.capacity())
			throw "No such element!";
	}

	// removing searched value from the ordered sequence
	this->handleRemoveInSeq(this->hashTable[index]);

	// removing searched value from the hash table
	delete this->hashTable[index];
	this->hashTable[index] = nullptr;
	elementsCount--;
	deletedCells[index] = true;
}

template <typename keyType, typename valueType, typename hashFunc>
void DoubleHashingHashTable<keyType, valueType, hashFunc>::copyFrom(const DoubleHashingHashTable<keyType, valueType, hashFunc>& other)
{
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
DoubleHashingHashTable<keyType, valueType, hashFunc>::DoubleHashingHashTable() : maxFillLevel(0.8), elementsCount(0), deletedCells(this->hashTable.capacity(), false)
{}
template <typename keyType, typename valueType, typename hashFunc>
DoubleHashingHashTable<keyType, valueType, hashFunc>::DoubleHashingHashTable(const DoubleHashingHashTable<keyType, valueType, hashFunc>& other)
{
	copyFrom(other);
}
template <typename keyType, typename valueType, typename hashFunc>
const DoubleHashingHashTable<keyType, valueType, hashFunc>& DoubleHashingHashTable<keyType, valueType, hashFunc>::operator= (const DoubleHashingHashTable<keyType, valueType, hashFunc>& other)
{
	if (this != &other)
	{
		this->free();
		copyFrom(other);
	}

	return *this;
}