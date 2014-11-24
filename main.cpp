
#include "AVLTree.h"
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "InventoryManager.h"
#include <stack>
#include <iostream>

using namespace std;

void displayMenuOptions();
void runMenu(HashTable<string, Card*>* hashTable, BinarySearchTree* keyTree,
	AVLTree* nameTree, stack<Card*>* deleteStack, InventoryManager& manage_inventory);
void welcome();
void displayMenuOptions();
void addManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable);
void searchManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable);
void deleteManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable, stack<Card*>* deleteStack);
void pushOnStack(Card *TempCard, stack<Card*>* deleteStack);
void saveManager(BinarySearchTree* keyTree, stack<Card*>* deleteStack, InventoryManager &);
void DeleteStack(stack<Card*>* deleteStack);
void displayHashStats(HashTable<string, Card*>* hashTable);
void displayTreeManager(BinarySearchTree* keyTree, AVLTree* nameTree);
void displayIndentedTreeManager(BinarySearchTree* keyTree, AVLTree* nameTree);
void displayHashedTable(HashTable<string, Card*>* hashTable);
bool validKey(string &key);
void displayList(LinkedList &anItem);
void farewell();

int main(){

	HashTable<string, Card*>* hashTable = 0;
	BinarySearchTree* keyTree = new BinarySearchTree;
	AVLTree* nameTree = new AVLTree;
	stack<Card*>* deleteStack = new stack<Card*>;
	InventoryManager manage_inventory;


	welcome();

	manage_inventory.inventoryCreation(keyTree, nameTree, hashTable);		//InvManager - by Jordan

	runMenu(hashTable, keyTree, nameTree, deleteStack, manage_inventory);

	farewell();

	//Destroy Structures - by Jordan

	//manage_inventory->destroyEverything(keyTree, nameTree, hashTable);

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
void runMenu(HashTable<string, Card*>* hashTable, BinarySearchTree* keyTree,
	AVLTree* nameTree, stack<Card*>* deleteStack, InventoryManager& manage_inventory)
{
	string choice;
	do{										//cycles through commands until the user decides to quit
		cout << "Please enter a command.\t<M> for help." << endl;
		getline(cin, choice);

		switch (toupper(choice[0])){
		case 'A':
			addManager(keyTree, nameTree, hashTable);
			break;
		case 'D':
			deleteManager(keyTree, nameTree, hashTable, deleteStack);
			break;
		case 'F':
			searchManager(keyTree, nameTree, hashTable);
			break;
		case 'H':
			hashTable->printTable(Card::display);
			break;
		case 'S':
			displayTreeManager(keyTree, nameTree);
			break;
		case 'I':
			displayIndentedTreeManager(keyTree, nameTree);
			break;
		case 'V':
			saveManager(keyTree, deleteStack, manage_inventory);
			break;
		case 'T':
			displayHashStats(hashTable);
			break;
		case 'M':
			displayMenuOptions();
			break;
		case 'Q':
			// Save Manager 
			cout << "Save the database and quitting - Coming Soon!\n";
			break;
		default:
			cout << "\nCommand not understood.  Please try again!\n\n";
			break;
		}
	} while (toupper(choice[0]) != 'Q');
}

///////////////////////////////////////////////////////////////////////////////

void addManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable) {
	string key = "", buffer = "";

	cout << "ADD MANAGER\n\tPlease enter a valid serial number in the format AA111." << endl;

	if (validKey(key)) {
		Card *TempCard = new Card;

		TempCard->setCode(key);

		cout << "Enter name: ";
		getline(cin, buffer);
		TempCard->setName(buffer);

		cout << "Enter cost: ";
		getline(cin, buffer);
		TempCard->setCost(buffer);

		cout << "Enter rarity: ";
		getline(cin, buffer);
		TempCard->setRarity(buffer);
		keyTree->insert(TempCard);
		cout << "Inserting into keyTree..." << endl;
		nameTree->insert(TempCard);
		cout << "Inserting into nameTree..." << endl;
		hashTable->addEntry(TempCard->getCode(), TempCard);
		cout << "Inserting into hashTable..." << endl;
	}
}

void searchManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable) {
	char option = NULL;
	string buffer;

	cout << "SEARCH MANAGER\n\t1: Key\n\t2: Name\n\n";

	cin >> option;

	if (!cin.good()) {
		cout << "Invalid input." << endl;
		return;
	}

	cin.clear();
	cin.ignore(INT_MAX, '\n');

	if (option == '1') {
		if (validKey(buffer)) {
			//keyTree->findNode(buffer);
			Card *TempCard = new Card;
			hashTable->search(buffer, TempCard);
			cout << "Searching for " << buffer << " in keyTree..." << endl;

			cout << buffer << " found!" << *TempCard << endl;
		}
	}
	else if (option == '2') {
		getline(cin, buffer);
		Card *target = new Card;
		target->setName(buffer);
		LinkedList * something = nameTree->getEntry(*target);
		cout << "Searching for " << buffer << " in nameTree..." << endl;
	}
	else
		cout << "Invalid input." << endl;
	//hashTable.search(something);
}

void deleteManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable, stack<Card*>* deleteStack) {
	char option = NULL;
	string key = "", name = "";

	cout << "DELETE MANAGER\n\t1: Key\n\t2: Name\n\n";

	cin >> option;

	if (!cin.good()) {
		cout << "Invalid input." << endl;
		return;
	}

	cin.clear();
	cin.ignore(INT_MAX, '\n');

	if (option == '1') {
		if (!validKey(key))
			return;
	}
	else if (option == '2') {
		getline(cin, name);
		Card* TempTree = new Card;
		TempTree->setName(name);
		LinkedList * something = nameTree->getEntry(*TempTree);
		//while (something->GetNext(TempTree));
		displayList(*something);
	}
	else {
		cout << "Invalid input." << endl;
		return;
	}

	Card *TempCard = keyTree->findNode(key)->getCardPtr();
	pushOnStack(TempCard, deleteStack);
	cout << "Pushing " << key << " onto undo-delete stack..." << endl;
	keyTree->remove(TempCard->getCode());
	cout << "Deleting " << key << " from keyTree..." << endl;
	nameTree->remove(*TempCard);
	cout << "Deleting " << key << " from nameTree..." << endl;
	//hashTable->remove(TempCard);
	cout << "Deleting " << key << " from hashTable..." << endl;
}

void pushOnStack(Card *TempCard, stack<Card*>* deleteStack) {
	deleteStack->push(TempCard);
}

void saveManager(BinarySearchTree* keyTree, stack<Card*>* deleteStack, InventoryManager &manage_inventory) {
	DeleteStack(deleteStack);
	cout << "Deleting stack..." << endl;
	manage_inventory.saveCurrentCollection(keyTree);
	cout << "Saving current collection..." << endl;
}

void DeleteStack(stack<Card*>* deleteStack) {
	while (!deleteStack->empty())
		deleteStack->pop();
}

void displayHashStats(HashTable<string, Card*>* hashTable) {
	hashTable->displayStatistics();
}

void welcome() {
	cout << "Welcome" << endl;
}

void farewell() {
	cout << "Goodbye." << endl;
}

bool validKey(string &key) {
	cout << "Enter key: ";
	getline(cin, key);

	if (key.length() != 5) {
		cout << "Invalid input." << endl;
		return false;
	}

	key[0] = toupper(key[0]);
	key[1] = toupper(key[1]);

	// 65 - 90 = A-Z
	// 48 - 57 = 0-9

	for (int i = 0; i < 2; i++) {
		if (key[i] < 65 || key[i] > 90) {
			cout << "Invalid input." << endl;
			return false;
		}
	}
	for (int i = 2; i < 5; i++) {
		if (key[i] < 48 || key[i] > 57) {
			cout << "Invalid input." << endl;
			return false;
		}
	}
	return true;
}

void displayTreeManager(BinarySearchTree* keyTree, AVLTree* nameTree) {
	char option = NULL;

	cout << "Which tree would you like to display?\n"
		<< "1: BST\n"
		<< "2: BST (Non-Unique)\n" << endl;

	cin >> option;
	while (!cin.good())
		return;

	if (option == '1') {
		if (keyTree->isEmpty())
			cout << "BST is empty! Nothing to display." << endl;
		else
			keyTree->displayTree();
	}
	else if (option == '2') {
		if (nameTree->isEmpty())
			cout << "BST (Non-Unique) is empty! Nothing to display." << endl;
		else
			nameTree->inOrder(displayList);
	}
	else
		cout << "Invalid input." << endl;

	cin.clear();
	cin.ignore(INT_MAX, '\n');
}

void displayIndentedTreeManager(BinarySearchTree* keyTree, AVLTree* nameTree) {
	char option = NULL;

	cout << "Which tree would you like to display?\n"
		<< "1: Indented BST\n"
		<< "2: Indented BST (Non-Unique)\n" << endl;

	cin >> option;
	while (!cin.good())
		return;

	if (option == '1') {
		if (keyTree->isEmpty())
			cout << "BST is empty! Nothing to display." << endl;
		else
			keyTree->displayIndentedTree();
	}
	else if (option == '2') {
		if (nameTree->isEmpty())
			cout << "BST (Non-Unique) is empty! Nothing to display." << endl;
		else
			nameTree->indentedList(displayList);
	}
	else
		cout << "Invalid input" << endl;

	cin.clear();
	cin.ignore(INT_MAX, '\n');
}

void displayHashedTable() {
	//if (hashTable.getListCount() != 0)
	//	hashTable.printTable(Card::display);
	//else
	//	cout << "Hashed table is empty! Nothing to display." << endl;
}

void displayList(LinkedList &anItem) {
	anItem.ResetCurr();
	Card* toPrint = 0;
	anItem.GetNext(toPrint);

	cout << "Displaying item - " << toPrint->getName();
	cout << " " << toPrint->getCode();
	while (anItem.GetNext(toPrint))
	{
		cout << ", " << toPrint->getCode();
	}
	cout << endl;
}
