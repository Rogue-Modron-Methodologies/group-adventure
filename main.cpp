#define INT_MAX 2147483647
#define NULL 0

#include "AVLTree.h"
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "InventoryManager.h"
#include "IOManagers.h"
#include <stack>
#include <iostream>

using namespace std;

void displayMenuOptions();
void runMenu(HashTable<string, Card*>* &hashTable, BinarySearchTree* keyTree,
	AVLTree* nameTree, stack<Card*>* deleteStack);
void displayMenuOptions();

int main(){

	HashTable<string, Card*>* hashTable = 0;
	BinarySearchTree* keyTree = new BinarySearchTree;
	AVLTree* nameTree = new AVLTree;
	stack<Card*>* deleteStack = new stack<Card*>;

	Managers::welcome();

	InventoryManager::inventoryCreation(keyTree, nameTree, hashTable);		//InvManager - by Jordan

	runMenu(hashTable, keyTree, nameTree, deleteStack);

	Managers::farewell();

	//Destroy Structures - by Jordan

	//InventoryManager::destroyEverything(keyTree, nameTree, hashTable);

	return 0;
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
//  Displays the information of all commands available to the user.
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
void displayMenuOptions()
{
	cout << endl;
	cout << "<A>\tAdd a card.\n\n";
	cout << "<D>\tDelete a card.\n\n";
	cout << "<U>\tUndo delete.\n\n";
	cout << "<F>\tSearch for a card.\n\n";
	cout << "<H>\tPrint in Hash Table Sequence.\n\n";
	cout << "<S>\tPrint Sorted List.\n\n";
	cout << "<I>\tPrint Indented Tree.\n\n";
	cout << "<V>\tSave the database.\n\n";
	cout << "<T>\tShow hash table statistics.\n\n";
	cout << "<M>\tShow Menu.\n\n";
	cout << "<Q>\tQuit.\n\n";
}

// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
//  Basic Menu - gets user input and switches between options.
//  Continues until user decides to quit.
// (¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯`'•.¸//(*_*)\\¸.•'´¯)
void runMenu(HashTable<string, Card*>* &hashTable, BinarySearchTree* keyTree,
	AVLTree* nameTree, stack<Card*>* deleteStack)
{
	string choice;
	do{										//cycles through commands until the user decides to quit
		cout << "Please enter a command.\t<M> for help." << endl;
		getline(cin, choice);

		switch (toupper(choice[0])){
		case 'A':
			Managers::addManager(keyTree, nameTree, hashTable);
			break;
		case 'D':
			Managers::deleteManager(keyTree, nameTree, hashTable, deleteStack);
			break;
		case 'U':
			Managers::undoDeleteManager(keyTree, nameTree, hashTable, deleteStack);
			break;
		case 'F':
			Managers::searchManager(keyTree, nameTree, hashTable);
			break;
		case 'H':
			Managers::displayHashedTable(hashTable);
			break;
		case 'S':
			Managers::displayTreeManager(keyTree, nameTree);
			break;
		case 'I':
			Managers::displayIndentedTreeManager(keyTree, nameTree);
			break;
		case 'V':
			Managers::saveManager(keyTree, deleteStack);
			break;
		case 'T':
			hashTable->displayStatistics();
			break;
		case 'M':
			displayMenuOptions();
			break;
		case 'Q':
			//saveManager(keyTree, deleteStack);
			break;
		default:
			cout << "\nCommand not understood.  Please try again!\n\n";
			break;
		}
	} while (toupper(choice[0]) != 'Q');
}
