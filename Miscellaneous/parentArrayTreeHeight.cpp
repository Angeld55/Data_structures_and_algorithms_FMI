#include <iostream>
#include <vector>
using namespace std;


std::vector<int> getNextLevel(const std::vector<int>& currLevel, const std::vector<int>& parentArray)
{
	std::vector<int> nextLevel;

	for (int i = 0; i < parentArray.size(); i++)
	{
		int currVertexParent = parentArray[i];
		auto it = std::find(currLevel.begin(), currLevel.end(), currVertexParent);
		if (it != currLevel.end())
			nextLevel.push_back(i);
	}
	return nextLevel;
}

int getHeight(const std::vector<int>& parentArray)
{
	std::vector<int> currentLevel = { -1 };
	int level = -1;
	while (!currentLevel.empty())
	{
		level++;
		currentLevel = getNextLevel(currentLevel, parentArray);
	}
	return level;
}

int main()
{
	std::vector<int> v= { -1,0, 1, 2 };
	cout << getHeight(v);

}
