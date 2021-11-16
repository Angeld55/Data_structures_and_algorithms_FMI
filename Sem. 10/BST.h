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
	
	void copyFrom_rec(const Node* otherNode, Node*& root);
	void free_rec(Node* root);

	void copyFrom(const BST& other);
	void free();
	
	bool contains_rec(int n, Node* currentNode, Node*& searched);
	void findMin(Node* root, Node*& minNode);
	bool remove_rec(int n, Node*& currentNode);
	size_t getHeight(Node* root) const;

	void createTreeRec(const std::vector<int>& v, int start, int end, Node*& root);
public:
	BST() = default;
	BST(const std::vector<int>& v);
	
	BST(const BST& other);
	BST& operator= (const BST& other);
	~BST();	

	bool insert(int n);
	bool contains(int n) const;
	bool remove(int n);
	void print() const;
};
