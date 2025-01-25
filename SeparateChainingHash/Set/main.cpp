#include "UnorderedSet.hpp"


int main()
{
    UnorderedSet<int> intSet(4);
    std::pair<bool, UnorderedSet<int>::ConstUnorderedSetIterator> result1 = intSet.insert(10);
    bool inserted1 = result1.first;
    UnorderedSet<int>::ConstUnorderedSetIterator it1 = result1.second;
    std::cout << inserted1 << "\n";

    std::pair<bool, UnorderedSet<int>::ConstUnorderedSetIterator> result2 = intSet.insert(10);
    bool inserted2 = result2.first;
    UnorderedSet<int>::ConstUnorderedSetIterator it2 = result2.second;
    std::cout << inserted2 << "\n";

    intSet.insert(1);
    intSet.insert(2);
    intSet.insert(3);
    intSet.insert(4);
    intSet.insert(5);

    UnorderedSet<int>::ConstUnorderedSetIterator foundIt = intSet.find(30);
    if (foundIt != intSet.cend())
    {
        std::cout << "Found\n";
    }
    else
    {
        std::cout << "Not found.\n";
    }

    bool removed3 = intSet.remove(3);
    std::cout << removed3 << "\n";


    std::cout << "All elements: ";
    for (UnorderedSet<int>::ConstUnorderedSetIterator it = intSet.cbegin(); it != intSet.cend(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    intSet.clear();
    std::cout << intSet.empty() << "\n";

    UnorderedSet<std::string> stringSet;
    stringSet.insert("Hello");
    stringSet.insert("World");

    for (UnorderedSet<std::string>::ConstUnorderedSetIterator it = stringSet.cbegin(); it != stringSet.cend(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    return 0;
}