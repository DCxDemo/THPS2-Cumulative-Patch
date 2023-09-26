#include "stdafx.h"
#include "CBruce.h"

CVector* CBruce_GetPosition(void* pBruce)
{
	return (CVector*)((int)pBruce + 0x08);
}

CVector* CBruce_GetVelocity(void* pBruce)
{
	return (CVector*)((int)pBruce + 0x4C);
}

int* CBruce_GetTestValueInt(void* pBruce, int offset)
{
	return (int*)((int)pBruce + offset);
}


/*
0000	dword - ptr CBruce Vtable
0004	dword - 202? unknown
0008	Vector (3 dwords) - position
0014	dword - ?? somehow related to friction or smth, updated on grass, resets by rail
0018	dword - related to rail balance? but not bluntslide
001C	dword - 0?
0020	dword - 0?
0024	dword - 00404040 some color?
0028	4 words, 3 = 1000, maybe scale?
002C	^^^
0030	dword - 0?

*/