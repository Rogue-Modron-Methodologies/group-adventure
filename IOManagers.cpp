/** Input/Output Managers
	Developer: Efrain Esquivel

	Team 3 Group Project
	De Anza - CIS 22C
	Fall 2014
	Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett */


#include "IOManagers.h"

void Managers::upper(string &s) {
	for (int i = 0; i < s.length(); i++)
		s[i] = toupper(s[i]);
}

bool Managers::validKey(string &key) {
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

void Managers::addManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* &hashTable) {
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
	if (hashTable->addEntry(TempCard->getCode(), TempCard)) {
		cout << "\nInserting " << "(" << TempCard << ")" << " into hashTable..." << endl;
		keyTree->insert(TempCard);
		cout << "Inserting " << "(" << TempCard << ")" << " into keyTree..." << endl;
		nameTree->insert(TempCard);
		cout << "Inserting " << "(" << TempCard << ")" << " into nameTree..." << endl;

		InventoryManager::checkLoadFactor(hashTable);
	}
	else
		cout << TempCard->getCode() << " already exists." << endl;
}

void Managers::searchManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable) {
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

		if (!listChoice)
			cout << buffer << " not found." << endl;
		else
			displayList(*listChoice);
		break;
	default:
		cout << "Invalid input." << endl;
	}
}

void Managers::deleteManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable, stack<Card*>* deleteStack) {
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

		if (!listChoice) {
			cout << name << " not found." << endl;
			return;
		}
		else {
			displayList(*listChoice);
			cout << "Enter the key of one the cards displayed above." << endl;
			if (!validKey(key))
				return;
		}
		break;
	default:
		cout << "Invalid entry." << endl;
		return;
	}

	if (hashTable->search(key, TempCard)) {

		deleteStack->push(TempCard);
		cout << "\nPushing " << key << " onto undo-delete stack..." << endl;

		if (keyTree->remove(key))
			cout << key << " removed from keyTree." << endl;
		if (nameTree->remove(*TempCard))
			cout << key << " removed from nameTree." << endl;
		if (hashTable->remove(key, TempCard))
			cout << key << " removed from hashTable." << endl;
	}
	else
		cout << key << " does not exist." << endl;
}

void Managers::undoDeleteManager(BinarySearchTree* keyTree, AVLTree* nameTree, HashTable<string, Card*>* hashTable, stack<Card*>* deleteStack) {
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

void Managers::saveManager(BinarySearchTree* keyTree, stack<Card*>* deleteStack) {
	DeleteStack(deleteStack);
	cout << "Deleting stack..." << endl;
	InventoryManager::saveCurrentCollection(keyTree);
	cout << "Saving current collection..." << endl;
}

void Managers::DeleteStack(stack<Card*>* deleteStack) {
	while (!deleteStack->empty())
		deleteStack->pop();
}

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