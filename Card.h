// Node for a binary tree
// Team 3 Group Project
// CIS 22C - 2014
// Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett

#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

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
        void setCode(string newCode) { code = newCode; }
        void setName(string newName) { name = newName; }
        void setCost(string newCost) { cost = newCost; }
        void setRarity(string newRarity) { rarity = newRarity; }

        string getCode() const { return code; }
        string getName() const { return name; }
        string getCost() const { return cost; }
        string getRarity() const { return rarity; }

        // Overloaded ostream operators to display Card and Card*
        friend ostream& operator<<(ostream& os, const Card &card);
        friend ostream& operator<<(ostream& os, Card* const &card);

        // These two static functions are used to pass into generic containers
        static unsigned int oat_hash(const string &key, int num);
        static void display(Card* const &card) { cout << card; }
};

#endif // CARD_H
