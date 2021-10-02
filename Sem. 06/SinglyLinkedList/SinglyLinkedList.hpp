#include <iostream>

template <typename T>
class SinglyLinkedList
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
	void copyFrom(const SinglyLinkedList& other);

public:
	SinglyLinkedList();
	SinglyLinkedList(const SinglyLinkedList& other);
	SinglyLinkedList operator=(const SinglyLinkedList& other);
	~SinglyLinkedList();

	void pushBack(const T&); 
	void pushFront(const T&); 

	T popLast();
	T popFront();

	void print() const;


	class SLinkedIterator
	{
		Node* currentElementPtr;

		friend class SinglyLinkedList;
	public:

		typedef std::forward_iterator_tag iterator_category;

		SLinkedIterator(Node* currentElementPtr = nullptr) : currentElementPtr(currentElementPtr) {}

		T& operator*()
		{
			return currentElementPtr->data;
		}

		T* operator->()
		{
			return &currentElementPtr->data;
		}

		SLinkedIterator& operator++()
		{
			if (currentElementPtr)
				currentElementPtr = currentElementPtr->next;
			return *this;
		}

		SLinkedIterator operator++(int)
		{
			SLinkedIterator copy(*this);
			++(*this);
			return copy;
		}

		SLinkedIterator& operator+=(size_t s)
		{

			while (s--)
				++(*this);

			return *this;
		}

		SLinkedIterator operator+(int i) const
		{

			SLinkedIterator res(*this);
			return res += i;
		}

		bool operator==(const SLinkedIterator& rhs) const { return currentElementPtr == rhs.currentElementPtr; }
		bool operator!=(const SLinkedIterator& rhs) const { return !(rhs == *this); }

	};
	SLinkedIterator begin()
	{
		return SLinkedIterator(head);
	}
	SLinkedIterator end()
	{
		return SLinkedIterator(nullptr);
	}

	SLinkedIterator insertAfter(const T& element, const SLinkedIterator& it);
	SLinkedIterator removeAfter(const SLinkedIterator& it);

};

template <typename T>
void SinglyLinkedList<T>::free()
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
void SinglyLinkedList<T>::copyFrom(const SinglyLinkedList& other)
{
	Node* iter = other.head;
	while (iter != nullptr)
	{
		pushBack(iter->data);
		iter = iter->next;
	}
	
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList()
{
	head = nullptr;
	tail = nullptr;
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList& other)
{
	copyFrom(other);
}

template <typename T>
SinglyLinkedList<T> SinglyLinkedList<T>::operator=(const SinglyLinkedList& other)
{
	if (this!=&other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
void SinglyLinkedList<T>::pushBack(const T& el)
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
void SinglyLinkedList<T>::pushFront(const T& el) 
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
T SinglyLinkedList<T>::popLast() //O(n)
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
T SinglyLinkedList<T>::popFront()
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
typename SinglyLinkedList<T>::SLinkedIterator SinglyLinkedList<T>::insertAfter(const T& element, const typename SinglyLinkedList<T>::SLinkedIterator& it)
{
	Node* newNode = new Node(element);
	Node* itNode = it.currentElementPtr;

	newNode->next = itNode->next;
	itNode->next = newNode;

	return SinglyLinkedList<T>::SLinkedIterator(newNode);
}


template <typename T>
typename SinglyLinkedList<T>::SLinkedIterator SinglyLinkedList<T>::removeAfter(const typename SinglyLinkedList<T>::SLinkedIterator& it)
{
	Node* toDelete = (it + 1).currentElementPtr;

	Node* newNext = toDelete == nullptr ? nullptr : toDelete->next;

	it.currentElementPtr->next = newNext;
	return SinglyLinkedList<T>::SLinkedIterator(newNext);

}

template <typename T>
void SinglyLinkedList<T>::print() const
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
SinglyLinkedList<T>::~SinglyLinkedList()
{
	free();
}


