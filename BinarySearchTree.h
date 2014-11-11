// Node for a binary tree
// Team 3 Group Project
// CIS 22C - 2014
// Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

class BinarySearchTree : public BinaryTree
{
private:
	// internal insert node: insert newNode in nodePtr subtree
	TreeNode* _insert(TreeNode* nodePtr, TreeNode* newNode);
    //edward was here
	// internal remove node: locate and delete target node under nodePtr subtree
	TreeNode* _remove(TreeNode* nodePtr, const string target, bool & success);

	// delete target node from tree, called by internal remove node
	TreeNode* deleteNode(TreeNode* targetNodePtr);

	// remove the leftmost node in the left subtree of nodePtr
	TreeNode* removeLeftmostNode(TreeNode* nodePtr, string & successor);

	// search for target node
	TreeNode* findNode(TreeNode* treePtr, const string & target) const;

public:
	// insert a node at the correct location
	bool insert(const string & anEntry);
	// remove a node if found
	bool remove(const string & anEntry);
	// find a target node
	bool getEntry(const string & target, string & returnedItem) const;

};

#endif
