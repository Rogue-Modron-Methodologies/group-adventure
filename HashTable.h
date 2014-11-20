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
    double avgInLists;

    // Pointer to hash function
    unsigned int (*hashPtr)(const KeyType&, int);

    // Initialize function (called by constructors)
    void init(unsigned int (*hashFunc)(const KeyType&, int), int size);

public:

    // Constructors
    HashTable(unsigned int (*hashFunc)(const KeyType&, int), int size);
    HashTable(unsigned int (*hashFunc)(const KeyType&, int), const HashTable&, int size);
    // Destructor
    ~HashTable() { destroyTable(); }
    // Takes in a key, and an item and adds to table if key not alredy in table.
    // If key is already in table, returns false
    bool addEntry(const KeyType &key, const ItemType &item);
    // Displays all items in the table in list form - takes in display func ptr
    void displayTable(void display(const ItemType&)) const;
    // Displays table locations and entries therein - takes in display func ptr
    void printTable(void display(const ItemType&)) const;
    // Takes key, empty item. Returns true if item
    // is found in table and sets item to the item found
    bool search(const KeyType &key, ItemType &item) const;
    // Takes in key, empty item. Returns true if item
    // is found in table and sets item to the item found.
    // Removes item from table and updates stats
    bool remove(const KeyType &key, ItemType &item);
    void displayStatistics() const;
    // Getters and Setters
    HeadHashNode<KeyType, ItemType>** getTable() const { return table; }
    int getTableSize() const { return tableSize; }
    int getFilledSlots() const { return filledSlots; }
    int getCollisions() const { return collisions; }
    double getLoadFactor() const {return loadFactor; }
    int getListCount() const { return listCount; }
    int getLongListCount() const { return longListCount; }
    double getAvgInLists() const { return avgInLists; }
    void getKeys(vector<KeyType> &keys);
    void getItems(vector<ItemType> &items);
    // Deallocates all memory from new calls since table creation
    void destroyTable();

};

/// Private functions

// Takes in function pointer and size, allocates table,
// initializes all table entries and statistics
template <class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::init(unsigned int (*hashFunc)(const KeyType&, int), int size)
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
    avgInLists = 0;
    hashPtr = hashFunc;
}

/// Public members

// Constructor takes in pointer to hash function, table size and initializes
template <class KeyType, class ItemType>
HashTable<KeyType, ItemType>::HashTable(unsigned int (*hashFunc)(const KeyType&, int), int size)
{
    init(hashFunc, size);
}

// Constructor takes in a hash func ptr, an existing HashTable, and a table
// size, and rehashes entries in existing table into a new table of the
// specified size
template <class KeyType, class ItemType>
HashTable<KeyType, ItemType>::HashTable(unsigned int (*hashFunc)(const KeyType&, int),
                                        const HashTable<KeyType, ItemType> &oldHT,
                                        int size)
{
    init(hashFunc, size);
    HeadHashNode<KeyType, ItemType> **oldTable = oldHT.getTable();
    for (int i = 0, oldSize = oldHT.getTableSize(); i < oldSize; i++) {
        HashNode<KeyType, ItemType> *node = oldTable[i];
        while (node) {
            KeyType key;
            node->getKey(key);
            ItemType item;
            node->getItem(item);
            addEntry(key, item);
            node = node->getNext();
        }
    }
}


// Takes in a key, and an item and adds to table, updates stats
template <class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::
    addEntry(const KeyType &key, const ItemType &value)
{
    ItemType blankItem;
    if (search(key, blankItem))
        return false;
    int index = hashPtr(key, tableSize);
    // If no collision, add to table
    if (!table[index]) {
        table[index] = new HeadHashNode<KeyType, ItemType>(key, value);
        filledSlots++;
        loadFactor = filledSlots / static_cast<double>(tableSize);
    }
    // If collision, add to entry in that table location
    else {
        table[index]->addToList(key, value);
        collisions++;
        int count = table[index]->getListCount();
        if (count == 1)
            listCount++;
        if (count > longListCount)
            longListCount = count;
        avgInLists = collisions / static_cast<double>(listCount);
    }
    return true;
}

// Takes in a func ptr and displays list of entries in table
template <class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::displayTable(void display(const ItemType&)) const
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
void HashTable<KeyType, ItemType>::printTable(void display(const ItemType&)) const
{
    short numSpaces = 3;
    int maxIndex = tableSize - 1;
    while (maxIndex /= 10) numSpaces++;
    for (int i = 0; i < tableSize; i++) {
        stringstream ss;
        ss << i << ": ";
        cout << "Index " << setw(numSpaces) << left << ss.str();
        HashNode<KeyType, ItemType> *hn = table[i];
        if (hn)
        {
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
    search(const KeyType &target, ItemType& foundItem) const
{
    int index = hashPtr(target, tableSize);
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
    remove(const KeyType &target, ItemType& removeItem)
{
    int index = hashPtr(target, tableSize);
    if (!table[index]->removeFromList(target, removeItem))
        return false;
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
        collisions--;
        int count = table[index]->getListCount();
        // If only head remains in list, must decrement listCount
        if (!count) listCount--;
        avgInLists = collisions / static_cast<double>(listCount);
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
void HashTable<KeyType, ItemType>::displayStatistics() const
{
    cout << fixed << setprecision(2);
    cout << "STATISTICS\n"
         << "Table Size: " << tableSize << endl
         << "Filled Slots: " << filledSlots << endl
         << "Load Factor: " << loadFactor << endl
         << "Longest List Length: " << longListCount << endl
         << "List Count: " << listCount << endl
         << "Collisions: " << collisions << endl
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
