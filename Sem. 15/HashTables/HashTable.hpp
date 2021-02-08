#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include "Iterator/Iterator.hpp"

using namespace std;

template <typename keyType, typename valueType, typename hashFunc = hash<keyType>>
class HashTable
{
protected:
	void free();

	struct Pair
	{
		keyType key;
		valueType value;

		Pair* prevInSeq;
		Pair* nextInSeq;

		Pair(const keyType& key, const valueType& value) : key(key), value(value)
		{
			prevInSeq = nullptr;
			nextInSeq = nullptr;
		}
		virtual ~Pair() {}
	};

	hashFunc hasher;
	vector<Pair*> hashTable;

	Pair* first;
	Pair* last;

private:
	void addElInTable(const keyType& key, const valueType& value,
		size_t index = 0, Pair* newBox = nullptr, size_t jump = 0, bool calledFromLinearProb = false);

public:
	virtual void put(const keyType& key, const valueType& value) = 0;
	virtual const valueType& get(const keyType& key) = 0;
	virtual void remove(const keyType& key) = 0;

	HashTable();
	virtual ~HashTable();

	void addElInTableAndSeq(const keyType& key, const valueType& value, size_t jump = 0, bool calledFromLinearProb = false);
	void resize();

	void handlePutInSeq(Pair* newBox);
	void handleRemoveInSeq(Pair* iter);

	class HashTableIterator : public Iterator<keyType, valueType>
	{
	private:
		Pair* box;

	public:
		HashTableIterator(Pair* box) : box(box) {}

		Pair operator*()
		{
			return *box;
		}
		void operator++()
		{
			if (box)
				box = box->nextInSeq;
		}
		void operator--()
		{
			if (box)
				box = box->prevInSeq;
		}
		bool operator!=(const Iterator<keyType, valueType>& other)
		{
			HashTableIterator* it2 = (HashTableIterator*)&other;
			return box != it2->box;
		}
	};

	HashTableIterator begin()
	{
		return HashTableIterator(this->first);
	}
	HashTableIterator end()
	{
		return HashTableIterator(nullptr);
	}
};

// functions used from LinearProbing and DoubleHashing
template <typename keyType, typename valueType, typename hashFunc>
void HashTable<keyType, valueType, hashFunc>::addElInTable(const keyType& key, const valueType& value,
	size_t index, Pair* newBox, size_t jump, bool calledFromLinearProb)
{
	int i = 1;
	while (hashTable[index])
	{
		if (calledFromLinearProb)
			(index += jump) %= hashTable.capacity();
		else
		{
			if (hash<size_t>{}(index) % hashTable.capacity())
				(index += (i * hash<size_t>{}(index))) %= hashTable.capacity();
			else
				(index += (i * (hash<size_t>{}(index)+1))) %= hashTable.capacity();
			i++;
		}
	}
	hashTable[index] = newBox;
}
template <typename keyType, typename valueType, typename hashFunc>
void HashTable<keyType, valueType, hashFunc>::addElInTableAndSeq(const keyType& key, const valueType& value, size_t jump, bool calledFromLinearProb)
{
	size_t index = hasher(key) % hashTable.capacity();
	Pair* newBox = new Pair(key, value);

	// adding newBox to the ordered sequence
	handlePutInSeq(newBox);

	// adding newBox to the hash table
	addElInTable(key, value, index, newBox, jump, calledFromLinearProb);
}
template <typename keyType, typename valueType, typename hashFunc>
void HashTable<keyType, valueType, hashFunc>::resize()
{
	vector<Pair*> resized(hashTable.capacity() * 2, nullptr);
	vector<Pair*> temp = hashTable;

	hashTable = resized;

	for (int i = 0; i < temp.size(); i++)
	{
		if (temp[i])
		{
			size_t index = hasher(temp[i]->key) % hashTable.capacity();
			addElInTable(temp[i]->key, temp[i]->value, index, temp[i]);
		}
	}
}
// 
// functions used to handle the order of the elements in the hash.
template <typename keyType, typename valueType, typename hashFunc>
void HashTable<keyType, valueType, hashFunc>::handlePutInSeq(Pair* newBox)
{
	if (!first) // no elements in the seq
		first = last = newBox;

	else // elements in seq
	{
		last->nextInSeq = newBox;
		newBox->prevInSeq = last;
		last = newBox;
	}
}
template <typename keyType, typename valueType, typename hashFunc>
void HashTable<keyType, valueType, hashFunc>::handleRemoveInSeq(Pair* iter)
{
	if (!iter->prevInSeq) // searched value is first in seq
	{
		first = iter->nextInSeq;

		if (!first)
			last = nullptr;
		else
			first->prevInSeq = nullptr;
	}
	else // searched value is not first
	{
		iter->prevInSeq->nextInSeq = iter->nextInSeq;

		if (iter->nextInSeq)
			iter->nextInSeq->prevInSeq = iter->prevInSeq;
		else
			last = iter->prevInSeq;
	}
}
//
template <typename keyType, typename valueType, typename hashFunc>
void HashTable<keyType, valueType, hashFunc>::free()
{
	for (int i = 0; i < hashTable.size(); i++)
	{
		if (hashTable[i])
			delete hashTable[i];
	}
}

template <typename keyType, typename valueType, typename hashFunc>
HashTable<keyType, valueType, hashFunc>::HashTable() : hashTable(1, nullptr), first(nullptr), last(nullptr) {}
template <typename keyType, typename valueType, typename hashFunc>
HashTable<keyType, valueType, hashFunc>::~HashTable()
{
	free();
}