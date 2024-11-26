#pragma once
#include <iostream>
#include <vector>

template <typename T>
class PriorityQueue
{
    static size_t leftChild(size_t i);
    static size_t rightChild(size_t i);
    static int parent(int i);

    void heapify(size_t ind);
    std::vector<T> data;

public:
    PriorityQueue() = default;
    PriorityQueue(const std::vector<T>& v);

    bool isEmpty() const;
    const T& peek() const;
    void pop(); // Премахва най-големия елемент (може и да го върнем).
    void insert(const T& el);
    size_t size() const;
};

template <typename T>
size_t PriorityQueue<T>::leftChild(size_t i)
{
    return 2 * i + 1;
}

template <typename T>
size_t PriorityQueue<T>::rightChild(size_t i)
{
    return 2 * i + 2;
}

template <typename T>
int PriorityQueue<T>::parent(int i)
{
    return (i - 1) / 2;
}

template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
    return data.empty();
}

template <typename T>
void PriorityQueue<T>::pop()
{
    if (isEmpty())
        throw std::runtime_error("Empty queue!");

    data[0] = data[data.size() - 1]; // Новият корен става последен елемент.
    data.pop_back();

    if (data.size() != 0)
        heapify(0); // Коренът започва да се "спуска" надолу, за да се запази пирамидалното свойство.
}

template <typename T>
const T& PriorityQueue<T>::peek() const
{
    if (isEmpty())
        throw std::runtime_error("Empty queue!");
    return data[0];
}

// Функция, която "спуска елемент". Елементът ако има ляво поддърво, което е пирамида и дясно поддърво, което е пирамида, образува нова пирамида, обединявайки двете + корена.
template <typename T>
void PriorityQueue<T>::heapify(size_t ind)
{
    int currentElementIndex = ind;
    while (true)
    {
        int leftChildIndex = leftChild(currentElementIndex);
        int rightChildIndex = rightChild(currentElementIndex);

        // Проверяваме дали има ляв/десен наследник и дали той е по-голям от текущия елемент.
        bool shouldGoLeft = leftChildIndex < data.size() && data[leftChildIndex] > data[currentElementIndex];
        bool shouldGoRight = rightChildIndex < data.size() && data[rightChildIndex] > data[currentElementIndex];

        if (shouldGoLeft && shouldGoRight)
        {
            // Ако и двата наследника са по-големи, се "спускаме" към по големия.
            if (data[leftChildIndex] > data[rightChildIndex])
            {
                std::swap(data[currentElementIndex], data[leftChildIndex]);
                currentElementIndex = leftChildIndex;
            }
            else
            {
                std::swap(data[currentElementIndex], data[rightChildIndex]);
                currentElementIndex = rightChildIndex;
            }
        }
        else if (shouldGoLeft)
        {
            std::swap(data[currentElementIndex], data[leftChildIndex]);
            currentElementIndex = leftChildIndex;
        }
        else if (shouldGoRight)
        {
            std::swap(data[currentElementIndex], data[rightChildIndex]);
            currentElementIndex = rightChildIndex;
        }
        else
            break;
    }
}

template <typename T>
void PriorityQueue<T>::insert(const T& el)
{
    data.push_back(el);
    int ind = data.size() - 1;
    int parentIndex = parent(ind);

    // Елементът е поставен на дъното на пирамидата и той се опитва да "изплува" нагоре, докато родителят е по-малък от него.
    while (ind > 0 && data[ind] > data[parentIndex])
    {
        std::swap(data[ind], data[parentIndex]);
        ind = parentIndex;
        parentIndex = parent(ind);
    }
}

template <typename T>
PriorityQueue<T>::PriorityQueue(const std::vector<T>& v)  // O(n)
{
    data = v;

    for (int i = v.size() / 2 - 1; i >= 0; i--)
        heapify(i);
}

template <typename T>
size_t PriorityQueue<T>::size() const
{
    return data.size();
}

