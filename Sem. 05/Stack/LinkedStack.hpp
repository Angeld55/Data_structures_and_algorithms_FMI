#include <iostream>

template <typename T>
class LinkedStack
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

	void Free();
	void CopyFrom(const LinkedStack& other);
public:
	LinkedStack();
	LinkedStack(const LinkedStack& other);
	LinkedStack operator=(const LinkedStack& other);
	~LinkedStack();


	void Push(T);  //O(1)
	T Pop(); //O(1)

	bool isEmpty() const;

};

template <typename T>
void LinkedStack<T>::Free()
{
	Node* iter = head;
	while (iter != nullptr)
	{
		Node* prev = iter;
		iter = iter->next;
		delete prev;
	}
}

template <typename T>
void LinkedStack<T>::CopyFrom(const LinkedStack& other)
{
	if (other.isEmpty())
		return;

	Node* iterOther = other.head;

	head = new Node(iterOther->data);
	Node* iterThis = head;
	do
	{
		iterOther = iterOther->next;
		if (iterOther)
		{
			iterThis->next = new Node(iterOther->data);
			iterThis = iterThis->next;
		}
	} while (iterOther);

}

template <typename T>
LinkedStack<T>::LinkedStack()
{
	head = nullptr;
}

template <typename T>
LinkedStack<T>::LinkedStack(const LinkedStack& other)
{
	CopyFrom(other);
}

template <typename T>
LinkedStack<T> LinkedStack<T>::operator=(const LinkedStack& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}


template <typename T>
void LinkedStack<T>::Push(T el)
{
	Node* newNode = new Node(el);
	if (isEmpty())
		head = newNode;
	else
	{
		newNode->next = head;
		head = newNode;
	}
}

template <typename T>
T LinkedStack<T>::Pop()
{
	if (isEmpty())
		throw "The LinkedStack is empty";
	else if (head->next==nullptr)
	{
		T el = head->data;
		delete head;
		head = nullptr;
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
bool LinkedStack<T>::isEmpty() const
{
	return head == nullptr;
}

template <typename T>
LinkedStack<T>::~LinkedStack()
{
	Free();
}