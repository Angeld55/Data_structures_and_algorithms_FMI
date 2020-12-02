#include "BST.h"


//Ако го има - prev ще бъде адресът на предишиния.
//Ако го няма - searched  е адресът на последния връх, преди позицията, която трябва да заеме този елемент.
bool BST::contains_rec(int n, Node* currentNode, Node*& prev) 
{
	if (!currentNode)
		return false;
	if (n == currentNode->data)
		return true;
	prev = currentNode;
	if (n > currentNode->data)
		return contains_rec(n, currentNode->right, prev);
	return contains_rec(n, currentNode->left, prev);
}
bool BST::contains(int n)
{
	Node* temp;
	return contains_rec(n, root,temp);
}

bool BST::insert(int n)
{
	if (root == nullptr)
	{
		root = new Node(n);
		return true;
	}
	Node* prev = nullptr;
	bool found = contains_rec(n, root, prev);
	if (found)
		return false;
	// prev е непосредствено преди правилната позиция за новия връх
	if (n > prev->data)          
		prev->right = new Node(n);
	else
		prev->left = new Node(n);
	return true;
}

void BST::findMin(Node* root, Node*& minNode)
{
	Node* iter = root;
	while (iter != nullptr)
	{
		minNode = iter;
		iter = iter->left;
	}
}
bool BST::remove_rec(int n, Node* root)
{
	Node* prev = nullptr;
	bool found = contains_rec(n, root, prev);
	if (!found)
		return false;
	Node*& toDelete = prev == nullptr ? root : n > prev->data ? prev->right : prev->left;
	
	if (!toDelete->left && !toDelete->right)
	{
		delete toDelete;
		toDelete = nullptr;
	}
	else if (!toDelete->left || !toDelete->right)
	{
		Node* newChild = toDelete->right == nullptr ? toDelete->left : toDelete->right;
		delete toDelete;
		toDelete = newChild;
	}
	else
	{
		Node* min;
		findMin(toDelete->right, min);
		std::swap(toDelete->data, min->data);
		return remove_rec(n, toDelete->right);
	}
	return true;
}
bool BST::remove(int n)
{
	return remove_rec(n,root);
}
