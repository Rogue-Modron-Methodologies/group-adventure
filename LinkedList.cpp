#include "LinkedList.h"

/**~*~*		Constructor
Creates the head node for the list and initializes the values
for the head node, count and current pointer.
*~**/
LinkedList::LinkedList()
{
	head = new ListNode;
	curr = head;
	count = 0;

	// initializing sentinel node
	head->next = 0;
}

/**~*~*		Destructor
Moves through the list from the beginning to the end and deletes
all of the nodes contained in the list.
*~**/
LinkedList::~LinkedList()
{
	ListNode *nodePtr;
	ListNode *nextPtr;

	nodePtr = head;

	do
	{
		nextPtr = nodePtr->next;
		delete nodePtr;
		nodePtr = nextPtr;
	} while (nodePtr);
}

/**~*~*		GetCount
Returns the total number of active nodes in the list.
*~**/
int LinkedList::GetCount() const
{
	return count;
}

/**~*~*		IsEmpty
Returns true is the list is empty and false if the list
contains active nodes.
*~**/
bool LinkedList::IsEmpty() const
{
	return count == 0;
}

/**~*~*		Search
Moves through the list and stops once it reaches a value greater
than or equal to its target value. Returns false if the target is
not found and true if it is. It also returns the data contained
in the node through reference parameters and sets the current
pointer to the target node.
*~**/
bool LinkedList::Search(Card &target)
{
	ListNode *nodePtr;

	if (!this)
	{
		return false;
	}

	nodePtr = head;

	// Move through the list until we reach a value greater than or equal to the target or a null pointer
	while (nodePtr->next && *nodePtr->next->data <= target)
	{
		nodePtr = nodePtr->next;
	}

	// Check if the node was not found and if so return false.
	if (*nodePtr->data != target)
		return false;

	// Update reference parameters with data from the node found.
	target = *nodePtr->data;

	// Set the current pointer to the target node.
	curr = nodePtr;

	return true;
}

/**~*~*		GetNext
Moves the current pointer to the next node and
returns the data contained in the new node
through reference parameters. Returns false
if the next node is null and resets curr to the
head node, otherwise it returns true.
*~**/
bool LinkedList::GetNext(Card* &nextNode)
{
	if (!curr->next)
	{
		curr = head;
		return false;
	}

	curr = curr->next;
	nextNode = curr->data;

	return true;
}

/**~*~*		GetFirst
Moves the current pointer to the next node and
returns the data contained in the new node
through reference parameters. Returns false
if the next node is null and resets curr to the
head node, otherwise it returns true.
*~**/
bool LinkedList::GetFirst(Card* &firstNode)
{
	if (!head->next)
	{
		return false;
	}

	firstNode = head->next->data;

	return true;
}

/**~*~*		Insert
Moves through the list and stops once it reaches a value greater
than or equal to its target value. Then it inserts the new node
by updating the relevant pointers. Finally it updates the
list count.
*~**/
void LinkedList::Insert(Card* newData)
{
	ListNode *newNode;
	ListNode *nodePtr;
	ListNode *prevPtr;

	// Initialize list node and store data in it
	newNode = new ListNode;
	newNode->data = newData;

	prevPtr = head;
	nodePtr = head->next;

	// Move through the list to find the point of insertion
	while (nodePtr && *nodePtr->data <= *newData)
	{
		nodePtr = nodePtr->next;
		prevPtr = prevPtr->next;
	}

	// Update all relevant pointers
	newNode->next = nodePtr;
	prevPtr->next = newNode;

	// Update the list count
	count++;
}

/**~*~*		Delete
Moves through the list and stops once it reaches a value greater
than or equal to its target value. Then it deletes the data by
updating the pointers and returns the contents by reference.
Finally it updates the current pointer to the previous node as
well as the count for the list.
*~**/
bool LinkedList::Delete(Card* delData)
{
	ListNode *nodePtr;
	ListNode *prevPtr;

	nodePtr = head->next;
	prevPtr = head;

	// Move through the list until we find a value that is not less than the data to be deleted
	while (nodePtr && *nodePtr->data < *delData)
	{
		nodePtr = nodePtr->next;
		prevPtr = prevPtr->next;
	}

	// Check if the node we stopped at matches the data to be deleted and if not return false
	if (*nodePtr->data != *delData)
		return false;

	delData = nodePtr->data;

	// Update pointers to remove node from the list and delete the node
	prevPtr->next = nodePtr->next;

	curr = prevPtr;

	delete nodePtr;

	// Update the list count
	count--;

	return true;
}
