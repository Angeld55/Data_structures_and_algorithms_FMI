#include <istream>

//Same implementation as DynamicArray. We only use PushBack and PopBack from it.

template<typename T>
class ArrayStack {

private:
	T* arr;
	size_t curSize;
	size_t capacity;

public:
	ArrayStack();
	ArrayStack(const ArrayStack<T>& other);
	ArrayStack<T>& operator=(const ArrayStack<T>& other);
	~ArrayStack();

private:
	void CopyFrom(const ArrayStack<T>& other);
	void Free();
	void Resize(size_t newCap);

public:
	void Push(const T& newElem); //add a new element in the end
	T Pop(); //removes the last element
	
	size_t GetSize() const;
};

template<typename T>
ArrayStack<T>::ArrayStack() : curSize(0), capacity(4) {
	arr = new T[capacity];
}


template<typename T>
ArrayStack<T>::ArrayStack(const ArrayStack<T>& other) {
	CopyFrom(other);
}

template<typename T>
ArrayStack<T>& ArrayStack<T>::operator=(const ArrayStack<T>& other) {

	if (this != &other) {
		Free();
		CopyFrom(other);
	}
	return *this;
}

template<typename T>
ArrayStack<T>::~ArrayStack() {
	Free();
}

template<typename T>
void ArrayStack<T>::CopyFrom(const ArrayStack<T>& other) {

	arr = new T[other.capacity];

	for (size_t i = 0; i < other.curSize; i++)
		arr[i] = other.arr[i];

	curSize = other.curSize;
	capacity = other.capacity;
}

template<typename T>
void ArrayStack<T>::Free() {
	delete[] arr;
}

template<typename T>
void ArrayStack<T>::Resize(size_t newCap) {

	T* temp = arr;
	arr = new T[newCap];
	for (size_t i = 0; i < curSize; i++)
		arr[i] = temp[i];

	capacity = newCap;
	delete[] temp;
}



template<typename T>
void ArrayStack<T>::Push(const T& newElem) {

	if (curSize >= capacity)
		Resize(capacity * 2);

	arr[curSize++] = newElem;
}

template<typename T>
T ArrayStack<T>::Pop() {

	T el = arr[curSize - 1];
	if (curSize)
		curSize--;
	else
		throw std::length_error("Already empty!");

	if (curSize * 2 <= capacity && capacity > 1)
		Resize(capacity / 2);
	return el;
}

template <typename T>
size_t ArrayStack<T>::GetSize() const
{
	return  curSize;
}

int main()
{
	ArrayStack<int> s;
	s.Push(4);
	s.GetSize();
}
