#pragma once
#include <stddef.h>

template<class T>
class const_vector_iterator
{
public:
    explicit const_vector_iterator(T* passedVal) : memPointer{ passedVal } {}
    const_vector_iterator(T* passedVal, size_t _push) : memPointer{ passedVal + _push } {}

    const_vector_iterator operator+(int off) const
    {
        return { memPointer + off };
    }

    const_vector_iterator operator-(int off) const
    {
        return { memPointer - off };
    }

    int operator-(const const_vector_iterator& other) const
    {
        return memPointer - other.memPointer;
    }

    const T* operator->() const noexcept
    {
        return memPointer;
    }

    const T& operator*() const noexcept
    {
        return *(memPointer);
    }

    bool operator==(const const_vector_iterator& it) const
    {
        return (memPointer == it.memPointer);
    }

    bool operator!=(const const_vector_iterator& it) const
    {
        return !(memPointer == it.memPointer);
    }

private:
    const T* memPointer;
};



template<class T>
class vector_iterator
{
public:
    explicit vector_iterator(T* passedVal) : memPointer{ passedVal } {};
    vector_iterator(T* passedVal, size_t _push) : memPointer{ passedVal + _push } {};

    vector_iterator& operator++()
    {
        memPointer++;
        return *this;
    }

    vector_iterator operator++(int)
    {
        vector_iterator it = *this;
        ++(*this);
        return it;
    }

    vector_iterator& operator--()
    {
        memPointer--;
        return *this;
    }

    vector_iterator operator--(int)
    {
        vector_iterator it = *this;
        --(*this);
        return it;
    }

    operator const_vector_iterator<T>() const
    {
        return const_vector_iterator<T>(memPointer);
    }

    vector_iterator operator+(int off) const
    {
        return { memPointer + off };
    }

    vector_iterator operator-(int off) const
    {
        return { memPointer - off };
    }

    T* operator->()
    {
        return memPointer;
    }

    const T* operator->() const
    {
        return memPointer;
    }

    T& operator*()
    {
        return *(memPointer);
    }

    bool operator==(const vector_iterator& it) const
    {
        return (memPointer == it.memPointer);
    }

    bool operator!=(const vector_iterator& it) const
    {
        return !(memPointer == it.memPointer);
    }

private:
    T* memPointer;
};



template<class T>
class reverse_vector_iterator
{
public:
    explicit reverse_vector_iterator(T* passedVal) : memPointer{ passedVal } {};
    reverse_vector_iterator(T* passedVal, size_t _push) : memPointer{ passedVal + _push } {};

    reverse_vector_iterator& operator++()
    {
        memPointer--;
        return *this;
    }

    reverse_vector_iterator operator++(int)
    {
        reverse_vector_iterator it = *this;
        ++(*this);
        return it;
    }

    reverse_vector_iterator& operator--()
    {
        memPointer++;
        return *this;
    }

    reverse_vector_iterator operator--(int)
    {
        reverse_vector_iterator it = *this;
        --(*this);
        return it;
    }

    reverse_vector_iterator operator+(int off) const
    {
        return { memPointer - off };
    }

    reverse_vector_iterator operator-(int off) const
    {
        return { memPointer + off };
    }

    T* operator->()
    {
        return memPointer;
    }

    const T* operator->() const
    {
        return memPointer;
    }

    T& operator*()
    {
        return *(memPointer);
    }

    bool operator==(const reverse_vector_iterator& it) const
    {
        return (memPointer == it.memPointer);
    }

    bool operator!=(const reverse_vector_iterator& it) const
    {
        return !(memPointer == it.memPointer);
    }

private:
    T* memPointer;
};