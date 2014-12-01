#ifndef IO_MANAGERS
#define IO_MANAGERS

#define INT_MAX 2147483647
#define NULL 0

#include "InventoryManager.h"
#include "Stack.h"
#include <iostream>

using namespace std;

class Managers {
private:
	// Input validation functions.
	static void upper(string &s);
	static bool validKey(string &key);
	static char option();
public:
	// Insert, delete, search, undo-delete, save, and delete stack managers.
	static void addManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* &hashTable);
	static void searchManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable);
	static void deleteManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable, Stack<Card*>* deleteStack);
	static void undoDeleteManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable, Stack<Card*>* deleteStack);
	static void saveManager(BinarySearchTree* keyTree, Stack<Card*>* deleteStack);
	static void deleteStackManager(Stack<Card*>* deleteStack);

	// Display managers.
	static void displayTreeManager(BinarySearchTree* keyTree, AVLTree* nameTree);
	static void displayIndentedTreeManager(BinarySearchTree* keyTree, AVLTree* nameTree);
	static void displayHashedTable(HashTable<string, Card*>* hashTable);
	static void displayList(LinkedList &anItem);
};

#endif
