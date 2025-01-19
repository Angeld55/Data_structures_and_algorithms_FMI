#include "Queue.hpp"
int main()
{
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    int x = 4;
    q.push(std::move(x));
    std::cout << q.front() << " " << q.back() << std::endl;
    q.pop();
    std::cout << q.front() << " " << q.size() << std::endl;
    return 0;
}
