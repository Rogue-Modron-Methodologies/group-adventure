

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
#include <string>
#include <iostream>

using namespace std;

class InventoryManager
{
private:
	void makeVector(vector<Card*> &, string);
//	void shuffleCollection(vector<Card*> &);
	void populateStructures(BinarySearchTree*, AVLTree*, HashTable<string, Card*>* &, vector<Card*> &);
	void checkLoadFactor(HashTable<string, Card*>* &);
	void reformHashTable(HashTable<string, Card*>* &);
	int getHashSizePrime(int);
	bool checkNotPrime(int);
	void saveCurrentCollection(BinarySearchTree*);
	void createNewHashTable(HashTable<string, Card*>* &, vector<Card*> &);
	bool getSaveFileName(string);
	void makeSaveFile(BinarySearchTree*, string);
	void destroyEverything(BinarySearchTree*, AVLTree*, HashTable<string, Card*>* );
	void ripEmUp(HashTable<string, Card*>* );

public:
	void inventoryCreation(BinarySearchTree*, AVLTree*, HashTable<string, Card*>* &);
	void saveCurrentCollection(BinarySearchTree*);
	void destroyEverything(BinarySearchTree*, AVLTree*, HashTable<string, Card*>* );
};

#endif //INVENTORY_MANAGER_H