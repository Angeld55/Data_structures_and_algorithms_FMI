#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node
{
	Node(int value) : value(value) {}

	int value;
	vector<Node*> children;
};
void getLongestPrettyPath(Node* root, vector<int>& path)
{
	path.push_back(root->value);

	vector<int> maxPath;
	for (int i = 0; i < root->children.size(); i++)
	{
		if (root->children[i]->value == 0 || root->value % root->children[i]->value != 0)
			continue;

		vector<int> subPath;

		getLongestPrettyPath(root->children[i], subPath);
		if (subPath.size() > maxPath.size())
			maxPath = subPath;
	}
	path.insert(path.end(), make_move_iterator(maxPath.begin()), make_move_iterator(maxPath.end()));
}

int main()
{
	Node* root = new Node(32);

	root->children.push_back(new Node(8));
	root->children.push_back(new Node(9));
	root->children.push_back(new Node(16));

	root->children[0]->children.push_back(new Node(4));
	root->children[0]->children.push_back(new Node(7));
	root->children[0]->children.push_back(new Node(2));

	root->children[0]->children[2]->children.push_back(new Node(0));

	root->children[2]->children.push_back(new Node(1));
	root->children[2]->children.push_back(new Node(4));

	root->children[2]->children[0]->children.push_back(new Node(1));
	root->children[2]->children[1]->children.push_back(new Node(3));

	vector<int> path;
	getLongestPrettyPath(root, path);
	for (int i = 0; i < path.size(); i++)
		cout << path[i] << " ";
}