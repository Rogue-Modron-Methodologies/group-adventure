// Node for a binary tree
// Team 3 Group Project
// CIS 22C - 2014
// Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett

#ifndef _HASH_TABLE
#define _HASH_TABLE

#include "HashEntry.h"
#include "Card.h"

class HashTable {
private:
      HashEntry **table;
public:
      HashTable();
      void get(const string &key, const Card &c);
      void put(const Card &c);
      int hash(const string &key);
      ~HashTable();
};

#endif

