#include "stdafx.h"
#include "LinkedList.h"

namespace LinkedList
{
	void LinkedList::AddFirst(LinkedListEntry* item)
	{
		if (First == NULL)
		{
			First = item;

			if (Last == NULL)
				Last = item;
		}
		else
		{
			item->pNext = First;
			First->pPrev = item;
			First = item;
		}
	}

	void LinkedList::AddLast(LinkedListEntry* item)
	{
		if (Last == NULL)
		{
			Last = item;
			if (First == NULL)
				First = item;
			else
				First->pNext = item;
		}
		else
		{
			item->pPrev = Last;
			Last->pNext = item;
			Last = item;
		}
	}
}