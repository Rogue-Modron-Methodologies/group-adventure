// Node for a binary tree
// Team 3 Group Project
// CIS 22C - 2014
// Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett

#ifndef _HASH_ENTRY
#define _HASH_ENTRY

class HashEntry
{

private:
	int key;
	int value;

public:
	HashEntry(int key, int value);
	int getKey();
	int getValue();

};

#endif

