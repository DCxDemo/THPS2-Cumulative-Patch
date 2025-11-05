#pragma once
#include "..\patch\hook.h"

namespace Init
{
	extern Hook::Reroute* pHookList;

	typedef void(*Init_KillAll_t)();
	typedef void(*DeleteList_t)();
	typedef void(*Init_Cleanup_t)(int cleanupType);
	typedef void(*Init_ResetMemory_t)(int param);
	//typedef void(*Init_Restart_t)();
	//typedef void(*Init_ForGame_t)();
	typedef void(*Init_DebugStuff_t)(); // empty func
	//typedef void(*Init_AtStart_t)();
	typedef void(*Init_AtEnd_t)();

	static const Init_KillAll_t Init_KillAll = (Init_KillAll_t)0x004581e0;
	static const DeleteList_t DeleteList = (DeleteList_t)0x00458440;
	static const Init_Cleanup_t Init_Cleanup = (Init_Cleanup_t)0x00458470;
	static const Init_ResetMemory_t Init_ResetMemory = (Init_ResetMemory_t)0x00458600;
	//static const Init_Restart_t Init_Restart = (Init_Restart_t)0x00458660;
	void Init_Restart();
	//static const Init_ForGame_t Init_ForGame = (Init_ForGame_t)0x004586a0;
	void Init_ForGame();
	static const Init_DebugStuff_t Init_DebugStuff = (Init_DebugStuff_t)0x004586c0;
	// static const Init_AtStart_t Init_AtStart = (Init_AtStart_t)0x004586d0;
	void Init_AtStart();
	static const Init_AtEnd_t Init_AtEnd = (Init_AtEnd_t)0x004587b0;

	// not really from here
	void TH2Main();
}