#pragma once
#include "../HashTable.hpp"

template<class KeyType, class ValueType, class HashFunc = std::hash<KeyType>>
class SeparateChainingHashTable : public HashTable<KeyType, ValueType, HashFunc>
{

	void free();
	void copyFrom(const SeparateChainingHashTable& other);

	struct SepChaingHashPair : public HashTable<KeyType, ValueType, HashFunc>::Pair
	{
		SepChaingHashPair(const KeyType& key, const ValueType& value) : HashTable<KeyType, ValueType, HashFunc>::Pair(key, value){}
		SepChaingHashPair* next = nullptr;
	};

public:
	SeparateChainingHashTable() = default;
	SeparateChainingHashTable(const SeparateChainingHashTable& other);
	const SeparateChainingHashTable& operator=(const SeparateChainingHashTable& other);
	~SeparateChainingHashTable();

	void put(KeyType key, ValueType value);
	const ValueType& get(KeyType key);
	bool remove(KeyType key);

};

template<class KeyType, class ValueType, class HashFunc>
SeparateChainingHashTable<KeyType, ValueType, HashFunc>::SeparateChainingHashTable(const SeparateChainingHashTable& other)
{
	copyFrom(other);
}


template<class KeyType, class ValueType, class HashFunc>
const SeparateChainingHashTable<KeyType, ValueType, HashFunc>& SeparateChainingHashTable<KeyType, ValueType, HashFunc>::operator=(const SeparateChainingHashTable<KeyType, ValueType, HashFunc>& other)
{
	if (this != &other)
	{
		//HashTable<KeyType, ValueType, HashFunc>::operator=(other);
		free();
		copyFrom(other);
	}
	return *this;
}

template<class KeyType, class ValueType, class HashFunc>
SeparateChainingHashTable<KeyType, ValueType, HashFunc>::~SeparateChainingHashTable()
{
	free();
}

template<class KeyType, class ValueType, class HashFunc>
void SeparateChainingHashTable<KeyType, ValueType, HashFunc>::put(KeyType key, ValueType value)
{
	size_t index = this->hasher(key) % this->capacity;
	SepChaingHashPair* newBox = new SepChaingHashPair(key, value);

	SepChaingHashPair* temp = (SepChaingHashPair*)(this->data[index]);
	this->data[index] = newBox;
	newBox->next = temp;
}

template<class KeyType, class ValueType, class HashFunc>
const ValueType& SeparateChainingHashTable<KeyType, ValueType, HashFunc>::get(KeyType key)
{
	size_t index = this->hasher(key) % this->capacity;

	SepChaingHashPair* iter = (SepChaingHashPair*)(this->data[index]);

	while (iter != nullptr)
	{
		if (iter->key == key)
			return iter->value;
		iter = iter->next;
	}
	throw "No such element!";

}

template<class KeyType, class ValueType, class HashFunc>
bool SeparateChainingHashTable<KeyType, ValueType, HashFunc>::remove(KeyType key)
{
	size_t index = this->hasher(key) % this->capacity;

	SepChaingHashPair* iter = (SepChaingHashPair*)(this->data[index]);
	
	if (iter == nullptr)
		return false;
	if (iter->key == key)
	{
		SepChaingHashPair* newBegin = iter->next;
		delete iter;
		this->data[index] = newBegin;
		return true;
	}


	SepChaingHashPair* prev = iter;
	iter = iter->next;

	while (iter != nullptr)
	{
		if (iter->key == key)
		{
			prev->next = iter->next;
			delete iter;
			return true;
		}
		iter = iter->next;
		prev = prev->next;
	}
	return false;
}
template<class KeyType, class ValueType, class HashFunc>
void SeparateChainingHashTable<KeyType, ValueType, HashFunc>::free()
{
	for (int i = 0; i < this->data.size(); i++)
	{
		SepChaingHashPair* iter = (SepChaingHashPair*)this->data[i];

		while (iter != nullptr)
		{
			SepChaingHashPair* next = iter->next;
			delete iter;
			iter = next;
		}
		this->data[i] = nullptr;
	}
}

template<class KeyType, class ValueType, class HashFunc>
void SeparateChainingHashTable<KeyType, ValueType, HashFunc>::copyFrom(const SeparateChainingHashTable& other)
{
	for (int i = 0; i < other.data.size(); i++)
	{
		SepChaingHashPair* otherIter = (SepChaingHashPair*)other.data[i]; 
		if (otherIter == nullptr)
			continue;
		
		this->data[i] = new SepChaingHashPair(*otherIter);
		SepChaingHashPair* currentIter = (SepChaingHashPair*)this->data[i];
		otherIter = otherIter->next;
	
		while (otherIter != nullptr)
		{
			currentIter->next = new SepChaingHashPair(*otherIter);
			otherIter = otherIter->next;
			currentIter = currentIter->next;
		} 
		currentIter->next = nullptr;
	}
}