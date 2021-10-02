
#include <iostream>
#include <string>
using namespace std;

struct  Node
{
	Node(const string& text) : text(text), next(nullptr){}
	string text;
	Node* next;
};
void Print(Node* list)
{
	Node* iter = list;
	do
	{
		cout << iter->text << endl;
		iter = iter->next;
	} while (iter != list);
}
bool shouldUnite(const string& lhs, const string& rhs)
{
	if (lhs == "" || rhs == "")
		return false;
	return lhs[lhs.size() - 1] == rhs[0];
}
void absorb(Node* first, Node* second)
{
	first->text += "-" + second->text;
	first->next = second->next;
	delete second;
}
void Free(Node* list)
{
	Node* iter = list;
	do
	{
		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	} while (iter != list);
}
void unite(Node* list)
{
	Node* iter = list;
	
	Node* lexMin = list;

	bool shouldFinish = false;
	while (!shouldFinish)
	{
		if (strcmp(iter->text.c_str(), lexMin->text.c_str()) < 0)
			lexMin = iter;

		Node* next = iter->next;
		if (next == list)
			shouldFinish = true;
		if (iter != next && shouldUnite(iter->text, next->text))
				absorb(iter, next);
		else
			iter = iter->next;
		
	}
	Print(lexMin);
	Free(lexMin);
}


//  pass-street-taxi-inc -> dog -> smile-eat-tall ->  
int main()
{

	//Node* f1 = new Node("street");
	//Node* f2 = new Node("taxi");
	//Node* f3 = new Node("inc");
	//Node* f4 = new Node("dog");
	//Node* f5 = new Node("smile");
	//Node* f6 = new Node("eat");
	//Node* f7 = new Node("tall");
	//Node* f8 = new Node("pass");

	//f1->next = f2;
	//f2->next = f3;
	//f3->next = f4;
	//f4->next = f5;
	//f5->next = f6;
	//f6->next = f7;
	//f7->next = f8;
	//f8->next = f1;

	Node* f1 = new Node("abc");
	Node* f2 = new Node("cbd");
	Node* f3 = new Node("dba");
	f1->next = f2;
	f2->next = f3;
	f3->next = f1;

	unite(f1);
}