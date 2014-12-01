

/** (っ◕‿◕)っ <(n_n<)

Inventory manager source file by Jordan Cox

Team 3 Group Project
CIS 22C - 2014
Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett

*/

#include "InventoryManager.h"

/** (っ◕‿◕)っ <(n_n<)
function calls other function, together they read files and creat initial data structures
*/
void InventoryManager::inventoryCreation(BinarySearchTree* binary_tree, AVLTree* avl_tree, HashTable<string, Card*>* &hash_table)
{
	ifstream input_file_names;
	string card_block;
	vector<Card*> card_collection;

	input_file_names.open("InputFileNames.txt");

	if (!input_file_names)														//if statement to ensure .txt file exists
	{
		cout << "\n\tERROR! InputFileNames.txt was not found!\n\n";

		exit(EXIT_FAILURE);
	}

	while (getline(input_file_names, card_block))
	{
		cout << "\n\tAdding cards from " << card_block << " to collection.\n";

		makeVector(card_collection, card_block);		//read file into vector

		if (!hash_table)								//beginning size of hash table
		{
			int prime;

			prime = getHashSizePrime(card_collection.size());

			hash_table = new HashTable<string, Card*>(Card::oat_hash, prime);

			cout << "\n\tHash size: " << hash_table->getTableSize() << "\n";

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
	cout << "\n\tLoad factor of hash table is " << fixed << setprecision(2) << hash_table->getLoadFactor() << ".\n";

	//if statment to check if load factor is greater then 75%, if yes call below
	if (hash_table->getLoadFactor() > 0.75)
		reformHashTable(hash_table);	//ReHash
}

/** (っ◕‿◕)っ <(n_n<)
reform hash table using count of old tables pointers
*/
void InventoryManager::reformHashTable(HashTable<string, Card*>* &hash_table)
{
	cout << "\n\tHash table load factor over 75%.\n\n\tRe-hashing.\n";

	int big_prime_number = getHashSizePrime((hash_table->getFilledSlots() + hash_table->getCollisions()));

	cout << "\n\tNew hash table size:- " << big_prime_number << endl;

	HashTable<string, Card*> *temp_table = new HashTable<string, Card*>(Card::oat_hash, *hash_table, big_prime_number);		//using old hash table to populate new one "re-hashing"

	delete hash_table;			//important re-hashing step

	hash_table = temp_table;			//important re-hashing step

	cout << "\n\tRe-hash complete.\n";

	cout << "\n\tLoad factor of hash table is " << fixed << setprecision(2) << hash_table->getLoadFactor() << ".\n\n";
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

	//while statment is to help get good name (don't forget there is a ! before the function call)
	while (!getSaveFileName(save_file_name));			//ask for name of save-to file and check availabilty of the name

	makeSaveFile(binary_tree, save_file_name);			//create file with user entered name and output card collection to file 
}

/** (っ◕‿◕)っ <(n_n<)
make sure user enters good name for save file
*/
bool InventoryManager::getSaveFileName(string &save_file_name)
{
	ifstream check_name;

	cout << "\n\n\tEnter name for save file. (Alphanumeric only)\n";		//cout message to request name

	getline(cin, save_file_name);

	removeNonAlphaNumeric(save_file_name);			//only alpanumeric allowed, this removes un-allowed characters

	if (save_file_name.size() == 0)
		return false;

	txtCheck(save_file_name);

	check_name.open(save_file_name);		

	if (!check_name)				//check name is good
	{
		cout << "\n\tSave file is called " << save_file_name << ".\n";

		return true;
	}
	else
	{
		check_name.close();

		cout << "\n\tA file with that name already exists\n";
		return replaceOrNot(save_file_name);				//if file exist check what user wants to do
	}
}

/** (っ◕‿◕)っ <(n_n<)
remove the untouchable characters from save file name
*/
void InventoryManager::removeNonAlphaNumeric(string &save_file_name)
{
	int i = save_file_name.size();

	while (i >= 0)
	{
		if (!isalnum(save_file_name[i]))
			save_file_name.erase(i, 1);
		
		i--;
	}
}

/** (っ◕‿◕)っ <(n_n<)
add a ".txt" if the user didn't include it
*/
void InventoryManager::txtCheck(string &save_file_name)
{
	int txt_check;

	txt_check = (save_file_name.size() - 4);							//int txt_check used for size comparisons and stating point for string comparison 

	if (txt_check > 0 && save_file_name.compare(txt_check, 4, ".txt") != 0)
	{
		save_file_name.append(".txt");
	}
	else if (txt_check < 1)
	{
		save_file_name.append(".txt");
	}

}

/** (っ◕‿◕)っ <(n_n<)
check if user wants to replace contents of a text file when saving current collection of cards
*/
bool InventoryManager::replaceOrNot(string &save_file_name)
{
	string option = " ";
	ofstream clear_file;

	while (option != "1" && option != "2")
	{ 
			//give user options in this situation
		cout << "\n\tWould you like to remove the card list saved in the file named \"" << save_file_name << "\" and save the new card list here?\n"
			<< "\t\t1: Remove old card list, save new card list in \"" << save_file_name << "\".\n"
			<< "\t\t2: Keep old card list and enter new file name to save the new card list to.\n";

		getline(cin, option);

		if (option == "1")
		{
			clear_file.open(save_file_name);			//emtpying file which will recieve new card collection

			cout << "\n\tContents of " << save_file_name << " successfully removed,\n"
				<< "\tnew card list will be saved here.\n";

			clear_file.close();

			/*const char * c = save_file_name.c_str();

			if (remove(c))										
			{ 
				cout << "\n\tContents of " << save_file_name << " successfully deleted,\n"
					<< "\tcards will be saved here.\n";

				return true;
			}
			else
			{ 
				cout << "\n\tError cleaning file\n";
				return false;
			}*/
		}
		else if (option == "2")
		{
			return false;										//user will be prompted to select a new name for a save file
		}
		else
		{
			cout << "\n\tINVALID ENTRY!!";		
		}
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
void InventoryManager::destroyEverything(BinarySearchTree* &binary_tree, AVLTree* &avl_tree, HashTable<string, Card*>* &hash_table)
{

	vector<Card*> card_collection;

	hash_table->getItems(card_collection);

	delete binary_tree;		//call delete binary_tree

	delete avl_tree;		//call delete avl_tree

	delete hash_table;		//call delete hash_table

	ripEmUp(card_collection);	//traverse hash_table deleting all card objects
}

/** (っ◕‿◕)っ <(n_n<)
delete cards
*/
void InventoryManager::ripEmUp(vector<Card*> &card_collection)
{
	for (int i = (card_collection.size()-1); i >= 0; i--)		//traverse hash_table deleting all card objects
	{
		delete card_collection[(i)];
	}
}