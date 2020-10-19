#include "Collection.h"
using namespace std;

template <typename T>
class Vector : public Collection<T>
{
	T* data;
	int count;
	int capacity;
	void CopyFrom(const Vector& other);
	void Free();
	void Resize(int newCap);
public:
	Vector();
	Vector(int capacity);

	void push_back(const T& el); // O(1)
	void push_front(const T& el); // O(n)
	void insert_At(const T& el, int index); // O(n)

	T peek(int index); // O(1)

	T pop_back(); // O(1)
	T pop_front(); // O(n)
	T remove_At(int index);

	void print() const;
};

int closestPowerOfTwo(int n)
{
	n--;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	return n + 1;
}
template <typename T>
Vector<T>::Vector() : Vector(4)
{
}
template <typename T>
Vector<T>::Vector(int capacity)
{
	this->capacity = closestPowerOfTwo(capacity);
	data = new T[this->capacity];
	count = 0;
}

template <typename T>
void Vector<T>::Resize(int newCap)
{
	T* temp = new T[newCap];
	for (int i = 0; i < count; i++)
		temp[i] = data[i];
	capacity = newCap;
	delete[] data;
	data = temp;
}

template <typename T>
void Vector<T>::push_back(const T& el)
{
	if (count == capacity)
		Resize(count * 2);
	data[count++] = el;
}
template <typename T>
void Vector<T>::push_front(const T& el)
{
	if (count == capacity)
		Resize(count * 2);
	for (int i = count; i >= 1; i--)
		data[i] = data[i - 1];
	data[0] = el;
}

template <typename T>
void Vector<T>::insert_At(const T& el, int index)
{
	if (index > count)
		throw "Error! Not a valid index!";
	if (count == capacity)
		Resize(capacity * 2);

	for (int i = count; i > index; i--)
		data[i] = data[i - 1];
	data[index] = el;
	count++;

}
template <typename T>
T Vector<T>::peek(int index)
{
	if (index < 0 || index >= count)
		throw "Invalid index!";
	return data[index];
}
template <typename T>
T Vector<T>::pop_back()
{
	if (count == 0)
		throw "Empty!";
	T el = data[--count];
	if (count < capacity / 2)
		Resize(capacity / 2);
	return el;

}
template <typename T>
T Vector<T>::pop_front()
{
	if (count == 0)
		throw "Empty!";
	T el = data[0];
	for (int i = 1; i < count; i++)
		data[i - 1] = data[i];
	if (--count < capacity / 2)
		Resize(capacity / 2);
	return el;
}

template <typename T>
T Vector<T>::remove_At(int index)
{
	if (index < 0 || index >= count)
		throw "Invalid index!";
	T el = data[index];

	for (int i = index; i < count - 1; i++)
		data[i] = data[i + 1];
	if (--count < capacity / 2)
		Resize(capacity / 2);
	return el;
}
template <typename T>
void Vector<T>::print() const
{
	for (int i = 0; i < count; i++)
	{
		cout << data[i] << " ";
	}
	for (int i = count; i < capacity; i++)
		cout << "_ ";
	cout << endl;
}