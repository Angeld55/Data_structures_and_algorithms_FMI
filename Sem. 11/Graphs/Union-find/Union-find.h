#include <iostream>
#include <vector>

class UnionFind
{
	std::vector<int> parent;
	std::vector<int> sizes;

	int getRoot(int n);
public:
	UnionFind(int n); //0...n-1
	bool areInOneSet(int n, int k);
	bool Union(int n, int k);
};