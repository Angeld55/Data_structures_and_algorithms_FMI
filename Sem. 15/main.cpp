#include <iostream>
#include <vector>
#include <iostream>
#include <string>
#include "HashTables/LinearProbingHashTable/LinearProbingHashTable.hpp"
#include "HashTables/SeparateChainingHashTable/SeparateChainingHashTable.hpp"


using namespace std;

struct MyHash
{	
	//example hash function for strings
	std::size_t operator()(const std::string& str) const 
	{
		size_t keyLength = str.length();
		size_t result = keyLength;
		for (int i = 0; i < keyLength; i++)
			result = (result << 4) ^ (result >> 8) ^ (str[i]);
		return result;
	}
};
int main()
{
	SeparateChainingHashTable<std::string, int> phoneBook;

	phoneBook.put("Police", 166);
	phoneBook.put("Ambulance", 150);
	phoneBook.put("Fire Department", 160);
	
	cout << phoneBook.get("Police") << endl;

	LinearProbingHashTable<std::string, std::string, MyHash> capitals;
	capitals.put("Bulgaria", "Sofia");
	capitals.put("Russia", "Moscow");
	capitals.put("Germany", "Berlin");

	cout << capitals.get("Russia") << endl;

}
