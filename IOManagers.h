// Team 3 Group Project
// CIS 22C - 2014
// Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett

#ifndef IO_MANAGERS
#define IO_MANAGERS

#define INT_MAX 2147483647
#define NULL 0

#include "InventoryManager.h"
#include "Stack.h"

using namespace std;

class IOManagers {
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
	static void displayName(LinkedList &anItem);
	static void displayCard(Card* const &card);
};

#endif
