#include "LinkedList.h"

void Test0()
{
	LinkedList L0;
	L0.InsertValue(8);
	L0.InsertValue(4);
	L0.InsertValue(12);
	L0.InsertValue(20);
	L0.InsertValue(16);

	LinkedList L1;
	L1.InsertValue(5);
	L1.InsertValue(20);
	L1.InsertValue(15);
	L1.InsertValue(10);
	L1.InsertValue(25);

	std::vector<LinkedList> Lists;
	Lists.push_back(L0);
	Lists.push_back(L1);
	LinkedList MergedList = LinkedList::MergeLists(Lists);
	MergedList.DebugPrint();
}

void Test1()
{
	LinkedList L0;
	L0.InsertValue(8);
	L0.InsertValue(4);
	L0.InsertValue(12);
	L0.InsertValue(20);
	L0.InsertValue(16);

	LinkedList L1;
	L1.InsertValue(5);
	L1.InsertValue(20);
	L1.InsertValue(15);
	L1.InsertValue(10);
	L1.InsertValue(25);

	LinkedList L2;
	L2.InsertValue(6);
	L2.InsertValue(30);
	L2.InsertValue(12);
	L2.InsertValue(24);
	L2.InsertValue(18);

	std::vector<LinkedList> Lists;
	Lists.push_back(L0);
	Lists.push_back(L1);
	Lists.push_back(L2);

	LinkedList& MergedList = LinkedList::MergeLists(Lists);
	MergedList.DebugPrint();
}

void StressTest0()
{
	std::vector<LinkedList> Lists;
	for (int i = 0; i < 200; ++i)
	{
		LinkedList List;
		for (int j = 0; j < 100; ++j)
		{
			List.InsertValue(rand() % 100 + (i * 5));
		}

		Lists.push_back(List);
	}

	LinkedList MergedList = LinkedList::MergeLists(Lists);
	MergedList.DebugPrint();
}

int main()
{
	Test1();
}
