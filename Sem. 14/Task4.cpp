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
    
}
