#include <iostream>
#include <vector>

class PriorityQueue
{
	int leftChild(int i);
	int rightChild(int i);
	int parent(int i);

	void heapify(int ind);
	std::vector<int> data;

	void print_rec(int elIndex, int spaces) const;
public:
	PriorityQueue() = default;
	PriorityQueue(const std::vector<int>& v);

	int get() const; //Връща най-големият елемент.
	void insert(int el);
	void print() const;
};
