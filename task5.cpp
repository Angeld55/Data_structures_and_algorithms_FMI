
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <list>
#include <unordered_map>
#include <iterator>
#include <algorithm>
#include <queue>
#include <map>

template <typename T>
class Counter
{
	std::unordered_map<T, size_t> counter;
public:
	Counter() = default;

	size_t count() const
	{
		return counter.size();
	}

	size_t operator[](const T& el) const
	{
		auto it = counter.find(el);

		if (it == counter.end())
			return 0;
		return (*it).second;
	}
	
	Counter& operator+=(const T& x)
	{

		auto it = counter.find(x);

		if (it == counter.end())
			counter.insert({ x, 1 });
		else
			(*it).second++;

		return *this;
	}

	Counter& operator-=(const T& x)
	{

		auto it = counter.find(x);

		if (it != counter.end())
		{
			(*it).second--;
			if((*it).second == 0)
				counter.erase(x);
		}
		return *this;
	}

	Counter<T> operator+(const Counter<T>& rhs)
	{
		Counter<T> result = *this;

		for (auto rhsIt = rhs.counter.begin(); rhsIt != rhs.counter.end(); rhsIt++)
		{
			auto lhsIt = result.counter.find((*rhsIt).first);

			if (lhsIt != result.counter.end())
				(*lhsIt).second += (*rhsIt).second;
			else
				result.counter.insert({ (*rhsIt).first, (*rhsIt).second});
		}

		return result;

	}

};

template <typename T>
Counter<T> operator+(const Counter<T>& counter, const T& element)
{
	Counter<T> copy = counter;
	copy += element;
	return copy;
}

template <typename T>
Counter<T> operator-(const Counter<T>& counter, const T& element)
{
	Counter<T> copy = counter;
	copy -= element;
	return copy;
}



int main()
{
	Counter<int> c;

	c += 3;
	c += 3;

	c += 5;

	Counter<int> c2 = c;

	Counter<int> c3 = c + c2;
	
	std::cout << c3[3] << " " << c3[5] << " " << c3[10] << std::endl;

}
