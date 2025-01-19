#include <iostream>
#include "UnionFind.h"

int main()
{
    UnionFind uf(10);

    std::cout << "Union(1, 2): " << uf.Union(1, 2) << std::endl;
    std::cout << "Union(2, 3): " << uf.Union(2, 3) << std::endl;
    std::cout << "Union(4, 5): " << uf.Union(4, 5) << std::endl;
    std::cout << "Union(6, 7): " << uf.Union(6, 7) << std::endl;
    std::cout << "Union(5, 6): " << uf.Union(5, 6) << std::endl;
    std::cout << "Union(3, 7): " << uf.Union(3, 7) << std::endl;

    std::cout << "areInOneSet(1, 7): " << uf.areInOneSet(1, 7) << std::endl;
    std::cout << "areInOneSet(4, 6): " << uf.areInOneSet(4, 6) << std::endl;
    std::cout << "areInOneSet(1, 4): " << uf.areInOneSet(1, 4) << std::endl;
    std::cout << "areInOneSet(8, 9): " << uf.areInOneSet(8, 9) << std::endl;

    return 0;
}
