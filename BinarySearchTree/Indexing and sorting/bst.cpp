#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T>
class BST
{
private:
    struct Node
    {
        T data;
        Node* left;
        Node* right;
        size_t subtreeSize;

        Node(const T& data, Node* left = nullptr, Node* right = nullptr)
            : data(data), left(left), right(right), subtreeSize(1) {}

        static size_t getSubtreeSize(const Node* ptr)
        {
            return ptr ? ptr->subtreeSize : 0;
        }
    };

    Node* root;

    Node* insertRec(Node* node, const T& value)
    {
        if (!node)
            return new Node(value);
        else if (value < node->data)
            node->left = insertRec(node->left, value);
        else if (value > node->data)
            node->right = insertRec(node->right, value);

        node->subtreeSize = 1 + Node::getSubtreeSize(node->left) + Node::getSubtreeSize(node->right);
        return node;
    }

    const Node& getNodeByIndexRec(const Node& current, size_t index) const
    {
        size_t leftSubtreeSize = Node::getSubtreeSize(current.left);
        if (index == leftSubtreeSize)
            return current;
        else if (index < leftSubtreeSize)
            return getNodeByIndexRec(*current.left, index);
        else
            return getNodeByIndexRec(*current.right, index - leftSubtreeSize - 1);
    }

    size_t getIndexOfRec(const Node* node, const T& value) const
    {
        if (!node)
            return static_cast<size_t>(-1);
        if (value == node->data)
            return Node::getSubtreeSize(node->left);
        else if (value < node->data)
            return getIndexOfRec(node->left, value);
        else
        {
            size_t leftSize = Node::getSubtreeSize(node->left);
            size_t rightIndex = getIndexOfRec(node->right, value);
            if (rightIndex == static_cast<size_t>(-1))
                return static_cast<size_t>(-1);
            return leftSize + 1 + rightIndex;
        }
    }

    void inOrderTraversal(const Node* node, std::vector<T>& result) const
    {
        if (!node)
            return;
        inOrderTraversal(node->left, result);
        result.push_back(node->data);
        inOrderTraversal(node->right, result);
    }

public:
    BST() : root(nullptr) {}

    void insert(const T& value)
    {
        root = insertRec(root, value);
    }

    const T& operator[](size_t index) const
    {
        if (!root)
            throw std::out_of_range("BST is empty.");
        if (index >= root->subtreeSize)
            throw std::out_of_range("Index out of range.");
        return getNodeByIndexRec(*root, index).data;
    }

    size_t getIndexOf(const T& value) const
    {
        return getIndexOfRec(root, value);
    }

    std::vector<T> treeSort() const
    {
        std::vector<T> sortedResult;
        inOrderTraversal(root, sortedResult);
        return sortedResult;
    }
};

int main()
{
    BST<int> tree;
    tree.insert(5);
    tree.insert(2);
    tree.insert(7);
    tree.insert(1);
    tree.insert(3);

    std::cout << "Element at index 0: " << tree[0] << "\n";
    std::cout << "Element at index 1: " << tree[1] << "\n";
    std::cout << "Element at index 2: " << tree[2] << "\n";
    std::cout << "Element at index 3: " << tree[3] << "\n";
    std::cout << "Element at index 4: " << tree[4] << "\n";

    std::cout << "Index of value 5: " << tree.getIndexOf(5) << "\n";
    std::cout << "Index of value 7: " << tree.getIndexOf(7) << "\n";
    std::cout << "Index of value 6 (not in tree): " << tree.getIndexOf(6) << "\n";

    std::vector<int> sorted = tree.treeSort();
    std::cout << "Tree sort result: ";
    for (int x : sorted)
        std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
