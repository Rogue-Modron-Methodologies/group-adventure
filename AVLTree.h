/**~*~*
  The AVLTree class is an AVL tree of Card objects with a
  non-unique key. In addition to containing various traversals
  and the functions necesarry for maintaining balance this tree
  also allows the user to either get all cards with the same name
  or search for a card with a specific name and code.

  Written by: Steven Bennett
  Date: 11/20/2014
  // Team 3 Group Project
  // CIS 22C - 2014
  // Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett
*~**/

#ifndef _AVL_TREE
#define _AVL_TREE

#include "AVLNode.h"

class AVLTree
{
protected:
	AVLNode*	rootPtr;		// ptr to root node
	int			count;			// number of nodes in tree
private:
	// delete all nodes from the tree
	void destroyTree(AVLNode* nodePtr);

	// internal traverse
	void _preorder(void visit(LinkedList &), AVLNode*) const;
	void _inorder(void visit(LinkedList &), AVLNode*) const;
	void _postorder(void visit(LinkedList &), AVLNode*) const;
	void _indentedList(void visit(LinkedList &), AVLNode*, int, char) ;

	// internal insert node: insert newNode in nodePtr subtree
	AVLNode* _insert(AVLNode* nodePtr, Card* newCardPtr);

	// internal remove node: locate and delete target node under nodePtr subtree
	AVLNode* _remove(AVLNode* nodePtr, Card target, bool & success);
	AVLNode* findMin(AVLNode* nodePtr);
	AVLNode* removeMin(AVLNode* nodePtr);

	// search for target node
	AVLNode* findNode(AVLNode* nodePtr, Card & target) const;


	// AVL height functions
	unsigned char height(AVLNode* nodePtr)
		{ return nodePtr ? nodePtr->getHeight() : 0; }
	int bfactor(AVLNode* nodePtr)
		{ return height(nodePtr->getRightPtr()) - height(nodePtr->getLeftPtr()); }
	void fixHeight(AVLNode* nodePtr);

	// AVL rotation functions
	AVLNode* rotateRight(AVLNode* nodePtr);
	AVLNode* rotateLeft(AVLNode* nodePtr);
	AVLNode* balance(AVLNode* nodePtr);
public:
	// "admin" functions
	AVLTree() { rootPtr = 0; count = 0; }
	AVLTree(const AVLTree & tree){ *this = tree; }
	~AVLTree() { destroyTree(rootPtr); }

	// common functions for all binary trees
	bool isEmpty() const	{ return count == 0; }
	int size() const	    { return count; }
	void clear()			{ destroyTree(rootPtr); rootPtr = 0; count = 0; }
	void preOrder(void visit(LinkedList &)) const { _preorder(visit, rootPtr); }
	void inOrder(void visit(LinkedList &)) const  { _inorder(visit, rootPtr); }
	void postOrder(void visit(LinkedList &)) const{ _postorder(visit, rootPtr); }
	void indentedList(void visit(LinkedList &)) { _indentedList(visit, rootPtr, 0, 'T'); }

	// insert a node at the correct location
	bool insert(Card* newEntry);
	// remove a node if found
	bool remove(Card & anEntry);
	// find a target node
	LinkedList *getEntry(Card & target) const;
	bool getCard(Card & target) const;
};
#endif
