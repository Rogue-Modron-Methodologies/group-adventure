/**~*~*

Written by: Steven Bennett
Date: 11/20/2014
*~**/

#ifndef _AVL_TREE
#define _AVL_TREE

#include "AVLNode.h"

class AVLTree
{
protected:
	AVLNode* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree
private:
	// delete all nodes from the tree
	void destroyTree(AVLNode* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	//AVLNode* copyTree(const AVLNode* nodePtr);

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
	//AVLTree & operator = (const AVLTree & sourceTree);

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
