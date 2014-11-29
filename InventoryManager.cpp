

/** (っ◕‿◕)っ <(n_n<)

Inventory manager source file by Jordan Cox

Team 3 Group Project
CIS 22C - 2014
Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett

*/

#include "InventoryManager.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream> 

using namespace std;

/** (っ◕‿◕)っ <(n_n<)
function calls other function, together they read files and creat initial data structures
*/
void InventoryManager::inventoryCreation(BinarySearchTree* binary_tree, AVLTree* avl_tree, HashTable<string, Card*>* &hash_table)
{
	ifstream input_file_names;
	string card_block;
	vector<Card*> card_collection;

	input_file_names.open("InputFileNameTemp.txt");

	if (!input_file_names)														//if statement to ensure .txt file exists
	{
		cout << "\n\tERROR! InputFileName.txt was not found!\n\n";

		exit(EXIT_FAILURE);
	}

	while (getline(input_file_names, card_block))
	{
		makeVector(card_collection, card_block);		//read file into vector

		if (!hash_table)								//beginning size of hash table
		{
			int prime;

			prime = getHashSizePrime(card_collection.size());

			hash_table = new HashTable<string, Card*>(Card::oat_hash, prime);

			cout << "Hash size: " << hash_table->getTableSize() << "\n";

		}

		populateStructures(binary_tree, avl_tree, hash_table, card_collection);	//CreateAndPopulateStructures

		checkLoadFactor(hash_table);					//check if re-hash needed
	}

	input_file_names.close();
}

/** (っ◕‿◕)っ <(n_n<)
read from files to make a vector of card pointers
*/
void InventoryManager::makeVector(vector<Card*> &card_collection, string card_block)
{
	ifstream block_source;
	string temp_code, block_name, temp_buff, code, name, cost, rarity;

	block_source.open(card_block.c_str());						//first 2 characters of first line of document represent block of magic cards

	getline(block_source, temp_buff);					//get first line of document

	block_name = temp_buff.substr(0, 2);				//get first 2 characters
	
	while (getline(block_source, code, '\t'))			//read document and assign card
	{
		code.insert(0, block_name);						//isnerts block code before card number to create unique key

		getline(block_source, name, '\t');				//puts card name into string

		for (int i = 0; i < name.length(); i++)			//needs to be uppercase
			name[i] = toupper(name[i]);

		getline(block_source, cost, '\t');				//puts card cost into string

		getline(block_source, rarity, '\n');			//puts card rarity into string

		for (int i = 0; i < rarity.length(); i++)		//needs to be uppercase
			rarity[i] = toupper(rarity[i]);

		Card* new_ptr = new Card(code, name, cost, rarity); //create new card object

		card_collection.push_back(new_ptr);				//add card pointer to vector
	}
	block_source.close();
}

/** (っ◕‿◕)っ <(n_n<)
populate the structures with cards (pointers)
*/
void InventoryManager::populateStructures(BinarySearchTree* binary_tree, AVLTree* avl_tree, HashTable<string, Card*>* hash_table, vector<Card*>& card_collection)
{
	int random_select;		
	Card* hold;

	srand(time(NULL));		

	//for loop repeats with size of vector and calls following functions from 
	//team's work
	while (0 < card_collection.size())
	{
		random_select = rand() % card_collection.size();			//randomise entree into structures (doesn't matter for hash, but what the hell)

		hash_table->addEntry(card_collection[random_select]->getCode(), card_collection[random_select]);	//Insert Hash

		binary_tree->insert(card_collection[random_select]);		//Insert binary Tree

		avl_tree->insert(card_collection[random_select]);		//Insert avl Tree

		card_collection.erase(card_collection.begin() + random_select);			//removes item just entered so it can't be randomly selected again
	}
}

/** (っ◕‿◕)っ <(n_n<)
checks load factor of hash
*/
void InventoryManager::checkLoadFactor(HashTable<string, Card*>* &hash_table)
{
	//if statment to check if load factor is greater then 75%, if yes call below
	if (hash_table->getLoadFactor() > 0.75)
		reformHashTable(hash_table);	//ReHash
}

/** (っ◕‿◕)っ <(n_n<)
reform hash table using count of old tables pointers
*/
void InventoryManager::reformHashTable(HashTable<string, Card*>* &hash_table)
{
	cout << "\n\n\tHash table load factor over 75%.\n\n\tRe-hashing.\n";

	int big_prime_number = getHashSizePrime((hash_table->getFilledSlots() + hash_table->getCollisions()));

	cout << "\n\tNew hash table size:- " << big_prime_number << endl;

	HashTable<string, Card*> *temp_table = new HashTable<string, Card*>(Card::oat_hash, *hash_table, big_prime_number);		//using old hash table to populate new one "re-hashing"

	delete hash_table;			//important re-hashing step

	hash_table = temp_table;			//important re-hashing step

	cout << "\n\tRe-hash complete.\n";
}

/** (っ◕‿◕)っ <(n_n<)
doubles the int passed into the function
*/
int InventoryManager::getHashSizePrime(int get_prime)
{
	int find_prime = ((get_prime * 2) + 1);		//start search with an odd number over twice the size of the current count

	while (checkNotPrime(find_prime))			//as long as function returns true keep searching for prime number
	{
		find_prime += 2;						//keep searching for a prime through odd numbers
	}

	return find_prime;
}

/** (っ◕‿◕)っ <(n_n<)
finds next prime number after int passed into function
*/
bool InventoryManager::checkNotPrime(int find_prime)
{
	for (int i = 3; i < (find_prime / 2); i += 2)
	{
		if (find_prime % i == 0)				//as soon as an interger leaves no remainder return true to continue search
			return true;
	}

	return false;								//prime number found
}

/** (っ◕‿◕)っ <(n_n<)
save the current collection of cards with user chosen name
*/
void InventoryManager::saveCurrentCollection(BinarySearchTree* binary_tree)
{
	string save_file_name;
	ofstream save_file;

	//while statment is to help get good name (don't forget there is a ! before the function call)
	while (!getSaveFileName(save_file_name));			//ask for name of save-too file and check availabilty of the name

	//save_file.open(save_file_name.c_str());

	makeSaveFile(binary_tree, save_file_name);			//create file with user entered name and output card collection to file 
}

/** (っ◕‿◕)っ <(n_n<)
make sure user enters good name for save file
*/
bool InventoryManager::getSaveFileName(string &save_file_name)
{
	ifstream check_name;
	int txt_check;

	cout << "\n\n\tEnter name of save file.\n";		//cout message to request name

	getline(cin, save_file_name);

	txt_check = (save_file_name.size() - 4);

	if (txt_check > 0 && save_file_name.compare(txt_check, 4, ".txt") != 0)
	{
		save_file_name.append(".txt");
	}

	check_name.open(save_file_name.c_str());

	if (!check_name)				//check name is good
	{
		check_name.close();
		return true;
	}
	else
	{
		cout << "\n\tA file with that name already exists\n";
		return replaceOrNot(save_file_name);
	}

	
}

bool InventoryManager::replaceOrNot(string &save_file_name)
{
	string option;

	cout << "\n\tWould you like to replace the file named " << save_file_name << " with a new card list?\n"
		<< "\t\t1: Keep file named " << save_file_name << " BUT replace the list of cards.\n"
		<< "\t\t2: Enter new file name to save the list of cards to.\n";

	getline(cin, option);

	if (option == "1")
	{
	const char * c = save_file_name.c_str();

		if (remove(c))
			cout << "\n\tFile successfully deleted\n";
		else
			cout << "\n\tError deleting file\n";
		return true;
	}
	else if (option == "2")
	{
		return false;
	}
	else
	{
		cout << "\n\tINVALID ENTRY!!";

		return replaceOrNot(save_file_name);
	}

}

/** (っ◕‿◕)っ <(n_n<)
save current collection to file
*/
void InventoryManager::makeSaveFile(BinarySearchTree* binary_tree, string save_file_name)
{
	ofstream save_file;

	save_file.open(save_file_name.c_str());

	binary_tree->writeTreeToFile(save_file);		//save tree to user named file

	save_file.close();
}

/** (っ◕‿◕)っ <(n_n<)
delete all stuctures to release memory
*/
void InventoryManager::destroyEverything(BinarySearchTree* binary_tree, AVLTree* avl_tree, HashTable<string, Card*>* hash_table)
{
	delete binary_tree;		//call delete binary_tree

	delete avl_tree;		//call delete avl_tree

	ripEmUp(hash_table);	//traverse hash_table deleting all card objects

	delete hash_table;		//call delete hash_table
}

/** (っ◕‿◕)っ <(n_n<)
delete cards
*/
void InventoryManager::ripEmUp(HashTable<string, Card*>* hash_table)
{
	vector<Card*> card_collection;

	hash_table->getItems(card_collection);

	for (int i = card_collection.size(); i >= 0; i--)		//traverse hash_table deleting all card objects
	{
		delete card_collection[i];
	}
}