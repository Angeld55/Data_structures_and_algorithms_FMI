#include "PriorityQueue.h"

int PriorityQueue::leftChild(int i)
{
	return 2 * i + 1;
}
int PriorityQueue::rightChild(int i)
{
	return 2 * i + 2;
}
int PriorityQueue::parent(int i)
{
	return (i - 1) / 2;
}
int PriorityQueue::get()
{
	int toReturn = data[0];
	data[0] = data[data.size() - 1];
	data.pop_back();
	heapify(0);
	return toReturn;
}
void PriorityQueue::heapify(int ind)
{
	int currentElementIndex = ind;
	while (true)
	{
		int leftChildIndex = leftChild(currentElementIndex);
		int rightChildIndex = rightChild(currentElementIndex);

		bool shouldGoLeft = leftChildIndex < data.size() && data[leftChildIndex] > data[currentElementIndex];
		bool shouldGoRight = rightChildIndex < data.size() && data[rightChildIndex] > data[currentElementIndex];


		if (shouldGoLeft && shouldGoRight)
		{
			if (data[leftChildIndex] > data[rightChildIndex])
			{
				std::swap(data[currentElementIndex], data[leftChildIndex]);
				currentElementIndex = leftChildIndex;
			}
			else
			{
				std::swap(data[currentElementIndex], data[rightChildIndex]);
				currentElementIndex = rightChildIndex;
			}
		}
		else if (shouldGoLeft)
		{
			std::swap(data[currentElementIndex], data[leftChildIndex]);
			currentElementIndex = leftChildIndex;
		}
		else if (shouldGoRight)
		{
			std::swap(data[currentElementIndex], data[rightChildIndex]);
			currentElementIndex = rightChildIndex;
		}
		else
			break;
	}

}

void PriorityQueue::insert(int el)
{
	data.push_back(el);
	int ind = data.size() - 1;
	int parentIndex = parent(ind);

	while (ind >= 0 && data[ind] > data[parentIndex])
	{
		std::swap(data[ind], data[parentIndex]);
		ind = parentIndex;
		parentIndex = parent(ind);
	}


}

PriorityQueue::PriorityQueue(const std::vector<int>& v)  // O(n)
{
	data = v;
	for (int i = v.size() / 2; i >= 0; i--)
		heapify(i);
}
void PriorityQueue::print()
{
	print_rec(0, 0);
}
void PriorityQueue::print_rec(int elIndex, int space)
{
	const int SPACES_COUNT = 10;
	if (elIndex >= data.size())
		return;

	space += SPACES_COUNT;
	print_rec(rightChild(elIndex), space);
	std::cout << std::endl;

	for (int i = SPACES_COUNT; i < space; i++)
		std::cout << " ";
	std::cout << data[elIndex] << "\n";

	print_rec(leftChild(elIndex), space);
}