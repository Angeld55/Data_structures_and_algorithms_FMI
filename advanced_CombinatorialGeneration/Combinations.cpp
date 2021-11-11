namespace Combinations
{
	void printBitstring(const std::vector<int>& bitstring)
	{
		for (int i = 0; i < bitstring.size(); i++)
			cout << bitstring[i] << " ";
		std::cout << std::endl;
	}


	void generateAllCombinationsRec(std::vector<int>& bitstring, int ind, int k)
	{
		size_t n = bitstring.size() - ind;

		if (ind >= bitstring.size() || k == 0)
		{
			printBitstring(bitstring);
			return;
		}
		else if (n == k)
		{
			for (int i = ind; i < bitstring.size(); i++)
				bitstring[i] = 1;

			printBitstring(bitstring);
			return;
		}

		bitstring[ind] = 0;
		generateAllCombinationsRec(bitstring, ind + 1, k);

		for (int i = ind + 1; i < bitstring.size(); i++)
			bitstring[i] = 0;

		bitstring[ind] = 1;
		generateAllCombinationsRec(bitstring, ind + 1, k - 1);
	}


	bool nextObj(std::vector<int>& comb, size_t n)
	{
		int j = comb.size() - 1;

		while (j >= 0 && comb[j] == n - comb.size() + j + 1)
			j--;

		if (j < 0)
			return false;

		comb[j]++;

		for (size_t i = j + 1; i < comb.size(); i++)
			comb[i] = comb[i - 1] + 1;

		return true;
	}

	void generateAllCombinationsIter(size_t n, size_t k)
	{
		std::vector<int> comb(k);
		for (size_t i = 0; i < k; i++)
			comb[i] = i + 1;

		do
		{
			printBitstring(comb);
		} while (nextObj(comb, n));
	}
}
int main()
{
	Combinations::generateAllCombinationsIter(5,3);

}
