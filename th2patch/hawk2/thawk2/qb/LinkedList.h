#pragma once
namespace LinkedList
{
	struct LinkedListEntry {
		void* pValue = NULL;
		LinkedListEntry* pPrev = NULL;
		LinkedListEntry* pNext = NULL;
	};

	class LinkedList
	{
		public:
			LinkedListEntry* First;
			LinkedListEntry* Last;

			void AddFirst(LinkedListEntry* item);
			void AddLast(LinkedListEntry* item);
	};
}