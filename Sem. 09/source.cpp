#include <iostream>
#include <stack>
#include "BST.h"
using namespace std;
int main()
{
	BST bst;

	bst.insert(2);
	bst.insert(1);
	bst.insert(3);
	
	bst.remove(2);
	cout << bst.contains(2);

}
