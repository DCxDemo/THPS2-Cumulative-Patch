#pragma once
#include "..\patch\hook.h"

namespace Db
{
	extern Hook::Reroute* pHookList;

	// typedef void(*Db_OTSize_t)();
	typedef void(*Db_UpdateSky_t)();
	typedef void(*Db_CallBack_t)();
	typedef void(*Db_Vblank_t)();
	typedef void(*Db_WaitRender_t)();
	typedef void(*Db_Render_t)();
	typedef void(*Db_InitAtStart_t)();
	typedef void(*Db_Reset_t)();
	// typedef void(*Db_AllocateBuffers_t)(int, int, int);
	typedef void(*Db_Init_t)(int, int, int, int);
	typedef void(*Db_FlipClear_t)();
	typedef void(*Db_DisplayDraw_t)();
	typedef void(*Db_FlipScreens_t)();


	//static const Db_OTSize_t Db_OTSize = (Db_OTSize_t)0x0042fc30;
	int Db_OTSize();
	static const Db_UpdateSky_t Db_UpdateSky = (Db_UpdateSky_t)0x0042fc40;
	static const Db_CallBack_t Db_CallBack = (Db_CallBack_t)0x0042fca0;
	static const Db_Vblank_t Db_Vblank = (Db_Vblank_t)0x0042fcf0;
	static const Db_WaitRender_t Db_WaitRender = (Db_WaitRender_t)0x0042fea0;
	static const Db_Render_t Db_Render = (Db_Render_t)0x0042ff90;
	static const Db_InitAtStart_t Db_InitAtStart = (Db_InitAtStart_t)0x430170;
	static const Db_Reset_t Db_Reset = (Db_Reset_t)0x430180;
	//static const Db_AllocateBuffers_t Db_AllocateBuffers = (Db_AllocateBuffers_t)0x004301c0;
	void Db_AllocateBuffers(int param_1, int param_2, bool extra);
	static const Db_Init_t Db_Init = (Db_Init_t)0x430290;
	static const Db_FlipClear_t Db_FlipClear = (Db_FlipClear_t)0x430480;
	static const Db_DisplayDraw_t Db_DisplayDraw = (Db_DisplayDraw_t)0x4304;
	static const Db_FlipScreens_t Db_FlipScreens = (Db_FlipScreens_t)0x430580;
}