#include <iostream>

//We use the implementation of linked list (we only have the AddLast(T) and RemoveFirst()) 

template <typename T>
class LinkedQueue
{
	struct Node
	{
		Node(T data)
		{
			this->data = data;
			next = nullptr;
		}
		T data;
		Node* next;
	};
	Node* head;
	Node* tail;

	void Free();
	void CopyFrom(const LinkedQueue& other);
public:
	LinkedQueue();
	LinkedQueue(const LinkedQueue& other);
	LinkedQueue operator=(const LinkedQueue& other);
	~LinkedQueue();

	void Enqueue(T); // O(1)

	T Dequeue(); //O(1)

	void Print();


};

template <typename T>
void LinkedQueue<T>::Free()
{
	Node* iter = head;
	while (iter!=nullptr)
	{
		Node* prev = iter;
		iter = iter->next;
		delete prev;
	}
}

template <typename T>
void LinkedQueue<T>::CopyFrom(const LinkedQueue& other)
{
	Node* iter = other.head;
	while (iter != nullptr)
	{
		Enqueue(iter->data);
		iter = iter->next;
	}
	
}

template <typename T>
LinkedQueue<T>::LinkedQueue()
{
	head = nullptr;
	tail = nullptr;
}

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue& other)
{
	CopyFrom(other);
}

template <typename T>
LinkedQueue<T> LinkedQueue<T>::operator=(const LinkedQueue& other)
{
	if (this!=&other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}

template <typename T>
void LinkedQueue<T>::Enqueue(T el)
{
	Node* newNode = new Node(el);
	if (head == nullptr&&tail == nullptr)//if its empty
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		tail->next = newNode;
		tail = newNode;
	}
}



template <typename T>
T LinkedQueue<T>::Dequeue()
{
	if (head == nullptr&&tail == nullptr)
		throw "The list is empty";
	else if (head == tail)
	{
		T el = head->data;
		delete head;
		head = nullptr;
		tail = nullptr;
		return el;
	}
	else
	{
		T el = head->data;
		Node* temp = head->next;
		delete head;
		head = temp;
		return el;
	}

}

template <typename T>
void LinkedQueue<T>::Print()
{
	Node* iter = head;
	while (iter != nullptr)
	{
		std::cout << iter->data;
		if (iter->next != nullptr)
			std::cout << "->";
		iter = iter->next;
	}
	std::cout << std::endl;

}
template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	Free();
}