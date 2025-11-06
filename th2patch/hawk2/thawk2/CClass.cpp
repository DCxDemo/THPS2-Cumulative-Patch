#include "stdafx.h"
#include "CClass.h"
#include "mem.h"

int* TotalCClassUsage = (int*)0x00567580;
int* Used = (int*)0x5675d0;

void* testMenu = (void*)0x0055e8a0;

void* CClass::operator new(size_t size)
{
	//calculate aligned size by 4 (mips legacy?)
	int sizeAligned = (size + 3) & ~3;

	//get pointer to allocated memory
	void* pAlloc = NsMem::Mem_New(size, 0, 1, 0);

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
	NsMem::Mem_Delete(p);

	//decrease usage var
	*TotalCClassUsage -= used - *Used;

	if (*TotalCClassUsage < 0)
		printf_s("my bad\r\n");
}

/*
void* __fastcall CMenu__AddEntry_Hook(void* _this, void* _edx, char* pText)
{
	return CMenu__AddEntry(_this, pText);
}

void* __fastcall _new_CMenu_Hook(void* _this, void* _edx, int param_2, int param_3, char param_4, short param_5, short param_6, int param_7)
{
	return _new_CMenu(_this, param_2, param_3, param_4, param_5, param_6, param_7);
}



void CreateTestMenu()
{
	printf_s("CreateTestMenu\n");

	testMenu = _new_CClass(0x180);
	if (testMenu != NULL)
	{
		testMenu = _new_CMenu_Hook(testMenu, NULL, 0x100, 0, 0, 0x14f, 0x100, 0x16);
	}
	
	CMenu__AddEntry_Hook(testMenu, NULL, "test 1");
	CMenu__AddEntry_Hook(testMenu, NULL, "test 2");
	CMenu__AddEntry_Hook(testMenu, NULL, "test 3");
	
}

*/
