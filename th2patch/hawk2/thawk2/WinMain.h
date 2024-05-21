#pragma once

#include "types.h"

extern HWND hWnd;

uint WinYield();

typedef void(*WinMain_t)(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
static const WinMain_t WinMainX = (WinMain_t)0x004f4ec0;

//typedef void(*Thawk2Entry_t)();
//static const Thawk2Entry_t Thawk2Entry = (Thawk2Entry_t)0x004ffe6c;




typedef void(*WINMAIN_Sleep_t)();
typedef void(*WINMAIN_FindFiles_t)();
typedef void(*WINMAIN_CanDoMode_t)();
typedef void(*WINMAIN_FindCD_t)();
typedef void(*tryOpenFile_t)();
typedef void(*WINMAIN_InstallSetup_t)();
typedef void(*WINMAIN_LoadOptions_t)();
typedef void(*WINMAIN_SaveOptions_t)();
//typedef void(*WINMAIN_LoadSetting_t)();
//typedef void(*WINMAIN_SaveSetting_t)();
//typedef void(*WINMAIN_ScreenDimensions_t)();
typedef void(*WINMAIN_SwitchRenderer_t)();
//typedef void(*WINMAIN_SwitchResolution_t)();

// there is more stuff down the line, mixed with directdraw initialization

static const WINMAIN_Sleep_t WINMAIN_Sleep = (WINMAIN_Sleep_t)0x004f3600;
static const WINMAIN_FindFiles_t WINMAIN_FindFiles = (WINMAIN_FindFiles_t)0x004f3610;
static const WINMAIN_CanDoMode_t WINMAIN_CanDoMode = (WINMAIN_CanDoMode_t)0x004f3710;
static const WINMAIN_FindCD_t WINMAIN_FindCD = (WINMAIN_FindCD_t)0x004f37e0;
static const tryOpenFile_t tryOpenFile = (tryOpenFile_t)0x004f3900;
static const WINMAIN_InstallSetup_t WINMAIN_InstallSetup = (WINMAIN_InstallSetup_t)0x004f39d0;
static const WINMAIN_LoadOptions_t WINMAIN_LoadOptions = (WINMAIN_LoadOptions_t)0x004f3c40;
static const WINMAIN_SaveOptions_t WINMAIN_SaveOptions = (WINMAIN_SaveOptions_t)0x004f3d10;
//static const WINMAIN_LoadSetting_t WINMAIN_LoadSetting = (WINMAIN_LoadSetting_t)0x004f3d50;
//static const WINMAIN_SaveSetting_t WINMAIN_SaveSetting = (WINMAIN_SaveSetting_t)0x004f3d80;
//static const WINMAIN_ScreenDimensions_t WINMAIN_ScreenDimensions = (WINMAIN_ScreenDimensions_t)0x004f3db0;
void WINMAIN_ScreenDimensions(int* width, int* height);
static const WINMAIN_SwitchRenderer_t WINMAIN_SwitchRenderer = (WINMAIN_SwitchRenderer_t)0x004f3dd0;
//static const WINMAIN_SwitchResolution_t WINMAIN_SwitchResolution = (WINMAIN_SwitchResolution_t)0x004f3f10;

//typedef void(*WINMAIN_WndProc_t)();
//static const WINMAIN_WndProc_t WINMAIN_WndProc = (WINMAIN_WndProc_t)0x004f4ba0;
LRESULT WINMAIN_WndProc(HWND hWnd, uint Msg, WPARAM wParam, LPARAM lParam);

typedef void(*WINMAIN_ShutDown_t)();
static const WINMAIN_ShutDown_t WINMAIN_ShutDown = (WINMAIN_ShutDown_t)0x004f5750;

void WINMAIN_PatchWndProc();