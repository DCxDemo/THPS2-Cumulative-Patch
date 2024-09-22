#pragma once

#include "..\patch\hook.h"

namespace Flash {

	extern Hook::Reroute* pHookList;

	//typedef void(*Flash_Reset_t)();
	//typedef bool(*Flash_FadeFinished_t)();
	//typedef void(*Flash_Screen_t)(int p1, int p2, int p3, int p4, int p5, int p6);
	//typedef void(*Flash_Fade_t)(int time, int sort);
	//typedef void(*Flash_Update_t)();
	typedef void(*Flash_Display_t)();

	//static const Flash_Reset_t			Flash_Reset = (Flash_Reset_t)0x449780;
	void Flash_Reset();
	//static const Flash_FadeFinished_t	Flash_FadeFinished = (Flash_FadeFinished_t)0x4497a0;
	bool Flash_FadeFinished();
	//static const Flash_Screen_t			Flash_Screen = (Flash_Screen_t)0x4497b0;
	void Flash_Screen(char r, char g, char b, int duration, int importance, int sort);
	//static const Flash_Fade_t			Flash_Fade = (Flash_Fade_t)0x449840;
	void Flash_Fade(int time, int sort);
	//static const Flash_Update_t			Flash_Update = (Flash_Update_t)0x449890;
	void Flash_Update();
	static const Flash_Display_t		Flash_Display = (Flash_Display_t)0x449950;

}