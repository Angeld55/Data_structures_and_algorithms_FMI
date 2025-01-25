#include "InsertionOrderHashSet.hpp"

int main() 
{
    InsertionOrderHashSet<std::string> hashSet;

    hashSet.add("Apple");
    hashSet.add("Banana");
    hashSet.add("Cherry");
    hashSet.add("Date");
    hashSet.add("Elderberry");

    std::cout << "Contents of the set (in insertion order):\n";
    for (auto it = hashSet.cbegin(); it != hashSet.cend(); ++it) 
        std::cout << *it << "\n";
    

    std::cout << "\nAdding duplicates:\n";
    hashSet.add("Apple");
    hashSet.add("Banana");

    std::cout << "Contents of the set after attempting to add duplicates:\n";
    for (auto it = hashSet.cbegin(); it != hashSet.cend(); ++it) 
        std::cout << *it << "\n";
    

    std::cout << "\nFinding elements:\n";
    if (hashSet.find("Cherry") != hashSet.cend()) 
        std::cout << "Found: Cherry\n";   
    else 
        std::cout << "Cherry not found\n";
    

    if (hashSet.find("Fig") != hashSet.cend()) 
        std::cout << "Found: Fig\n";
    
    else 
        std::cout << "Fig not found\n";
    

    std::cout << "\nRemoving elements:\n";
    hashSet.remove("Banana");
    hashSet.remove("Date");

    std::cout << "Contents of the set after removal:\n";
    for (auto it = hashSet.cbegin(); it != hashSet.cend(); ++it) 
        std::cout << *it << "\n";
    


    return 0;
}
