#pragma once

#include "lib/xinput/CXBOXController.h"

void PrintDebugStuff();
void VibrationTest(CXBOXController* Player1);
void Panel_BalanceRail(int Balance, int Max, int Length, int Width,
	int x, int y, uint LineColor, uint MarkerColor, bool horz);
void Panel_DrawBalanceBarUD(int x, int y, int Length, int Width, uint color);
void Panel_DrawBalanceBarLR(int x, int y, int Length, int Width, uint color);