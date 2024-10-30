#include "SinglyLinkedList.hpp"

bool testPushFront()
{
    SinglyLinkedList<int> list;
    list.pushFront(10);
    list.pushFront(20);
    return list.front() == 20 && list.back() == 10 && list.getSize() == 2;
}

bool testPushBack()
{
    SinglyLinkedList<int> list;
    list.pushBack(10);
    list.pushBack(20);
    return list.front() == 10 && list.back() == 20 && list.getSize() == 2;
}

bool testPopFront()
{
    SinglyLinkedList<int> list;
    list.pushBack(10);
    list.pushBack(20);
    list.popFront();
    return list.front() == 20 && list.getSize() == 1;
}

bool testFrontBack()
{
    SinglyLinkedList<int> list;
    list.pushBack(10);
    list.pushBack(20);
    return list.front() == 10 && list.back() == 20;
}

bool testConstFrontBack()
{
    const SinglyLinkedList<int> list = []() {
        SinglyLinkedList<int> temp;
        temp.pushBack(10);
        temp.pushBack(20);
        return temp;
    }();
    return list.front() == 10 && list.back() == 20;
}

bool testGetSizeIsEmpty()
{
    SinglyLinkedList<int> list;
    bool emptyBefore = list.isEmpty();
    list.pushBack(10);
    bool notEmptyAfter = !list.isEmpty();
    bool correctSize = list.getSize() == 1;
    return emptyBefore && notEmptyAfter && correctSize;
}

bool testConcat()
{
    SinglyLinkedList<int> list1, list2;
    list1.pushBack(1);
    list1.pushBack(2);
    list2.pushBack(3);
    list2.pushBack(4);
    SinglyLinkedList<int> concatenated = concat(list1, list2);
    return concatenated.front() == 1 && concatenated.back() == 4 && concatenated.getSize() == 4;
}

bool testPrint()
{
    SinglyLinkedList<int> list;
    list.pushBack(10);
    list.pushBack(20);
    list.pushBack(30);
    list.print();
    // Expected output: "10 20 30" (No validation, just visual)
    return true;
}

bool testIterator()
{
    SinglyLinkedList<int> list;
    list.pushBack(10);
    list.pushBack(20);
    list.pushBack(30);

    int sum = 0;
    for (auto it = list.begin(); it != list.end(); ++it)
        sum += *it;

    return sum == 60;
}

bool testConstIterator()
{
    const SinglyLinkedList<int> list = []() {
        SinglyLinkedList<int> temp;
        temp.pushBack(10);
        temp.pushBack(20);
        temp.pushBack(30);
        return temp;
    }();

    int sum = 0;
    for (auto it = list.cbegin(); it != list.cend(); ++it)
        sum += *it;

    return sum == 60;
}

bool testInsertAfter()
{
    SinglyLinkedList<int> list;
    list.pushBack(10);
    list.pushBack(20);
    auto it = list.begin();
    list.insertAfter(15, it);
    ++it;
    return *it == 15 && list.getSize() == 3;
}

bool testRemoveAfter()
{
    SinglyLinkedList<int> list;
    list.pushBack(10);
    list.pushBack(20);
    list.pushBack(30);
    auto it = list.begin();
    list.removeAfter(it);
    return *it == 10 && *(++it) == 30 && list.getSize() == 2;
}

bool testPushFrontMultipleElements()
{
    SinglyLinkedList<int> list;
    list.pushFront(10);
    list.pushFront(20);
    list.pushFront(30);
    return list.front() == 30 && list.back() == 10 && list.getSize() == 3;
}

bool testPushBackMultipleElements()
{
    SinglyLinkedList<int> list;
    list.pushBack(10);
    list.pushBack(20);
    list.pushBack(30);
    return list.front() == 10 && list.back() == 30 && list.getSize() == 3;
}

bool testPopFrontUntilEmpty()
{
    SinglyLinkedList<int> list;
    list.pushBack(10);
    list.pushBack(20);
    list.pushBack(30);
    list.popFront();
    list.popFront();
    list.popFront();
    return list.isEmpty() && list.getSize() == 0;
}

bool testMixedPushFrontAndBack()
{
    SinglyLinkedList<int> list;
    list.pushBack(10);
    list.pushFront(20);
    list.pushBack(30);
    list.pushFront(40);

    bool testPass = list.front() == 40 && list.back() == 30 && list.getSize() == 4;
    
    list.popFront();
    list.popFront();
    testPass = testPass && (list.front() == 10 && list.back() == 30);
    
    return testPass;
}


bool testRemoveAfterVariousPositions()
{
    SinglyLinkedList<int> list;
    list.pushBack(10);
    list.pushBack(20);
    list.pushBack(30);
    list.pushBack(40);

    // Remove after head
    auto it = list.begin();
    it = list.removeAfter(it);
    bool testPass = list.getSize() == 3 && list.front() == 10 && *(it) == 30 && *(it + 1) == 40;
    it = list.removeAfter(it);
    testPass &= list.back() == 30 && list.getSize() == 2 && it == list.end();
    
    return testPass;
}

bool testConcatLargeLists()
{
    SinglyLinkedList<int> list1, list2;
    for (int i = 1; i <= 100; ++i) list1.pushBack(i);
    for (int i = 101; i <= 200; ++i) list2.pushBack(i);

    SinglyLinkedList<int> concatenated = concat(list1, list2);

    bool testPass = concatenated.getSize() == 200 && concatenated.front() == 1 && concatenated.back() == 200;

    // Verify ordering of elements in concatenated list
    auto it = concatenated.begin();
    for (int i = 1; i <= 200; ++i, ++it) {
        testPass = testPass && (*it == i);
    }

    return testPass;
}

bool testIteratorOnEmptyList()
{
    SinglyLinkedList<int> list;
    bool testPass = true;
    for (auto it = list.begin(); it != list.end(); ++it) {
        testPass = false; // Should never enter this loop
    }
    return testPass && list.isEmpty();
}

bool testIteratorIncrementAndComparison()
{
    SinglyLinkedList<int> list;
    for (int i = 1; i <= 5; ++i) list.pushBack(i);
    
    auto it = list.begin();
    it += 2; // Move to the third element
    bool testPass = *it == 3;

    // Test operator+
    auto it2 = it + 2; // Should point to the 5th element
    testPass = testPass && (*it2 == 5);

    return testPass;
}

bool testConstIteratorUsage()
{
    const SinglyLinkedList<int> list = []() {
        SinglyLinkedList<int> temp;
        for (int i = 1; i <= 5; ++i) temp.pushBack(i);
        return temp;
    }();

    bool testPass = true;
    int expectedValue = 1;
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        testPass = testPass && (*it == expectedValue++);
    }

    return testPass && expectedValue == 6;
}

int main()
{
    std::cout << "Test Push Front: " << testPushFront() << std::endl;
    std::cout << "Test Push Back: " << testPushBack() << std::endl;
    std::cout << "Test Pop Front: " << testPopFront() << std::endl;
    std::cout << "Test Front and Back: " << testFrontBack() << std::endl;
    std::cout << "Test Const Front and Back: " << testConstFrontBack() << std::endl;
    std::cout << "Test Get Size and Is Empty: " << testGetSizeIsEmpty() << std::endl;
    std::cout << "Test Concat: " << testConcat() << std::endl;
    std::cout << "Test Print (Visual): " << testPrint() << std::endl;
    std::cout << "Test Iterator: " << testIterator() << std::endl;
    std::cout << "Test Const Iterator: " << testConstIterator() << std::endl;
    std::cout << "Test Insert After: " << testInsertAfter() << std::endl;
    std::cout << "Test Remove After: " << testRemoveAfter() << std::endl;
    std::cout << "Test Push Front Multiple Elements: " << testPushFrontMultipleElements() << std::endl;
    std::cout << "Test Push Back Multiple Elements: " << testPushBackMultipleElements() << std::endl;
    std::cout << "Test Pop Front Until Empty: " << testPopFrontUntilEmpty() << std::endl;
    std::cout << "Test Mixed Push Front and Back: " << testMixedPushFrontAndBack() << std::endl;
    std::cout << "Test Remove After Various Positions: " << testRemoveAfterVariousPositions() << std::endl;
    std::cout << "Test Concat Large Lists: " << testConcatLargeLists() << std::endl;
    std::cout << "Test Iterator on Empty List: " << testIteratorOnEmptyList() << std::endl;
    std::cout << "Test Iterator Increment and Comparison: " << testIteratorIncrementAndComparison() << std::endl;
    std::cout << "Test Iterator Increment and Comparison: " << testConstIteratorUsage() << std::endl;

    return 0;
}
