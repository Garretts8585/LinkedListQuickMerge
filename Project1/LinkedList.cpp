#include "LinkedList.h"

// STL includes
#include <iostream>

static int ComparisonCount = 0;

LinkedList::LinkedList()
{
	Head = nullptr;
}

LinkedList::LinkedList(ListNode* InHead)
{
	Head = InHead;
}

LinkedList::~LinkedList()
{
	// Delete each here
}

void LinkedList::InsertValue(int Value)
{
	if (Head == nullptr)
	{
		Head = new ListNode(Value);
		return;
	}

	if (Value <= Head->Value)
	{
		ListNode* NewNode = new ListNode(Value);
		NewNode->Next = Head;
		Head = NewNode;
		return;
	}

	ListNode* CurrentNode = Head;

	while (CurrentNode)
	{
		if (CurrentNode->Value <= Value && (CurrentNode->Next == nullptr || Value <= CurrentNode->Next->Value))
		{
			ListNode* NewNode = new ListNode(Value);

			if (CurrentNode->Next)
			{
				NewNode->Next = CurrentNode->Next;
			}

			CurrentNode->Next = NewNode;

			return;
		}

		CurrentNode = CurrentNode->Next;
	}
}

void LinkedList::DebugPrint() const
{
	ListNode* CurrentNode = Head;
	while (CurrentNode)
	{
		std::cout << CurrentNode->Value;
		if (CurrentNode->Next)
		{
			std::cout << " -> ";
		}
		CurrentNode = CurrentNode->Next;
	}

	std::cout << std::endl;
}

LinkedList LinkedList::MergeLists(std::vector<LinkedList>& lists) {

	return QuickMergeLists(lists, 0, static_cast<int>(lists.size()) - 1);
}

LinkedList LinkedList::Merge2Lists(LinkedList& List1, LinkedList& List2) {
	// Exit early if one of the lists is empty 
	if (List1.Head == nullptr) {
		return List2;
	}
	else if (List2.Head == nullptr) {
		return List1;
	}

	ListNode* Head = nullptr;
	ListNode* CurrentNode = nullptr;

	ListNode* List1Node = List1.Head;
	ListNode* List2Node = List2.Head;

	// Add lowest node in the two lists until both are empty
	while (List1Node != nullptr || List2Node != nullptr) {
		// Select next node in the merged list
		const bool PickList1 = List2Node == nullptr || (List1Node && List1Node->Value < List2Node->Value);

		ListNode* NextNode = nullptr;
		if (PickList1) {

			NextNode = List1Node;
			List1Node = List1Node->Next;
		}
		else {

			NextNode = List2Node;
			List2Node = List2Node->Next;
		}

		// Set previous node's next pointer to the current node, or update the head point if unset
		if (!Head) {

			Head = NextNode;
			CurrentNode = NextNode;
		}
		else {

			CurrentNode->Next = NextNode;
			CurrentNode = NextNode;
		}
	}
	// Clear other lists
	List1.Head = nullptr;
	List2.Head = nullptr;
	return LinkedList(Head);
}

LinkedList LinkedList::QuickMergeLists(std::vector<LinkedList>& lists, int StartIndex, int EndIndex) {

	// Handle base cases were we have 2 or fewer lists to merge
	if (StartIndex > EndIndex) {
		// Nothing to merge in this case, return an empty list
		return LinkedList(nullptr);
	}
	else if (StartIndex == EndIndex) {

		return lists[StartIndex];
	}
	else if (StartIndex == EndIndex - 1) {

		return Merge2Lists(lists[StartIndex], lists[EndIndex]);
	}

	// Select a middle pivot index and quick merge the left and right, with the pivot being included in the right list
	int PivotIndex = (StartIndex + EndIndex + 1) / 2;
	LinkedList LeftMergedList = QuickMergeLists(lists, StartIndex, PivotIndex - 1);
	LinkedList RightMergedList = QuickMergeLists(lists, PivotIndex, EndIndex);

	// Return the merging of the two merged left and right lists 
	return Merge2Lists(LeftMergedList, RightMergedList);
}

LinkedList LinkedList::IterativeMergeLists(std::vector<LinkedList>& lists) {
	if (lists.size() == 0) {
		return LinkedList();
	}

	for (int i = 1; i < lists.size(); ++i) {
		lists[0] = Merge2Lists(lists[0], lists[i]);
	}
	return lists[0];
}