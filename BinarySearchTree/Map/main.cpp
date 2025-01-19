#include <iostream>
#include "Map.hpp"

int main() {
    Map<int, std::string> myMap;

    myMap.insert(10, "ten");
    myMap.insert(20, "twenty");
    myMap.insert(5, "five");
    myMap.insert(15, "fifteen");

    std::cout << "In-order traversal of the Map:\n";
    for (auto it = myMap.cbegin(); it != myMap.cend(); ++it) 
        std::cout << (*it).first << " -> " << (*it).second << "\n";

    std::cout << "\nContainsKey tests:\n";
    std::cout << "Does the Map contain 10? " << (myMap.containsKey(10) ? "Yes" : "No") << "\n";
    std::cout << "Does the Map contain 25? " << (myMap.containsKey(25) ? "Yes" : "No") << "\n";

    std::cout << "\nRemoving key 10...\n";
    if (myMap.remove(10)) 
        std::cout << "Key 10 removed.\n";
    else 
        std::cout << "Key 10 not found.\n";
    

    std::cout << "After removal:\n";
    for (auto it = myMap.cbegin(); it != myMap.cend(); ++it) {
        std::cout << (*it).first << " -> " << (*it).second << "\n";
    }

    std::cout << "\nSize of the Map: " << myMap.size() << "\n";
    std::cout << "Is the Map empty? " << (myMap.empty() ? "Yes" : "No") << "\n";

    std::cout << "\nInserting duplicate key 5...\n";
    if (!myMap.insert(5, "duplicate")) 
        std::cout << "Duplicate key 5 was not inserted.\n";
    

    std::cout << "\nFinal Map state:\n";
    for (auto it = myMap.cbegin(); it != myMap.cend(); ++it) 
        std::cout << (*it).first << " -> " << (*it).second << "\n";
    

    return 0;
}
