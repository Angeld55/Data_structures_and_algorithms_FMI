#include <iostream>
#include "LinkedDeque.hpp"  // Include your LinkedDeque header here

int main()
{
    // 1) Create a LinkedDeque of int
    LinkedDeque<int> dq;

    // 2) Push some elements (front and back)
    dq.push_front(10);
    dq.push_front(20);
    dq.push_back(30);
    dq.push_back(40);

    // 3) Print the contents
    std::cout << "Initial deque contents:\n";
    dq.print();  // 20 <-> 10 <-> 30 <-> 40

    // 4) Use iterators to traverse (read/write)
    std::cout << "\nTraverse with iterator and modify the second element:\n";
    {
        auto it = dq.begin();
        // *it = 20  (the first element)
        ++it;
        // *it = 10  (the second element)
        *it = 99; // Modify the second element
    }
    dq.print();  // 20 <-> 99 <-> 30 <-> 40

    // 5) Insert an element using iterator
    std::cout << "\nInsert a value (555) before the 99:\n";
    {
        auto it = dq.begin();
        ++it; // 'it' now points to 99
        dq.insert(it, 555);
    }
    dq.print();  // 20 <-> 555 <-> 99 <-> 30 <-> 40

    // 6) Erase an element using iterator
    std::cout << "\nErase the element 555 using iterator:\n";
    {
        auto it = dq.begin();
        ++it; // 'it' now points to 555
        dq.erase(it);
    }
    dq.print(); // 20 <-> 99 <-> 30 <-> 40

    // 7) Pop from front and back
    std::cout << "\nPop front and back:\n";
    dq.pop_front(); // removes 20
    dq.pop_back();  // removes 40
    dq.print();     // 99 <-> 30

    // 8) Demonstrate const_iterator usage
    std::cout << "\nTraverse with const_iterator:\n";
    {
        const LinkedDeque<int>& constRef = dq;
        for (auto cit = constRef.cbegin(); cit != constRef.cend(); ++cit)
        {
            std::cout << *cit << " ";
        }
        std::cout << std::endl;
    }

    // 9) Clear everything
    std::cout << "\nClear the deque:\n";
    dq.clear();
    dq.print();  // (should print nothing)

    std::cout << "\nDone!\n";
    return 0;
}
