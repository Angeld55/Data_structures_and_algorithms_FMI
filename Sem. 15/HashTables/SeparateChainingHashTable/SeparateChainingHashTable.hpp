#pragma once
#include "../HashTable.hpp"

template<typename KeyType, typename ValueType, typename HashFunc = std::hash<KeyType>>
class SeparateChainingHashTable : public HashTable<KeyType, ValueType, HashFunc>
{

	void free();
	void copyFrom(const SeparateChainingHashTable& other);

	struct SepChaingHashPair : public Pair 
	{
		SepChaingHashPair(const KeyType& key, const ValueType& value) : Pair(key, value){}
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

template<typename KeyType, typename ValueType, typename HashFunc = std::hash<KeyType>>
SeparateChainingHashTable<KeyType, ValueType, HashFunc>::SeparateChainingHashTable(const SeparateChainingHashTable& other)
{
	copyFrom(other);
}


template<typename KeyType, typename ValueType, typename HashFunc = std::hash<KeyType>>

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

template<typename KeyType, typename ValueType, typename HashFunc = std::hash<KeyType>>
SeparateChainingHashTable<KeyType, ValueType, HashFunc>::~SeparateChainingHashTable()
{
	free();
}

template<typename KeyType, typename ValueType, typename HashFunc = std::hash<KeyType>>
void SeparateChainingHashTable<KeyType, ValueType, HashFunc>::put(KeyType key, ValueType value)
{
	size_t index = hasher(key) % capacity;
	SepChaingHashPair* newBox = new SepChaingHashPair(key, value);

	SepChaingHashPair* temp = (SepChaingHashPair*)data[index];
	data[index] = newBox;
	newBox->next = temp;
}

template<typename KeyType, typename ValueType, typename HashFunc = std::hash<KeyType>>
const ValueType& SeparateChainingHashTable<KeyType, ValueType, HashFunc>::get(KeyType key)
{
	size_t index = hasher(key) % capacity;

	SepChaingHashPair* iter = (SepChaingHashPair*)data[index];

	while (iter != nullptr)
	{
		if (iter->key == key)
			return iter->value;
		iter = iter->next;
	}
	throw "No such element!";

}

template<typename KeyType, typename ValueType, typename HashFunc = std::hash<KeyType>>
bool SeparateChainingHashTable<KeyType, ValueType, HashFunc>::remove(KeyType key)
{
	size_t index = hasher(key) % capacity;

	SepChaingHashPair* iter = (SepChaingHashPair*)data[index];
	
	if (iter == nullptr)
		return false;
	if (iter->key == key)
	{
		SepChaingHashPair* newBegin = iter->next;
		delete iter;
		data[index] = newBegin;
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
template<typename KeyType, typename ValueType, typename HashFunc = std::hash<KeyType>>
void SeparateChainingHashTable<KeyType, ValueType, HashFunc>::free()
{
	for (int i = 0; i < data.size(); i++)
	{
		SepChaingHashPair* iter = (SepChaingHashPair*)data[i];

		while (iter != nullptr)
		{
			SepChaingHashPair* next = iter->next;
			delete iter;
			iter = next;
		}
		data[i] = nullptr;
	}
}

template<typename KeyType, typename ValueType, typename HashFunc = std::hash<KeyType>>
void SeparateChainingHashTable<KeyType, ValueType, HashFunc>::copyFrom(const SeparateChainingHashTable& other)
{
	for (int i = 0; i < other.data.size(); i++)
	{
		SepChaingHashPair* otherIter = (SepChaingHashPair*)other.data[i]; 
		if (otherIter == nullptr)
			continue;
		
		data[i] = new SepChaingHashPair(*otherIter);
		SepChaingHashPair* currentIter = (SepChaingHashPair*)data[i];
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