#include "InsertionOrderHashMap.hpp"

int main() 
{
    InsertionOrderHashMap<std::string, int> map;

    map.add("apple", 10);
    map.add("banana", 20);
    map.add("cherry", 30);

    std::cout << "Contents of the map:\n";
    for (auto it = map.cbegin(); it != map.cend(); ++it) 
        std::cout << (*it).first << ": " << (*it).second << "\n";
    

    std::cout << "\nFinding 'banana':\n";
    auto found = map.find("banana");
    if (found != map.cend()) 
        std::cout << (*found).first << ": " << (*found).second << "\n";
    else 
        std::cout << "Key not found.\n";
    

    std::cout << "\nRemoving 'apple'...\n";
    map.remove("apple");

    std::cout << "Contents of the map after removal:\n";
    for (auto it = map.cbegin(); it != map.cend(); ++it) 
        std::cout << (*it).first << ": " << (*it).second << "\n";
    

    return 0;
}
