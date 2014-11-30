/**~*~*
  This is a sorted linked list of Card pointers. It begins at a head node
  and is terminated by a null pointer. The list can be searched and have 
  entries deleted. It also has a current pointer to allow outside programs
  to easily walk the list either from beginning to end or from a searched node.

  Written by: Steven Bennett
  Date: 11/20/2014
*~**/
#ifndef Linked_List_H
#define Linked_List_H

#include "Card.h"

class LinkedList
{
private:
	// Declare structure for list nodes
	struct ListNode
	{
		Card*		data;				// Data to be stored in the list
		ListNode*	next;				// Pointer to the next node
	};
	ListNode*	head;					// Pointer to the sentinel node
	ListNode*	curr;					// Pointer to the current node
	int			count;					// Count of total active nodes in the list
public:
	// Constructor
	LinkedList();

	// Destructor
	~LinkedList();

	// Linked List Methods
	int GetCount() const;
	bool IsEmpty() const;
	void ResetCurr() {curr = head;}
	bool Search(Card &target);
	bool GetNext(Card* &nextNode);
	bool GetFirst(Card* &nextNode);
	void Insert(Card* newData);
	bool Delete(Card* delData);
};

#endif
