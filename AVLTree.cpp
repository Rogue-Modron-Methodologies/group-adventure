#include "AVLTree.h"
///////////////////////// public function definitions ///////////////////////////

/**~*~*
Here we define how the = operator is used to copy one tree over another.
First we check if the trees have identical root pointers and if so we
immediately return out of the function. If they are different then we
first clear out the destination tree and then copy the contents of the
source tree as well as it's node count into the destination tree.
*~**//*
AVLTree & AVLTree::operator=(const AVLTree & sourceTree)
{
	if (rootPtr == sourceTree.rootPtr)
		return *this;

	clear();
	rootPtr = copyTree(sourceTree.rootPtr);
	count = sourceTree.count;

	return *this;
}*/

/**~*~*
insert creates a node to store the data provided and then calls the
_insert function to insert the node into the tree.
*~**/
bool AVLTree::insert(Card* newEntry)
{
	rootPtr = _insert(rootPtr, newEntry);
	return true;
}

/**~*~*
remove takes the provided target value and calls the _remove function.
If the desired entry is found target is updated with the entries data
and remove returns true, otherwise remove returns false.
*~**/
bool AVLTree::remove(Card & target)
{
	bool isSuccessful = false;
	rootPtr = _remove(rootPtr, target, isSuccessful);
	return isSuccessful;
}

/**~*~*
getEntry takes the provided target value and calls the findNode function.
If the desired entry is found returnedItem is updated with the entries
data and getEntry returns true, otherwise getEntry returns false.
*~**/
LinkedList* AVLTree::getEntry(Card & target) const
{
	AVLNode* returnPtr = 0;
	LinkedList* returnedList = 0;

	returnPtr = findNode(rootPtr, target);
	if (returnPtr)
	{
		returnedList = returnPtr->getItem();
	}

	return returnedList;
}

/**~*~*
*~**/
bool AVLTree::getCard(Card & target) const
{
	LinkedList* searchList = 0;

	searchList = getEntry(target);
	return searchList->Search(target);
}

///////////////////////// private function definitions ///////////////////////////

/**~*~*
destroyTree checks if the pointer it is given is valid. If it is
destroyTree then calls itself on the nodes left and right pointers
and then deletes the node.
*~**/
void AVLTree::destroyTree(AVLNode* nodePtr)
{
	if (nodePtr)
	{
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		//delete nodePtr;
		nodePtr = NULL;
	}
	return;
}

/**~*~*
copyTree checks if the pointer it is given is valid. If it is copyTree
then creates a new node and copies the value stored in the node into
the new node. Then copyTree calls itself on the left and right node
pointers.
*~**//*
AVLNode* AVLTree::copyTree(const AVLNode* nodePtr)
{
AVLNode* newNodePtr = 0;
if (nodePtr)
{
newNodePtr = new AVLNode(nodePtr->getItem());
newNodePtr->setLeftPtr(copyTree(nodePtr->getLeftPtr()));
newNodePtr->setRightPtr(copyTree(nodePtr->getRightPtr()));
}

return newNodePtr;
}*/

/**~*~*
_preorder is a recursive version of the pre-order traversal. First we check if the
pointer we are given is null. If it isn't then we process the data in the node and
call _preorder on the nodes left and right pointers.
*~**/
void AVLTree::_preorder(void visit(LinkedList &), AVLNode* nodePtr) const
{
	if (nodePtr != 0)
	{
		LinkedList* item = nodePtr->getItem();
		visit(*item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	}
}

/**~*~*
_inorder is a recursive version of the in-order traversal. First we check if the
pointer we are given is null. If it isn't then we call _inorder on the left pointer,
process the data in the node and finally call _inorder on the right pointer.
*~**/
void AVLTree::_inorder(void visit(LinkedList &), AVLNode* nodePtr) const
{
	if (nodePtr != 0)
	{
		_inorder(visit, nodePtr->getLeftPtr());
		LinkedList* item = nodePtr->getItem();
		visit(*item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}

/**~*~*
_postorder is a recursive version of the post-order traversal. First we check if the
pointer we are given is null. If it isn't then we call _postorder on the nodes left
and right pointers and then process the data in the node.
*~**/
void AVLTree::_postorder(void visit(LinkedList &), AVLNode* nodePtr) const
{
	if (nodePtr != 0)
	{
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		LinkedList* item = nodePtr->getItem();
		visit(*item);
	}
}

/**~*~*
_indentedList is nearly identical to the recursive pre-order traversal. However we have
an additional perameter that tracks the current level of the tree we are in. Then before
printing the data we print level-1 tabs followed by the level number and ". "
*~**/
void AVLTree::_indentedList(void visit(LinkedList &), AVLNode* nodePtr, int level, char child) 
{

	if (nodePtr != 0)
	{
		level++;
		for (int i = 1; i < level; i++)
			cout << "\t";
		int bal = bfactor(nodePtr);
		cout << level << "." << child << "." << bal << " ";
		LinkedList* item = nodePtr->getItem();
		visit(*item);

		_indentedList(visit, nodePtr->getRightPtr(), level, 'R');
		_indentedList(visit, nodePtr->getLeftPtr(), level, 'L');
	}
}

/**~*~*
_insert traverses the tree until it reaches a null pointer. Once _insert does
it adds the provided entry into the tree and updates the tree's counter.
*~**/
AVLNode* AVLTree::_insert(AVLNode* nodePtr, Card* newCardPtr)
{
	if (!nodePtr)
	{
		nodePtr = new AVLNode(newCardPtr);
		count++;
		return balance(nodePtr);
	}
	// Here we fetch the first card pointers in the lists so they can be compared to each other
	Card* nodeCardPtr = 0;
	nodePtr->getItem()->GetFirst(nodeCardPtr);

	if (nodeCardPtr->getName() > newCardPtr->getName())
		nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newCardPtr));
	else if (nodeCardPtr->getName() < newCardPtr->getName())
		nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newCardPtr));
	else
	{
		nodePtr->getItem()->Insert(newCardPtr);
		count++;
	}

	return balance(nodePtr);
}

/**~*~*
*~**/
AVLNode* AVLTree::_remove(AVLNode* nodePtr, Card target, bool & success)
{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}

	Card* nodeCardPtr = 0;
	nodePtr->getItem()->GetFirst(nodeCardPtr);

	if (target.getName() < nodeCardPtr->getName())
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (target.getName() > nodeCardPtr->getName())
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else
	{
		if (nodePtr->getItem()->GetCount() > 1)
		{
			success = nodePtr->getItem()->Delete(&target);
			return nodePtr;
		}

		AVLNode* left = nodePtr->getLeftPtr();
		AVLNode* root = nodePtr->getRightPtr();

		delete nodePtr;

		if (!root)
		{
			success = true;
			return left;
		}

		AVLNode* min = findMin(root);
		min->setRightPtr(removeMin(root));
		min->setLeftPtr(left);

		success = true;
		return balance(min);
	}
	return balance(nodePtr);
}

/**~*~*
*~**/
AVLNode* AVLTree::findMin(AVLNode* nodePtr)
{
	return nodePtr->getLeftPtr() ? findMin(nodePtr->getLeftPtr()) : nodePtr;
}

/**~*~*
*~**/
AVLNode* AVLTree::removeMin(AVLNode* nodePtr)
{
	if (nodePtr->getLeftPtr() == 0)
		return nodePtr->getRightPtr();
	nodePtr->setLeftPtr(removeMin(nodePtr->getLeftPtr()));
	return balance(nodePtr);
}
/**~*~*
*~**/
AVLNode* AVLTree::findNode(AVLNode* nodePtr, Card & target) const
{
	if (!nodePtr)
		return nodePtr;
	Card* nodeCardPtr = 0;
	nodePtr->getItem()->GetFirst(nodeCardPtr);
	if (nodeCardPtr->getName() > target.getName())
		nodePtr = findNode(nodePtr->getLeftPtr(), target);
	else if (nodeCardPtr->getName() < target.getName())
		nodePtr = findNode(nodePtr->getRightPtr(), target);
	return nodePtr;
}

/**~*~*
*~**/
void AVLTree::fixHeight(AVLNode* nodePtr)
{
	unsigned char hl = height(nodePtr->getLeftPtr());
	unsigned char hr = height(nodePtr->getRightPtr());
	nodePtr->setHeight((hl > hr ? hl : hr) + 1);
}

/**~*~*
*~**/
AVLNode* AVLTree::rotateRight(AVLNode* nodePtr)
{
	AVLNode* newRoot = nodePtr->getLeftPtr();

	nodePtr->setLeftPtr(newRoot->getRightPtr());
	newRoot->setRightPtr(nodePtr);

	fixHeight(nodePtr);
	fixHeight(newRoot);

	return newRoot;
}

/**~*~*
*~**/
AVLNode* AVLTree::rotateLeft(AVLNode* nodePtr)
{
	AVLNode* newRoot = nodePtr->getRightPtr();

	nodePtr->setRightPtr(newRoot->getLeftPtr());
	newRoot->setLeftPtr(nodePtr);

	fixHeight(nodePtr);
	fixHeight(newRoot);

	return newRoot;
}

/**~*~*
*~**/
AVLNode* AVLTree::balance(AVLNode* nodePtr)
{
	fixHeight(nodePtr);

	if (bfactor(nodePtr) == 2)
	{
		if (bfactor(nodePtr->getRightPtr()) < 0)
			nodePtr->setRightPtr(rotateRight(nodePtr->getRightPtr()));
		return rotateLeft(nodePtr);
	}

	if (bfactor(nodePtr) == -2)
	{
		if (bfactor(nodePtr->getLeftPtr()) > 0)
			nodePtr->setLeftPtr(rotateLeft(nodePtr->getLeftPtr()));
		return rotateRight(nodePtr);
	}

	return nodePtr;
}
