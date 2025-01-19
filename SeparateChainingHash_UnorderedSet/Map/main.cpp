#include <iostream>
#include <string>
#include "UnorderedMap.hpp"

int main()
{
    UnorderedMap<std::string, int> myMap(4);
    myMap.insert("apple", 100);
    myMap.insert("banana", 200);
    myMap.insert("orange", 300);
    myMap.insert("pear", 400);
    std::cout << "Size: " << myMap.size() << std::endl;
    auto it = myMap.find("banana");
    if (it != myMap.cend())
        std::cout << "Found banana with value " << it->second << std::endl;
    
    myMap.remove("orange");
    std::cout << "Size after removing orange: " << myMap.size() << std::endl;
    for (auto iter = myMap.cbegin(); iter != myMap.cend(); ++iter)
        std::cout << iter->first << " -> " << iter->second << std::endl;
    myMap.clear();
    std::cout << "Size after clear: " << myMap.size() << std::endl;
    return 0;
}
