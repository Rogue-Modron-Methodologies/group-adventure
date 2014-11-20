// HeadHashNode extends HashNode to include a list counter and member functions
// Instantiations of this class are entries in the HashTable

// Team 3 Group Project
// CIS 22C - 2014
// Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett

#ifndef _HEAD_HASH_NODE
#define _HEAD_HASH_NODE

#include "HashNode.h"

template <class KeyType, class ItemType>
class HeadHashNode : public HashNode<KeyType, ItemType>
{

private:
    // listCount is count of all entries in the list, not including the first
    int listCount;

public:
    // Constructor and destructor
    HeadHashNode(const KeyType &key, const ItemType &item);
    ~HeadHashNode();

    // Methods to add or remove HashNode from list
    void addToList(const KeyType &key, const ItemType &item);
    bool removeFromList(const KeyType &target, ItemType &item);

    // Returns listCount
    int getListCount() const { return listCount; }

};

// Constructor
template <class KeyType, class ItemType>
HeadHashNode<KeyType, ItemType>::HeadHashNode(const KeyType &key,
                    const ItemType &item) : HashNode<KeyType, ItemType>(key, item)
{
    listCount = 0;
}

// Destructor
template <class KeyType, class ItemType>
HeadHashNode<KeyType, ItemType>::~HeadHashNode()
{
    HashNode<KeyType, ItemType> *deleteNode = this->getNext(), *oneAfter;
    while (deleteNode) {
        oneAfter = deleteNode->getNext();
        delete deleteNode;
        deleteNode = oneAfter;
    }
}

// Member function to add HashNode to list
template <class KeyType, class ItemType>
void HeadHashNode<KeyType, ItemType>::addToList(const KeyType &key, const ItemType &item)
{
    HashNode<KeyType, ItemType> *walk = this;
    while (walk->getNext()) {
        walk = walk->getNext();
    }
    walk->setNext(new HashNode<KeyType, ItemType>(key, item));
    listCount++;
}

// Member function to remove an entry from the list
// Returns true if member found and also returns by value item removed

// If item is the first in list (ie the HeadHashNode), the function will not
// delete this entry. If it's the only entry in the list, no change to the list
// is made. If not, we set the Head's key, item, and next to that of the next
// item in the list, before deleting the next item.

// If item is not first in the list, we just delete that entry
template <class KeyType, class ItemType>
bool HeadHashNode<KeyType, ItemType>::removeFromList(const KeyType &target, ItemType &item)
{
    KeyType key;
    this->getKey(key);
    HashNode<KeyType, ItemType> *nWalk = this->getNext(), *prev = this;
    // Need special handling if key found is first entry
    if (key == target) {
        this->getItem(item);
        // If head has next item, set the Head's key, item, and next to that
        // of the next item in the list, before deleting the next item.
        if (listCount) {
            listCount--;
            KeyType nextKey;
            nWalk->getKey(nextKey);
            this->setKey(nextKey);
            ItemType nextItem;
            nWalk->getItem(nextItem);
            this->setItem(nextItem);
            this->setNext(nWalk->getNext());
            delete nWalk;
        }
        return true;
    }
    // Handles cases when key found in node other than head
    while (nWalk) {
        nWalk->getKey(key);
        if (key == target) {
            listCount--;
            nWalk->getItem(item);
            prev->setNext(nWalk->getNext());
            delete nWalk;
            return true;
        }
        prev = nWalk;
        nWalk = nWalk->getNext();

    }
    return false;
}
#endif

