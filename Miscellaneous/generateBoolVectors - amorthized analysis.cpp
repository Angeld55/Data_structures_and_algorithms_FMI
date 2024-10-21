#include <iostream>
#include <vector>

void print(const std::vector<int>& v)
{
    std::cout << "[";
    for (auto it = v.begin(); it != v.end(); it++)
    {
        std::cout << (*it) << " ";
    }
    std::cout << "]" << std::endl;
}

void next(std::vector<int>& v)
{
    int ind = v.size() - 1;
    while (ind >= 0 && v[ind] == 1)
        v[ind--] = 0;
    if (ind >= 0)
        v[ind] = 1;
}

void nextWithIterators(std::vector<int>& v) //just for exercise 
{
    auto it = v.rbegin(); //reverse iterator 

    while (it != v.rend() && *it == 1)
        *it++ = 0;

    if (it != v.rend())
        *it = 1;
}

void generateBoolVectors(int n)
{
    std::vector<int> v(n, 0);
    unsigned count = 1 << n;

    for (unsigned i = 0; i < count; i++)
    {
        print(v);
        nextWithIterators(v);
    }
}

int main()
{
    generateBoolVectors(3);
}
