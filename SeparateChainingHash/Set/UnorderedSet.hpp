#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>

template <typename Key, typename Hasher = std::hash<Key>>
class UnorderedSet
{
private:
    std::list<Key> data;
    std::vector<std::pair<typename std::list<Key>::iterator, size_t>> hashTable;

    size_t elementCount = 0;
    double loadFactorThreshold = 0.75;
    Hasher hasher;

    typename std::list<Key>::iterator getElementByChain(size_t chainIndex, const Key& element);
    typename std::list<Key>::const_iterator getElementByChain(size_t chainIndex, const Key& element) const;
    void rehash(size_t newSize);

public:
    class ConstUnorderedSetIterator
    {
        friend class UnorderedSet;

    private:
        typename std::list<Key>::const_iterator currElement;

        ConstUnorderedSetIterator(typename std::list<Key>::const_iterator it)
            : currElement(it) {
        }

    public:
        ConstUnorderedSetIterator() {}

        ConstUnorderedSetIterator& operator++()
        {
            ++currElement;
            return *this;
        }

        ConstUnorderedSetIterator operator++(int)
        {
            ConstUnorderedSetIterator temp = *this;
            ++(*this);
            return temp;
        }

        const Key& operator*() const
        {
            return *currElement;
        }

        const Key* operator->() const
        {
            return &(*currElement);
        }

        bool operator==(const ConstUnorderedSetIterator& other) const
        {
            return currElement == other.currElement;
        }

        bool operator!=(const ConstUnorderedSetIterator& other) const
        {
            return currElement != other.currElement;
        }
    };

    explicit UnorderedSet(size_t initHashSize = 16);

    std::pair<bool, ConstUnorderedSetIterator> insert(const Key& element);
    ConstUnorderedSetIterator find(const Key& element) const;
    bool remove(const Key& element);
    bool remove(const ConstUnorderedSetIterator& iter);
    void clear();
    bool empty() const;
    size_t size() const
    {
        return elementCount;
    }
    ConstUnorderedSetIterator cbegin() const
    {
        return ConstUnorderedSetIterator(data.cbegin());
    }
    ConstUnorderedSetIterator cend() const
    {
        return ConstUnorderedSetIterator(data.cend());
    }
};

template <typename Key, typename Hasher>
UnorderedSet<Key, Hasher>::UnorderedSet(size_t initHashSize)
    : hashTable(initHashSize, std::make_pair(data.end(), 0))
{
}

//code duplicate!! (should be fixed)
template <typename Key, typename Hasher>
typename std::list<Key>::iterator UnorderedSet<Key, Hasher>::getElementByChain(size_t chainIndex, const Key& element)
{
    size_t chainSize = hashTable[chainIndex].second;
    if (chainSize == 0)
    {
        return data.end();
    }
    typename std::list<Key>::iterator currIt = hashTable[chainIndex].first;
    for (size_t i = 0; i < chainSize; i++)
    {
        if (*currIt == element)
        {
            return currIt;
        }
        ++currIt;
    }
    return data.end();
}

template <typename Key, typename Hasher>
typename std::list<Key>::const_iterator UnorderedSet<Key, Hasher>::getElementByChain(size_t chainIndex, const Key& element) const
{
    size_t chainSize = hashTable[chainIndex].second;
    if (chainSize == 0)
    {
        return data.cend();
    }
    typename std::list<Key>::const_iterator currIt = hashTable[chainIndex].first;
    for (size_t i = 0; i < chainSize; i++)
    {
        if (*currIt == element)
        {
            return currIt;
        }
        ++currIt;
    }
    return data.cend();
}

template <typename Key, typename Hasher>
std::pair<bool, typename UnorderedSet<Key, Hasher>::ConstUnorderedSetIterator> UnorderedSet<Key, Hasher>::insert(const Key& element)
{
    if (hashTable.empty())
    {
        hashTable.resize(16, std::make_pair(data.end(), 0));
    }

    size_t bucketIndex = hasher(element) % hashTable.size();
    typename std::list<Key>::iterator foundIt = getElementByChain(bucketIndex, element);
    if (foundIt != data.end())
    {
        return std::make_pair(false, ConstUnorderedSetIterator(foundIt));
    }
    std::pair<typename std::list<Key>::iterator, size_t>& chainInfo = hashTable[bucketIndex];
    if (chainInfo.second == 0)
    {
        data.push_front(element);
        chainInfo.first = data.begin();
    }
    else
    {
        typename std::list<Key>::iterator newIt = data.insert(chainInfo.first, element);
        chainInfo.first = newIt;
    }
    chainInfo.second++;
    elementCount++;


    double currentLoadFactor = static_cast<double>(elementCount) / hashTable.size();
    if (currentLoadFactor > loadFactorThreshold)
    {
        rehash(hashTable.size() * 2);
        size_t newBucketIndex = hasher(element) % hashTable.size();
        typename std::list<Key>::iterator newPos = getElementByChain(newBucketIndex, element);
        return std::make_pair(true, ConstUnorderedSetIterator(newPos));
    }

    return std::make_pair(true, ConstUnorderedSetIterator(chainInfo.first));
}

template <typename Key, typename Hasher>
typename UnorderedSet<Key, Hasher>::ConstUnorderedSetIterator UnorderedSet<Key, Hasher>::find(const Key& element) const
{
    if (hashTable.empty())
    {
        return cend();
    }
    size_t bucketIndex = hasher(element) % hashTable.size();
    typename std::list<Key>::const_iterator foundIt = getElementByChain(bucketIndex, element);
    if (foundIt == data.end())
    {
        return cend();
    }
    return ConstUnorderedSetIterator(foundIt);
}

template <typename Key, typename Hasher>
bool UnorderedSet<Key, Hasher>::remove(const Key& element)
{
    if (hashTable.empty())
    {
        return false;
    }
    size_t bucketIndex = hasher(element) % hashTable.size();
    typename std::list<Key>::iterator foundIt = getElementByChain(bucketIndex, element);
    if (foundIt == data.end())
    {
        return false;
    }

    std::pair<typename std::list<Key>::iterator, size_t>& chainInfo = hashTable[bucketIndex];
    if (foundIt == chainInfo.first)
    {
        typename std::list<Key>::iterator nextIt = foundIt;
        ++nextIt;
        chainInfo.first = nextIt;
    }

    data.erase(foundIt);
    chainInfo.second--;
    elementCount--;
    return true;
}

template <typename Key, typename Hasher>
bool UnorderedSet<Key, Hasher>::remove(const ConstUnorderedSetIterator& iter)
{
    if (iter == cend() || hashTable.empty())
    {
        return false;
    }
    const Key& element = *iter;
    return remove(element);
}

template <typename Key, typename Hasher>
void UnorderedSet<Key, Hasher>::clear()
{
    data.clear();
    hashTable.clear();
    elementCount = 0;
}

template <typename Key, typename Hasher>
bool UnorderedSet<Key, Hasher>::empty() const
{
    return (elementCount == 0);
}

template <typename Key, typename Hasher>
void UnorderedSet<Key, Hasher>::rehash(size_t newSize)
{
    std::vector<Key> oldElements;
    oldElements.reserve(elementCount);
    typename std::list<Key>::iterator it = data.begin();
    while (it != data.end())
    {
        oldElements.push_back(*it);
        ++it;
    }
    data.clear();
    hashTable.clear();
    hashTable.resize(newSize, std::make_pair(data.end(), 0));
    elementCount = 0;
    typename std::vector<Key>::iterator vecIt = oldElements.begin();
    while (vecIt != oldElements.end())
    {
        insert(*vecIt);
        ++vecIt;
    }
}
