#include "../HashTable.hpp"

template <typename keyType, typename valueType, typename hashFunc = hash<keyType>>
class SeparateChainingHashTable : public HashTable<keyType, valueType, hashFunc>
{
private:
	struct SeparateChainingHashTablePair : public HashTable<keyType, valueType, hashFunc>::Pair
	{
		SeparateChainingHashTablePair* next;

		SeparateChainingHashTablePair(const keyType& key, const valueType& value) : HashTable<keyType, valueType, hashFunc>::Pair(key, value)
		{
			next = nullptr;
		}
		~SeparateChainingHashTablePair()
		{
			if (next)
				delete next;
		}
	};

	void copyFrom(const SeparateChainingHashTable<keyType, valueType, hashFunc>& other);

public:
	void put(const keyType& key, const valueType& value);
	const valueType& get(const keyType& key);
	void remove(const keyType& key);

	SeparateChainingHashTable();
	SeparateChainingHashTable(const SeparateChainingHashTable<keyType, valueType, hashFunc>& other);
	const SeparateChainingHashTable<keyType, valueType, hashFunc>& operator= (const SeparateChainingHashTable<keyType, valueType, hashFunc>& other);
};

template <typename keyType, typename valueType, typename hashFunc>
void SeparateChainingHashTable<keyType, valueType, hashFunc>::put(const keyType& key, const valueType& value)
{
	size_t index = this->hasher(key) % this->hashTable.capacity();

	SeparateChainingHashTablePair* newBegin = new SeparateChainingHashTablePair(key, value);

	// adding newBegin to the ordered sequence
	this->handlePutInSeq(newBegin);

	// adding newBegin to the hash table
	SeparateChainingHashTablePair* temp = (SeparateChainingHashTablePair*)(this->hashTable[index]);
	this->hashTable[index] = newBegin;
	newBegin->next = temp;
}
template <typename keyType, typename valueType, typename hashFunc>
const valueType& SeparateChainingHashTable<keyType, valueType, hashFunc>::get(const keyType& key)
{
	size_t index = this->hasher(key) % this->hashTable.capacity();
	SeparateChainingHashTablePair* iter = (SeparateChainingHashTablePair*)(this->hashTable[index]);

	while (iter)
	{
		if (iter->key == key)
			return iter->value;

		iter = iter->next;
	}

	throw "No such element!";
}
template <typename keyType, typename valueType, typename hashFunc>
void SeparateChainingHashTable<keyType, valueType, hashFunc>::remove(const keyType& key)
{
	size_t index = this->hasher(key) % this->hashTable.capacity();

	SeparateChainingHashTablePair* iter = (SeparateChainingHashTablePair*)(this->hashTable[index]);
	SeparateChainingHashTablePair* prev = nullptr;

	if (!iter)
		throw "No such element!";

	// removing iter from the hash table
	if (iter->key == key)
	{
		SeparateChainingHashTablePair* newBegin = iter->next;
		this->hashTable[index] = newBegin;
	}
	else
	{
		prev = iter;
		iter = iter->next;

		bool found = false;

		while (iter && !found)
		{
			if (iter->key == key)
				found = true;
			else
			{
				iter = iter->next;
				prev = prev->next;
			}
		}
	}

	if (iter == prev)
		throw "No such element!";

	// removing iter from the ordered sequence
	this->handleRemoveInSeq(iter);

	if (prev)
		prev->next = iter->next;

	iter->next = nullptr;
	delete iter;
}

template <typename keyType, typename valueType, typename hashFunc>
void SeparateChainingHashTable<keyType, valueType, hashFunc>::copyFrom(const SeparateChainingHashTable<keyType, valueType, hashFunc>& other)
{
	typename HashTable<keyType, valueType, hashFunc>::Pair* iter = other.first;

	while (iter)
	{
		put(iter->key, iter->value);
		iter = iter->nextInSeq;
	}
}

template <typename keyType, typename valueType, typename hashFunc>
SeparateChainingHashTable<keyType, valueType, hashFunc>::SeparateChainingHashTable()
{
	this->first = this->last = nullptr;
}
template <typename keyType, typename valueType, typename hashFunc>
SeparateChainingHashTable<keyType, valueType, hashFunc>::SeparateChainingHashTable(const SeparateChainingHashTable<keyType, valueType, hashFunc>& other)
{
	copyFrom(other);
}
template <typename keyType, typename valueType, typename hashFunc>
const SeparateChainingHashTable<keyType, valueType, hashFunc>& SeparateChainingHashTable<keyType, valueType, hashFunc>::operator= (const SeparateChainingHashTable<keyType, valueType, hashFunc>& other)
{
	if (this != &other)
	{
		this->free();
		copyFrom(other);
	}

	return *this;
}