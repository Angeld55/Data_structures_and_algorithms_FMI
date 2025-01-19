#include <iostream>
#include <deque>

template <typename T, typename Container = std::deque<T>>
class Queue
{
private:
    Container container;

public:
    void push(const T& value)
    {
        container.push_back(value);
    }

    void push(T&& value)
    {
        container.push_back(std::move(value));
    }

    void pop()
    {
        container.pop_front();
    }

    T& front()
    {
        return container.front();
    }

    const T& front() const
    {
        return container.front();
    }

    T& back()
    {
        return container.back();
    }

    const T& back() const
    {
        return container.back();
    }

    bool empty() const
    {
        return container.empty();
    }

    size_t size() const
    {
        return container.size();
    }
};