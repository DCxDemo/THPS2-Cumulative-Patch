#include "stdafx.h"
#include "types.h"
#include "..\patch\hook.h"

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

namespace Trig
{
	extern Hook::Reroute* pHookList;

	typedef struct TrigFileHeader {
		char magic[4]; // _TRG
		ushort version;	// must be 2 
		ushort project;	// must be 0, 1 in mhpb
		int numNodes;	// number of nodes
		int* Nodes; // pointers to nodes
	} TrigFileHeader;


	extern int* NumCheatRestarts;
	extern int* NumHorseRestarts;
	extern TrigFileHeader* TrigFile;
	extern int* OffsetList;
	extern short** ppOffsetList;
	extern int* NumNodes;


	// Trig_ClearTrigMenu
	// Trig_DeleteCommandPoints
	// Trig_ResetCPCollisionFlags
	// Trig_ResetCPExecutedFlags
	// Trig_TriggerCommandPoint
	// Trig_SetRestart
	// CBruce::FudgeAngles??????

	typedef void(*Trig_ExecuteRestart_t)();

	// typedef void(*Trig_DeleteTrigFile_t)();
	typedef void(*Trig_LoadTRG_t)(char* trgName);
	// some unused loading func, create empty?
	// GetFlag
	// SkipFlags
	// Trig_CreateObject - big one
	typedef void(*Trig_SendPulseToNode_t)(ushort pNode);
	// GetCommandPoint
	// Trig_SendPulse
	// SendSignalToNode
	// SendSignalToLinks
	// SendSuspend
	// SendUnSuspend
	// SendSuspendOrActivate
	// SkipString
	// Trig_AllocateDualBuffer - unused
	// Trig_RemoveDualBuffer
	typedef void(*ExecuteCommandList_t)(void* pList, int nodeIndex, bool param_3);
	// SendVisibleFromNode
	// SendKillFromNode
	// KillInList
	// SkipCommand
	typedef void(*Trig_ScanRestart_t)();
	//typedef void(*Trig_InitialParseTRGFile_t)();
	// Trig_ParseTRGFile
	// CreateCommandPoint
	typedef short* (*Trig_GetLinksPointer_t)(int nodeIndex);


	static const Trig_ExecuteRestart_t Trig_ExecuteRestart = (Trig_ExecuteRestart_t)0x004c2090;

	static const Trig_SendPulseToNode_t Trig_SendPulseToNode = (Trig_SendPulseToNode_t)0x004c2b10;
	// static const Trig_DeleteTrigFile_t Trig_DeleteTrigFile = (Trig_DeleteTrigFile_t)0x004c2360;
	void Trig_DeleteTrigFile();
	 static const Trig_LoadTRG_t Trig_LoadTRG = (Trig_LoadTRG_t)0x004c2390;
	void Trig_LoadTRG_Hook(char* trgName);
	static const ExecuteCommandList_t ExecuteCommandList = (ExecuteCommandList_t)0x004c3020;
	static const Trig_ScanRestart_t Trig_ScanRestart = (Trig_ScanRestart_t)0x004c5100;
	// static const Trig_InitialParseTRGFile_t Trig_InitialParseTRGFile = (Trig_InitialParseTRGFile_t)0x004c52b0;
	void Trig_InitialParseTRGFile();


	static const Trig_GetLinksPointer_t Trig_GetLinksPointer = (Trig_GetLinksPointer_t)0x004c57b0;
}