#pragma once

struct CVector {
	int X;
	int Y;
	int Z;
};

typedef struct CVector CVector;

struct CSVector {
	short X;
	short Y;
	short Z;
};

typedef struct CSVector CSVector;

CVector* CBruce_GetPosition(void* pBruce);
CVector* CBruce_GetVelocity(void* pBruce);
int* CBruce_GetTestValueInt(void* pBruce, int offset);