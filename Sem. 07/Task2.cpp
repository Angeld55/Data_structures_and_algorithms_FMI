
#include <iostream>
#include <string>
using namespace std;

struct SNode
{
	SNode(int digit, SNode* next) : next(next), digit(digit){}

	SNode* next = nullptr;
	int digit;
};
struct  DNode
{
	DNode(SNode* number) : number(number) {}

	SNode* number;

	DNode* next;
	DNode* prev;
};

int eval(SNode* first)
{
	SNode* iter = first;
	int result = 0;

	while (iter != nullptr)
	{
		(result *= 10) += iter->digit;
		iter = iter->next;
	}
	return result;
}
DNode* findMid(DNode* list)
{
	DNode* slow = list;
	DNode* fast = list;

	while (fast != nullptr)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}
bool isIncreasingOrDecreasing(DNode* first, DNode* last, bool Increasing)
{
	DNode* iter = first;

	while (iter != last && iter->next != nullptr)
	{
		DNode* next = iter->next;
		if (Increasing && eval(iter->number) >= eval(next->number))
			return false;
		if (!Increasing && eval(iter->number) <= eval(next->number))
			return false;
		iter = iter->next;

	}
	return true;
}
bool task(DNode* list)
{
	DNode* mid = findMid(list);

	return isIncreasingOrDecreasing(list, mid->prev, true)
		&& isIncreasingOrDecreasing(mid, nullptr, false);

}
void Free(SNode* list)
{
	SNode* iter = list;
	while (iter != nullptr)
	{
		SNode* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}
}
void Free(DNode* list)
{
	DNode* iter = list;
	while (iter != nullptr)
	{
		Free(iter->number);
		DNode* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}
}
//  pass-street-taxi-inc -> dog -> smile-eat-tall ->  
int main()
{
	SNode* l1 = new SNode(3, new SNode(4, new SNode(1, nullptr)));


	SNode* l2 = new SNode(5, new SNode(5, new SNode(1, new SNode(4,nullptr))));
	SNode* l3 = new SNode(9, new SNode(9, new SNode(9, new SNode(9, nullptr))));

	SNode* l4 = new SNode(9, new SNode(5, new SNode(2, new SNode(9, nullptr))));
	SNode* l5 = new SNode(9, new SNode(9, new SNode(4, new SNode(4, nullptr))));
	SNode* l6 = new SNode(3, new SNode(4,nullptr));

	DNode* d1 = new DNode(l1);
	DNode* d2 = new DNode(l2);
	DNode* d3 = new DNode(l3);//s
	DNode* d4 = new DNode(l4);
	DNode* d5 = new DNode(l5);//f
	DNode* d6 = new DNode(l6);
	d1->prev = nullptr;
	d1->next = d2;
	d2->prev = d1;
	d2->next = d3;
	d3->prev = d2;
	d3->next = d4;
	d4->next = d5;
	d4->prev = d3;
	d5->next = d6;
	d5->prev = d4;
	d6->prev = d5;
	d6->next = nullptr;

	cout << task(d1);

	Free(d1);
}