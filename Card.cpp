// Team 3 Group Project
// CIS 22C - 2014
// Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett

#include "Card.h"
#include <string>

using namespace std;

// Very slightly modified version of Jenkins' One-At-A-Time Hash
// http://en.wikipedia.org/wiki/Jenkins_hash_function#one-at-a-time
unsigned int Card::oat_hash(const string &key, int num )
{
    unsigned int h = 5381;

    for (int i = 0, len = key.length(); i < len; i++) {
        h += key[i];
        h += ( h << 10 );
        h ^= ( h >> 6 );
    }

    h += ( h << 3 );
    h ^= ( h >> 11 );
    h += ( h << 15 );
    return h % num;
 }

// These are not actually Card member functions, but overloaded friend functions
ostream& operator<<(ostream& os, const Card &card) {
    os << card.getCode() << " " << card.getName() << " "
       << card.getCost() << " " << card.getRarity();
    return os;
}

ostream& operator<<(ostream& os, Card* const &card) {
    os << *card;
    return os;
}

/**~*~*
Comparison operators are defined so that Card objects are compared based on their code data field.
*~**/
bool Card::operator>(const Card& other)
{
	if (code <= other.code)
		return false;
	return true;
}
bool Card::operator<(const Card& other)
{
	if (code >= other.code)
		return false;
	return true;
}
bool Card::operator>=(const Card& other)
{
	return !(*this < other);
}
bool Card::operator<=(const Card& other)
{
	return !(*this > other);
}
bool Card::operator==(const Card& other)
{
	if (code == other.code)
		return true;
	return false;
}
bool Card::operator!=(const Card& other)
{
	return !(*this == other);
}
