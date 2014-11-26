// Node for a binary tree
// Team 3 Group Project
// CIS 22C - 2014
// Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE
#include "TreeNode.h"

class BinarySearchTree
{
protected:
    TreeNode* rootPtr;					// ptr to root node
    int count;							// number of nodes in tree
        
public:
    // "admin" functions
    BinarySearchTree() { rootPtr = 0; count = 0; }
    BinarySearchTree(const BinarySearchTree & sourceTree);
    BinarySearchTree & operator = (const BinarySearchTree & sourceTree);
    ~BinarySearchTree() { };
    
    // common functions for all BinarySearchTree trees
    bool isEmpty() const;
    int size() const;
    bool clear(); //        destroys tree

    // insert a node at the correct location
    bool insert(Card* nodePtr);
    // remove a node if found
    bool remove(const string & code);
    // find a target node
    TreeNode* findNode(const string & target);
    // displays tree in order
    void displayTree();
    // display indented tree
    void displayIndentedTree();
    //  write tree to file
    void writeTreeToFile(ofstream &outFile);
    
private:
    
	// internal insert node: insert newNode in nodePtr subtree
	TreeNode* _insert(TreeNode* nodePtr, TreeNode* newNode);

	// internal remove node: locate and delete target node under nodePtr subtree
	TreeNode* _remove(TreeNode* nodePtr, const string target);

    // search for target node
    TreeNode* _findNode(TreeNode* treePtr, const string & code);
    
    //seach for min node
    TreeNode* findMin(TreeNode* root);
    
    void _displayTree(TreeNode* nodePtr);
    
    void _displayIndentedTree(TreeNode* nodePtr, int &lineNum);
    
    // delete all nodes from the tree
    void destroyTree(TreeNode* nodePtr);
    // copy from the tree rooted at nodePtr and returns a pointer to the copy
    TreeNode* copyTree(const TreeNode* nodePtr);
    // recursive traversals
    void _inorder(TreeNode* nodePtr) const;
    
	void _writeTreeToFile(TreeNode* current_pointer, ofstream &outFile);

};

#endif





































