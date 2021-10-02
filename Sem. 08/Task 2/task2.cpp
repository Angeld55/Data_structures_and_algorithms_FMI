#include <iostream>
using namespace std;

struct Node
{
	Node* next;
	int value;
	Node(int value, Node* next) : value(value), next(next){}
};
// 99 3 -3  6 -10 4 8 6 2 -8
Node* FilterSumZero(Node* begin)
{
	Node* iter = begin;
	stack<Node*> st;

	while (iter != nullptr)
	{
		stack<Node*> stCopy = st;
		int currentSum = iter->value;

		bool deleted = false;
		while (!stCopy.empty())
		{
			Node* temp = stCopy.top();
			stCopy.pop();
			currentSum += temp->value;


			if (currentSum == 0)
			{
				deleted = true;
				if (temp == begin)
				{
					begin = iter->next;
					iter = begin;
				}
				else
				{
					stCopy.top()->next = iter->next;
					iter = iter->next;
				}
				int deletedCount = 0;
				while (temp != iter)
				{
					Node* toDelete = temp;
					temp = temp->next;
					deletedCount++;
					delete toDelete;
				}
				for (int i = 0; i < deletedCount - 1; i++)
					st.pop();
				break;
			}

		}
		if (!deleted)
		{
			st.push(iter);
			iter = iter->next;
		}
	}
	return begin;

}
void Print(Node* list)
{
	while (list != nullptr)
	{
		cout << list->value << " ";
		list = list->next;
	}
}
int main()
{
	Node* list = new Node(99, new Node(3, new Node(-3, new Node(6, new Node(-10, new Node(4, new Node(8, new Node(6, new Node(2, new Node(-8, nullptr))))))))));
	Print(FilterSumZero(list));
}