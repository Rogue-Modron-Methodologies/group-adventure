// Hash Table is a dynamically allocated array of pointers to a HeadHashNode

// Team 3 Group Project
// CIS 22C - 2014
// Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett

#ifndef _HASH_TABLE
#define _HASH_TABLE

#include "HeadHashNode.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

template <class KeyType, class ItemType>
class HashTable
{

private:

    // Table is an array of pointers to a HeadHashNode
    HeadHashNode<KeyType, ItemType> **table;

    //Statistics
    int tableSize;
    int filledSlots;
    int collisions;
    double loadFactor;
    int listCount;
    int longListCount;
    int totalInLists;
    double avgInLists;

    // Member function takes in a hash function pointer and a key and
    // returns an index between 0 and (tableSize - 1)
    unsigned int getHashValue(unsigned int hash(const KeyType &, int),
                              const KeyType &key);
    // Initialize function called by constructors
    void init(int size);

public:

    // Constructors
    HashTable(int size);
    HashTable(unsigned int hash(const KeyType&, int), const HashTable&, int size);
    // Destructor
    ~HashTable() { destroyTable(); }
    // Takes in a hash function ptr, a key, and an item and adds to table
    void addEntry(unsigned int hash(const KeyType&, int),
                  const KeyType &key, const ItemType &item);
    // Displays all items in the table in list form - takes in display func ptr
    void displayTable(void display(const ItemType&));
    // Displays table locations and entries therein - takes in display func ptr
    void printTable(void display(const ItemType&));
    // Takes in hash function ptr, key, empty item. Returns true if item
    // is found in table and sets item to the item found
    bool search(unsigned int hash(const KeyType&, int),
                  const KeyType &key, ItemType &item);
    // Takes in hash function ptr, key, empty item. Returns true if item
    // is found in table and sets item to the item found. Removes item from
    // table and updates stats
    bool remove(unsigned int hash(const KeyType&, int),
                  const KeyType &key, ItemType &item);
    void displayStatistics();
    // Getters and Setters
    HeadHashNode<KeyType, ItemType>** getTable() const { return table; }
    int getTableSize() const { return tableSize; }
    int getFilledSlots() const { return filledSlots; }
    int getCollisions() const { return collisions; }
    double getLoadFactor() const {return loadFactor; }
    int getListCount() const { return listCount; }
    int getLongListCount() const { return longListCount; }
    int getTotalInLists() const { return totalInLists; }
    double getAvgInLists() const { return avgInLists; }
    void getKeys(vector<KeyType> &keys);
    void getItems(vector<ItemType> &items);
    // Deallocates all memory from new calls since table creation
    void destroyTable();

};

/// Private functions

// Allocates table, initializes all table entries and statistics
template <class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::init(int size)
{
    table = new HeadHashNode<KeyType, ItemType>*[size];
    for (int i = 0; i < size; i++)
        table[i] = 0;
    tableSize = size;
    filledSlots = 0;
    collisions = 0;
    loadFactor= 0;
    listCount = 0;
    longListCount = 0;
    totalInLists = 0;
    avgInLists = 0;
}

// Takes in a hash function pointer and a key, calls function and
// returns an index between 0 and (tableSize - 1)
template <class KeyType, class ItemType>
unsigned int HashTable<KeyType, ItemType>::
    getHashValue(unsigned int hash(const KeyType&, int), const KeyType &key)
{
    return hash(key, tableSize);
}

/// Public members

// Constructor takes in table size and initializes
template <class KeyType, class ItemType>
HashTable<KeyType, ItemType>::HashTable(int size)
{
    init(size);
}

// Constructor takes in a hash func ptr, an existing HashTable, and a table
// size, and rehashes entries in existing table into a new table of the
// specified size
template <class KeyType, class ItemType>
HashTable<KeyType, ItemType>::HashTable(unsigned int hash(const KeyType&, int),
                                        const HashTable<KeyType, ItemType> &oldHT,
                                        int size)
{
    init(size);
    HeadHashNode<KeyType, ItemType> **oldTable = oldHT.getTable();
    for (int i = 0, oldSize = oldHT.getTableSize(); i < oldSize; i++) {
        HashNode<KeyType, ItemType> *node = oldTable[i];
        while (node) {
            KeyType key;
            node->getKey(key);
            ItemType item;
            node->getItem(item);
            addEntry(hash, key, item);
            node = node->getNext();
        }
    }
}


// Takes in a hash func ptr, a key, and an item and adds to table, updates stats
template <class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::
    addEntry(unsigned int hash(const KeyType&, int),
             const KeyType &key, const ItemType &value)
{
    int index = getHashValue(hash, key);
    // If no collision, add to table
    if (!table[index]) {
        table[index] = new HeadHashNode<KeyType, ItemType>(key, value);
        filledSlots++;
        loadFactor = filledSlots / static_cast<double>(tableSize);
    }
    // If collision, add to entry in that table location
    else {
        table[index]->addToList(key, value);
        collisions++, totalInLists++;
        int count = table[index]->getListCount();
        if (count == 1)
            listCount++;
        if (count > longListCount)
            longListCount = count;
        avgInLists = totalInLists / static_cast<double>(listCount);
    }
}

// Takes in a func ptr and displays list of entries in table
template <class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::displayTable(void display(const ItemType&))
{
    for (int i = 0; i < tableSize; i++) {
        HashNode<KeyType, ItemType> *hn = table[i];
        while (hn) {
            ItemType item;
            hn->getItem(item);
            display(item);
            cout << endl;
            hn = hn->getNext();
        }
    }
}

// Takes in a func ptr and displays table locations and entries therein
template <class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::printTable(void display(const ItemType&))
{
    short numSpaces = 3;
    int maxIndex = tableSize - 1;
    while (maxIndex /= 10) numSpaces++;
    for (int i = 0; i < tableSize; i++) {
        stringstream ss;
        ss << i << ": ";
        cout << "Index " << setw(numSpaces) << left << ss.str();
        HashNode<KeyType, ItemType> *hn = table[i];
        if (hn) {
            ItemType item;
            hn->getItem(item);
            display(item);
            hn = hn->getNext();
        }
        else cout << "// empty";
        cout << endl;
        while (hn) {
            cout << setw(numSpaces + 11) << " ";
            ItemType item;
            hn->getItem(item);
            display(item);
            cout << endl;
            hn = hn->getNext();
        }
    }
}

// Takes in hash function ptr, key, empty item. Returns true if item
// is found in table and sets item to the item found.
template <class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::
    search(unsigned int hash(const KeyType&, int),
           const KeyType &target, ItemType& foundItem)
{
    int index = getHashValue(hash, target);
    HashNode<KeyType, ItemType> *node = table[index];
    while (node) {
        KeyType k;
        node->getKey(k);
        if (k == target) {
            node->getItem(foundItem);
            return true;
        }
        node = node->getNext();
    }
    return false;
}

// Takes in hash function ptr, key, empty item. Returns true if item
// is found in table and sets item to the item found. Removes item from
// table and updates stats
template <class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::
    remove(unsigned int hash(const KeyType&, int),
           const KeyType &target, ItemType& removeItem)
{
    int index = getHashValue(hash, target);
    if (!table[index]->removeFromList(target, removeItem))
        return false;
    totalInLists--;
    ItemType headItem;
    table[index]->getItem(headItem);
    // If the removeItem is still in the list, then that means it is the only
    // entry in the list and the HeadHashEntry must be deleted
    if (headItem == removeItem) {
        filledSlots--;
        loadFactor = filledSlots / static_cast<double>(tableSize);
        delete table[index];
        table[index] = 0;
    }
    else {
        collisions--, totalInLists--;
        avgInLists = totalInLists / static_cast<double>(listCount);
        int count = table[index]->getListCount();
        // If only head remains in list, must decrement listCount
        if (!count) listCount--;
        // If updated list has one less entry than the long list, we need
        // to make sure longListCount still accurate
        if (count == (longListCount - 1)) {
            longListCount = count;
            for (int i = 0; i < tableSize; i++) {
                if (table[i]) {
                    count = table[i]->getListCount();
                    if (count > longListCount) {
                        longListCount = count;
                        break;
                    }
                }
            }
        }
    }
    return true;
}

// Displays stats
template <class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::displayStatistics()
{
    cout << fixed << setprecision(2);
    cout << "STATISTICS\n"
         << "Table Size: " << tableSize << endl
         << "Filled Slots: " << filledSlots << endl
         << "Collisions: " << collisions << endl
         << "Load Factor: " << loadFactor << endl
         << "List Count: " << listCount << endl
         << "Longest List Length: " << longListCount << endl
         << "Total In Lists: " << totalInLists << endl
         << "Average in Lists: " << avgInLists << "\n\n";

}

// Returns a list of keys in a vector
template <class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::getKeys(vector<KeyType> &keys)
{
    for (int i = 0; i < tableSize; i++) {
        HashNode<KeyType, ItemType> *node = table[i];
        while (node) {
			KeyType key;
			node->getKey(key);
            keys.push_back(key);
            node = node->getNext();
        }
    }
}

// Returns a list of items in a vector
template <class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::getItems(vector<ItemType> &keys)
{
    for (int i = 0; i < tableSize; i++) {
        HashNode<KeyType, ItemType> *node = table[i];
        while (node) {
			ItemType item;
			node->getItem(item);
            keys.push_back(item);
            node = node->getNext();
        }
    }
}

// Deallocates all memory from new calls since table creation
template <class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::destroyTable()
{
    for (int i = 0; i < tableSize; i++)
    {
        if (table[i])
            delete table[i];
    }
    delete [] table;
}


#endif
