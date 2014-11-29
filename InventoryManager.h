

/** (っ◕‿◕)っ <(n_n<)

Inventory manager header file by Jordan Cox

Team 3 Group Project
CIS 22C - 2014
Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett

*/

#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "Card.h"
#include "BinarySearchTree.h"
#include "AVLTree.h"
#include "HashTable.h"

class InventoryManager
{
private:

	static void makeVector(vector<Card*> &, string);
	static void populateStructures(BinarySearchTree*, AVLTree*, HashTable<string, Card*>*, vector<Card*> &);
	static void reformHashTable(HashTable<string, Card*>* &);
	static int getHashSizePrime(int);
	static bool checkNotPrime(int);
	static bool getSaveFileName(string&);
	static void makeSaveFile(BinarySearchTree*, string);
	static bool replaceOrNot(string&);
	static void ripEmUp(vector<Card*> &);

public:

	static void inventoryCreation(BinarySearchTree*, AVLTree*, HashTable<string, Card*>* &);
	static void checkLoadFactor(HashTable<string, Card*>* &);
	static void saveCurrentCollection(BinarySearchTree*);
	static void destroyEverything(BinarySearchTree* &, AVLTree* &, HashTable<string, Card*>* &);
};

#endif //INVENTORY_MANAGER_H