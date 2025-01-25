#include <iostream>
#include "HashSet.hpp"

int main()
{
    HashSet<int> set;

    // Add elements
    set.add(10);
    set.add(20);
    set.add(30);

    std::cout << "Added elements: 10, 20, 30\n";

    // Check size
    std::cout << "Set size: " << set.getSize() << "\n";

    // Test contains (using get)
    if (set.get(20) != set.cend())
    {
        std::cout << "Set contains 20\n";
    }
    else
    {
        std::cout << "Set does not contain 20\n";
    }

    if (set.get(40) == set.cend())
    {
        std::cout << "Set does not contain 40\n";
    }

    // Remove an element
    set.remove(20);
    std::cout << "Removed element 20\n";

    if (set.get(20) == set.cend())
    {
        std::cout << "Set does not contain 20 after removal\n";
    }

    // Iterate over the set
    std::cout << "Remaining elements in the set: ";
    for (auto it = set.cbegin(); it != set.cend(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Test adding a duplicate element
    try
    {
        set.add(10);
        std::cout << "Added duplicate element 10\n";
    }
    catch (const std::logic_error& e)
    {
        std::cout << "Caught exception: " << e.what() << "\n";
    }

    return 0;
}
