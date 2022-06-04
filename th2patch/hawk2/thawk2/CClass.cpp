#include "stdafx.h"
#include "CClass.h"

int* TotalCClassUsage = (int*)0x00567580;
int* Used = (int*)0x5675d0;

void* CClass::operator new(size_t size)
{
	//calculate aligned size by 4 (mips legacy?)
	int sizeAligned = (size + 3) & ~3;

	//get pointer to allocated memory
	void* pAlloc = Mem_New(size, 0, 1, 0);

	//reset allocation
	memset(pAlloc, 0, sizeAligned);

	//increase usage var
	*TotalCClassUsage += 4 + sizeAligned;

	return pAlloc;
}

void CClass::operator delete(void* p)
{
	//remember how much we used before deletion
	int used = *Used;

	//delete
	Mem_Delete(p);

	//decrease usage var
	*TotalCClassUsage -= used - *Used;

	if (*TotalCClassUsage < 0)
		printf("my bad\r\n");
}