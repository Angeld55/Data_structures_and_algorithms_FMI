#include <iostream>

template <typename T>
class SinglyLinkedList
{
private:
	struct Node
	{
		T data;
		Node* next;

		Node(const T& data)
		{
			this->data = data;
			next = nullptr;
		}
	};

	Node* head;
	Node* tail;

public:
	SinglyLinkedList();
	SinglyLinkedList(const SinglyLinkedList<T>& other);
	SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& other);
	~SinglyLinkedList();

private:
	void copyFrom(const SinglyLinkedList<T>& other);
	void free();

public:
	void pushFront(const T& el);
	void pushBack(const T& el);

	void popFront();

	const T& front() const;
	const T& back() const;

	template <typename U>
	friend SinglyLinkedList<U> concat(SinglyLinkedList<U>& lhs, SinglyLinkedList<U>& rhs);

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
void SinglyLinkedList<T>::pushFront(const T& el)
{
	Node* newNode = new Node(el);

	if (!head)
	{
		head = tail = newNode;
		return;
	}

	newNode->next = head;
	head = newNode;
}
template <typename T>
void SinglyLinkedList<T>::pushBack(const T& el)
{
	Node* newNode = new Node(el);

	if (!tail)
	{
		head = tail = newNode;
		return;
	}

	tail->next = newNode;
	tail = newNode;
}

template <typename T>
void SinglyLinkedList<T>::popFront()
{
	if (!head)
		throw std::logic_error("Empty list!");

	if (head == tail)
	{
		delete head;
		head = tail = nullptr;
		return;
	}

	Node* toDelete = head;
	head = head->next;
	delete toDelete;
}

template <typename T>
const T& SinglyLinkedList<T>::front() const
{
	if (!head)
		throw std::logic_error("Empty list!");

	return head->data;
}

template <typename T>
const T& SinglyLinkedList<T>::back() const 
{
	if (!tail)
		throw std::logic_error("Empty list!");

	return tail->data;
}

template <typename T>
SinglyLinkedList<T> concat(SinglyLinkedList<T>& lhs, SinglyLinkedList<T>& rhs)
{
	SinglyLinkedList<T> result;

	if (!lhs.head)
	{
		result.head = rhs.head;
		result.tail = rhs.tail;
	}
	else if (!rhs.head)
	{
		result.head = lhs.head;
		result.tail = lhs.tail;
	}
	else
	{
		lhs.tail->next = rhs.head;
		result.head = lhs.head;
		result.tail = rhs.tail;
	}

	rhs.head = rhs.tail = lhs.head = lhs.tail = nullptr;

	return result;
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
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), tail(nullptr)
{}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other) : head(nullptr), tail(nullptr)
{
	copyFrom(other);
}

template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}
template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
	free();
}

template <typename T>
void SinglyLinkedList<T>::copyFrom(const SinglyLinkedList<T>& other)
{
	Node* iter = other.head;

	while (iter)
	{
		pushBack(iter->data);
		iter = iter->next;
	}
}

template <typename T>
void SinglyLinkedList<T>::free()
{
	Node* iter = head;

	while (iter)
	{
		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}
	head = tail = nullptr;
}

template <typename T>
void SinglyLinkedList<T>::print() const
{
	Node* iter = head;

	while (iter)
	{
		std::cout << iter->data << ' ';
		if (iter->next)
			std::cout << "->" << ' ';
		iter = iter->next;
	}

	std::cout << std::endl;
}
