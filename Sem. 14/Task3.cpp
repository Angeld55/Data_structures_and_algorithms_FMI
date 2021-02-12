#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node
{
	Node(int value) : value(value) {}

	int value;
	vector<Node*> children;
	
	~Node()
	{
	    for(int i = 0; i < children.size(); i++)
	        delete children[i];
	}
};

bool isTreeSeenTheSameFromBothSides(Node* root, vector<int>& view)
{
	vector<Node*> currentLevel = { root };

	while (currentLevel.size() >= 1)
	{
		if (currentLevel[0]->value != currentLevel[currentLevel.size() - 1]->value)
		{
			view.clear();
			return false;
		}
		view.push_back(currentLevel[0]->value);

		vector<Node*> nextLevel;
		for (int i = 0; i < currentLevel.size(); i++)
		{
			nextLevel.insert(nextLevel.end(),
				std::make_move_iterator(currentLevel[i]->children.begin()),
				std::make_move_iterator(currentLevel[i]->children.end()));
		}
		currentLevel = nextLevel;
	}
	return true;
}
int main()
{
	Node* root = new Node(5);

	root->children.push_back(new Node(3));
	root->children.push_back(new Node(9));
	root->children.push_back(new Node(3));

	root->children[0]->children.push_back(new Node(4));
	root->children[0]->children.push_back(new Node(3));
	root->children[0]->children.push_back(new Node(7));

	root->children[0]->children[2]->children.push_back(new Node(9));

	root->children[2]->children.push_back(new Node(5));
	root->children[2]->children.push_back(new Node(4));

	root->children[2]->children[0]->children.push_back(new Node(2));
	root->children[2]->children[1]->children.push_back(new Node(9));

	vector<int> view;
	bool result = isTreeSeenTheSameFromBothSides(root, view);
	cout << result << endl << endl;
	for (int i = 0; i < view.size(); i++)
		cout << view[i] << endl;
	
	delete root;
}
