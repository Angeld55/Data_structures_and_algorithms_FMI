#pragma once

#include <list>
#include <vector>
#include <forward_list>
#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <functional>

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class InsertionOrderHashMap
{
public:
    using Element = std::pair<Key, Value>;

    class ConstIterator 
    {
    public:
        const Element& operator*() const;
        ConstIterator& operator++();
        ConstIterator operator++(int);
        const Element* operator->() const;
        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;

    private:
        typename std::list<Element>::const_iterator currElement;
        ConstIterator(typename std::list<Element>::const_iterator curr);
        friend class InsertionOrderHashMap;
    };

    InsertionOrderHashMap();
    void add(const Key& key, const Value& value);
    void remove(const Key& key);
    ConstIterator find(const Key& key) const;
    ConstIterator cbegin() const;
    ConstIterator cend() const;
    double loadFactor() const;

private:
    std::list<Element> data;
    std::vector<std::forward_list<typename std::list<Element>::iterator>> hashTable;
    double maxLoadFactor = 0.75;
    Hash getHash;

    void resize();
    size_t getHashCode(const Key& key) const;
};


// Constructor
template <typename Key, typename Value, typename Hash>
InsertionOrderHashMap<Key, Value, Hash>::InsertionOrderHashMap()
{
    hashTable.resize(8);
}

// ConstIterator Implementation
template <typename Key, typename Value, typename Hash>
InsertionOrderHashMap<Key, Value, Hash>::ConstIterator::ConstIterator(typename std::list<Element>::const_iterator curr)
    : currElement(curr) {}

template <typename Key, typename Value, typename Hash>
const typename InsertionOrderHashMap<Key, Value, Hash>::Element&
InsertionOrderHashMap<Key, Value, Hash>::ConstIterator::operator*() const
{
    return *currElement;
}

template <typename Key, typename Value, typename Hash>
typename InsertionOrderHashMap<Key, Value, Hash>::ConstIterator&
InsertionOrderHashMap<Key, Value, Hash>::ConstIterator::operator++()
{
    ++currElement;
    return *this;
}

template <typename Key, typename Value, typename Hash>
typename InsertionOrderHashMap<Key, Value, Hash>::ConstIterator
InsertionOrderHashMap<Key, Value, Hash>::ConstIterator::operator++(int)
{
    ConstIterator temp = *this;
    ++(*this);
    return temp;
}

template <typename Key, typename Value, typename Hash>
const typename InsertionOrderHashMap<Key, Value, Hash>::Element*
InsertionOrderHashMap<Key, Value, Hash>::ConstIterator::operator->() const {
    return &(*currElement);
}

template <typename Key, typename Value, typename Hash>
bool InsertionOrderHashMap<Key, Value, Hash>::ConstIterator::operator==(const ConstIterator& other) const
{
    return currElement == other.currElement;
}

template <typename Key, typename Value, typename Hash>
bool InsertionOrderHashMap<Key, Value, Hash>::ConstIterator::operator!=(const ConstIterator& other) const
{
    return currElement != other.currElement;
}

// Public methods
template <typename Key, typename Value, typename Hash>
void InsertionOrderHashMap<Key, Value, Hash>::add(const Key& key, const Value& value)
{
    if (loadFactor() >= maxLoadFactor) {
        resize();
    }

    size_t hashCode = getHashCode(key);
    auto& bucket = hashTable[hashCode];
    auto iter = std::find_if(bucket.begin(), bucket.end(), [&key](const auto& it) {
        return it->first == key;
        });

    if (iter != bucket.end()) return;

    data.emplace_back(key, value);
    bucket.push_front(--data.end());
}

template <typename Key, typename Value, typename Hash>
void InsertionOrderHashMap<Key, Value, Hash>::remove(const Key& key)
{
    size_t hashCode = getHashCode(key);
    auto& bucket = hashTable[hashCode];
    bucket.remove_if([this, &key](const auto& it) {
        if (it->first == key) {
            data.erase(it);
            return true;
        }
        return false;
        });
}

template <typename Key, typename Value, typename Hash>
typename InsertionOrderHashMap<Key, Value, Hash>::ConstIterator
InsertionOrderHashMap<Key, Value, Hash>::find(const Key& key) const
{
    size_t hashCode = getHashCode(key);
    const auto& bucket = hashTable[hashCode];
    auto iter = std::find_if(bucket.begin(), bucket.end(), [&key](const auto& it) {
        return it->first == key;
        });

    if (iter == bucket.end()) return cend();
    return ConstIterator(*iter);
}

template <typename Key, typename Value, typename Hash>
typename InsertionOrderHashMap<Key, Value, Hash>::ConstIterator
InsertionOrderHashMap<Key, Value, Hash>::cbegin() const
{
    return ConstIterator(data.cbegin());
}

template <typename Key, typename Value, typename Hash>
typename InsertionOrderHashMap<Key, Value, Hash>::ConstIterator
InsertionOrderHashMap<Key, Value, Hash>::cend() const
{
    return ConstIterator(data.cend());
}

template <typename Key, typename Value, typename Hash>
double InsertionOrderHashMap<Key, Value, Hash>::loadFactor() const
{
    return static_cast<double>(data.size()) / hashTable.size();
}


template <typename Key, typename Value, typename Hash>
void InsertionOrderHashMap<Key, Value, Hash>::resize()
{
    size_t newSize = hashTable.size() * 2;
    std::vector<std::forward_list<typename std::list<Element>::iterator>> newHashTable(newSize);

    for (auto it = data.begin(); it != data.end(); ++it) {
        size_t newHashCode = getHashCode(it->first) % newSize;
        newHashTable[newHashCode].push_front(it);
    }

    hashTable = std::move(newHashTable);
}


template <typename Key, typename Value, typename Hash>
size_t InsertionOrderHashMap<Key, Value, Hash>::getHashCode(const Key& key) const
{
    return getHash(key) % hashTable.size();
}
