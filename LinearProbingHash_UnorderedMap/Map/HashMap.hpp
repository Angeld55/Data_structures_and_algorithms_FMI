#pragma once

#include <vector>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility> 
#include <iostream>
#include <functional>

template <class KeyType, class ValueType, class Hasher = std::hash<KeyType>>
class HashMap
{
private:
    struct Bucket
    {
        std::optional<std::pair<KeyType, ValueType>> entry;
        bool tombstone = false;
    };

public:
    using element = std::pair<KeyType, ValueType>;

    class ConstIterator
    {
    public:
        const element& operator*() const
        {
            return *(context.buckets[index].entry);
        }

        ConstIterator operator++(int)
        {
            ConstIterator old(*this);
            advance();
            return old;
        }

        ConstIterator& operator++()
        {
            advance();
            return *this;
        }

        bool operator==(const ConstIterator& other) const
        {
            return (&context == &other.context) && (index == other.index);
        }

        bool operator!=(const ConstIterator& other) const
        {
            return !(*this == other);
        }

    private:
        friend class HashMap<KeyType, ValueType, Hasher>;

        ConstIterator(int idx, const HashMap& ctx)
            : index(idx), context(ctx)
        {
        }

        void advance()
        {
            do
            {
                ++index;
            } while (index >= 0 && index < (int)context.buckets.size()
                && !context.isActive(context.buckets[index]));

            if (index < 0 || index >= (int)context.buckets.size())
            {
                index = -1;
            }
        }

        int index;
        const HashMap& context;
    };

    HashMap(size_t table_size = 10, size_t probe_step = 3)
        : size(0), k(probe_step), buckets(table_size)
    {
    }

    void add(const KeyType& key, const ValueType& value)
    {
        double loadFactor = static_cast<double>(size) / buckets.size();
        if (loadFactor > maxLoadFactor)
        {
            resize(buckets.size() * 2);
        }

        size_t idx = hasher(key) % buckets.size();
        while (isActive(buckets[idx]))
        {
            if (buckets[idx].entry->first == key)
            {
                throw std::logic_error("Already exists!");
            }
            idx = (idx + k) % buckets.size();
        }

        buckets[idx].entry = std::make_pair(key, value);
        buckets[idx].tombstone = false;
        ++size;
    }

    void remove(const KeyType& key)
    {
        size_t idx = hasher(key) % buckets.size();
        size_t start = idx;
        while (true)
        {
            if (!buckets[idx].entry.has_value() && !buckets[idx].tombstone)
            {
                break;
            }
            if (isActive(buckets[idx]) && buckets[idx].entry->first == key)
            {
                buckets[idx].tombstone = true;
                buckets[idx].entry.reset();
                --size;
                break;
            }

            idx = (idx + k) % buckets.size();
            if (idx == start)
                break;
        }
    }

    ConstIterator get(const KeyType& key) const
    {
        size_t idx = hasher(key) % buckets.size();
        size_t start = idx;
        while (true)
        {
            if (!buckets[idx].entry.has_value() && !buckets[idx].tombstone)
            {
                return cend();
            }
            if (isActive(buckets[idx]) && buckets[idx].entry->first == key)
            {
                return ConstIterator((int)idx, *this);
            }

            idx = (idx + k) % buckets.size();
            if (idx == start)
            {
                return cend();
            }
        }
    }

    ConstIterator cbegin() const
    {
        if (size == 0)
        {
            return cend();
        }
        for (int i = 0; i < (int)buckets.size(); i++)
        {
            if (isActive(buckets[i]))
            {
                return ConstIterator(i, *this);
            }
        }
        return cend();
    }

    ConstIterator cend() const
    {
        return ConstIterator(-1, *this);
    }

    size_t getSize() const
    {
        return size;
    }

private:
    bool isActive(const Bucket& b) const
    {
        return b.entry.has_value() && !b.tombstone;
    }

    void resize(size_t newSize)
    {
        std::vector<Bucket> oldBuckets = std::move(buckets);
        buckets.resize(newSize);
        for (auto& b : buckets)
        {
            b.entry.reset();
            b.tombstone = false;
        }
        size = 0;

        for (auto& b : oldBuckets)
        {
            if (isActive(b))
            {
                add(b.entry->first, b.entry->second);
            }
        }
    }

private:
    size_t size;
    size_t k;
    std::vector<Bucket> buckets;
    Hasher hasher{};
    const double maxLoadFactor = 0.8;
};
