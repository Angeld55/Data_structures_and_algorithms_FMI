#pragma once

template <typename T>
class BST;

template <typename T>
void printBst(const BST<T>& bst)
{
	struct BST_Print
	{
		typename BST<T>::Node* currentNode;
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

	int treeHeight = bst.getHeight(bst.root);
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
		q.push({ bst.root, INITIAL_SPACES, true, true, 0 });


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