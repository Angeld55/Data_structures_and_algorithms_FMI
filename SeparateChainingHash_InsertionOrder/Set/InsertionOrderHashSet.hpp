#pragma once

#include <list>
#include <vector>
#include <forward_list>
#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <functional>

template <typename Key, typename Hash = std::hash<Key>>
class InsertionOrderHashSet
{
public:
    class ConstIterator
    {
    public:
        const Key& operator*() const;
        ConstIterator& operator++();
        ConstIterator operator++(int);
        const Key* operator->() const;
        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;

    private:
        typename std::list<Key>::const_iterator currElement;
        ConstIterator(typename std::list<Key>::const_iterator curr);
        friend class InsertionOrderHashSet;
    };

    InsertionOrderHashSet();

    void add(const Key& key);
    void remove(const Key& key);
    ConstIterator find(const Key& key) const;
    ConstIterator cbegin() const;
    ConstIterator cend() const;

private:
    std::list<Key> data;
    std::vector<std::forward_list<typename std::list<Key>::iterator>> hashTable;
    double maxLoadFactor = 0.75;
    Hash getHash;

    void resize();
    size_t getHashCode(const Key& key) const;
    double loadFactor() const;
};


template <typename Key, typename Hash>
InsertionOrderHashSet<Key, Hash>::ConstIterator::ConstIterator(
    typename std::list<Key>::const_iterator curr)
    : currElement(curr) {}

template <typename Key, typename Hash>
const Key& InsertionOrderHashSet<Key, Hash>::ConstIterator::operator*() const
{
    return *currElement;
}

template <typename Key, typename Hash>
typename InsertionOrderHashSet<Key, Hash>::ConstIterator&
InsertionOrderHashSet<Key, Hash>::ConstIterator::operator++()
{
    ++currElement;
    return *this;
}

template <typename Key, typename Hash>
typename InsertionOrderHashSet<Key, Hash>::ConstIterator
InsertionOrderHashSet<Key, Hash>::ConstIterator::operator++(int)
{
    ConstIterator temp = *this;
    ++(*this);
    return temp;
}

template <typename Key, typename Hash>
const Key* InsertionOrderHashSet<Key, Hash>::ConstIterator::operator->() const
{
    return &(*currElement);
}

template <typename Key, typename Hash>
bool InsertionOrderHashSet<Key, Hash>::ConstIterator::operator==(const ConstIterator& other) const
{
    return currElement == other.currElement;
}

template <typename Key, typename Hash>
bool InsertionOrderHashSet<Key, Hash>::ConstIterator::operator!=(const ConstIterator& other) const
{
    return currElement != other.currElement;
}

template <typename Key, typename Hash>
InsertionOrderHashSet<Key, Hash>::InsertionOrderHashSet()
{
    hashTable.resize(8); // initial number of buckets
}

template <typename Key, typename Hash>
void InsertionOrderHashSet<Key, Hash>::add(const Key& key)
{
    if (loadFactor() >= maxLoadFactor)
    {
        resize();
    }

    size_t hashCode = getHashCode(key);
    auto& bucket = hashTable[hashCode];

    auto it = std::find_if(bucket.begin(), bucket.end(),
        [&key](auto listIt) { return *listIt == key; });
    if (it != bucket.end()) {
        return;
    }

    data.push_back(key);
    auto insertedIt = --data.end();
    bucket.push_front(insertedIt);
}

template <typename Key, typename Hash>
void InsertionOrderHashSet<Key, Hash>::remove(const Key& key)
{
    size_t hashCode = getHashCode(key);
    auto& bucket = hashTable[hashCode];

    bucket.remove_if([this, &key](const auto& listIt) {
        if (*listIt == key)
        {
            data.erase(listIt);
            return true;
        }
        return false;
        });
}

template <typename Key, typename Hash>
typename InsertionOrderHashSet<Key, Hash>::ConstIterator
InsertionOrderHashSet<Key, Hash>::find(const Key& key) const
{
    size_t hashCode = getHashCode(key);
    const auto& bucket = hashTable[hashCode];

    auto it = std::find_if(bucket.begin(), bucket.end(),
        [&key](auto listIt) { return *listIt == key; });
    if (it == bucket.end()) {
        return cend();
    }
    return ConstIterator(*it);
}

template <typename Key, typename Hash>
typename InsertionOrderHashSet<Key, Hash>::ConstIterator
InsertionOrderHashSet<Key, Hash>::cbegin() const
{
    return ConstIterator(data.cbegin());
}

template <typename Key, typename Hash>
typename InsertionOrderHashSet<Key, Hash>::ConstIterator
InsertionOrderHashSet<Key, Hash>::cend() const
{
    return ConstIterator(data.cend());
}

template <typename Key, typename Hash>
double InsertionOrderHashSet<Key, Hash>::loadFactor() const
{
    return static_cast<double>(data.size()) / hashTable.size();
}

template <typename Key, typename Hash>
void InsertionOrderHashSet<Key, Hash>::resize()
{
    size_t newSize = hashTable.size() * 2;
    std::vector<std::forward_list<typename std::list<Key>::iterator>> newHashTable(newSize);

    for (auto it = data.begin(); it != data.end(); ++it)
    {
        size_t newHashCode = getHash(*it) % newSize;
        newHashTable[newHashCode].push_front(it);
    }

    hashTable = std::move(newHashTable);
}

template <typename Key, typename Hash>
size_t InsertionOrderHashSet<Key, Hash>::getHashCode(const Key& key) const
{
    return getHash(key) % hashTable.size();
}
