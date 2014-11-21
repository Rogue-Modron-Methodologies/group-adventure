#include "Card.h"
#include <string>

using namespace std;

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

ostream& operator<<(ostream& os, const Card* const &card) {
    os << *card;
    return os;
}
