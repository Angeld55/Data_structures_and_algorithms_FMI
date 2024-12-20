#pragma once

#include <vector>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility> 
#include <iostream>


template <class KeyType, class ValueType, class Hasher = std::hash<KeyType>>
class LinearProbingHash
{
public:
    using element = std::pair<KeyType, ValueType>;

    class Iterator
    {
    public:
        const element& operator*() const;
        Iterator operator++(int dummy);
        Iterator& operator++();
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        Iterator(int index, const LinearProbingHash<KeyType, ValueType, Hasher>& context);

        int index;
        const LinearProbingHash<KeyType, ValueType, Hasher>& context;
        friend class LinearProbingHash<KeyType, ValueType, Hasher>;
    };

    LinearProbingHash(size_t table_size = 10, size_t probe_step = 3);

    void add(const KeyType& key, const ValueType& value);
    void remove(const KeyType& key);
    Iterator get(const KeyType& key) const;
    Iterator begin() const;
    Iterator end() const;

    size_t getSize() const;

private:
    bool containsElementAtIndex(size_t index) const;

    std::vector<std::optional<element>> data;
    const element tombstone;
    size_t size;
    size_t n; // Table size
    size_t k; // Probe step

    Hasher hasher;
};

template <class KeyType, class ValueType, class Hasher>
LinearProbingHash<KeyType, ValueType, Hasher>::LinearProbingHash(size_t table_size, size_t probe_step)
    : n(table_size), k(probe_step), tombstone(std::make_pair(KeyType(), ValueType())), size(0)
{
    data.resize(n);
}

template <class KeyType, class ValueType, class Hasher>
void LinearProbingHash<KeyType, ValueType, Hasher>::add(const KeyType& key, const ValueType& value)
{
    int indexToPut = hasher(key) % n;

    while (containsElementAtIndex(indexToPut))
    {
        if (data[indexToPut]->first == key)
            throw std::logic_error("Already exists!");

        (indexToPut += k) %= n;
    }
    data[indexToPut] = { key, value };
    size++;
}

template <class KeyType, class ValueType, class Hasher>
void LinearProbingHash<KeyType, ValueType, Hasher>::remove(const KeyType& key)
{
    int index = hasher(key) % n;

    while (data[index] != std::nullopt)
    {
        if (data[index] != tombstone && data[index]->first == key)
        {
            data[index] = tombstone;
            size--;
            break;
        }
        (index += k) %= n;
    }
}

template <class KeyType, class ValueType, class Hasher>
class LinearProbingHash<KeyType, ValueType, Hasher>::Iterator LinearProbingHash<KeyType, ValueType, Hasher>::get(const KeyType& key) const
{
    int index = hasher(key) % n;

    while (data[index] != std::nullopt)
    {
        if (data[index] != tombstone && data[index]->first == key)
        {
            return Iterator(index, *this);
        }
        (index += k) %= n;
    }
    return end(); // not found!!
}

template <class KeyType, class ValueType, class Hasher>
class LinearProbingHash<KeyType, ValueType, Hasher>::Iterator LinearProbingHash<KeyType, ValueType, Hasher>::begin() const
{
    if (size == 0)
        return end();

    for (int i = 0; ; i++)
    {
        if (containsElementAtIndex(i))
            return Iterator(i, *this);
    }
}

template <class KeyType, class ValueType, class Hasher>
class LinearProbingHash<KeyType, ValueType, Hasher>::Iterator LinearProbingHash<KeyType, ValueType, Hasher>::end() const
{
    return Iterator(-1, *this);
}

template <class KeyType, class ValueType, class Hasher>
size_t LinearProbingHash<KeyType, ValueType, Hasher>::getSize() const
{
    return size;
}

template <class KeyType, class ValueType, class Hasher>
bool LinearProbingHash<KeyType, ValueType, Hasher>::containsElementAtIndex(size_t index) const
{
    return data[index] != std::nullopt && data[index] != tombstone;
}


template <class KeyType, class ValueType, class Hasher>
LinearProbingHash<KeyType, ValueType, Hasher>::Iterator::Iterator(int index, const LinearProbingHash<KeyType, ValueType, Hasher>& context)
    : index(index), context(context) {}

template <class KeyType, class ValueType, class Hasher>
const class LinearProbingHash<KeyType, ValueType, Hasher>::element& LinearProbingHash<KeyType, ValueType, Hasher>::Iterator::operator*() const
{
    return *context.data[index];
}


template <class KeyType, class ValueType, class Hasher>
class LinearProbingHash<KeyType, ValueType, Hasher>::Iterator LinearProbingHash<KeyType, ValueType, Hasher>::Iterator::operator++(int dummy)
{
    int oldIndex = index;
    while (++index < context.data.size() && !context.containsElementAtIndex(index)) {}

    if (index == context.data.size())
    {
        index = -1;
    }

    return Iterator(oldIndex, context);
}

template <class KeyType, class ValueType, class Hasher>
class LinearProbingHash<KeyType, ValueType, Hasher>::Iterator& LinearProbingHash<KeyType, ValueType, Hasher>::Iterator::operator++()
{
    while (++index < context.data.size() && !context.containsElementAtIndex(index)) {}

    if (index == context.data.size())
        index = -1;

    return *this;
}

template <class KeyType, class ValueType, class Hasher>
bool LinearProbingHash<KeyType, ValueType, Hasher>::Iterator::operator==(const Iterator& other) const
{
    return index == other.index;
}

template <class KeyType, class ValueType, class Hasher>
bool LinearProbingHash<KeyType, ValueType, Hasher>::Iterator::operator!=(const Iterator& other) const
{
    return index != other.index;
}
