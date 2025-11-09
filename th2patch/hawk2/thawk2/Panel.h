#pragma once
#include "types.h"

namespace Panel
{
	typedef void(*Panel_Line_t)(short x0, short y0, short x1, short y1, int color);
	typedef void(*Panel_BalanceUD_t)(int Balance, int Max, int Length, int x, int y, int LineColor, uint MarkerColor);
	typedef void(*Panel_Init_t)();
	typedef void(*Panel_Uninit_t)();

	typedef void(*DisplayTapesSkate_t)();

	typedef void(*DisplayScore_t)(int x, int y);

	


	typedef void(*Panel_Display_t)();

	typedef void(*Panel_Bail_t)();

	static const Panel_Line_t Panel_Line = (Panel_Line_t)0x00488410;
	static const Panel_BalanceUD_t Panel_BalanceUD = (Panel_BalanceUD_t)0x00488550;
	static const Panel_Init_t Panel_Init = (Panel_Init_t)0x00488640;
	static const Panel_Uninit_t Panel_Uninit = (Panel_Uninit_t)0x004889f0;


	static const DisplayTapesSkate_t DisplayTapesSkate = (DisplayTapesSkate_t)0x004891d0;
	
	static const DisplayScore_t DisplayScore = (DisplayScore_t)0x004893d0;



	//draws user interface
	static const Panel_Display_t Panel_Display = (Panel_Display_t)0x48a980;

	//called once, triggers when player bails
	static const Panel_Bail_t Panel_Bail = (Panel_Bail_t)0x0048b0a0;


	void Panel_LineX(float x1, float x2, float x3, float x4, int r, int g, int b);
	void Panel_BalanceRail(int Balance, int Max, int Length, int Width, int x, int y, uint LineColor, uint MarkerColor, bool horz);
	void Panel_DrawBalanceBarUD(int x, int y, int Length, int Width, uint color);
	void Panel_DrawBalanceBarLR(int x, int y, int Length, int Width, uint color);


}