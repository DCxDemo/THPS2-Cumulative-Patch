#pragma once

/*
	Rail.h
	======
	- Handles rail logic.
*/



//move to trig

typedef short*(*Trig_GetLinksPointer_t)(int nodeIndex);
static const Trig_GetLinksPointer_t Trig_GetLinksPointer = (Trig_GetLinksPointer_t)0x004c57b0;



typedef short(*Rail_Flags_t)(int nodeIndex);
//typedef uint(*Rail_Type_t)(int nodeIndex);
typedef void(*Rail_FlagsPointer_t)();
//typedef bool(*Rail_IsRailNode_t)(int nodeIndex);
typedef int(*Rail_GetLink_t)(int nodeIndex, int linkIndex);
//typedef int(*Rail_NumLinks_t)(int nodeIndex);
//typedef int(*Rail_NextNode_t)(int nodeIndex);
//typedef int(*Rail_PrevNode_t)(int nodeIndex);
typedef void(*Rail_PrevNodeQuick_t)();
typedef void(*Rail_Active_t)(int nodeIndex, bool active);
//typedef void(*Rail_KillRail_t)(int nodeIndex);
//typedef void(*Rail_SwitchOn_t)(int nodeIndex);
typedef void(*GetIndexOfNode_t)();
typedef void(*SetupLookup_t)();
typedef void(*Rail_CreateRails_t)();
typedef void(*Rail_Init_t)();
typedef void(*Rail_DeleteAll_t)();
typedef void(*CRail_t)();
typedef void(*CRail_destruct_t)();
typedef void(*CRail_destroy_t)();
typedef void(*Rail_Update_t)();

static const Rail_Flags_t Rail_Flags = (Rail_Flags_t)0x004a7850;
//static const Rail_Type_t Rail_Type = (Rail_Type_t)0x004a78b0;
static const Rail_FlagsPointer_t Rail_FlagsPointer = (Rail_FlagsPointer_t)0x004a78d0;
//static const Rail_IsRailNode_t Rail_IsRailNode = (Rail_IsRailNode_t)0x004a7920;
static const Rail_GetLink_t Rail_GetLink = (Rail_GetLink_t)0x004a7970;
//static const Rail_NumLinks_t Rail_NumLinks = (Rail_NumLinks_t)0x004a7aa0;
//static const Rail_NextNode_t Rail_NextNode = (Rail_NextNode_t)0x004a7b00;
//static const Rail_PrevNode_t Rail_PrevNode = (Rail_PrevNode_t)0x004a7b70;
static const Rail_PrevNodeQuick_t Rail_PrevNodeQuick = (Rail_PrevNodeQuick_t)0x004a7c10;
static const Rail_Active_t Rail_Active = (Rail_Active_t)0x004a7ca0;
//static const Rail_KillRail_t Rail_KillRail = (Rail_KillRail_t)0x004a7cf0;
//static const Rail_SwitchOn_t Rail_SwitchOn = (Rail_SwitchOn_t)0x004a7d00;
static const GetIndexOfNode_t GetIndexOfNode = (GetIndexOfNode_t)0x004a7d10;
static const SetupLookup_t SetupLookup = (SetupLookup_t)0x004a7d90;
static const Rail_CreateRails_t Rail_CreateRails = (Rail_CreateRails_t)0x004a7eb0;
static const Rail_Init_t Rail_Init = (Rail_Init_t)0x004a8150;
static const Rail_DeleteAll_t Rail_DeleteAll = (Rail_DeleteAll_t)0x004a8180;
static const CRail_t CRail = (CRail_t)0x004a81a0;
static const CRail_destruct_t CRail_destruct = (CRail_destruct_t)0x004a87f0;
static const CRail_destroy_t CRail_destroy = (CRail_destroy_t)0x004a8810;
static const Rail_Update_t Rail_Update = (Rail_Update_t)0x004a8850;

