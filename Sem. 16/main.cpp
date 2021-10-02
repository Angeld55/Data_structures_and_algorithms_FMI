#include "HashTables/SeparateChainingHashTable/SeparateChainingHashTable.hpp"
#include "HashTables/LinearProbingHashTable/LinearProbingHashTable.hpp"
#include "HashTables/DoubleHashingHashTable/DoubleHashingHashTable.hpp"

int main()
{
	SeparateChainingHashTable<string, int> phoneBook;

	phoneBook.put("Police", 166);
	phoneBook.put("Ambulance", 150);
	phoneBook.put("Fire Department", 160);
	


	for (auto it = phoneBook.begin(); it != phoneBook.end(); ++it)
		cout << "Key: " << (*it).key << ", Value: " << (*it).value << endl;
	cout << endl;

}