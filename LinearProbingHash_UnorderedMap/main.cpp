#include "LinearProbingHashDict.hpp"
int main() 
{
    LinearProbingHash<std::string, int> hashTable;

    hashTable.add("apple", 10);
    hashTable.add("banana", 20);
    hashTable.add("cherry", 30);

    for (auto it = hashTable.begin(); it != hashTable.end(); it++)
    {
        std::cout << (*it).first << " " << (*it).second << std::endl;
    }

    auto it = hashTable.get("banana");
    if (it != hashTable.end()) 
    {
        std::cout << "Found: " << (*it).first << " -> " << (*it).second << std::endl;

    }


    hashTable.remove("apple");

    std::cout << "Size of table: " << hashTable.getSize() << std::endl;

    return 0;
}
