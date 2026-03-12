#include "LinkedList.h"

// STL includes
#include <iostream>

static int ComparisonCount = 0;

LinkedList::LinkedList() {
	Head = nullptr;
}

LinkedList::LinkedList(ListNode* InHead) {

	Head = nullptr;

	//Deep copy list
	while (InHead != nullptr) {
		InsertValue(InHead->Value);

		InHead = InHead->Next;
	}
}

LinkedList::LinkedList(const LinkedList& RHS) {

	Head = nullptr;

	ListNode* RHHead = RHS.Head;

	//Deep copy list
	while (RHHead != nullptr) {
		InsertValue(RHHead->Value);

		RHHead = RHHead->Next;
	}
}

LinkedList& LinkedList::operator=(const LinkedList& RHS) {

	Head = nullptr;
	ListNode* RHHead = RHS.Head;

	//Deep copy list
	while (RHHead != nullptr) {
		InsertValue(RHHead->Value);

		RHHead = RHHead->Next;
	}

	return *this;
}

LinkedList::~LinkedList() {
	// Delete each node
	ListNode* CurrentNode = Head;
	while (CurrentNode != nullptr) {
		ListNode* NextNode = CurrentNode->Next;

		delete CurrentNode;

		CurrentNode = NextNode;
	}
}

void LinkedList::InsertValue(int Value)
{
	if (Head == nullptr) {
		Head = new ListNode(Value);
		return;
	}

	if (Value <= Head->Value) {
		ListNode* NewNode = new ListNode(Value);
		NewNode->Next = Head;
		Head = NewNode;
		return;
	}

	ListNode* CurrentNode = Head;

	while (CurrentNode) {

		if (CurrentNode->Value <= Value && (CurrentNode->Next == nullptr || Value <= CurrentNode->Next->Value)) {
			ListNode* NewNode = new ListNode(Value);

			if (CurrentNode->Next) {
				NewNode->Next = CurrentNode->Next;
			}

			CurrentNode->Next = NewNode;

			return;
		}

		CurrentNode = CurrentNode->Next;
	}
}

void LinkedList::DebugPrint() const {

	ListNode* CurrentNode = Head;
	while (CurrentNode) {

		std::cout << CurrentNode->Value;
		if (CurrentNode->Next) {
			std::cout << " -> ";
		}
		CurrentNode = CurrentNode->Next;
	}

	std::cout << std::endl;
}

LinkedList& LinkedList::MergeLists(std::vector<LinkedList>& lists) {

	int MergedIndex = -1;
	QuickMergeLists(lists, 0, static_cast<int>(lists.size()) - 1, MergedIndex);

	return lists[MergedIndex];
}

ListNode* LinkedList::Merge2Lists(LinkedList& List1, LinkedList& List2) {
	// Exit early if one of the lists is empty 
	if (List1.Head == nullptr) {
		return List2.Head;
	}
	else if (List2.Head == nullptr) {
		return List1.Head;
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
	
	// Set 1 to the combined list and clear 2
	List1.Head = Head;
	List2.Head = nullptr;

	return List1.Head;
}

ListNode* LinkedList::QuickMergeLists(std::vector<LinkedList>& lists, int StartIndex, int EndIndex, int& OutMergedIndex) {

	// Handle base cases were we have 2 or fewer lists to merge
	if (StartIndex > EndIndex) {
		// Nothing to merge in this case, return an empty list
		return nullptr;
	}
	else if (StartIndex == EndIndex) {

		OutMergedIndex = StartIndex;
		return lists[StartIndex].Head;
	}
	else if (StartIndex == EndIndex - 1) {

		OutMergedIndex = StartIndex;
		return Merge2Lists(lists[StartIndex], lists[EndIndex]);
	}

	// Select a middle pivot index and quick merge the left and right, with the pivot being included in the right list
	int PivotIndex = (StartIndex + EndIndex + 1) / 2;

	int MergedIndexLeft = -1;
	ListNode* LeftMergedList = QuickMergeLists(lists, StartIndex, PivotIndex - 1, MergedIndexLeft);

	int MergedIndexRight = -1;
	ListNode* RightMergedList = QuickMergeLists(lists, PivotIndex, EndIndex, MergedIndexRight);

	// Return the merging of the two merged left and right lists 

	OutMergedIndex = MergedIndexLeft;
	return Merge2Lists(lists[MergedIndexLeft], lists[MergedIndexRight]);
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