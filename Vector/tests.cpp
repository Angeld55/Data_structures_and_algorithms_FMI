#define TEST_DIR_VECTOR_ALLOC "vector-allocator/vector.hpp"
#define TEST_DIR_VECTOR "vector/vector.hpp"

#include TEST_DIR_VECTOR
#include <algorithm>
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

struct Entity
{
	int x;

	Entity(int _x)
		: x(_x)
	{}
	Entity()
		: x()
	{}

	~Entity()
	{
		x = -1;
	}
};

void tests_default()
{
	vector<Entity> v;

	v.push_back(Entity(1));
	assert(v.back().x == 1);
	assert(v.size() == 1);
	assert(v.capacity() == 1);

	v.emplace_back(2);
	assert(v.back().x == 2);
	assert(v.size() == 2);
	assert(v.capacity() == 2);

	for (int i = 3; i <= 10; i++)
		v.emplace_back(i);

	for (int i = 1; i <= 10; i++)
		assert(v[i - 1].x == i);

	for (int i = 1; i <= 10; i++)
		assert((v.begin() + (i - 1))->x == i);

	assert(v.size() == 10);
	assert(v.capacity() == 16);

	int cnt = 1;
	for (auto e : v)
		assert(e.x == cnt++);
}

void test_resize_reserve()
{
	std::vector<Entity> v;
	vector<Entity> v1;

	assert(v1.size() == v.size() && v1.capacity() == v.capacity());
	assert(v.data() == nullptr && v1.data() == nullptr);

	v.reserve(10);
	v1.reserve(10);
	assert(v1.size() == v.size() && v1.capacity() == v.capacity());

	v.reserve(20);
	v1.reserve(20);
	assert(v1.size() == v.size() && v1.capacity() == v.capacity());

	v.reserve(10);
	v1.reserve(10);
	assert(v1.size() == v.size() && v1.capacity() == v.capacity());

	v.shrink_to_fit();
	v1.shrink_to_fit();
	assert(v1.size() == v.size() && v1.capacity() == v.capacity());

	v.resize(10);
	v1.resize(10);
	assert(v1.size() == v.size() && v1.capacity() == v.capacity());

	v.resize(20);
	v1.resize(20);
	assert(v1.size() == v.size() && v1.capacity() == v.capacity());

	for (size_t i = 0; i < v1.size(); i++)
		v1[i].x = i;

	v.resize(10);
	v1.resize(10);

	for (size_t i = 0; i < v1.size(); i++)
		assert(v1[i].x == i);
	
	assert(v1.size() == v.size() && v1.capacity() == v.capacity());
	assert(v1.front().x == 0 && v1.back().x == 9);

	v.push_back(1);
	v.push_back(2);
	v.emplace_back(3);

	v1.push_back(1);
	v1.push_back(2);
	v1.emplace_back(3);

	v.shrink_to_fit();
	v1.shrink_to_fit();
	assert(v1.size() == v.size() && v1.capacity() == v.capacity());
}

void push_pop_tests()
{
	vector<int> v;

	for (size_t i = 0; i < 100; i++)
		v.push_back(i);

	int j = 100;
	while (!v.empty())
	{
		assert(v.back() == --j);
		v.pop_back();
	}
}

void erase_tests()
{
	vector<int> v;
	for (size_t i = 1; i <= 100; i++)
	{
		v.push_back(i);
	}

	v.erase(v.begin(), v.begin() + 49);

	int j = 50;

	for (auto x : v)
	{
		assert(x == j++);
	}

	assert(v.size() == 51);

	v.erase(v.begin());
	assert(v.front() == 51 && v.size() == 50);

	v.erase(v.begin() + 10, v.begin() + 20);
	assert(v.size() == 40);

	for (auto x : v)
	{
		assert(!(x >= 61 && x <= 70));
	}

	v.erase(v.begin(), v.end());
	assert(v.empty());
}

int called = 0;

struct constructor_called
{
	constructor_called()
	{
		++called;
	}
};

void constructor_tests()
{
	// Default construct
	vector<int> start;
	assert(start.size() == 0 && start.capacity() == 0 && start.data() == nullptr);
	start.push_back(0);
	assert(start.size() == 1 && start.capacity() == 1 && start.data() != nullptr);
	start.pop_back();
	assert(start.size() == 0 && start.capacity() == 1 && start.data() != nullptr);

	size_t length = 200;

	for (size_t i = 0; i < length; i++)
		start.push_back(rand() % 1000);

	// Copy constructor tests
	vector<int> copy(start);
	for (size_t i = 0; i < length; i++)
		assert(copy[i] == start[i]);

	// Move constructor tests
	vector<int> moved(std::move(copy));
	assert(copy.data() == nullptr && copy.size() == 0 && copy.capacity() == 0);

	for (size_t i = 0; i < length; i++)
		assert(moved[i] == start[i]);

	// Parameter constructors
	std::vector<constructor_called> v(10);
	assert(called == 10);
	v.reserve(20);
	assert(called == 10);

	std::vector<Entity> v2(20, 20);
	for (const auto& e : v2)
	{
		assert(e.x == 20);
	}
}

void push_back_tests()
{
	vector<int> v;

	for (size_t i = 0; i < 1000; i++)
		v.push_back(i);

	assert(v.size() == 1000);

	for (int i = 0; i < 1000; i++)
		assert(v[i] == i);
}

void erase_test()
{
	vector<int> v;

	for (size_t i = 0; i < 1001; i++)
		v.push_back(i);

	auto it = v.begin();

	while (it != v.end())
	{
		if ((*it % 2) == 0)
		{
			v.erase(it);
			it = v.begin();
		}
		++it;
	}

	for (auto x : v)
		assert(x % 2);

	assert(v.size() == 500);
}

void iterator_tests()
{
	vector<int> v;
	for (size_t i = 0; i < 100; i++)
	{
		v.push_back(i);
	}

	for (size_t i = 0; i < 100; i++)
	{
		assert(*(v.begin() + i) == i);
		assert(*(v.end() - i - 1) == 100 - i - 1);

		if (i)
			assert(v.begin() != (v.begin() + i) && (v.begin() + i) != v.end());
	}

	auto it = v.begin();
	assert(*it == 0);
	vector<Entity> v1;
	v1.emplace_back(1);
	v1.emplace_back(2);

	assert((++v1.begin())->x == 2);
	assert(++(++v1.begin()) == v1.end());
	assert(--v1.end() == ++v1.begin());

	int j = 99;
	for (auto rit = v.rbegin(); rit != v.rend(); ++rit)
	{
		assert(*rit == j--);
	}

	assert((v1.rbegin())->x == 2);
	assert((++v1.rbegin())->x == 1);
}

// Still a test with more complex objects
void run_all()
{
	vector<std::thread> v;
	vector<std::function<void()>> tests;

	tests.push_back(constructor_tests);
	tests.push_back(tests_default);
	tests.push_back(test_resize_reserve);
	tests.push_back(push_back_tests);
	tests.push_back(push_pop_tests);
	tests.push_back(erase_tests);
	tests.push_back(erase_test);
	tests.push_back(iterator_tests);

	for (const auto& func : tests)
	{
		v.emplace_back(func);
	}

	for (auto& c_thread : v)
	{
		c_thread.join();
	}
}

int main()
{
	std::cout << "Start tests...\n";
	run_all();
	std::cout << "No assertions failed!";
}