#include <iostream>

//Implementation without iterators (for now)
template <typename T>
class LinkedList
{
	struct Node
	{
		Node(const T& data)
		{
			this->data = data;
			next = nullptr;
		}
		T data;
		Node* next;
	};

	Node* head;
	Node* tail;

	void free();
	void copyFrom(const LinkedList& other);

public:
	LinkedList();
	LinkedList(const LinkedList& other);
	LinkedList operator=(const LinkedList& other);
	~LinkedList();

	void addLast(const T&); // O(1)
	void addFirst(const T&);  //O(1)

	T removeLast(); //O(n)
	T removeFirst(); //O(1)

	void print() const;
};

template <typename T>
void LinkedList<T>::free()
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
void LinkedList<T>::copyFrom(const LinkedList& other)
{
	Node* iter = other.head;
	while (iter != nullptr)
	{
		addLast(iter->data);
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
	copyFrom(other);
}

template <typename T>
LinkedList<T> LinkedList<T>::operator=(const LinkedList& other)
{
	if (this!=&other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
void LinkedList<T>::addLast(const T& el)
{
	Node* newNode = new Node(el);

	if (head == nullptr && tail == nullptr)//if its empty
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
void LinkedList<T>::addFirst(const T& el) 
{
	Node* newNode = new Node(el);

	if (head == nullptr && tail == nullptr)//if its empty
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
T LinkedList<T>::removeLast() //O(n)
{
	std::cout << "Warning: O(n) operation. Consider using another structure!" << std::endl;

	if (head == nullptr && tail == nullptr)
		throw std::runtime_error("The list is empty!");

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
T LinkedList<T>::removeFirst()
{
	if (head == nullptr && tail == nullptr)
		throw  std::runtime_error("The list is empty!");
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
void LinkedList<T>::print() const
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
LinkedList<T>::~LinkedList()
{
	free();
}


