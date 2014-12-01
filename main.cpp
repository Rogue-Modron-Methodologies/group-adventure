/** 
Team 3 Group Project
De Anza - CIS 22C
Fall 2014
Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett */

#include "IOManagers.h"

void welcome();
void displayMenuOptions();
void runMenu(HashTable<string, Card*>* &hashTable, BinarySearchTree* keyTree,
	AVLTree* nameTree, Stack<Card*>* deleteStack);
void farewell();

int main(){

	HashTable<string, Card*>* hashTable = 0;
	BinarySearchTree* keyTree = new BinarySearchTree;
	AVLTree* nameTree = new AVLTree;
	Stack<Card*>* deleteStack = new Stack<Card*>();

	welcome();

	InventoryManager::inventoryCreation(keyTree, nameTree, hashTable);

	runMenu(hashTable, keyTree, nameTree, deleteStack);

	farewell();

	InventoryManager::destroyEverything(keyTree, nameTree, hashTable);
	delete deleteStack;

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
	AVLTree* nameTree, Stack<Card*>* deleteStack)
{
	char choice;
	do{										//cycles through commands until the user decides to quit
		cout << "Please enter a command.\t<M> for help." << endl;
		choice = IOManagers::option();
		switch (choice){
		case 'A':
			IOManagers::addManager(keyTree, nameTree, hashTable);
			break;
		case 'D':
			IOManagers::deleteManager(keyTree, nameTree, hashTable, deleteStack);
			break;
		case 'U':
			IOManagers::undoDeleteManager(keyTree, nameTree, hashTable, deleteStack);
			break;
		case 'F':
			IOManagers::searchManager(keyTree, nameTree, hashTable);
			break;
		case 'H':
			IOManagers::displayHashedTable(hashTable);
			break;
		case 'S':
			IOManagers::displayTreeManager(keyTree, nameTree);
			break;
		case 'I':
			IOManagers::displayIndentedTreeManager(keyTree, nameTree);
			break;
		case 'V':
			IOManagers::saveManager(keyTree, deleteStack);
			break;
		case 'T':
			hashTable->displayStatistics();
			break;
		case 'M':
			displayMenuOptions();
			break;
		case 'Q':
			IOManagers::saveManager(keyTree, deleteStack);
			break;
		default:
			cout << "\nCommand not understood.  Please try again!\n\n";
			break;
		}
	} while (choice != 'Q');
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
