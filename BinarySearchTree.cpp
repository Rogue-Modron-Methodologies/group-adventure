//
//  BinarySearchTree.cpp
//  Created by Edward Lim on 11/13/14.
//  Copyright (c) 2014 Edward Lim. All rights reserved.
// Team 3 Group Project
// CIS 22C - 2014
// Jamie Johnson, Edward Lim, Nick Arduini, Efrain Esquivel, Jordan Cox, and Steven Bennett
//

#include <stdio.h>
#include "BinarySearchTree.h"
#include <iomanip>
#include <fstream>
#include <iostream>

using namespace std;
/*
 INSERTS A NODE INTO THE BINARY TREE
 AND RETURNS TRUE
 */
bool BinarySearchTree::insert(Card* newCardPtr){
    
    TreeNode* newCard = new TreeNode();
    newCard->setCardPtr(newCardPtr);
    rootPtr = _insert(rootPtr,newCard);
    count++;
    return true;
}
/*
 THIS FUNCTION IS THE PRIVATE FUNCTION
 THAT GETS CALLED BY THE PUB FUNCTION
 INSERT()
 */
TreeNode* BinarySearchTree::_insert(TreeNode* nodePtr, TreeNode* newNode){
    
    if(nodePtr == 0){
        nodePtr = newNode;
    }
    else if(newNode->getCardPtr()->getCode() < nodePtr->getCardPtr()->getCode()){
        if(nodePtr->getLeftPtr())
            _insert(nodePtr->getLeftPtr(),newNode);
        else
            nodePtr->setLeftPtr(newNode);
    }
    else{
        if(nodePtr->getRightPtr())
            _insert(nodePtr->getRightPtr(),newNode);
        else
            nodePtr->setRightPtr(newNode);
    }
    return nodePtr;
}

/*
 DELETES THE TARGET NODE PASSED INTO FUNCTION
 USER PASSESS IN A CODE!!!
 ALWAYS ASSUME THAT INFO PASSED IN IS TRUE!!!
 */
bool BinarySearchTree::remove(const string & code){
    bool isRemoved = false;
    
    _remove(rootPtr, code);
    isRemoved = true, count--;
    
    return isRemoved; // toggles if not found
}
/*
 THIS FUNCTION IS CALLED BY THE PUBLIC FUNCTION
 AND IT REMOVES THE NODE PASSED IN, ALWAYS ASSUME
 NODE EXIST ALL IT DOES NOTHING
 */
TreeNode* BinarySearchTree::_remove(TreeNode* root, string target){
    
    if(root == NULL) return root;
    else if(target < root->getCardPtr()->getCode()){
        root->setLeftPtr((_remove(root->getLeftPtr(),target)));
    }
    else if(target > root->getCardPtr()->getCode()){
        root->setRightPtr((_remove(root->getRightPtr(),target)));
    }
    else{ //        basically keeps setting left/right as root node
        // Case 1:  No child
        if(root->getLeftPtr() == NULL && root->getRightPtr() == NULL) {			    		
        	delete root;
       		root = NULL;
        }
        //Case 2: One child
        else if(root->getRightPtr() == NULL) {
			TreeNode *temp = root->getLeftPtr();
			delete root;
			root = temp;
        }
        else if(root->getLeftPtr() == NULL) {
			TreeNode *temp = root->getRightPtr();
			delete root;
			root = temp;
        }
        // case 3: 2 children
        else {

            TreeNode *temp = findMin(root->getRightPtr());
            
            //Data transfer
            root->setCardPtr(temp->getCardPtr());
            
            root->setRightPtr(_remove(root->getRightPtr(),temp->getCardPtr()->getCode()));
        }
    }
    return root;
}
/*
 RETRUNS A POINTER, IF NOT FOUND RETURNS NULL,
 ELSE REUTRNS A POINTER TO THE NODE
 */
TreeNode* BinarySearchTree::findNode(const string & code){
    
    TreeNode* node= _findNode(rootPtr,code);

    return node;
    
}
/*
 THIS FUNCTION IS CALLED BY THE PUBLIC FUNCTION
 FINDNODE() AND IT CALLS PASSES THE ROOT AND THE
 KEY(CODE) AND RETURNS THE NODE IF FOUND, ELSE
 RETURNS NULL
 */
TreeNode* BinarySearchTree::_findNode(TreeNode* treePtr, const string & code){
    
    if(!treePtr) return treePtr;

    else if (code == treePtr->getCardPtr()->getCode())
        return treePtr;
    else if (code < treePtr->getCardPtr()->getCode()) {
        if (left == NULL)
            return NULL;
        else
            return _findNode(treePtr->getLeftPtr(), code);
    }
    else if (code > treePtr->getCardPtr()->getCode()) {
        if (right == NULL)
            return NULL;
        else
            return _findNode(treePtr->getRightPtr(), code);
    }
    return NULL;
}
/*
 THIS FUCNCTION DISPLAY THE TREE IN
 IN ORDER TRAVERSAL
 */
void BinarySearchTree::displayTree(void display(Card* const &card)){
	_displayTree(display, rootPtr);
}
void BinarySearchTree::_displayTree(void display(Card* const &card), TreeNode* nodePtr){
    
    if(nodePtr){
		_displayTree(display, nodePtr->getLeftPtr());
        
		display(nodePtr->getCardPtr());
        cout << endl;
        
		_displayTree(display, nodePtr->getRightPtr());
    }
}
/*
 THIS FUCNCTION DISPLAY THE TREE IN
 IN ORDER TRAVERSAL WITH INDENTS
 */
void BinarySearchTree::displayIndentedTree(void display(Card* const &card)){
    
    int lineNum = 0;
    
	_displayIndentedTree(display, rootPtr, lineNum);
    
}
/*
 THIS FUCNCTION DISPLAY THE TREE IN
 IN ORDER TRAVERSAL WITH INDENTS
 */
void BinarySearchTree::_displayIndentedTree(void display(Card* const &card), TreeNode* nodePtr, int &lineNum){ //       lineNum should always pass 0 in
    
    if(nodePtr){
        for(int i=0;i<lineNum;i++) {    cout << "\t";}
        lineNum++;
        
		cout << lineNum << ".) ";
		display(nodePtr->getCardPtr());
		cout << endl;
        
		_displayIndentedTree(display, nodePtr->getRightPtr(), lineNum);
		_displayIndentedTree(display, nodePtr->getLeftPtr(), lineNum);
        
        lineNum--;
        
    }
}
/*
 THIS FUCNCTION FINDS THE MINIMUN IN A
 TREE/ SUBTREE AND RETURNS THE POINTER
 TO THE NODE
 */
TreeNode* BinarySearchTree::findMin(TreeNode* root)
{
    while(root->getLeftPtr() != NULL) root = root->getLeftPtr();
    return root;
}

/*
 THIS FUNCTION CALLS THE DESTROY TREE
 PRIVATE FUNCTION AND RETURNS FALSE
 IF ROOT IS EMPTY
 */
bool BinarySearchTree::clear(){
    if(rootPtr == NULL){
        return false;
    }
    destroyTree(rootPtr);
    count = 0;
    return true;
}
/*
 THIS FUNCTION IS CALLED BY THE
 PUB FUCNCTION CLEAR(), IT DESTROYS
 ALL THE ELEMENTS IN THE TREE
 */
void BinarySearchTree::destroyTree(TreeNode* nodePtr){
    if (!nodePtr)return;
    destroyTree(nodePtr->getLeftPtr());
    destroyTree(nodePtr->getRightPtr());
	delete nodePtr;
    nodePtr = NULL;
}
/**
 RETURNS THE NUM OF NODES IN THE TREE
 */
int BinarySearchTree::size() const{
    return count;
}
/**
 RETURNS BOOL, IF TREE IS EMPTY RETURNS
 TRUE, ELSE FALSE
 */
bool BinarySearchTree::isEmpty() const{
    bool isEmp = false;
    if(count == 0) isEmp = true;
    
    return isEmp;
}
/*
 PASS IN A OFSTREAM OPERATOR AND
 A FILE NAME I WILL SAVE IT TO THE FILE
 (MAKE SURE STRING IS VALID BEFORE PASSED)
 */
void BinarySearchTree::writeTreeToFile(ofstream &outFile){
    _writeTreeToFile(rootPtr,outFile);
}
/*
 THIS FUNCTION GETS CALLED BY THE PUB
 FUCNTION WRITETREETOFILE() AND SAVES
 THE TREE TO A FILE
 */
void BinarySearchTree::_writeTreeToFile(TreeNode* current_pointer,ofstream &outFile){
    
    if (current_pointer == 0)
        return;
    
    _writeTreeToFile(current_pointer->getLeftPtr(), outFile);
    
    outFile << current_pointer->getCardPtr()->getCode() << "\t"
    << current_pointer->getCardPtr()->getName() << "\t"
    << current_pointer->getCardPtr()->getCost() << "\t"
    << current_pointer->getCardPtr()->getRarity() << endl;
    
    _writeTreeToFile(current_pointer->getRightPtr(), outFile);
    
}
