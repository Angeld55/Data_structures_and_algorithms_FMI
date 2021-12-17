#include <iostream>
#include <queue>

template <typename T>
class BST
{
	struct Node
	{
		Node(const T& data) :dataPtr(new T(data)), left(nullptr), right(nullptr), prev(nullptr)
		{}
		T* dataPtr;
		Node* left;
		Node* right;
		Node* prev;

		Node(const Node& other)
		{
			copy(other);
		}

		Node& operator=(const Node& other)
		{
			if (this != &other)
			{
				free();
				copy(other);
			}
			return *this;
		}

		~Node()
		{
			free();
		}

		void swap(Node& other)
		{
			std::swap(dataPtr, other.dataPtr);
		}

	private:
		void copy(const Node& other)
		{
			dataPtr = new T(other.dataPtr);
		}

		void free()
		{
			delete dataPtr;
		}
	};
	
	Node* root = nullptr;
	
	void copyFrom_rec(const Node* otherNode, Node*& root);
	void free_rec(Node* root);

	void copyFrom(const BST& other);
	void free();
	
	bool contains_rec(const T& n, Node* currentNode, Node*& searched);
	void findMin(Node* root, Node*& minNode);
	bool remove_rec(const T& n, Node*& currentNode);
	size_t getHeight(Node* root) const;

	void createTreeRec(const std::vector<int>& v, int start, int end, Node*& root);
public:
	BST() = default;
	BST(const std::vector<int>& v);
	
	BST(const BST& other);
	BST& operator= (const BST& other);
	~BST();	

	bool isEmpty() const;
	bool insert(const T& n);
	bool contains(const T& n) const;
	bool remove(const T& n);
	void print() const;
};

template <typename T>
bool BST<T>::isEmpty() const
{
	return root == nullptr;
}


template <typename T>
bool BST<T>::contains_rec(const T& n, Node* currentNode, Node*& prev)
{
	if (!currentNode)
		return false;
	if (n == *(currentNode->dataPtr))
	{
		return true;
	}
	prev = currentNode;
	if (n > *(currentNode->dataPtr))
		return contains_rec(n, currentNode->right, prev);
	return contains_rec(n, currentNode->left, prev);
}

template <typename T>
bool BST<T>::contains(const T& n) const
{
	Node* temp;
	return contains_rec(n, root, temp);
}

template <typename T>
bool BST<T>::insert(const T& n)
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

	Node* newCreated = new Node(n);
	if (n > *(prev->dataPtr))
		prev->right = newCreated;
	
	else
		prev->left = newCreated;
	
	newCreated->prev = prev;

	return true;
}

template <typename T>
void BST<T>::findMin(Node* root, Node*& minNode)
{
	Node* iter = root;
	while (iter != nullptr)
	{
		minNode = iter;
		iter = iter->left;
	}
}


template <typename T>
bool BST<T>::remove_rec(const T& n, Node*& currentNode)
{
	Node* prev = nullptr;
	bool found = contains_rec(n, currentNode, prev);
	if (!found)
		return false;
	Node*& toDelete = prev == nullptr ? currentNode : n > *(prev->dataPtr) ? prev->right : prev->left;

	if (!toDelete->left && !toDelete->right)
	{
		delete toDelete;
		toDelete = nullptr;
	}
	else if (!toDelete->left || !toDelete->right)
	{
		Node* newChild = toDelete->right == nullptr ? toDelete->left : toDelete->right;
		newChild->prev = toDelete->prev;
		delete toDelete;
		toDelete = newChild;
	}
	else
	{
		Node* min;
		findMin(toDelete->right, min);
		toDelete->swap(*min);
		return remove_rec(n, min->prev == toDelete ? toDelete->right : min->prev->left); //so we change the pointer for the parent!
	}
	return true;
}

template <typename T>
bool BST<T>::remove(const T& n)
{
	return remove_rec(n, root);
}

template <typename T>
size_t BST<T>::getHeight(Node* root) const
{
	if (root == nullptr)
		return 0;
	return std::max(getHeight(root->left), getHeight(root->right)) + 1;
}

template <typename T>
void BST<T>::print() const
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
				std::cout << std::string((spacesCount << 1) - 2, ' ');
			}

			if (currentNode != nullptr)
				std::cout << *(currentNode->dataPtr);
			else
				std::cout << "  ";
			if (newLineAfter)
				std::cout << std::endl;
		}
	};

	int treeHeight = getHeight(root);
	int maxDigits = 2;
	int spaceForAleaf = (maxDigits << 1) + 2;// 2*digitcount for the digits of the leaf and the node above, and +2 for spacing
	int leafCount = 1 << (treeHeight - 1);
	const int INITIAL_SPACES = (spaceForAleaf * leafCount) >> 1;//(leaf count * space for one leaf)/2 because we want it to be in the center

	auto spacesCountModifier = [](int i)
	{
		return i >> 1;
	};

	std::queue<BST_Print> q;

	if (treeHeight != 0)
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

template <typename T>
void BST<T>::createTreeRec(const std::vector<int>& v, int start, int end, Node*& root)
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

template <typename T>
BST<T>::BST(const std::vector<int>& v)
{
	if (!std::is_sorted(v.begin(), v.end()))
		throw "Array should be sorted!";
	createTreeRec(v, 0, v.size() - 1, root);
}

template <typename T>
BST<T>::BST(const BST& other) : root(nullptr)
{
	copyFrom(other);
}


template <typename T>
BST<T>& BST<T>::operator=(const BST& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
BST<T>::~BST()
{
	free();
}

template <typename T>
void BST<T>::copyFrom_rec(const Node* otherNode, Node*& root)
{
	if (!otherNode)
		return;
	root = new Node(*(otherNode->dataPtr));

	copyFrom_rec(otherNode->left, root->left);
	copyFrom_rec(otherNode->right, root->right);
}

template <typename T>
void BST<T>::copyFrom(const BST& other)
{
	copyFrom_rec(other.root, root);
}

template <typename T>
void BST<T>::free_rec(Node* root)
{
	if (!root)
		return;

	free_rec(root->left);
	free_rec(root->right);

	delete root;
}


template <typename T>
void BST<T>::free()
{
	free_rec(root);
}
