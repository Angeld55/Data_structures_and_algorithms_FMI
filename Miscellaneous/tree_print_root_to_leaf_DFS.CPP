#include <iostream>
#include <vector>

struct Node
{
    char data;
    std::vector<Node*> children;
};

void printRootToLeafPaths(const Node* root, std::string& str) //DFS / str could be hidden in wrapper func
{
    str.push_back(root->data);
    if (root->children.empty())
        std::cout << str << std::endl;
    else
    {
        for (const Node* ch : root->children)
            printRootToLeafPaths(ch, str);
    }
    str.pop_back();
}
void free(Node* root)
{
    for (Node* child : root->children)
        free(child);
    delete root;
}

int main()
{
    Node* root = new Node{ 'a' };

    root->children.push_back(new Node{'b'});
    root->children.push_back(new Node{ 'c' });
    root->children.push_back(new Node{ 'd' });
    root->children.at(0)->children.push_back(new Node{ 'x' });
    root->children.at(0)->children.push_back(new Node{ 'y' });

    std::string str; 
    printRootToLeafPaths(root, str);
    free(root);
}

