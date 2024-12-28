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

enum class EStats : int {
	STATS_AIR = 0,
	STATS_HANGTIME = 1,
	STATS_OLLIE = 2,
	STATS_SPEED = 3,
	STATS_SPIN = 4,
	STATS_LANDING = 5,
	STATS_SWITCH = 6,
	STATS_RAILBALANCE = 7,
	STATS_LIPBALANCE = 8,
	STATS_MANUALS = 9
};


class CBruce
{
public:
	CBruce::CBruce(void*);
	void* pSkater;
	int CBruce::ManualBalance();
	int CBruce::RailBalance();
	int CBruce::PhysicsState();
	int CBruce::TotalScore();
	char* CBruce::CBruce_GetTrickName();
	int CBruce::GetValue(int addr);
	void CBruce::SetValue(int addr, int newValue);
	char CBruce::GetValueChar(char addr);
	int CBruce::Terrain();

};

CVector* CBruce_GetPosition(void* pSkater);
CVector* CBruce_GetVelocity(void* pSkater);
int* CBruce_GetTestValueInt(void* pSkater, int offset);