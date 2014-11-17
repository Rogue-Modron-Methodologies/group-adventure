// Hash Node for list entries in hash table
// Also the superclass of HeadHashNode, which is the entry in the HashTable

// Team 3 Group Project
// CIS 22C - 2014
// Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett

#ifndef _HASH_NODE
#define _HASH_NODE

template <class KeyType, class ItemType>
class HashNode
{

private:
    KeyType key;
    ItemType item;
    HashNode *next;

public:

    HashNode(const KeyType &key, const ItemType &item);
    virtual ~HashNode() {}

    // Getters and Setters
    void setKey(const KeyType &k) { key = k; }
    void setItem(const ItemType &i) { item = i; }
    void setNext(HashNode *n) { next = n; }
    void getKey(KeyType &kt) const { kt = key; }
    void getItem(ItemType &it) const { it = item; }
    HashNode* getNext() const { return next; }

};

// Constructor
template <class KeyType, class ItemType>
HashNode<KeyType, ItemType>::HashNode(const KeyType &key, const ItemType &item)
{
    this->key = key;
    this->item = item;
    next = 0;
}

#endif
