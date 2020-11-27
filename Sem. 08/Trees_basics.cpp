#include <iostream>
#include <vector>
#include <string>

using namespace std;
// Éåðàðõè÷íè ñòðóêòóðè îò äàííè.
// Äúðâî.

//äâîè÷íî äúðâî

//Çàä1: Ôóíêöèÿ, êîÿòî ïðèåìà äâîè÷íî äúðâî è åëåìåíò è âðúùà äàëè åëåìåíòúò å ÷àñò îò äúðâîòî.
//
//Çàä2: Ôóíêöèÿ, êîÿòî ïðèåìà äâîè÷íî äúðâî è âðúùà ñóìàòà íà åëåìåíòèòå.
//Çàä3: Ôóíêöèÿ, êîÿòî ïðèåìà äâîè÷íî äúðâî è âðúùà ìàêñ åëåìåíò.
//Çàä4: Ôóíêöèÿ, êîÿòî ïðèåìà äâîè÷íî äúðâî è âðúùà âèñî÷èíàòà ìó.
//Çàä5: Ôóíêöèÿ, êîÿòî ïðèåìà äâîè÷íî äúðâî è âðúùà äàëè åëåìåíòèòå ñà ÷èñëàòà îò 1...n áåç äà ñå ïîâòàðÿò.
 // n - áðîé íà âúðõîâåòå â äúðâîòî

// Çàä6: Ôóíêöèÿ, êîÿòî ïðèåìà äâîè÷íî äúðâî îò ñèìâîëè. È âðúùà äóìèòå, êîèòî ñà îò êîðåíà äî âñÿêî ëèñòî

// Çàä7: Ôóíêöèÿ, êîÿòî ïðèåìà äâîè÷íî äúðâî îò ñèìâîëè è íèâî. Âðúùà äóìàòà ïîëó÷åíà îò ñèìîâîëèòå íà íèâîòî.


// Äîìàøíî : Âñè÷êè ôóíêöèè äà ãè ïðåðàáîòèòå äà ðàáîòÿò ñ NodeFull. Äúðâåòà ñ ïðîèçâîëåí áðîé íàñëåäíèöè. 

struct NodeFull
{
	int value;
	vector<NodeFull*> children;
};

struct Node
{

	
	Node(int value) :value(value), left(nullptr), right(nullptr)
	{}
	int value;
	Node* left;
	Node* right;
};
bool contains(Node* root, int elem)
{
	if (root == nullptr)
		return false;
	return root->value == elem || contains(root->left, elem) || contains(root->right, elem);
}
int sum(Node* root)
{
	if (root == nullptr)
		return 0;
	return root->value + sum(root->left) + sum(root->right);
}
int max(int a, int b)
{
	return a > b ? a : b;
}
int max(int a, int b, int c)
{
	return max(max(a, b), c);
}
int maxElementInTree(Node* root)
{
	if (root->left == nullptr && root->right == nullptr)
		return root->value;
	else if (root->left == nullptr && root->right != nullptr)
		return max(root->value, maxElementInTree(root->right));
	else if (root->left != nullptr && root->right == nullptr)
		return max(root->value, maxElementInTree(root->left));

	return max(root->value, maxElementInTree(root->left), maxElementInTree(root->right));
}
int heght(Node* root)
{
	if (root == nullptr)
		return -1;
	return 1 + max(heght(root->left), heght(root->right));
}

int countElements(Node* root)
{
	if (root == nullptr)
		return 0;
	return 1 + countElements(root->left) + countElements(root->right);
}
bool markOccurrencesHelper(Node* root, vector<bool>& temp)
{
	if (root == nullptr)
		return true;
	if (root->value < 1 || root->value > temp.size())
		return false;
	if (temp[root->value - 1]) // ïðîâåðÿâàìå çà ïîâòîðåíèå
		return false;
	temp[root->value - 1] = true;
	return markOccurrencesHelper(root->left, temp) && markOccurrencesHelper(root->right, temp);
}


void fillWords(Node* root, vector<string>& words, string currentWord)
{
	if (root == nullptr)
		return;
	if (root->left == nullptr && root->right == nullptr)
		words.push_back(currentWord + (char)root->value);
	fillWords(root->left, words, currentWord + (char)root->value);
	fillWords(root->right, words, currentWord + (char)root->value);
}
vector<string> getWords(Node* root)
{
	vector<string> result;
	fillWords(root, result, "");
	return result;
}

bool isPermutation(Node* root )
{
	vector<bool> temp(countElements(root)); // F F F F F F F F... F

	if (!markOccurrencesHelper(root, temp))
		return false;

	for (int i = 0; i < temp.size(); i++)
	{
		if (!temp[i])
			return false;
	}
	return true;
}

string getStringOnLevel(Node* root, int level)
{
	if (root == nullptr)
		return "";
	if (level == 0)
	{
		string res;
		res += (char)root->value;
		return res;
	}
	return getStringOnLevel(root->left, level - 1) + getStringOnLevel(root->right, level - 1);
}
void Free(Node* root)
{
    if(root == nullptr)
        return;
    Free(root->left);
    Free(root->right);
    delete root;
}
int main() 
{	
	// Àêî íÿêúäå èìàìå ÷èñëî, êîåòî íå å [1..n]
	Node* root = new Node('A');
	Node* n1 = new Node('B');
	Node* n2 = new Node('C');
	Node* n3 = new Node('D');
	Node* n4 = new Node('E');
	Node* n5 = new Node('F');
	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n2->left = n4;
	n2->right = n5;

	//cout << isPermutation(root);
	cout << getStringOnLevel(root, 1);
	Free(root);
	return 0;
}
 
