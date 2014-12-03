/** Input/Output Managers
	Developer: Efrain Esquivel

	Team 3 Group Project
	De Anza - CIS 22C
	Fall 2014
	Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett */


#include "IOManagers.h"

// Member function upper sets all characters in a string
// to uppercase.
void IOManagers::upper(string &s) {
	for (unsigned int i = 0; i < s.length(); i++)
		s[i] = toupper(s[i]);
}

// Member function validKey checks to make sure the key
// a user enters is valid.
bool IOManagers::validKey(string &key) {
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
char IOManagers::option() {
	string option = "";
	cout << "> ";
	getline(cin, option);
	if (option.length() != 1)
		return '\0';
	return toupper(option[0]);
}

// Member function addManager adds a new card to the BST, AVL Tree, and Hashed Table
void IOManagers::addManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* &hashTable) {
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
		cout << "\nInserting " << "(" << TempCard << ")" << " into Hashed Table..." << endl;
		keyTree->insert(TempCard);
		cout << "Inserting " << "(" << TempCard << ")" << " into BST..." << endl;
		nameTree->insert(TempCard);
		cout << "Inserting " << "(" << TempCard << ")" << " into AVL Tree..." << endl;

		InventoryManager::checkLoadFactor(hashTable);
	}
	else
		cout << target->getCode() << " already exists." << endl;
}

// Member function searchManager searches the hashed table for a card if a key is given;
// otherwise, it displays all cards with the same name if a name is given.
void IOManagers::searchManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable) {
	string buffer;
	Card TempCard;
	Card *tempPtr = NULL;
	LinkedList *listChoice = NULL;

	cout << "SEARCH MANAGER\n\t1: Key\n\t2: Name\n\n";

	switch (option()) {
	case '1':
		if (validKey(buffer)) {
			if (hashTable->search(buffer, tempPtr))
				cout << buffer << " found!\n\t" << *tempPtr << endl;
			else
				cout << buffer << " not found." << endl;
		}
		break;
	case '2':
		cout << "Enter the name of the card to be searched.\nName: ";
		getline(cin, buffer);
		upper(buffer);
		TempCard.setName(buffer);
		listChoice = nameTree->getEntry(TempCard);

		if (!listChoice) // Check if name is found.
			cout << buffer << " not found." << endl;
		else
		{
			cout << buffer << " found!\n";
			displayName(*listChoice);
		}
		break;
	default:
		cout << "Invalid input." << endl;
	}
}

// Member function deleteManager deletes a card from the BST, AVL Tree, and Hashed Table by key or name.
// If name is given, a list is displayed and the user must choose the key corresponding
// to the card they wish to delete.
// The deleted card gets pushed onto the undo delete stack.
void IOManagers::deleteManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable, Stack<Card*>* deleteStack) {
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
				displayName(*listChoice);
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
			cout << key << " removed from BST." << endl;
		if (nameTree->remove(*tempPtr))
			cout << key << " removed from AVL Tree." << endl;
		if (hashTable->remove(key, tempPtr))
			cout << key << " removed from Hashed Table." << endl;
	}
	else
		cout << key << " does not exist." << endl;
}

// Member function undoDeleteManager restores a deleted card back to the BST, AVL Tree, and Hashed Table.
// If a card with the same key is found, the two cards are displayed and the user chooses which card
// to keep.
void IOManagers::undoDeleteManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable, Stack<Card*>* deleteStack) {
	if (deleteStack->isEmpty()) {
		cout << "Nothing to restore. Stack is empty!" << endl;
		return;
	}
	Card *topCard = NULL, *TempCard = NULL;
	deleteStack->getTop(topCard);
	string key = topCard->getCode();


	if (hashTable->search(key, TempCard)) {
		cout << "(" << topCard << ")'s key already exists in db.\n"
			<< "\nReplace (" << TempCard << ") with (" << topCard << ")? y/n: ";

		switch (option()) {
		case 'Y':
			if (keyTree->remove(key))
				cout << key << " removed from BST." << endl;
			if (nameTree->remove(*TempCard))
				cout << key << " removed from AVL Tree." << endl;
			if (hashTable->remove(key, TempCard))
				cout << key << " removed from Hashed Table." << endl;
			delete TempCard;
			break;
		case 'N':
			deleteStack->pop();
			return;
		default:
			cout << "Invalid entry." << endl;
		}
	}

	
	keyTree->insert(topCard);
	cout << "Inserting into BST..." << endl;
	nameTree->insert(topCard);
	cout << "Inserting into AVL Tree..." << endl;
	hashTable->addEntry(topCard->getCode(), topCard);
	cout << "Inserting into Hashed Table..." << endl;
	cout << "(" << topCard << ")" << " restored." << endl;

	InventoryManager::checkLoadFactor(hashTable);

	deleteStack->pop();
}

// Member function saveManager empties the undo delete stack and saves the collection.
void IOManagers::saveManager(BinarySearchTree* keyTree, Stack<Card*>* deleteStack) {
	deleteStackManager(deleteStack);
	cout << "Deleting stack..." << endl;
	InventoryManager::saveCurrentCollection(keyTree);
	cout << "Saving current collection..." << endl;
}

// Member function DeleteStack empties the undo delete stack.
// Note: Thinking about deprecating this one.
void IOManagers::deleteStackManager(Stack<Card*>* deleteStack) {
	while (!deleteStack->isEmpty()) {
		Card* deleteCard;
		deleteStack->pop(deleteCard);
		delete deleteCard;
	}
}

// Member function displayTreeManager displays either the BST or AVL Tree.
void IOManagers::displayTreeManager(BinarySearchTree* keyTree, AVLTree* nameTree) {
	cout << "Which tree would you like to display?\n1: BST\n2: AVL\n" << endl;

	switch (option()) {
	case '1':
		if (keyTree->isEmpty())
			cout << "BST is empty! Nothing to display." << endl;
		else
			keyTree->displayTree(displayCard);
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
void IOManagers::displayIndentedTreeManager(BinarySearchTree* keyTree, AVLTree* nameTree) {
	cout << "Which tree would you like to display?\n1: Indented BST\n2: Indented AVL\n" << endl;

	switch (option()) {
	case '1':
		if (keyTree->isEmpty())
			cout << "BST is empty! Nothing to display." << endl;
		else
			keyTree->displayIndentedTree(displayCard);
		break;
	case '2':
		if (nameTree->isEmpty())
			cout << "AVL tree is empty! Nothing to display." << endl;
		else
			nameTree->indentedList(displayList);
		break;
	default:
		cout << "Invalid entry." << endl;
	}
}

// Member function displayHashedTable displays either the full hashed table
// including the empty indicies or only the occupied indicies.
void IOManagers::displayHashedTable(HashTable<string, Card*>* hashTable) {
	if (hashTable->getListCount() == 0) {
		cout << "Hashed table is empty! Nothing to display." << endl;
		return;
	}
	cout << "HASHED TABLE DISPLAY MANAGER\n\t1: Full Table\n\t2: Contents Only\n\n" << endl;

	switch (option()) {
	case '1':
		hashTable->printTable(displayCard);
		break;
	case '2':
		hashTable->displayTable(displayCard);
		break;
	default:
		cout << "Invalid entry." << endl;
	}
}

// Member function displayList displays a list of keys corresponding
// to a name of a card.
void IOManagers::displayList(LinkedList &anItem) {
	anItem.ResetCurr();
	Card* toPrint = 0;
	anItem.GetNext(toPrint);

	cout << toPrint->getName();
	cout << " " << toPrint->getCode();
	while (anItem.GetNext(toPrint))
	{
		cout << ", " << toPrint->getCode();
	}
	cout << endl;
}

// Member function displayName displays complete information
// about all cards with the same name.
void IOManagers::displayName(LinkedList &anItem) {
	anItem.ResetCurr();
	Card* toPrint = 0;
	anItem.GetNext(toPrint);

	cout << "\t" << *toPrint << endl;
	while (anItem.GetNext(toPrint))
	{
		cout << "\t" << *toPrint << endl;
	}
}

// Member function displayCard displays the code for
// a card followed by its name.
void IOManagers::displayCard(Card* const &card) {
	cout << card->getCode() << " "
		 << card->getName();
}
