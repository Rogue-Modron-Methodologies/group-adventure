/**~*~*

Written by: Steven Bennett
Date: 11/20/2014
*~**/

#ifndef _AVL_NODE
#define _AVL_NODE

#include "LinkedList.h"

class AVLNode
{
private:
	LinkedList  item;         // Data portion
	unsigned char		  height;		// height of the node
	AVLNode* leftPtr;			// Pointer to left child
	AVLNode* rightPtr;		// Pointer to right child

public:
	// constructors
	AVLNode(Card* anItem)	{ item.Insert(anItem);
		height = 0; leftPtr = 0; rightPtr = 0;}
	AVLNode(const LinkedList & anItem,
		unsigned char size,
		AVLNode* left, AVLNode* right)
		{item = anItem; height = size;
		leftPtr = left; rightPtr = right;}
	// accessors
	void setItem(const LinkedList & anItem) { item = anItem; }
	void setHeight(const unsigned char & size) { height = size; }
	void setLeftPtr(AVLNode* left) { leftPtr = left; }
	void setRightPtr(AVLNode* right) { rightPtr = right; }
	// mutators
	LinkedList* getItem()
		{LinkedList* itemPtr = &item; return itemPtr;}
	unsigned char getHeight() const	 { return height; }
	AVLNode* getLeftPtr() const  { return leftPtr; }
	AVLNode* getRightPtr() const { return rightPtr; }

	bool isLeaf() const { return (leftPtr == 0 && rightPtr == 0); }
};

#endif 
