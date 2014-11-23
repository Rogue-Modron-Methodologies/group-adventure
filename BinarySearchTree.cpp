//
//  BinarySearchTree.cpp
//  hw4
//
//  Created by Edward Lim on 11/13/14.
//  Copyright (c) 2014 Edward Lim. All rights reserved.
//

#include <stdio.h>
<<<<<<< HEAD
#include "BinaryTree.h"
=======
>>>>>>> 78f6e996f33ec374414674b67dbcdf5a20487cd8
#include "BinarySearchTree.h"
#include <iomanip>
#include <fstream>
#include <iostream>

using namespace std;
/*
 INSERTS A NODE INTO THE BINARY TREE
modified pointer to node is passed in
 */
bool BinarySearchTree::insert(Card* newCardPtr){
    
    TreeNode* newCard = new TreeNode;
    newCard->setCardPtr(newCardPtr);
    rootPtr = _insert(rootPtr,newCard);
    count++;
    return true;
}

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
 IF NODE IS NOT FOUND, RETURNS FALSE
 */
bool BinarySearchTree::remove(const string & code){
    bool isRemoved = false;
    _remove(rootPtr, code);
    isRemoved = true, count--;
    
    return isRemoved;
}

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
            //delete root;
            root = NULL; 
        }
        //Case 2: One child
        else if(root->getRightPtr() == NULL) {
            //TreeNode* temp = root;
            root = root->getLeftPtr();
            //delete temp;
        }
        else if(root->getLeftPtr() == NULL) {
            //TreeNode* temp = root;
            root = root->getRightPtr();
            //delete temp;
        }
        // case 3: 2 children
        else {
            TreeNode *temp = findMin(root->getRightPtr());
            
            //Data transfer
            root->getCardPtr()->setName(temp->getCardPtr()->getName());
            root->getCardPtr()->setCode(temp->getCardPtr()->getCode());
            root->getCardPtr()->setCost(temp->getCardPtr()->getCost());
            root->getCardPtr()->setRarity(temp->getCardPtr()->getRarity());
     
            root->setRightPtr(_remove(root->getRightPtr(),temp->getCardPtr()->getCode()));
        }
    }
    return root;
}
/*
 RETRUNS A BOOL, IF NOT FOUND RETURNS FALSE, 
 ELSE RETURNS TRUE WITH DISPLAY MESSAGE. 
 (NO DISP MSG IF FALSE)
 */
TreeNode* BinarySearchTree::findNode(const string & code){
    
    TreeNode* node= _findNode(rootPtr,code);

    return node;

}
TreeNode* BinarySearchTree::_findNode(TreeNode* treePtr, const string & code){
    if(!treePtr) return treePtr;
    
    else if(treePtr->getCardPtr()->getCode() == code) return treePtr;
    
    else if(code < treePtr->getCardPtr()->getCode()){
        if(!(treePtr->getLeftPtr()))
            return treePtr->getLeftPtr();
        else
            _findNode(treePtr->getLeftPtr(),code);
    }
    else{
        if(treePtr->getRightPtr())
            return treePtr->getRightPtr();
        else
            _findNode(treePtr->getRightPtr(),code);
    }
    return treePtr = NULL;
}
/*
 THIS FUCNCTION DISPLAY THE TREE IN 
 IN ORDER TRAVERSAL
 */
void BinarySearchTree::displayTree(){
    _displayTree(rootPtr);
}
void BinarySearchTree::_displayTree(TreeNode* nodePtr){
    
    if(nodePtr){
        _displayTree(nodePtr->getLeftPtr());
<<<<<<< HEAD

             cout << "Name: "<< nodePtr->getCardPtr()->getName() << " "
                  << "Code: "<<nodePtr->getCardPtr()->getCode() << endl;

=======
        
        cout << "\n---------------------------\n"
             << "Name: "<< nodePtr->getCardPtr()->getName() << endl
             << "Code: "<<nodePtr->getCardPtr()->getCode() << endl
             << "Rarity: "<<nodePtr->getCardPtr()->getRarity() << endl
             << "Cost: "<<nodePtr->getCardPtr()->getCost() << endl
             << "\n---------------------------\n";
>>>>>>> 78f6e996f33ec374414674b67dbcdf5a20487cd8
        _displayTree(nodePtr->getRightPtr());
    }
}
/*
 THIS FUCNCTION DISPLAY THE TREE IN
 IN ORDER TRAVERSAL WITH INDENTS
 */
void BinarySearchTree::displayIndentedTree(){
    
    int lineNum = 0;
    
    _displayIndentedTree(rootPtr,lineNum);
    
}

void BinarySearchTree::_displayIndentedTree(TreeNode* nodePtr, int &lineNum){ //       lineNum should always pass 0 in
    
    if(nodePtr){
        for(int i=0;i<lineNum;i++) {    cout << "\t";}
        lineNum++;
        
<<<<<<< HEAD
        cout << lineNum << ".) " << "Name: "<< nodePtr->getCardPtr()->getName();
        cout << " " << "Code: " << nodePtr->getCardPtr()->getCode() << endl;
=======
        cout << lineNum << ".) " << nodePtr->getCardPtr()->getName();
        cout << "\t" << nodePtr->getCardPtr()->getCode() << endl;
>>>>>>> 78f6e996f33ec374414674b67dbcdf5a20487cd8
        _displayIndentedTree(nodePtr->getRightPtr(),lineNum);
        _displayIndentedTree(nodePtr->getLeftPtr(),lineNum);
        
        lineNum--;
        
    }
}
//Function to find minimum in a tree.
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

void BinarySearchTree::destroyTree(TreeNode* nodePtr){
    if (!nodePtr)return;
    destroyTree(nodePtr->getLeftPtr());
    destroyTree(nodePtr->getRightPtr());
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

void BinarySearchTree::_writeTreeToFile(TreeNode* root,ofstream &outFile){
    _writeTreeToFile(root->getLeftPtr(),outFile);
    outFile << root->getCardPtr()->getName() << " "
<<<<<<< HEAD
            << root->getCardPtr()->getCode() << endl;
=======
            << root->getCardPtr()->getCode();
>>>>>>> 78f6e996f33ec374414674b67dbcdf5a20487cd8
    _writeTreeToFile(root->getRightPtr(),outFile);
}












