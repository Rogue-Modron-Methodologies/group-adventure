/** Input/Output Managers
	Developer: Efrain Esquivel

	Team 3 Group Project
	De Anza - CIS 22C
	Fall 2014
	Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett */


#include "IOManagers.h"

// Member function upper sets all characters in a string
// to uppercase.
void Managers::upper(string &s) {
	for (int i = 0; i < s.length(); i++)
		s[i] = toupper(s[i]);
}

// Member function validKey checks to make sure the key
// a user enters is valid.
bool Managers::validKey(string &key) {
	cout << "Enter key: ";
	getline(cin, key);

	if (key.length() != 5) { // Must be 5 characters
		cout << "Invalid input." << endl;
		return false;
	}

	upper(key); // Converts to uppercase

	for (int i = 0; i < 2; i++) { // Checks to make sure first two characters are letters
		if (key[i] < 65 || key[i] > 90) {
			cout << "Invalid input." << endl;
			return false;
		}
	}
	for (int i = 2; i < 5; i++) { // Checks to make sure last 3 characters are numbers
		if (key[i] < 48 || key[i] > 57) {
			cout << "Invalid input." << endl;
			return false;
		}
	}
	return true;
}

// Member function option returns a valid, uppercase character
// to be used in switch statements.
// If invalid, it returns NULL
char Managers::option() {
	char option = NULL;
	cout << "Enter option: ";
	cin >> option;
	if (!cin.good())
		return NULL;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	return toupper(option);
}

// Member function addManager adds a new card to the BST, AVL Tree, and Hashed Table
void Managers::addManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* &hashTable) {
	string key = "", buffer = "";

	cout << "ADD MANAGER\n\tPlease enter a valid serial number in the format AA111." << endl;

	if (!validKey(key))
		return;

	Card *target = NULL;

	if (!hashTable->search(key, target)) { // Checks if card key already exists first

		Card *TempCard = new Card();

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

		hashTable->addEntry(TempCard->getCode(), TempCard);
		cout << "\nInserting " << "(" << TempCard << ")" << " into hashTable..." << endl;
		keyTree->insert(TempCard);
		cout << "Inserting " << "(" << TempCard << ")" << " into keyTree..." << endl;
		nameTree->insert(TempCard);
		cout << "Inserting " << "(" << TempCard << ")" << " into nameTree..." << endl;

		InventoryManager::checkLoadFactor(hashTable);
	}
	else
		cout << target->getCode() << " already exists." << endl;
}

// Member function searchManager searches the hashed table for a card if a key is given;
// otherwise, it displays all cards with the same name if a name is given.
void Managers::searchManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable) {
	string buffer;
	Card *TempCard;
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

		if (!listChoice) // Check if name is found.
			cout << buffer << " not found." << endl;
		else
			displayList(*listChoice);
		break;
	default:
		cout << "Invalid input." << endl;
	}
}

// Member function deleteManager deletes a card from the BST, AVL Tree, and Hashed Table by key or name.
// If name is given, a list is displayed and the user must choose the key corresponding
// to the card they wish to delete.
// The deleted card gets pushed onto the undo delete stack.
void Managers::deleteManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable, stack<Card*>* deleteStack) {
	string key = "", name = "";
	Card TempCard;
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
		TempCard.setName(name);
		listChoice = nameTree->getEntry(TempCard);

		if (!listChoice) {
			cout << name << " not found." << endl;
			return;
		}
		else {
			if (listChoice->GetCount() == 1) {
				Card* nameCard;
				listChoice->GetFirst(nameCard);
				key = nameCard->getCode();
			}
			else {
				displayList(*listChoice);
				cout << "Enter the key of one the cards displayed above." << endl;
				if (!validKey(key))
					return;
			}
		}
		break;
	default:
		cout << "Invalid entry." << endl;
		return;
	}

	Card *tempPtr = NULL;

	if (hashTable->search(key, tempPtr)) { // Check if card exists.

		deleteStack->push(tempPtr);
		cout << "\nPushing " << key << " onto undo-delete stack..." << endl;

		if (keyTree->remove(key))
			cout << key << " removed from keyTree." << endl;
		if (nameTree->remove(*tempPtr))
			cout << key << " removed from nameTree." << endl;
		if (hashTable->remove(key, tempPtr))
			cout << key << " removed from hashTable." << endl;
	}
	else
		cout << key << " does not exist." << endl;
}

// Member function undoDeleteManager restores a deleted card back to the BST, AVL Tree, and Hashed Table.
// If a card with the same key is found, the two cards are displayed and the user chooses which card
// to keep.
void Managers::undoDeleteManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable, stack<Card*>* deleteStack) {
	if (deleteStack->empty()) {
		cout << "Nothing to restore. Stack is empty!" << endl;
		return;
	}

	string key = deleteStack->top()->getCode();
	Card *TempCard = NULL;

	if (hashTable->search(key, TempCard)) {
		cout << "(" << deleteStack->top() << ")" << " already exists.\n"
			<< "\nReplace (" << TempCard << ") with (" << deleteStack->top() << ")? y/n: ";

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

// Member function saveManager empties the undo delete stack and saves the collection.
void Managers::saveManager(BinarySearchTree* keyTree, stack<Card*>* deleteStack) {
	DeleteStack(deleteStack);
	cout << "Deleting stack..." << endl;
	InventoryManager::saveCurrentCollection(keyTree);
	cout << "Saving current collection..." << endl;
}

// Member function DeleteStack empties the undo delete stack.
// Note: Thinking about deprecating this one.
void Managers::DeleteStack(stack<Card*>* deleteStack) {
	while (!deleteStack->empty()) {
		Card* deleteCard = deleteStack->top();
		delete deleteCard;
		deleteStack->pop();
	}
}

// Member function displayTreeManager displays either the BST or AVL Tree.
void Managers::displayTreeManager(BinarySearchTree* keyTree, AVLTree* nameTree) {
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

// Member function displayIndentedTreeManager displays the BST or AVL Tree indented.
void Managers::displayIndentedTreeManager(BinarySearchTree* keyTree, AVLTree* nameTree) {
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

// Member function displayHashedTable displays either the full hashed table
// including the empty indicies or only the occupied indicies.
void Managers::displayHashedTable(HashTable<string, Card*>* hashTable) {
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

// Member function displayList displays a list of keys corresponding
// to a name of a card.
void Managers::displayList(LinkedList &anItem) {
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