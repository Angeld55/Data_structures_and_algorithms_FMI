#pragma once

#include <vector>

class UnionFind
{
private:
    std::vector<int> parent;
    std::vector<int> sizes;

public:
    UnionFind(int n);
    int getRoot(int n);
    bool areInOneSet(int n, int k);
    bool Union(int n, int k);
};

