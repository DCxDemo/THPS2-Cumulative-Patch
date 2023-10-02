#include "stdafx.h"
#include "CBruce.h"

CVector* CBruce_GetPosition(void* pSkater)
{
	return (CVector*)((int)pSkater + 0x08);
}

CVector* CBruce_GetVelocity(void* pSkater)
{
	return (CVector*)((int)pSkater + 0x4C);
}



#define CBRUCE_RAILBALANCE 0x2EF0
//0x2ef4
//0x2ef8
//0x2efc
//0x2f00
//0x2f04
//0x2f08
//0x2f0c
//0x2f10
#define CBRUCE_MANUALBALANCE 0x2F14

#define CBRUCE_PHYSICSSTATE 0x30B8

CBruce::CBruce(void* pBruce)
{
	pSkater = (void*)(*((int*)pBruce));
}

int CBruce::ManualBalance()
{
	return *(int*)((int)pSkater + CBRUCE_MANUALBALANCE);
}

int CBruce::RailBalance()
{
	return *(int*)((int)pSkater + CBRUCE_RAILBALANCE);
}

int CBruce::PhysicsState()
{
	return *(int*)((int)pSkater + CBRUCE_PHYSICSSTATE);
}

int* CBruce_GetManualBalanceOld(void* pSkater)
{
	return (int*)((int)pSkater + 0x2F18);
}


int* CBruce_GetTestValueInt(void* pSkater, int offset)
{
	return (int*)((int)pSkater + offset);
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