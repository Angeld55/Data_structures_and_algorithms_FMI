#include "Union-find.h"

UnionFind::UnionFind(int n) : parent(n), sizes(n)
{
	for (int i = 0; i < n; i++)
	{
		parent[i] = i;
		sizes[i] = 1;
	}
}
int UnionFind::getRoot(int n)
{
	while (parent[n] != n)
		n = parent[n];
	return n;
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
		return false;
	if (sizes[root1] > sizes[root2])
		std::swap(root1, root2);

	parent[root1] = root2;
	sizes[root2] += sizes[root1];
	return true;
}
