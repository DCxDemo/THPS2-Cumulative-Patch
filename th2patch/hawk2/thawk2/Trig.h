#include "stdafx.h"
#include "types.h"
#include "..\patch\hook.h"

namespace Trig
{
	enum class ENodeType : short
	{
		Baddy = 1,
		Crate = 2,
		Point = 3,
		AutoExec = 4,
		PowerUp = 5,
		CommandPoint = 6,
		SeedableBaddy = 7,
		Restart = 8,
		Barrel = 9,
		RailPoint = 10,
		RailDef = 11,
		TrickOb = 12,
		CamPt = 13,
		GoalOb = 14,
		AutoExec2 = 15,
		TrickObCluster = 17, // in mhpb
		Terminator = 255
	};

	extern Hook::Reroute* pHookList;

	typedef void(*Trig_LoadTRG_t)(char* trgName);
	typedef void(*ExecuteCommandList_t)(void* pList, int nodeIndex, bool param_3);
	typedef void(*Trig_ScanRestart_t)();
	//typedef void(*Trig_InitialParseTRGFile_t)();

	static const Trig_LoadTRG_t Trig_LoadTRG = (Trig_LoadTRG_t)0x004c2390;
	//void Trig_LoadTRG(char* trgName);
	static const ExecuteCommandList_t ExecuteCommandList = (ExecuteCommandList_t)0x004c3020;
	static const Trig_ScanRestart_t Trig_ScanRestart = (Trig_ScanRestart_t)0x004c5100;
	//static const Trig_InitialParseTRGFile_t Trig_InitialParseTRGFile = (Trig_InitialParseTRGFile_t)0x004c52b0;
	void Trig_InitialParseTRGFile();
}