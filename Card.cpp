// Team 3 Group Project
// CIS 22C - 2014
// Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett

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
