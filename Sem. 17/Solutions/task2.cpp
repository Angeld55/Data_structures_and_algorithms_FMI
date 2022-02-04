
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <list>
#include <unordered_map>
#include <iterator>
#include <algorithm>

struct Node
{
    int data;
    Node* left;
    Node* right;

    Node(int data) :data(data), left(nullptr), right(nullptr) {}
};

 void getAllLeftorientedPaths_helper(const Node* root, bool madeRightMove, std::vector<std::vector<int>>& result, std::vector<int>& path)
{
     if (root == nullptr)
     {
         return;
     }

    path.push_back(root->data);

    if (!root->left && !root->right)
    {
        result.push_back(path);
        path.pop_back();
        return;
    }

    getAllLeftorientedPaths_helper(root->left, madeRightMove, result, path);

    if (!madeRightMove)
    {
        getAllLeftorientedPaths_helper(root->right, true, result, path);
    }
    path.pop_back();
}

 std::vector<std::vector<int>> getAllLeftorientedPaths(const Node* root)
 {
     std::vector<int> path;
     std::vector<std::vector<int>> allPaths;
     getAllLeftorientedPaths_helper(root, false, allPaths, path);

     return std::move(allPaths);
}

 std::vector<std::vector<int>> filterPaths(const std::vector<std::vector<int>>& paths, bool (*fun_ptr)(const std::vector<int>& path))
 {
     std::vector<std::vector<int>> result;
     std::copy_if(paths.begin(), paths.end(), std::back_inserter(result), fun_ptr);
     return result;
 }

 void free(Node* root)
 {
     if (root == nullptr)
         return;

     free(root->left);
     free(root->right);
 }
int main()
{
    Node* root = new Node(8);
    root->left = new Node(3);
    root->right = new Node(10);
    root->left->left = new Node(1);
    root->left->right = new Node(6);

    root->left->right->left = new Node(4);
    root->left->right->right = new Node(7);

    root->right->right = new Node(14);
    root->right->right->left = new Node(13);


    auto allPaths = getAllLeftorientedPaths(root);

    auto res = filterPaths(allPaths, [](const std::vector<int>&) {return true; });


    for (size_t i = 0; i < res.size(); i++)
    {
        for (size_t j = 0; j < res[i].size(); j++)
        {
            std::cout << res[i][j] << " ";
        }

        std::cout << std::endl;
    }

    free(root);
    return 0;
}
