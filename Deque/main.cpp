#include "Deque.hpp"
#include <iostream>

bool testPushBack()
{
	Deque<int> deque;
	deque.pushBack(10);
	deque.pushBack(20);
	deque.pushBack(30);

	return deque.size() == 3 && deque[0] == 10 && deque[1] == 20 && deque[2] == 30;
}

bool testPushFront()
{
	Deque<int> deque;
	deque.pushFront(10);
	deque.pushFront(20);
	deque.pushFront(30);

	return deque.size() == 3 && deque[0] == 30 && deque[1] == 20 && deque[2] == 10;
}

bool testPopBack()
{
	Deque<int> deque;
	deque.pushBack(10);
	deque.pushBack(20);
	deque.pushBack(30);
	deque.popBack();

	return deque.size() == 2 && deque[0] == 10 && deque[1] == 20;
}

bool testPopFront()
{
	Deque<int> deque;
	deque.pushBack(10);
	deque.pushBack(20);
	deque.pushBack(30);
	deque.popFront();

	return deque.size() == 2 && deque[0] == 20 && deque[1] == 30;
}

bool testEmplaceBack()
{
	Deque<std::string> deque;
	deque.emplaceBack(3, 'a'); // Adds "aaa" to the back

	return deque.size() == 1 && deque[0] == "aaa";
}

bool testEmplaceFront()
{
	Deque<std::string> deque;
	deque.emplaceFront(3, 'b'); // Adds "bbb" to the front

	return deque.size() == 1 && deque[0] == "bbb";
}

bool testFrontBackAccess()
{
	Deque<int> deque;
	deque.pushBack(10);
	deque.pushBack(20);
	deque.pushFront(5);

	return deque.front() == 5 && deque.back() == 20;
}

bool testIsEmpty()
{
	Deque<int> deque;
	return deque.isEmpty();
}

bool testResize()
{
	Deque<int> deque;
	for (int i = 0; i < 20; ++i)
	{
		deque.pushBack(i);
	}
	bool success = true;
	for (int i = 0; i < 20; ++i)
	{
		success = success && deque[i] == i;
	}
	return success && deque.size() == 20;
}
bool testShrinkToFit()
{
	Deque<int> deque;

	// Step 1: Add elements to exceed the initial currCapacity and trigger resize
	for (int i = 0; i < 20; ++i)
	{
		deque.pushBack(i);
	}

	// Step 2: Remove a few elements to create extra currCapacity
	for (int i = 0; i < 10; ++i)
	{
		deque.popFront();
	}

	// Step 3: Call shrinkToFit to reduce currCapacity to match the current size
	size_t sizeBeforeShrink = deque.size();
	deque.shrinkToFit();

	// Step 4: Check if the currCapacity matches the current size
	bool capacityMatchesSize = (deque.size() == sizeBeforeShrink && deque.capacity() == deque.size());

	// Step 5: Verify elements are in the correct order after shrinking
	bool elementsIntact = true;
	for (size_t i = 0; i < deque.size(); ++i)
	{
		if (deque[i] != i + 10) // Elements should be [10, 11, ..., 19] after popping
		{
			elementsIntact = false;
			break;
		}
	}

	if(!(capacityMatchesSize && elementsIntact))
		return false;

	// Step 6: Empty the whole deque then try shrink_to_fit
	// on an empty container.
	while(deque.size()) { deque.popFront(); }
	deque.shrinkToFit();
	if(deque.size() != 0) return false;

	deque.pushBack(1);
	deque.pushBack(2);
	deque.pushBack(3);
	deque.pushBack(4);

	if(deque.size() != 4 || deque.front() != 1 || deque.back() != 4) return false;

	return true;
}


bool testIteratorIncrement() {
	Deque<int> deque;
	deque.pushBack(1);
	deque.pushBack(2);
	deque.pushBack(3);

	auto it = deque.begin();
	if (*it != 1) return false;

	it++;
	if (*it != 2) return false;

	++it;
	if (*it != 3) return false;

	return it == deque.end() - 1;
}

bool testIteratorDecrement() {
	Deque<int> deque;
	deque.pushBack(1);
	deque.pushBack(2);
	deque.pushBack(3);

	auto it = deque.end() - 1;
	if (*it != 3) return false;

	it--;
	if (*it != 2) return false;

	--it;
	if (*it != 1) return false;

	return it == deque.begin();
}

bool testIteratorEquality() {
	Deque<int> deque;
	deque.pushBack(10);
	deque.pushBack(20);

	auto it1 = deque.begin();
	auto it2 = deque.begin();
	if (it1 != it2) return false;

	++it2;
	if (it1 == it2) return false;

	return true;
}

bool testConstIterator() {
	Deque<int> deque;
	deque.pushBack(5);
	deque.pushBack(15);
	deque.pushBack(25);

	const Deque<int>& constDeque = deque;
	auto it = constDeque.begin();

	if (*it != 5) return false;
	++it;
	if (*it != 15) return false;
	++it;
	if (*it != 25) return false;

	return it == constDeque.end() - 1;
}

bool testIteratorDereference() {
	Deque<int> deque;
	deque.pushBack(100);
	deque.pushBack(200);
	deque.pushBack(300);

	auto it = deque.begin();
	if (*it != 100) return false;

	++it;
	if (*it != 200) return false;

	it++;
	if (*it != 300) return false;

	return true;
}

bool testCopyConstructor()
{
	Deque<int> deque;
	deque.pushBack(1);
	deque.pushBack(2);
	deque.pushBack(3);

	Deque<int> copy(deque);

	if(deque.size() != copy.size()) return false;

	while(copy.size())
	{
		if(copy.front() != deque.front()) return false;
		copy.popFront();
		deque.popFront();
	}

	if(deque.size() != copy.size()) return false;

	return true;
}

bool testMoveAndAssignment()
{
	constexpr size_t SIZE = 4;

	Deque<int> d;

	for (size_t i = 0; i < SIZE; i++)
		d.pushBack(i);

	Deque<int> d1;
	d1 = d;

	for (size_t i = 0; i < d1.size(); i++)
		if(d1[i] != d[i]) return false;
	
	Deque<int> moved(std::move(d1));

	if(moved.size() != SIZE || d1.size() != 0) return false;

	d1 = std::move(moved);
	moved = std::move(d1);

	if(moved.size() != SIZE || d1.size() != 0) return false;

	for (size_t i = 0; i < d1.size(); i++)
		if(moved[i] != d[i]) return false;
	
	while(moved.size())
	{
		if(moved.front() != d.front() || moved.back() != d.back())
			return false;
		moved.popBack();
		d.popBack();

		if(moved.isEmpty() || d.isEmpty())
			break;

		moved.popFront();
		d.popFront();
	}

	if(!moved.isEmpty() || !d.isEmpty()) return false;

	return true;
}

int main()
{
	std::cout << "Test Push Back: " << (testPushBack() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Push Front: " << (testPushFront() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Pop Back: " << (testPopBack() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Pop Front: " << (testPopFront() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Emplace Back: " << (testEmplaceBack() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Emplace Front: " << (testEmplaceFront() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Front and Back Access: " << (testFrontBackAccess() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Is Empty: " << (testIsEmpty() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Resize: " << (testResize() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Shrink To Fit: " << (testShrinkToFit() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Iterator Increment: " << (testIteratorIncrement() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Iterator Decrement: " << (testIteratorDecrement() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Iterator Equality: " << (testIteratorEquality() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Const Iterator: " << (testConstIterator() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Iterator Dereference: " << (testIteratorDereference() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Copy Cnstructor: " << (testCopyConstructor() ? "PASSED" : "FAILED") << "\n";
	std::cout << "Test Move Constructor And Assignment: " << (testMoveAndAssignment() ? "PASSED" : "FAILED") << "\n";

	return 0;
}
