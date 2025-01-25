#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <list>

template <typename Key, typename T, typename Hasher = std::hash<Key>>
class UnorderedMap
{
private:
    std::list<std::pair<Key, T>> data;
    std::vector<std::pair<typename std::list<std::pair<Key, T>>::iterator, size_t>> hashTable;
    size_t elementCount = 0;
    double loadFactorThreshold = 0.75;
    Hasher hasher;

    typename std::list<std::pair<Key, T>>::iterator getElementByChain(size_t chainIndex, const Key& key);
    typename std::list<std::pair<Key, T>>::const_iterator getElementByChain(size_t chainIndex, const Key& key) const;
    void rehash(size_t newSize);

public:
    class ConstUnorderedMapIterator
    {
        friend class UnorderedMap;

    private:
        typename std::list<std::pair<Key, T>>::const_iterator currElement;

        ConstUnorderedMapIterator(typename std::list<std::pair<Key, T>>::const_iterator it)
            : currElement(it)
        {
        }

    public:
        ConstUnorderedMapIterator() {}

        ConstUnorderedMapIterator& operator++()
        {
            ++currElement;
            return *this;
        }

        ConstUnorderedMapIterator operator++(int)
        {
            ConstUnorderedMapIterator temp = *this;
            ++(*this);
            return temp;
        }

        const std::pair<Key, T>& operator*() const
        {
            return *currElement;
        }

        const std::pair<Key, T>* operator->() const
        {
            return &(*currElement);
        }

        bool operator==(const ConstUnorderedMapIterator& other) const
        {
            return currElement == other.currElement;
        }

        bool operator!=(const ConstUnorderedMapIterator& other) const
        {
            return currElement != other.currElement;
        }
    };

    explicit UnorderedMap(size_t initHashSize = 16);

    std::pair<bool, ConstUnorderedMapIterator> insert(const Key& key, const T& value);
    ConstUnorderedMapIterator find(const Key& key) const;
    bool remove(const Key& key);
    bool remove(const ConstUnorderedMapIterator& iter);
    void clear();
    bool empty() const;
    size_t size() const
    {
        return elementCount;
    }

    ConstUnorderedMapIterator cbegin() const
    {
        return ConstUnorderedMapIterator(data.cbegin());
    }

    ConstUnorderedMapIterator cend() const
    {
        return ConstUnorderedMapIterator(data.cend());
    }
};

template <typename Key, typename T, typename Hasher>
UnorderedMap<Key, T, Hasher>::UnorderedMap(size_t initHashSize)
    : hashTable(initHashSize, std::make_pair(data.end(), 0))
{
}

template <typename Key, typename T, typename Hasher>
typename std::list<std::pair<Key, T>>::iterator UnorderedMap<Key, T, Hasher>::getElementByChain(size_t chainIndex, const Key& key)
{
    size_t chainSize = hashTable[chainIndex].second;
    if (chainSize == 0) return data.end();

    auto currIt = hashTable[chainIndex].first;
    for (size_t i = 0; i < chainSize; i++)
    {
        if (currIt->first == key) return currIt;
        ++currIt;
    }
    return data.end();
}

template <typename Key, typename T, typename Hasher>
typename std::list<std::pair<Key, T>>::const_iterator UnorderedMap<Key, T, Hasher>::getElementByChain(size_t chainIndex, const Key& key) const
{
    size_t chainSize = hashTable[chainIndex].second;
    if (chainSize == 0) return data.cend();

    auto currIt = hashTable[chainIndex].first;
    for (size_t i = 0; i < chainSize; i++)
    {
        if (currIt->first == key) return currIt;
        ++currIt;
    }
    return data.cend();
}

template <typename Key, typename T, typename Hasher>
std::pair<bool, typename UnorderedMap<Key, T, Hasher>::ConstUnorderedMapIterator> UnorderedMap<Key, T, Hasher>::insert(const Key& key, const T& value)
{
    if (hashTable.empty()) hashTable.resize(16, std::make_pair(data.end(), 0));

    size_t bucketIndex = hasher(key) % hashTable.size();
    auto foundIt = getElementByChain(bucketIndex, key);
    if (foundIt != data.end()) return std::make_pair(false, ConstUnorderedMapIterator(foundIt));

    auto& chainInfo = hashTable[bucketIndex];
    if (chainInfo.second == 0)
    {
        data.push_front(std::make_pair(key, value));
        chainInfo.first = data.begin();
    }
    else
    {
        auto newIt = data.insert(chainInfo.first, std::make_pair(key, value));
        chainInfo.first = newIt;
    }
    chainInfo.second++;
    elementCount++;

    double currentLoadFactor = static_cast<double>(elementCount) / hashTable.size();
    if (currentLoadFactor > loadFactorThreshold)
    {
        rehash(hashTable.size() * 2);
        size_t newBucketIndex = hasher(key) % hashTable.size();
        auto newPos = getElementByChain(newBucketIndex, key);
        return std::make_pair(true, ConstUnorderedMapIterator(newPos));
    }
    return std::make_pair(true, ConstUnorderedMapIterator(chainInfo.first));
}

template <typename Key, typename T, typename Hasher>
typename UnorderedMap<Key, T, Hasher>::ConstUnorderedMapIterator UnorderedMap<Key, T, Hasher>::find(const Key& key) const
{
    if (hashTable.empty()) return cend();

    size_t bucketIndex = hasher(key) % hashTable.size();
    auto foundIt = getElementByChain(bucketIndex, key);
    if (foundIt == data.end()) return cend();

    return ConstUnorderedMapIterator(foundIt);
}

template <typename Key, typename T, typename Hasher>
bool UnorderedMap<Key, T, Hasher>::remove(const Key& key)
{
    if (hashTable.empty()) return false;

    size_t bucketIndex = hasher(key) % hashTable.size();
    auto foundIt = getElementByChain(bucketIndex, key);
    if (foundIt == data.end()) return false;

    auto& chainInfo = hashTable[bucketIndex];
    if (foundIt == chainInfo.first)
    {
        auto nextIt = foundIt;
        ++nextIt;
        chainInfo.first = nextIt;
    }

    data.erase(foundIt);
    chainInfo.second--;
    elementCount--;
    return true;
}

template <typename Key, typename T, typename Hasher>
bool UnorderedMap<Key, T, Hasher>::remove(const ConstUnorderedMapIterator& iter)
{
    if (iter == cend() || hashTable.empty()) return false;

    const Key& key = iter.currElement->first;
    return remove(key);
}

template <typename Key, typename T, typename Hasher>
void UnorderedMap<Key, T, Hasher>::clear()
{
    data.clear();
    hashTable.clear();
    elementCount = 0;
}

template <typename Key, typename T, typename Hasher>
bool UnorderedMap<Key, T, Hasher>::empty() const
{
    return elementCount == 0;
}

template <typename Key, typename T, typename Hasher>
void UnorderedMap<Key, T, Hasher>::rehash(size_t newSize)
{
    std::vector<std::pair<Key, T>> oldElements;
    oldElements.reserve(elementCount);

    for (auto it = data.begin(); it != data.end(); ++it)
    {
        oldElements.push_back(*it);
    }

    data.clear();
    hashTable.clear();
    hashTable.resize(newSize, std::make_pair(data.end(), 0));
    elementCount = 0;

    for (auto& elem : oldElements)
    {
        insert(elem.first, elem.second);
    }
}
