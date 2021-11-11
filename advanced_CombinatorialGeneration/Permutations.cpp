namespace Permutations
{

	void printPermutation(const std::vector<int>& v)
	{
		std::cout << "( ";
		for (size_t i = 0; i < v.size(); i++)
			std::cout << v[i] << " ";
		std::cout << " )" << std::endl;
	}
	void generatePermutationsRec(vector<int>& v, size_t index)
	{
		if (index == v.size())
			printPermutation(v);
		else
		{
			for (size_t i = index; i < v.size(); i++)
			{
				std::swap(v[index], v[i]);
				generatePermutationsRec(v, index + 1);
				std::swap(v[index], v[i]);
			}
		}
	}

	bool nextObj(std::vector<int>& permutation)
	{
		if (permutation.size() <= 1)
			return false;

		int index = permutation.size() - 2;

		while (index >= 0 && permutation[index] > permutation[index + 1])
			index--;

		if (index < 0)
			return false;

		size_t j = permutation.size() - 1;

		while (permutation[j] < permutation[index])
			j--;

		std::swap(permutation[j], permutation[index]);

		std::reverse(permutation.begin() + index + 1, permutation.end());

		return true;
	}

	void generateAllPermutationsIter(const std::vector<int>& v)
	{
		std::vector<int> currentPermutation = v;

		do
		{
			printPermutation(currentPermutation);
	
		} while (nextObj(currentPermutation));
	}

	size_t fact(size_t n)
	{

		return (n == 0) || (n == 1) ? 1 : n* fact(n - 1);
	}

	size_t rank(std::vector<int>& v, size_t ind)
	{
		if (ind == v.size())
			return 0;

		size_t result = (v[ind] - 1) * fact(v.size() - 1 - ind);

		for (size_t i = ind + 1; i < v.size(); i++)
		{
			if (v[i] > v[ind])
				v[i]--;
		}

		return result + rank(v, ind + 1);
	}
}


int main()
{
	std::vector<int> v = { 1, 2, 3, 4, 5 };
	Permutations::generatePermutationsRec(v, 0);

}
