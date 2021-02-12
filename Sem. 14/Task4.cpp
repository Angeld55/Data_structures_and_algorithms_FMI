#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

struct Node
{
	int data;
	vector<Node*> children;

	Node(int data) : data(data) {}
	
	~Node()
	{
	    for(int i = 0; i < children.size(); i++)
	        delete children[i];
	}
};

void getLongestPrettyPath(Node* root, vector<int>& path)
{
	path.push_back(root->data);
	vector<int> longestPath;

	for (int i = 0; i < root->children.size(); i++)
	{
		if (!root->children[i]->data || !root->data % root->children[i]->data)
			continue;

		vector<int> subPath;
		getLongestPrettyPath(root->children[i], subPath);

		if (subPath.size() > longestPath.size())
			longestPath = subPath;
	}

	path.insert(path.end(), longestPath.begin(), longestPath.end());
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
	
	vector<int> path;
	getLongestPrettyPath(root,path);
	
	for(int i = 0; i < path.size(); i++)
	    cout << path[i] << " ";
	
	delete root;
}
