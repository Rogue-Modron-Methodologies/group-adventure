// Node for a binary tree
// Team 3 Group Project
// CIS 22C - 2014
// Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett

#ifndef CARD_H
#define CARD_H

#include <string>

using namespace std;

class Card
{
    private:
        string code;			// Unique Key - Combination of Set and Card Number
        string name;			// Name of the Card
        string cost;			// Casting Cost of the Card
        string rarity;			// Rarity of the Card
    public:
        Card();
        ~Card();
        void setCode(const string newCode) { code = newCode; }
        void setName(const string newName) { name = newName; }
        void setCost(const string newCost) { cost = newCost; }
        void setRarity(const string newRarity) { rarity = newRarity; }
        string getCode() const { return code; }
        string getName() const { return name; }
        string getCost() const { return cost; }
        string getRarity() const { return rarity; }


};

#endif // CARD_H
