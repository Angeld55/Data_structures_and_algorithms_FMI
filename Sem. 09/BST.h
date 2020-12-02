#include <iostream>


class BST
{
	struct Node
	{
		Node(int data) :data(data), left(nullptr), right(nullptr)
		{}
		int data;
		Node* left;
		Node* right;
	};
	
	Node* root = nullptr;

	bool contains_rec(int n, Node* currentNode, Node*& searched);
	void findMin(Node* root, Node*& minNode);
	bool remove_rec(int n, Node* root);
public:
	bool insert(int n);
	bool contains(int n);
	bool remove(int n);

};