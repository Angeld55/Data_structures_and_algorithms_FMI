#include "UnionFind.h"

UnionFind::UnionFind(int n) : parent(n), height(n, 0)
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
    }
}

int UnionFind::getRoot(int n)
{
    if (parent[n] != n)
    {
        parent[n] = getRoot(parent[n]);
    }
    return parent[n];
}

bool UnionFind::areInOneSet(int n, int k)
{
    return getRoot(n) == getRoot(k);
}

bool UnionFind::Union(int n, int k)
{
    int root1 = getRoot(n);
    int root2 = getRoot(k);

    if (root1 == root2)
    {
        return false;
    }

    if (height[root1] < height[root2])
    {
        parent[root1] = root2;
    }
    else if (height[root1] > height[root2])
    {
        parent[root2] = root1;
    }
    else
    {
        parent[root2] = root1;
        height[root1]++;
    }

    return true;
}
