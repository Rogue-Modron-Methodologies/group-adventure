#define INT_MAX 2147483647
#define NULL 0

#include "AVLTree.h"
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "InventoryManager.h"
#include <stack>
#include <iostream>

using namespace std;

void displayMenuOptions();
void runMenu(HashTable<string, Card*>* &hashTable, BinarySearchTree* keyTree,
	AVLTree* nameTree, stack<Card*>* deleteStack);
void welcome();
void displayMenuOptions();
void addManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* &hashTable);
void upper(string &s);
void searchManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable);
void deleteManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable, stack<Card*>* deleteStack);
void undoDeleteManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable, stack<Card*>* deleteStack);
void saveManager(BinarySearchTree* keyTree, stack<Card*>* deleteStack);
void DeleteStack(stack<Card*>* deleteStack);
void displayHashStats(HashTable<string, Card*>* hashTable);
void displayTreeManager(BinarySearchTree* keyTree, AVLTree* nameTree);
void displayIndentedTreeManager(BinarySearchTree* keyTree, AVLTree* nameTree);
void displayHashedTable(HashTable<string, Card*>* hashTable);
bool validKey(string &key);
char option();
void displayList(LinkedList &anItem);
void farewell();

int main(){

	HashTable<string, Card*>* hashTable = 0;
	BinarySearchTree* keyTree = new BinarySearchTree;
	AVLTree* nameTree = new AVLTree;
	stack<Card*>* deleteStack = new stack<Card*>;


	welcome();

	InventoryManager::inventoryCreation(keyTree, nameTree, hashTable);		//InvManager - by Jordan

	runMenu(hashTable, keyTree, nameTree, deleteStack);

	farewell();

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
			addManager(keyTree, nameTree, hashTable);
			break;
		case 'D':
			deleteManager(keyTree, nameTree, hashTable, deleteStack);
			break;
		case 'U':
			undoDeleteManager(keyTree, nameTree, hashTable, deleteStack);
			break;
		case 'F':
			searchManager(keyTree, nameTree, hashTable);
			break;
		case 'H':
			displayHashedTable(hashTable);
			break;
		case 'S':
			displayTreeManager(keyTree, nameTree);
			break;
		case 'I':
			displayIndentedTreeManager(keyTree, nameTree);
			break;
		case 'V':
			saveManager(keyTree, deleteStack);
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

///////////////////////////////////////////////////////////////////////////////

void addManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* &hashTable) {
	string key = "", buffer = "";

	cout << "ADD MANAGER\n\tPlease enter a valid serial number in the format AA111." << endl;

	if (!validKey(key))
		return;

	Card *TempCard = new Card;

	TempCard->setCode(key);

	cout << "Enter name: ";
	getline(cin, buffer);
	upper(buffer);
	TempCard->setName(buffer);

	cout << "Enter cost: ";
	getline(cin, buffer);
	upper(buffer);
	TempCard->setCost(buffer);

	cout << "Enter rarity: ";
	getline(cin, buffer);
	upper(buffer);
	TempCard->setRarity(buffer);

	keyTree->insert(TempCard);
	cout << "\nInserting " << "(" << TempCard << ")" << " into keyTree..." << endl;
	nameTree->insert(TempCard);
	cout << "Inserting " << "(" << TempCard << ")" << " into nameTree..." << endl;
	hashTable->addEntry(TempCard->getCode(), TempCard);
	cout << "Inserting " << "(" << TempCard << ")" << " into hashTable..." << endl;

	InventoryManager::checkLoadFactor(hashTable);
}

void upper(string &s) {
	for (int i = 0; i < s.length(); i++)
		s[i] = toupper(s[i]);
}

void searchManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable) {
	string buffer;
	Card *TempCard = new Card;
	LinkedList *listChoice = NULL;

	cout << "SEARCH MANAGER\n\t1: Key\n\t2: Name\n\n";

	switch (option()) {
	case '1':
		if (validKey(buffer)) {
			if (hashTable->search(buffer, TempCard))
				cout << buffer << " found!\n\t" << *TempCard << endl;
			else
				cout << buffer << " not found." << endl;
		}
		break;
	case '2':
		cout << "Enter the name of the card to be searched.\nName: ";
		getline(cin, buffer);
		upper(buffer);
		TempCard->setName(buffer);
		listChoice = nameTree->getEntry(*TempCard);

		while (listChoice->GetNext(TempCard))
			cout << TempCard << endl;
		break;
	default:
		cout << "Invalid input." << endl;
	}
}

void deleteManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable, stack<Card*>* deleteStack) {
	string key = "", name = "";
	Card *TempCard = new Card;
	LinkedList *listChoice = NULL;


	cout << "DELETE MANAGER\n\t1: Key\n\t2: Name\n\n";

	switch (option()) {
	case '1':
		if (!validKey(key))
			return;
		break;
	case '2':
		cout << "Enter the name of the card to be deleted.\nName: ";
		getline(cin, name);
		upper(name);
		TempCard->setName(name);
		listChoice = nameTree->getEntry(*TempCard);

		//while (listChoice->GetNext(TempCard))
		//	cout << TempCard << endl;

		displayList(*listChoice);

		cout << "Enter the key of one the cards displayed above." << endl;
		if (!validKey(key))
			return;
		break;
	default:
		cout << "Invalid entry." << endl;
		return;
	}

	hashTable->search(key, TempCard);
	
	deleteStack->push(TempCard);
	cout << "\nPushing " << key << " onto undo-delete stack..." << endl;

	if (keyTree->remove(key))
		cout << key << " removed from keyTree." << endl;
	else
		cout << key << " does not exist in keyTree." << endl;

	if (nameTree->remove(*TempCard))
		cout << key << " removed from nameTree." << endl;
	else
		cout << key << " does not exist in nameTree." << endl;

	if (hashTable->remove(key, TempCard))
		cout << key << " removed from hashTable." << endl;
	else
		cout << key << " does not exist in hashTable." << endl;
}

void undoDeleteManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable, stack<Card*>* deleteStack) {
	if (deleteStack->empty()) {
		cout << "Nothing to restore. Stack is empty!" << endl;
		return;
	}
	
	string key = deleteStack->top()->getCode();
	Card *TempCard = NULL;

	if (hashTable->search(key, TempCard)) {
		cout << "(" << deleteStack->top() << ")" << " already exists.\n"
			<< "\tReplace the card in the list? y/n: ";

		switch (option()) {
		case 'Y':
			if (keyTree->remove(key))
				cout << key << " removed from keyTree." << endl;
			if (nameTree->remove(*TempCard))
				cout << key << " removed from nameTree." << endl;
			if (hashTable->remove(key, TempCard))
				cout << key << " removed from hashTable." << endl;
			break;
		case 'N':
			deleteStack->pop();
			return;
		default:
			cout << "Invalid entry." << endl;
		}
	}

	TempCard = deleteStack->top();
	
	keyTree->insert(TempCard);
	cout << "Inserting into keyTree..." << endl;
	nameTree->insert(TempCard);
	cout << "Inserting into nameTree..." << endl;
	hashTable->addEntry(TempCard->getCode(), TempCard);
	cout << "Inserting into hashTable..." << endl;
	cout << "(" << TempCard << ")" << " restored." << endl;

	deleteStack->pop();
}

void saveManager(BinarySearchTree* keyTree, stack<Card*>* deleteStack) {
	DeleteStack(deleteStack);
	cout << "Deleting stack..." << endl;
	InventoryManager::saveCurrentCollection(keyTree);
	cout << "Saving current collection..." << endl;
}

void DeleteStack(stack<Card*>* deleteStack) {
	while (!deleteStack->empty())
		deleteStack->pop();
}

void welcome() {
	cout << "Greetings. This program is designed to organize\n"
		 << "a database of Magic: The Gathering cards using a\n"
		 << "binary search tree, an AVL tree, and a hashed table.\n\n"
		 << "Developers (in alphabetical order):"
		 << "\n\tEdward Lim"
		 << "\n\tEfrain Esquivel"
		 << "\n\tJamie Johnson"
		 << "\n\tJordan Cox"
		 << "\n\tNick Arduini"
		 << "\n\tSteven Bennet\n" << endl;
}

void farewell() {
	cout << "Thank you and farewell. We hope you enjoyed this presentation." << endl;
}

bool validKey(string &key) {
	cout << "Enter key: ";
	getline(cin, key);

	if (key.length() != 5) {
		cout << "Invalid input." << endl;
		return false;
	}
	
	upper(key);
	
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

char option() {
	char option = NULL;
	cout << "Enter option: ";
	cin >> option;
	if (!cin.good())
		return NULL;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	return toupper(option);
}

void displayTreeManager(BinarySearchTree* keyTree, AVLTree* nameTree) {
	cout << "Which tree would you like to display?\n1: BST\n2: AVL\n" << endl;

	switch (option()) {
	case '1':
		if (keyTree->isEmpty())
			cout << "BST tree is empty! Nothing to display." << endl;
		else
			keyTree->displayTree();
		break;
	case '2':
		if (nameTree->isEmpty())
			cout << "AVL tree is empty! Nothing to display." << endl;
		else
			nameTree->inOrder(displayList);
		break;
	default:
		cout << "Invalid entry." << endl;
	}
}

void displayIndentedTreeManager(BinarySearchTree* keyTree, AVLTree* nameTree) {
	cout << "Which tree would you like to display?\n1: Indented BST\n2: Indented AVL\n" << endl;

	switch (option()) {
	case '1':
		if (keyTree->isEmpty())
			cout << "BST tree is empty! Nothing to display." << endl;
		else
			keyTree->displayIndentedTree();
		break;
	case '2':
		if (nameTree->isEmpty())
			cout << "AVL tree is empty! Nothing to display." << endl;
		else
			nameTree->indentedList(displayList);
	default:
		cout << "Invalid entry." << endl;
	}
}

void displayHashedTable(HashTable<string, Card*>* hashTable) {
	if (hashTable->getListCount() == 0) {
		cout << "Hashed table is empty! Nothing to display." << endl;
		return;
	}
	cout << "HASHED TABLE DISPLAY MANAGER\n\t1: Full Table\n\t2: Contents Only\n\n" << endl;

	switch (option()) {
	case '1': 
		hashTable->printTable(Card::display);
		break;
	case '2':
		hashTable->displayTable(Card::display);
		break;
	default:
		cout << "Invalid entry." << endl;
	}
}

void displayList(LinkedList &anItem) {
	anItem.ResetCurr();
	Card* toPrint = 0;
	anItem.GetNext(toPrint);

	cout << "Displaying item - " << toPrint->getName();
	cout << "\n\n\t\t" << toPrint->getCode();
	while (anItem.GetNext(toPrint))
	{
		cout << "\n\t\t" << toPrint->getCode();
	}
	cout << endl;
}