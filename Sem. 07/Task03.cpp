#include <iostream>
#include <string>

using namespace std;

struct Node
{
	string data;
	Node* next;

	Node(const string& data, Node* next = nullptr) : data(data), next(next)
	{}
};

void free(Node* iter)
{
	if (!iter)
		return;

	Node* first = iter;
	do
	{
		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	} while (iter != first);
}
void print(Node* iter)
{
	if (!iter)
		return;

	Node* first = iter;
	do
	{
		cout << iter->data << endl;
		iter = iter->next;
	} while (iter != first);
}

bool shouldUnite(const string& lhs, const string& rhs)
{
	if (lhs == "" || rhs == "")
		return false;

	return lhs[lhs.size() - 1] == rhs[0];
}
void absorb(Node* lhs, Node* rhs)
{
	lhs->data.append(" -> ");
	lhs->data.append(rhs->data);

	lhs->next = rhs->next;
	delete rhs;
}

void unite(Node* list)
{
	Node* first = list;
	Node* lexMin = first;

	bool shouldFinish = false;
	
	do
	{
		if (list->next == first)
			shouldFinish = true;

		if (shouldUnite(list->data, list->next->data))
			absorb(list, list->next);
		else
		{
			list = list->next;

			if (list->data < lexMin->data)
				lexMin = list;
		}
	} while (!shouldFinish);

	print(lexMin);
	free(lexMin);
}

int main()
{
	Node* f1 = new Node("street");
	Node* f2 = new Node("taxi");
	Node* f3 = new Node("ink");
	Node* f4 = new Node("dog");
	Node* f5 = new Node("smile");
	Node* f6 = new Node("eat");
	Node* f7 = new Node("tall");
	Node* f8 = new Node("pass");

	f1->next = f2;
	f2->next = f3;
	f3->next = f4;
	f4->next = f5;
	f5->next = f6;
	f6->next = f7;
	f7->next = f8;
	f8->next = f1;

	unite(f6);
}