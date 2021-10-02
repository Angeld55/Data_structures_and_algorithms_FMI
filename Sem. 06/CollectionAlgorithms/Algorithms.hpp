
namespace CustomAlgorithms
{

	template <typename Iter, typename ElementType>
	bool containsElement(Iter it1, Iter it2, const ElementType searched)
	{
		while (it1 != it2)
		{
			if (*it1 == searched)
				return true;

			++it1;
		}
		return false;
	}


	template <typename Iter>
	bool isSorted(Iter it1, Iter it2)
	{
		while (it1 != it2)
		{
			Iter next = it1 + 1;

			if (next == it2)
				break;

			if (*it1 > *next)
				return false;

			++it1;
		}
		return true;
	}
}