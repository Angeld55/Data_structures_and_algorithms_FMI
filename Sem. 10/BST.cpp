#include "BST.h"
#include <algorithm> 
#include <string>

bool BST::contains_rec(int n, Node* currentNode, Node*& prev) 
{
	if (!currentNode)
		return false;
	if (n == currentNode->data)
	{
		return true;
	}
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
bool BST::remove_rec(int n, Node*& currentNode)
{
	Node* prev = nullptr;
	bool found = contains_rec(n, currentNode, prev);
	if (!found)
		return false;
	Node*& toDelete = prev == nullptr ? currentNode : n > prev->data ? prev->right : prev->left;
	
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
int BST::getHeight(Node* root)
{
	if (root == nullptr)
		return 0;
	return std::max(getHeight(root->left), getHeight(root->right)) + 1;
}
void BST::print()
{
	struct BST_Print
	{
		Node* currentNode;
		int spacesCount;
		bool newLineAfter;
		bool isFirstElement;
		int levelOfNode;
		void print()
		{
			if (isFirstElement) {
				std::cout << std::string(spacesCount - 2, ' ');
			}
			else {
				std::cout << std::string((spacesCount << 1) -2, ' ');
			}

			if (currentNode != nullptr)
				std::cout << currentNode->data;
			else
				std::cout << "  ";
			if (newLineAfter)
				std::cout << std::endl;
		}
	};

	int treeHeight = getHeight(root);
	int maxDigits = 2;
	int spaceForAleaf = (maxDigits<<1) + 2;// 2*digitcount for the digits of the leaf and the node above, and +2 for spacing
	int leafCount = 1 << (treeHeight - 1);
	const int INITIAL_SPACES = (spaceForAleaf* leafCount)>>1;//(leaf count * space for one leaf)/2 because we want it to be in the center

	auto spacesCountModifier = [](int i)
	{
		return i >> 1;
	};

	std::queue<BST_Print> q;

	if (treeHeight!=0)
		q.push({ root, INITIAL_SPACES, true, true, 0 });


	while (!q.empty())
	{
		BST_Print current = q.front();
		current.print();
		q.pop();
		
		if (current.levelOfNode == treeHeight - 1 && current.newLineAfter) 
			break;
		
		if (!current.currentNode)
		{
			q.push({ nullptr, spacesCountModifier(current.spacesCount), false, current.isFirstElement, current.levelOfNode + 1 });
			q.push({ nullptr, spacesCountModifier(current.spacesCount), current.newLineAfter,false, current.levelOfNode + 1 });
		}
		else
		{
			q.push({ current.currentNode->left, spacesCountModifier(current.spacesCount), false,current.isFirstElement, current.levelOfNode + 1 });
			q.push({ current.currentNode->right, spacesCountModifier(current.spacesCount), current.newLineAfter,false, current.levelOfNode + 1 });
		}
	}
}
void BST::createTreeRec(const std::vector<int>& v, int start, int end, Node*& root)
{
	if (start > end)
	{
		root = nullptr;
		return;
	}
	int mid = (start + end) / 2;
	root = new Node(v[mid]);
	createTreeRec(v, start, mid - 1, root->left);
	createTreeRec(v, mid + 1, end, root->right);
}

BST::BST(const std::vector<int>& v)
{
	if (!std::is_sorted(v.begin(), v.end()))
		throw "Array should be sorted!";
	createTreeRec(v, 0, v.size()-1, root);
}

BST::BST(const BST& other) : root(nullptr)
{
	copyFrom(other);
}

BST& BST::operator=(const BST& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

BST::~BST()
{
	free();
}

void BST::copyFrom_rec(const Node* otherNode, Node*& root)
{
	if (!otherNode)
		return;
	root = new Node(otherNode->data);

	copyFrom_rec(otherNode->left, root->left);
	copyFrom_rec(otherNode->right, root->right);
}

void BST::copyFrom(const BST& other)
{
	copyFrom_rec(other.root, root);
}

void BST::free_rec(Node* root)
{
	if (!root)
		return;

	free_rec(root->left);
	free_rec(root->right);

	delete root;
}

void BST::free()
{
	free_rec(root);
}
