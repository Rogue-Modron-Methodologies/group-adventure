#ifndef IO_MANAGERS
#define IO_MANAGERS

#include "AVLTree.h"
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "InventoryManager.h"
#include <stack>
#include <iostream>

using namespace std;

class Managers {
private:
	// Input validation functions.
	static void upper(string &s);
	static bool validKey(string &key);
	static char option();
public:
	// Welcome and farewell functions.
	static void welcome();
	static void farewell();

	// Insert, delete, search, undo-delete, save, and delete stack managers.
	static void addManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* &hashTable);
	static void searchManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable);
	static void deleteManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable, stack<Card*>* deleteStack);
	static void undoDeleteManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable, stack<Card*>* deleteStack);
	static void saveManager(BinarySearchTree* keyTree, stack<Card*>* deleteStack);
	static void DeleteStack(stack<Card*>* deleteStack);
	
	// Display managers.
	static void displayHashStats(HashTable<string, Card*>* hashTable);
	static void displayTreeManager(BinarySearchTree* keyTree, AVLTree* nameTree);
	static void displayIndentedTreeManager(BinarySearchTree* keyTree, AVLTree* nameTree);
	static void displayHashedTable(HashTable<string, Card*>* hashTable);
	static void displayList(LinkedList &anItem);
};

#endif