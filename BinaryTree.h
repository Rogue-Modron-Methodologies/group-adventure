// Node for a binary tree
// Team 3 Group Project 
// CIS 22C - 2014
// Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett

#ifndef _BINARY_TREE
#define _BINARY_TREE

using namespace std;

#include "TreeNode.h"

class BinaryTree
{
protected:
	TreeNode* rootPtr;					// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
	BinaryTree() { rootPtr = 0; count = 0; }
	BinaryTree(const BinaryTree & sourceTree);
	BinaryTree & operator = (const BinaryTree & sourceTree);
	virtual ~BinaryTree() { };

	// common functions for all binary trees
	bool isEmpty() const;
	int size() const;
	int getHeight() const;
	void clear();
	// recursive traversals
	void preOrder() const;
	void inOrder() const;
	void postOrder() const;
	// abstract functions to be implemented by derived class
	virtual bool insert(const string & code) = 0;
	virtual bool remove(const string & code) = 0;
	virtual bool getEntry(const string & anEntry, string & returnedItem) const = 0;

private:
	// delete all nodes from the tree
	void destroyTree(TreeNode* nodePtr);
	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	TreeNode* copyTree(const TreeNode* nodePtr);
	// recursive traversals
	void _preorder(TreeNode* nodePtr) const;
	void _inorder(TreeNode* nodePtr) const;
	void _postorder(TreeNode* nodePtr) const;

};

#endif 
