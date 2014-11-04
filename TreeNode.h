// Node for a binary tree
// Team 3 Group Project
// CIS 22C - 2014
// Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett

#ifndef _TREE_NODE
#define _TREE_NODE

#include <iomanip>
#include "Card.h"

class TreeNode
{
private:
	Card* cardPtr;
	TreeNode* leftPtr;		// Pointer to left child
	TreeNode* rightPtr;		// Pointer to right child

public:
	// constructor
	TreeNode()	{ leftPtr = 0; rightPtr = 0; }

	// accessors
	void setLeftPtr(TreeNode* left) { leftPtr = left; }
	void setRightPtr(TreeNode* right) { rightPtr = right; }
	void setCardPtr(Card* card) { cardPtr = card; }
	// mutators
	TreeNode* getLeftPtr() const  { return leftPtr; }
	TreeNode* getRightPtr() const { return rightPtr; }
	Card* getCardPtr() const { return cardPtr; }

	bool isLeaf() const { return (leftPtr == 0 && rightPtr == 0); }
};

#endif
