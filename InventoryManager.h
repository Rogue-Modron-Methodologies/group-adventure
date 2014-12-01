

/** (っ◕‿◕)っ <(n_n<)

Inventory manager header file by Jordan Cox

Team 3 Group Project
CIS 22C - 2014
Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett

*/

#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "BinarySearchTree.h"
#include "AVLTree.h"
#include "HashTable.h"

#include <fstream>
#include <cstdlib>
#include <ctime>

class InventoryManager
{
private:

	static void makeVector(vector<Card*> &, string);				//create cards and vector of pointers 
	static void populateStructures(BinarySearchTree*, AVLTree*, HashTable<string, Card*>*, vector<Card*> &);		//uses a vector of pointers to create data structures
	static void reformHashTable(HashTable<string, Card*>* &);		//reforms hash table
	static int getHashSizePrime(int);								//determins size of new hash table
	static bool checkNotPrime(int);									//finds a prime number
	static bool getSaveFileName(string&);							//gets suggestion for a save file name from user
	static void removeNonAlphaNumeric(string&);						//makes sure save file name is alphanumeric
	static void txtCheck(string &);									//if needed, appends .txt to save file name
	static bool replaceOrNot(string&);								//asks user what to do if save file name already being used
	static void makeSaveFile(BinarySearchTree*, string);			//save current cards to file from BST (inorder)
	static void ripEmUp(vector<Card*> &);							//destroys cards, free memory

public:

	static void inventoryCreation(BinarySearchTree*, AVLTree*, HashTable<string, Card*>* &);			//calls various functions to read files and create data structures
	static void checkLoadFactor(HashTable<string, Card*>* &);											//checks load factor, if over 75% calls function to reform hash table 
	static void saveCurrentCollection(BinarySearchTree*);												//all the functions needed to save current cards to a file
	static void destroyEverything(BinarySearchTree* &, AVLTree* &, HashTable<string, Card*>* &);		//destroy data structures f=and free memory
};

#endif //INVENTORY_MANAGER_H