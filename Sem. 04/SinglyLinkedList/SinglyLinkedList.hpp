#include <iostream>

template <typename T>
class LinkedList
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
	void CopyFrom(const LinkedList& other);
public:
	LinkedList();
	LinkedList(const LinkedList& other);
	LinkedList operator=(const LinkedList& other);
	~LinkedList();

	void AddLast(T); // O(1)
	void AddFirst(T);  //O(1)

	T RemoveLast(); //O(n)
	T RemoveFirst(); //O(1)

	void Print();

	T GetAtIndex(int index);

};

template <typename T>
void LinkedList<T>::Free()
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
void LinkedList<T>::CopyFrom(const LinkedList& other)
{
	Node* iter = other.head;
	while (iter != nullptr)
	{
		AddLast(iter->data);
		iter = iter->next;
	}
	
}

template <typename T>
LinkedList<T>::LinkedList()
{
	head = nullptr;
	tail = nullptr;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other)
{
	CopyFrom(other);
}

template <typename T>
LinkedList<T> LinkedList<T>::operator=(const LinkedList& other)
{
	if (this!=&other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}

template <typename T>
void LinkedList<T>::AddLast(T el)
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
void LinkedList<T>::AddFirst(T el) 
{
	Node* newNode = new Node(el);
	if (head == nullptr&&tail == nullptr)//if its empty
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		newNode->next = head;
		head = newNode;
	}
}
template <typename T>
T LinkedList<T>::RemoveLast() //O(n)
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
		Node* prev = head;
		Node* current = head->next;
		while (current != tail)
		{
			prev = prev->next;
			current = current->next;
		}
		T el = tail->data;
		delete tail;
		tail = prev;
		prev->next = nullptr;
		return el;

	}

}
template <typename T>
T LinkedList<T>::RemoveFirst()
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
void LinkedList<T>::Print()
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
T LinkedList<T>::GetAtIndex(int index)
{
	Node* res = head;
	for (int i = 0; res != nullptr&&i< index; i++)
		res = res->next;

	if (res == nullptr)
		throw "No such index";
	return res->data;
}
template <typename T>
LinkedList<T>::~LinkedList()
{
	Free();
}


