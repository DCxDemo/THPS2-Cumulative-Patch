/*
	Rail.h
	======
	- Handles rail logic.
*/

#pragma once
#include "..\patch\hook.h"
#include "types.h"

namespace Rail {

	typedef struct Vector3i {
		int X;
		int Y;
		int Z;
	} Vector3i;

	// CRail is a doubly linked list
	typedef struct CRail {
		void* vTable;
		char active;
		char flags;
		ushort railIndex;
		Vector3i position;
		Vector3i angle;
		CRail* pPrev;
		CRail* pNext;
	} CRail;

	typedef struct RailLookupEntry {
		int nodeIndex;
		int prevIndex;
	} RailLookupEntry;


	extern Hook::Reroute* pHookList;

	//move to trig


	// typedef short(*Rail_Flags_t)(ushort nodeIndex);
	// typedef uint(*Rail_Type_t)(ushort nodeIndex);
	// typedef void(*Rail_FlagsPointer_t)();
	// typedef bool(*Rail_IsRailNode_t)(ushort nodeIndex);
	typedef uint(*Rail_GetLink_t)(ushort nodeIndex, int linkIndex);
	// typedef int(*Rail_NumLinks_t)(ushort nodeIndex);
	// typedef uint(*Rail_NextNode_t)(ushort nodeIndex);
	// typedef int(*Rail_PrevNode_t)(ushort nodeIndex);
	typedef void(*Rail_PrevNodeQuick_t)();
	// typedef void(*Rail_Active_t)(ushort nodeIndex, bool active);
	// typedef void(*Rail_KillRail_t)(ushort nodeIndex);
	// typedef void(*Rail_SwitchOn_t)(ushort nodeIndex);
	// typedef uint(*GetIndexOfNode_t)(ushort nodeIndex);
	// typedef void(*SetupLookup_t)();
	typedef void(*Rail_CreateRails_t)();
	typedef void(*Rail_Init_t)();
	typedef void(*Rail_DeleteAll_t)();
	typedef void(*CRail_t)();
	typedef void(*CRail_destruct_t)();
	typedef void(*CRail_destroy_t)();
	typedef void(*Rail_Update_t)();

	//static const Rail_Flags_t Rail_Flags = (Rail_Flags_t)0x004a7850;
	ushort Rail_Flags(uint node);

	//static const Rail_Type_t Rail_Type = (Rail_Type_t)0x004a78b0;
	uint Rail_Type(uint node);

	//static const Rail_FlagsPointer_t Rail_FlagsPointer = (Rail_FlagsPointer_t)0x004a78d0;
	ushort* Rail_FlagsPointer(uint node);

	//static const Rail_IsRailNode_t Rail_IsRailNode = (Rail_IsRailNode_t)0x004a7920;
	uint Rail_IsRailNode(uint node);

	static const Rail_GetLink_t Rail_GetLink = (Rail_GetLink_t)0x004a7970;

	//static const Rail_NumLinks_t Rail_NumLinks = (Rail_NumLinks_t)0x004a7aa0;
	short Rail_NumLinks(uint node);

	//static const Rail_NextNode_t Rail_NextNode = (Rail_NextNode_t)0x004a7b00;
	int Rail_NextNode(uint node);

	//static const Rail_PrevNode_t Rail_PrevNode = (Rail_PrevNode_t)0x004a7b70;
	int Rail_PrevNode(uint node);

	static const Rail_PrevNodeQuick_t Rail_PrevNodeQuick = (Rail_PrevNodeQuick_t)0x004a7c10;

	//static const Rail_Active_t Rail_Active = (Rail_Active_t)0x004a7ca0;
	void Rail_Active(uint node, char active);

	//static const Rail_KillRail_t Rail_KillRail = (Rail_KillRail_t)0x004a7cf0;
	void Rail_KillRail(uint node);

	//static const Rail_SwitchOn_t Rail_SwitchOn = (Rail_SwitchOn_t)0x004a7d00;
	void Rail_SwitchOn(uint node);

	//static const GetIndexOfNode_t GetIndexOfNode = (GetIndexOfNode_t)0x004a7d10;
	//static const SetupLookup_t SetupLookup = (SetupLookup_t)0x004a7d90;

	static const Rail_CreateRails_t Rail_CreateRails = (Rail_CreateRails_t)0x004a7eb0;
	static const Rail_Init_t Rail_Init = (Rail_Init_t)0x004a8150;
	static const Rail_DeleteAll_t Rail_DeleteAll = (Rail_DeleteAll_t)0x004a8180;

	static const CRail_t CRail_CRail = (CRail_t)0x004a81a0;
	static const CRail_destruct_t CRail_destruct = (CRail_destruct_t)0x004a87f0;
	static const CRail_destroy_t CRail_destroy = (CRail_destroy_t)0x004a8810;
	static const Rail_Update_t Rail_Update = (Rail_Update_t)0x004a8850;


}