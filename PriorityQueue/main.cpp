#include <iostream>
#include "priorityQueue.hpp"

int main()
{
    PriorityQueue<int> pq;
    
    pq.insert(3);
    pq.insert(10);
    pq.insert(0);
    
    std::cout << pq.peek();
}
