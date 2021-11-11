#include <iostream>
#include <vector>

using namespace std;

namespace Subsets
{
	void printBitString(const std::vector<int>& bitString)
	{
		for (int i = 0; i < bitString.size(); i++)
			cout << bitString[i] << " ";
		std::cout << std::endl;
	}
	void printSubset(const std::vector<int>& bitString, const std::vector<int>& set)
	{
		std::cout << "{";

		for (size_t i = 0; i < bitString.size(); i++)
		{
			if (bitString[i] == 1)
				std::cout << set[i] << " ";
		}
		std::cout << "}";
		std::cout << std::endl;
	}

	void generateAllBitstringsRec(const std::vector<int>& v, std::vector<int>& bitString, size_t pos)
	{
		if (pos == v.size())
		{
			printSubset(bitString, v);
			return;
		}

		bitString[pos] = 0;
		generateAllBitstringsRec(v, bitString , pos + 1);

		bitString[pos] = 1;
		generateAllBitstringsRec(v, bitString , pos + 1);
	}

	void generateAllSubsetsRec(const std::vector<int>& v)
	{
		vector<int> bitstring(v.size());

		generateAllBitstringsRec(v, bitstring, 0);
	}

	bool nextObj(std::vector<int>& bitString)
	{
		int i = bitString.size() - 1;

		while (i >= 0 && bitString[i] == 1)
			bitString[i--] = 0;

		if (i < 0)
			return false;

		bitString[i] = 1;

		return true;
	}

	void generateAllSubsetsIter(const std::vector<int>& v)
	{
		std::vector<int> bitString(v.size()); 

		do
		{
			printSubset(bitString, v);
			//printBitString(bitString);
		} while (nextObj(bitString));
	}

	size_t rank(const std::vector<int> bitString)
	{
		size_t m = 1;
		size_t result = 0;
		for (size_t i = bitString.size() - 1; i >= 0; i--, m*=2)
			result += (m*bitString[i]);

		return result;
	}

}


int main()
{
	std::vector<int> v = { 1, 2, 3, 4, 5 };
	Subsets::generateAllSubsetsRec(v);

}

