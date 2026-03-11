#pragma once

// STL includes
#include <vector>

/*
* Node for link list class
*/
struct ListNode {

	/* Constructors */
	ListNode() {

		Value = -1;
		Next = nullptr;
	}

	ListNode(int InValue) {

		Value = InValue;
		Next = nullptr;
	}

	// Number data the node holds
	int Value;

	// Point to the next element in the list, no next if null 
	ListNode* Next;
};

/*
* Class for a simple linked list that sorts elements in ascending order
*/
class LinkedList {

public:
	/* Constructors */
	LinkedList();
	LinkedList(ListNode* Head);

	/* Destructor */
	~LinkedList();

	/* Creates and inserts a new node with the given value into the list while keeping it in ascending order */
	void InsertValue(int Value);

	/* Prints value of nodes in order to standard output */
	void DebugPrint() const;

	/* Merges a list of separate linked lists together */
	static LinkedList MergeLists(std::vector<LinkedList>& lists);

	/* Merges two linked lists together */
	static LinkedList Merge2Lists(LinkedList& List1, LinkedList& List2);

protected:
	/** iteratively merges all lists together by choosing a pivot,
	*  merging all lists before the and after the pivot and recursively calling quick merge on
	*  the left and right until we are merging only 2 linked lists together
	*/
	static LinkedList QuickMergeLists(std::vector<LinkedList>& lists, int StartIndex, int EndIndex);

	/** Brute force merge algorthim to compare to QuickMergeLists */
	static LinkedList IterativeMergeLists(std::vector<LinkedList>& lists);

	// Head of the list, null if empty
	ListNode* Head;
};