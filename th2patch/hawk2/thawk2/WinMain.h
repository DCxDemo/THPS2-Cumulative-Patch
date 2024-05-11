#pragma once

#include "types.h"

extern HWND hWnd;

typedef void(*WINMAIN_ShutDown_t)();
static const WINMAIN_ShutDown_t WINMAIN_ShutDown = (WINMAIN_ShutDown_t)0x004f5750;

uint WinYield();
void WINMAIN_ScreenDimensions(int* width, int* height);
