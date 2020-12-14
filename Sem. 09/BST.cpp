#include "BST.h"
#include <algorithm> 
#include <string>
//Ако го има - prev ще бъде адресът на предишиния.
//Ако го няма - searched  е адресът на последния връх, преди позицията, която трябва да заеме този елемент.
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
	// pos е непосредствено преди правилната позиция за новия връх
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
		int levelOfNode;

		void print()
		{
			std::cout << std::string(spacesCount, ' ');
			if (currentNode != nullptr)
				std::cout << currentNode->data;
			else
				std::cout << "  ";
			if (newLineAfter)
				std::cout << std::endl;
		}
	};
	int treeHeight = getHeight(root);

	const int INITIAL_SPACES = 32;

	auto spacesCountModifier = [](int i)
	{
		return i /= 2;
	};

	std::queue<BST_Print> q;

	q.push({ root, INITIAL_SPACES, true, 0 });


	while (!q.empty())
	{
		BST_Print current = q.front();
		current.print();
		q.pop();

		if (!current.currentNode)
		{
			if (current.levelOfNode <= treeHeight)
			{
				q.push({ nullptr, spacesCountModifier(current.spacesCount), false, current.levelOfNode + 1 });
				q.push({ nullptr, spacesCountModifier(current.spacesCount), current.newLineAfter, current.levelOfNode + 1 });
			}
		}
		else
		{
			q.push({ current.currentNode->left, spacesCountModifier(current.spacesCount), false, current.levelOfNode + 1 });
			q.push({ current.currentNode->right, spacesCountModifier(current.spacesCount), current.newLineAfter, current.levelOfNode + 1 });
		}
	}
}
void BST::createTreeRec(std::vector<int> v, int start, int end, Node*& root)
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
BST::BST(std::vector<int> v)
{
	if (!std::is_sorted(v.begin(), v.end()))
		throw "Array should be sorted!";
	createTreeRec(v, 0, v.size()-1, root);
}
