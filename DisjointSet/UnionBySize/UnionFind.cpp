#include "UnionFind.h"
#include <algorithm>

UnionFind::UnionFind(int n) : parent(n), sizes(n, 1)
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

    if (sizes[root1] < sizes[root2])
    {
        parent[root1] = root2;
        sizes[root2] += sizes[root1];
    }
    else
    {
        parent[root2] = root1;
        sizes[root1] += sizes[root2];
    }

    return true;
}
