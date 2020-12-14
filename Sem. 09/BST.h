#include <iostream>
#include <queue>

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
	int getHeight(Node* root);

	void createTreeRec(std::vector<int> v, int start, int end, Node*& root);
public:
	BST() = default;
	BST(std::vector<int> v);

	bool insert(int n);
	bool contains(int n);
	bool remove(int n);
	void print();
};