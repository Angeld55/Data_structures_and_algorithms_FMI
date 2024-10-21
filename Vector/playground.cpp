#include "vector/vector.hpp"
#include <algorithm>
int main() 
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);

	std::find(v1.begin(), v1.end());
}