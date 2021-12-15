#pragma once
#include <iostream>
#include <vector>

template <typename T>
class PriorityQueue
{
	template <typename T>
	struct Node
	{

		Node(const T& data, size_t timeStamp) : data(data), timeStamp(timeStamp){}

		T data;
		size_t timeStamp;

		bool operator>(const Node& other) const
		{
			// !(data < other.data) && !(data < other.data && other.data < data)

			if (!(data < other.data) && ((data < other.data)  || (other.data < data) ))
				return true;

			else if (other.data == data)
				return timeStamp < other.timeStamp;

			return false;
		}
	};

	size_t objectTimestamp = 0;

	size_t leftChild(size_t i) const;
	size_t rightChild(size_t i) const;
	int parent(int i) const;

	void heapify(size_t ind);
	std::vector<Node<T>*> data;

	void free();
	void copyFrom(const PriorityQueue<T> other);


	void print_rec(size_t elIndex, size_t spaces) const;
public:
	PriorityQueue() = default;
	PriorityQueue(const std::vector<T>& v);

	PriorityQueue(const PriorityQueue<T>& other);
	PriorityQueue<T>& operator= (const PriorityQueue<T>& other);
	~PriorityQueue();

	bool isEmpty() const;
	const T& peek() const;
	void pop(); //Връща най-големият елемент.
	void insert(const T& el);
	void print() const;
};

template <typename T>
size_t PriorityQueue<T>::leftChild(size_t i) const
{
	return 2 * i + 1;
}

template <typename T>
size_t PriorityQueue<T>::rightChild(size_t i) const
{
	return 2 * i + 2;
}

template <typename T>
int PriorityQueue<T>::parent(int i) const
{
	return (i - 1) / 2;
}

template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
	return data.empty();
}

template <typename T>
void PriorityQueue<T>::pop()
{
	if (isEmpty())
		throw std::runtime_error("Empty queue!");

	delete data[0];

	data[0] = data[data.size() - 1]; // Новият корен става последен елемент.
	data.pop_back();

	if (data.size() != 0)
		heapify(0); // Коренът започва да се "спуска" надолу, за да се запази пирамидалното свойство.
}

template <typename T>
const T& PriorityQueue<T>::peek() const
{
	if (isEmpty())
		throw std::runtime_error("Empty queue!");
	return data[0]->data;
}

//Функция, която "спуска елемент". Елементът ако има ляво поддърво, което е пирамида и дясно поддърво, което е пирамида, образува нова пирамида, обединявайки двете + корена.
template <typename T>
void PriorityQueue<T>::heapify(size_t ind)
{
	int currentElementIndex = ind;
	while (true)
	{
		int leftChildIndex = leftChild(currentElementIndex);
		int rightChildIndex = rightChild(currentElementIndex);

		//Проверяваме дали има ляв/десен наследник и дали той е по-голям от текущия елемент.
		bool shouldGoLeft = leftChildIndex < data.size() && *data[leftChildIndex] > *data[currentElementIndex];
		bool shouldGoRight = rightChildIndex < data.size() && *data[rightChildIndex] > *data[currentElementIndex];


		if (shouldGoLeft && shouldGoRight)
		{
			//Ако и двата наследника са по-големи, се "спускаме" към по големия.
			if (*data[leftChildIndex] > *data[rightChildIndex])
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

template <typename T>
void PriorityQueue<T>::insert(const T& el)
{
	Node<T>* newElement = new Node<T>(el, objectTimestamp++);

	data.push_back(newElement);
	int ind = data.size() - 1;
	int parentIndex = parent(ind);

	//Елементът е поставен на дъното на пирамидата и той се опитва да "изплува" нагоре, докато родителят е по-малък от него.
	while (ind >= 0 && *data[ind] > *data[parentIndex])
	{
		std::swap(data[ind], data[parentIndex]);
		ind = parentIndex;
		parentIndex = parent(ind);
	}


}

template <typename T>
PriorityQueue<T>::PriorityQueue(const std::vector<T>& v)  // O(n)
{
	for (unsigned i = 0; i < v.size(); i++)
		data.push_back(new Node<T>(v[i], objectTimestamp++));

	for (int i = v.size() / 2 - 1; i >= 0; i--)
		heapify(i);
}

template <typename T>
void PriorityQueue<T>::print() const
{
	print_rec(0, 0);
}

template <typename T>
void PriorityQueue<T>::print_rec(size_t elIndex, size_t space) const
{
	const int SPACES_COUNT = 10;
	if (elIndex >= data.size())
		return;

	space += SPACES_COUNT;
	print_rec(rightChild(elIndex), space);
	std::cout << std::endl;

	for (int i = SPACES_COUNT; i < space; i++)
		std::cout << " ";
	std::cout << (*data[elIndex]).data << "\n";

	print_rec(leftChild(elIndex), space);
}

template <typename T>
void PriorityQueue<T>::free()
{
	for (unsigned i = 0; i < data.size(); i++)
		delete data[i];
	objectTimestamp = 0;
}

template <typename T>
void PriorityQueue<T>::copyFrom(const PriorityQueue<T> other)
{
	objectTimestamp = other.objectTimestamp;

	for (unsigned i = 0; i < other.data.size(); i++)
		data.push_back(new Node<T>(other.data[i]));
}

template <typename T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& other)
{
	copyFrom(other);
}

template <typename T>
PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
	free();
}
