#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template <typename T>
struct NodeFull
{
	T data;
	vector<NodeFull<T>*> children;

	NodeFull(T data) : data(data) {}
};
template <typename T>
void print(NodeFull<T>* root)
{
	cout << root->data << " ";

	for (int i = 0; i < root->children.size(); i++)
		print(root->children[i]);
}
template <typename T>
void free(NodeFull<T>* root)
{
	for (int i = 0; i < root->children.size(); i++)
		free(root->children[i]);

	delete root;
}


// Задача 1: Да се напише функция, която приема произволно дърво и връща дали дадено число се съдържа в него.
template <typename T>
bool contains(NodeFull<T>* root, T element)
{
	int size = root->children.size();

	if (root->data == element)
		return true;

	for (int i = 0; i < size; i++)
	{
		if (contains(root->children[i], element))
			return true;
	}
	return false;
}

// Задача 2: Да се напише функция, която приема произволно дърво и връща сумата на елементите в него.
template <typename T>
int sum(NodeFull<T>* root)
{
	int sum = root->data;

	for (int i = 0; i < root->children.size(); i++)
		sum += sum(root->children[i]);
	return sum;
}

// Задача 3: Да се напише функция, която приема произволно дърво и връща най-големият елемент в него.
template <typename T>
T maxT(NodeFull<T>* root)
{
	T maxEl = root->data;

	for (int i = 0; i < root->children.size(); i++)
		maxEl = max(maxEl, maxT(root->children[i]));
	return maxEl;
}

// Задача 4: Да се напише функция, която приема произволно дърво и връща височината му.
template <typename T>
int height(NodeFull<T>* root)
{
	int maxHeight = -1;

	for (int i = 0; i < root->children.size(); i++)
	{
		int currHeight = height(root->children[i]);
		if (currHeight > maxHeight)
			maxHeight = currHeight;
	}
	return maxHeight + 1;
}

// Задача 5: Да се напише функция, която приема произволно дърво и връща броя на елементите му.
template <typename T>
int getNumOfElements(NodeFull<T>* root)
{
	int numOfElements = 1;

	for (int i = 0; i < root->children.size(); i++)
		numOfElements += getNumOfElements(root->children[i]);
	return numOfElements;
}

// Задача 6: Да се напише функция, която приема произволно дърво с n върха и проверява дали 
// числата от 1 до n се срещат точно веднъж в дървото.
bool markOccurances(NodeFull<int>* root, vector<bool>& nums, int n)
{
	if (root->data < 1 || root->data > n)
		return false;
	if (nums[root->data - 1])
		return false;

	nums[root->data - 1] = true;
	for (int i = 0; i < root->children.size(); i++)
	{
		if (!markOccurances(root->children[i], nums, n))
			return false;
	}
	return true;
}
bool isPermutation(NodeFull<int>* root)
{
	int size = getNumOfElements(root);
	vector<bool> nums(size);

	return markOccurances(root, nums, size);
}

// Задача 7: Да се напише функция, която приема произволно дърво, чиито елементи са символи и цяло число к 
// и отпечатва думата на к - тото ниво на дървото.
string word(NodeFull<char>* root, int k)
{
	string wordOnLevel;

	if (root == nullptr)
		return "";
	if (k == 1)
		return wordOnLevel + (char)root->data;

	for (int i = 0; i < root->children.size(); i++)
		wordOnLevel += word(root->children[i], k - 1);
	return wordOnLevel;
}

// Задача 8: Да се напише функция, която приема произволно дърво и връща всички думи, които са получени от корена до някое листо.
void fillWords(NodeFull<char>* root, vector<string>& v, string currentWord)
{
	currentWord += root->data;
	if (root->children.size() == 0)
	{
		v.push_back(currentWord);
		return;
	}

	for (int i = 0; i < root->children.size(); i++)
		fillWords(root->children[i], v, currentWord);
}

// Задача 9: Да се напише функция, която приема произволно дърво и връща сумата на листата.
template<typename T>
T sumOfLeaves(NodeFull<T>* root)
{
	int sum = 0;
	if (root->children.size() == 0)
		return root->data;

	for (int i = 0; i < root->children.size(); i++)
		sum += sumOfLeaves(root->children[i]);
	return sum;
}

// Задача 10: Напишете фунцкия, която намира максималната разклоненост(брой деца) на дърво.
template <typename T>
int getNumOfLeaves(NodeFull<T>* root)
{
	int numOfLeaves = 0;
	if (root->children.empty())
		numOfLeaves++;

	for (int i = 0; i < root->children.size(); i++)
		numOfLeaves += getNumOfLeaves(root->children[i]);

	return numOfLeaves;
}
template <typename T>
int maxBranching(NodeFull<T>* root)
{
	int maxBranching = 1;
	int tempBranching = 0;

	for (int i = 0; i < root->children.size(); i++)
		tempBranching = getNumOfLeaves(root->children[i]);

	if (tempBranching > maxBranching)
		maxBranching = tempBranching;

	return maxBranching;
}


int main()
{
	NodeFull<int>* root = new NodeFull<int>(1);

	(root->children).push_back(new NodeFull<int>(2));
	(root->children).push_back(new NodeFull<int>(3));
	(root->children).push_back(new NodeFull<int>(4));
	(root->children[0]->children).push_back(new NodeFull<int>(5));
	(root->children[1]->children).push_back(new NodeFull<int>(6));
	(root->children[1]->children[0]->children).push_back(new NodeFull<int>(7));
	(root->children[2]->children).push_back(new NodeFull<int>(8));
	(root->children[2]->children).push_back(new NodeFull<int>(10));
}
