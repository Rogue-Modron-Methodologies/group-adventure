#include "AVLTree.h"
///////////////////////// public function definitions ///////////////////////////

/**~*~*		insert
insert creates a node to store the data provided and then calls the
_insert function to insert the node into the tree.
*~**/
bool AVLTree::insert(Card* newEntry)
{
	rootPtr = _insert(rootPtr, newEntry);
	return true;
}

/**~*~*		remove
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

/**~*~*		getEntry
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

/**~*~*		getCard
getCard takes a card reference parameter that contains a name as well as
a code for the desired card. It first locates the linked list containing
all cards with the specified name in the AVL tree. If the name is found
then we call the linked lists Search function to find the card with the
specified code and return what the linked list search returns. Otherwise
the name given was not found and we return false.
*~**/
bool AVLTree::getCard(Card & target) const
{
	LinkedList* searchList = 0;

	searchList = getEntry(target);

	if (searchList)
		return searchList->Search(target);

	return false;
}

///////////////////////// private function definitions ///////////////////////////

/**~*~*		destroyTree
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
		delete nodePtr;
		nodePtr = NULL;
	}
	return;
}

/**~*~*		_preorder
_preorder is a recursive version of the pre-order traversal. First we check if the
pointer we are given is null. If it isn't then we process the data in the node and
call _preorder on the nodes left and right pointers.
*~**/
void AVLTree::_preorder(void visit(LinkedList &), AVLNode* nodePtr) const
{
	// Check if node pointer is valid
	if (nodePtr != 0)
	{
		// Fetch data from AVL tree node
		LinkedList* item = nodePtr->getItem();
		// Call the display function passed as a parameter
		visit(*item);

		// Recursive call on node's children
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	}
}

/**~*~*		_inorder
_inorder is a recursive version of the in-order traversal. First we check if the
pointer we are given is null. If it isn't then we call _inorder on the left pointer,
process the data in the node and finally call _inorder on the right pointer.
*~**/
void AVLTree::_inorder(void visit(LinkedList &), AVLNode* nodePtr) const
{
	// Check if node pointer is valid
	if (nodePtr != 0)
	{
		// Recursive call on node's left child
		_inorder(visit, nodePtr->getLeftPtr());

		// Fetch data from AVL tree node
		LinkedList* item = nodePtr->getItem();
		// Call the display function passed as a parameter
		visit(*item);

		// Recursive call on node's right child
		_inorder(visit, nodePtr->getRightPtr());
	}
}

/**~*~*		_postorder
_postorder is a recursive version of the post-order traversal. First we check if the
pointer we are given is null. If it isn't then we call _postorder on the nodes left
and right pointers and then process the data in the node.
*~**/
void AVLTree::_postorder(void visit(LinkedList &), AVLNode* nodePtr) const
{
	// Check if node pointer is valid
	if (nodePtr != 0)
	{
		// Recursive call on node's children
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());

		// Fetch data from AVL tree node
		LinkedList* item = nodePtr->getItem();
		// Call the display function passed as a parameter
		visit(*item);
	}
}

/**~*~*		_indentedList
_indentedList is nearly identical to the recursive pre-order traversal. However we have
an additional perameter that tracks the current level of the tree we are in. Then before
printing the data we print level-1 tabs followed by the level number and ". "
*~**/
void AVLTree::_indentedList(void visit(LinkedList &), AVLNode* nodePtr, int level, char child) 
{
	// Check if node pointer is valid
	if (nodePtr != 0)
	{
		level++;		// Increment level value to match current hight

		// Loop to print tabs for indendented display
		for (int i = 1; i < level; i++)
			cout << "\t";

		// Print out current hight followed by if this is a left or right child as well as the balance factor
		int bal = bfactor(nodePtr);
		cout << level << "." << child << "." << bal << " ";

		// Fetch data from AVL tree node
		LinkedList* item = nodePtr->getItem();
		// Call the display function passed as a parameter
		visit(*item);

		// Recursive call on node's children
		_indentedList(visit, nodePtr->getRightPtr(), level, 'R');
		_indentedList(visit, nodePtr->getLeftPtr(), level, 'L');
	}
}

/**~*~*		_insert
_insert traverses the tree until it reaches a null pointer or finds a
matching name already in the tree. If a null pointer is found a new
node is created and the card added to the linked list. Otherwise a match
is found and the new card is added to the linked list. In either case we
increment the tree's count and call the balance function on return to
maintain the tree's balance.
*~**/
AVLNode* AVLTree::_insert(AVLNode* nodePtr, Card* newCardPtr)
{
	// Check if node pointer is invalid
	if (!nodePtr)
	{
		// If nodePtr is invalid then a new node must be created
		nodePtr = new AVLNode(newCardPtr);
		count++;
		// Calling balance function in return to ensure AVL tree remains balanced
		return balance(nodePtr);
	}
	// Here we fetch the first card pointers in the lists so they can be compared to each other
	Card* nodeCardPtr = 0;
	nodePtr->getItem()->GetFirst(nodeCardPtr);

	// Here we traverse the list searching for a match or an invalid nodePtr
	if (nodeCardPtr->getName() > newCardPtr->getName())
		nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newCardPtr));
	else if (nodeCardPtr->getName() < newCardPtr->getName())
		nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newCardPtr));
	else
	{
		// If a match is found then we simply add the new card to the existing linked list
		nodePtr->getItem()->Insert(newCardPtr);
		count++;
	}

	// Calling balance function in return to ensure AVL tree remains balanced
	return balance(nodePtr);
}

/**~*~*		_remove
_remove traverses the AVL Tree looking for a card with a specified name and code.
First it goes through the tree looking for a matching name. If none is found then
success is set to false and a null pointer is returned. If the name is found then
we check how many different cards we have by that name. If it is more than one we
delete the card with the matching code from the linked list. Otherwise we delete
the entire node and update the structure of the AVL tree.
*~**/
AVLNode* AVLTree::_remove(AVLNode* nodePtr, Card target, bool & success)
{
	// First we check if nodePtr is invalid and if so set success to false and return a null pointer
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}

	// Here we create a card pointer and us it to compare the target against values stored in the tree
	Card* nodeCardPtr = 0;
	nodePtr->getItem()->GetFirst(nodeCardPtr);

	// Here we move through the tree comparing the current node to the target
	if (target.getName() < nodeCardPtr->getName())
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (target.getName() > nodeCardPtr->getName())
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else
	{
		// If we get here then we have found a node with a card name that matches the target

		// First we check if the linked list has more than one node in it
		if (nodePtr->getItem()->GetCount() > 1)
		{
			// If it does then we simply call the linked lists delete function
			success = nodePtr->getItem()->Delete(&target);
			return nodePtr;
		}
		// If we get here then we know we need to completely delete the node found
		// So we begin by saving the pointers to the target nodes children
		AVLNode* left = nodePtr->getLeftPtr();
		AVLNode* root = nodePtr->getRightPtr();		// We arbitrarily decide to have the right child be the prefered new root

		// With the children saved we delete the target node and set success to true
		delete nodePtr;
		success = true;

		// Now we check if the right child is actually valid
		if (!root)
			// If it isn't then we return the left child as the new root
			return left;

		// If the deleted node has a right subtree then we need to find the smallest value stored in it to use as the new root
		AVLNode* min = findMin(root);
		// Now we have to remove the smallest node from the right subtree so we can promote it to root
		min->setRightPtr(removeMin(root));
		min->setLeftPtr(left);

		// Finally we have to call balance to ensure the AVL tree remains balanced in spite of the removals
		return balance(min);
	}
	return balance(nodePtr);
}

/**~*~*		findMin
findMin checks if the nodePtr's left child is valid. If so it then
calls itself on the left child. If not then it has found the lowest
value in the tree and returns a pointer to that node.
*~**/
AVLNode* AVLTree::findMin(AVLNode* nodePtr)
{
	return nodePtr->getLeftPtr() ? findMin(nodePtr->getLeftPtr()) : nodePtr;
}

/**~*~*		removeMin
Similar to findMin removeMin moves through the tree until it reaches
a null left pointer. Once removeMin does it updates the parrent's
left pointer to nodePtr's right child instead of nodePtr. Then as
removeMin returns back through the tree it calls balance to ensure
that the AVL tree remains balanced.
*~**/
AVLNode* AVLTree::removeMin(AVLNode* nodePtr)
{
	// Check if nodePtr's left child is invalid
	if (nodePtr->getLeftPtr() == 0)
		// Now we have reached the smallest node and we return a pointer to it's right child
		return nodePtr->getRightPtr();
	// Here we update nodePtr's left child with the pointer returned by the next call of removeMin
	nodePtr->setLeftPtr(removeMin(nodePtr->getLeftPtr()));
	// Here we call balance to check for any imbalances as a result of the deletion
	return balance(nodePtr);
}
/**~*~*		findNode
findNode moves through the tree looking for the card name passed to it in the
target parameter. If the name is found then we return a pointer to the node
containing that card name. Otherwise we return a null pointer.
*~**/
AVLNode* AVLTree::findNode(AVLNode* nodePtr, Card & target) const
{
	// Here we check if nodePtr is invalid and if so return it as a failure indicator
	if (!nodePtr)
		return nodePtr;

	// Here we create a card pointer and us it to compare the target against values stored in the tree
	Card* nodeCardPtr = 0;
	nodePtr->getItem()->GetFirst(nodeCardPtr);

	// Here we move through the tree comparing the current node to the target
	if (nodeCardPtr->getName() > target.getName())
		nodePtr = findNode(nodePtr->getLeftPtr(), target);
	else if (nodeCardPtr->getName() < target.getName())
		nodePtr = findNode(nodePtr->getRightPtr(), target);

	// By this point if we haven't returned a null pointer or made a recursive call then we have found the target node.
	return nodePtr;
}

/**~*~*		fixHeight
fixHeight updates the height of a given node by fetching the height of its
left and right children. Then it compares them to find the larger value and
then adds one to it.
*~**/
void AVLTree::fixHeight(AVLNode* nodePtr)
{
	unsigned char hl = height(nodePtr->getLeftPtr());
	unsigned char hr = height(nodePtr->getRightPtr());
	nodePtr->setHeight((hl > hr ? hl : hr) + 1);
}

/**~*~*		rotateRight
rotateRight takes a node pointer and rotates it to the right and promotes
the nodes left child to the original nodes possition.
*~**/
AVLNode* AVLTree::rotateRight(AVLNode* nodePtr)
{
	// Here we save a pointer of what will be the new root of the subtree
	AVLNode* newRoot = nodePtr->getLeftPtr();

	// Here we move the new root's right subtree to be nodePtr's left subtree
	nodePtr->setLeftPtr(newRoot->getRightPtr());
	// Here we make nodePtr the new roots right subtree
	newRoot->setRightPtr(nodePtr);

	// Here we fix the hight of nodePtr and the new root
	fixHeight(nodePtr);
	fixHeight(newRoot);

	// Here we return a pointer to the new root
	return newRoot;
}

/**~*~*		rotateLeft
rotateLeft takes a node pointer and rotates it to the left and promotes
the nodes right child to the original nodes possition.
*~**/
AVLNode* AVLTree::rotateLeft(AVLNode* nodePtr)
{
	// Here we save a pointer of what will be the new root of the subtree
	AVLNode* newRoot = nodePtr->getRightPtr();

	// Here we move the new root's left subtree to be nodePtr's right subtree
	nodePtr->setRightPtr(newRoot->getLeftPtr());
	// Here we make nodePtr the new roots left subtree
	newRoot->setLeftPtr(nodePtr);

	// Here we fix the hight of nodePtr and the new root
	fixHeight(nodePtr);
	fixHeight(newRoot);

	// Here we return a pointer to the new root
	return newRoot;
}

/**~*~*		balance
balance first updates the height of the current node and then checks
if it is overly right or left heavy. If it is then it calls the
appropriate rotations and returns a node pointer to the root
of the current tree
*~**/
AVLNode* AVLTree::balance(AVLNode* nodePtr)
{
	// First we update nodePtr's height to ensure it is accurate
	fixHeight(nodePtr);

	// Here we check if nodePtr is overly right heavy
	if (bfactor(nodePtr) == 2)
	{
		// Here we check if the right subtree is left heavy
		if (bfactor(nodePtr->getRightPtr()) < 0)
			// If it is then we need to do a right rotation on the right subtree
			nodePtr->setRightPtr(rotateRight(nodePtr->getRightPtr()));
		// To set up for the left rotation of the tree
		return rotateLeft(nodePtr);
	}

	// Here we check if nodePtr is overly left heavy
	if (bfactor(nodePtr) == -2)
	{
		// Here we check if the right subtree is right heavy
		if (bfactor(nodePtr->getLeftPtr()) > 0)
			// If it is then we need to do a left rotation on the left subtree
			nodePtr->setLeftPtr(rotateLeft(nodePtr->getLeftPtr()));
		// To set up for the right rotation of the tree
		return rotateRight(nodePtr);
	}

	return nodePtr;
}
