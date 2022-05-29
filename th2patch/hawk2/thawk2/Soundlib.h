#pragma once

#include <windows.h>
//#include <dsound.h>

//pointer to directsound object
//LPDIRECTSOUND* pDevice = (LPDIRECTSOUND*)0x029d4fb0;

typedef void(*SOUNDLIB_Init_t)(HWND* hWnd);
typedef void(*SOUNDLIB_Shutdown_t)();
typedef void(*SOUNDLIB_LoadVABList_t)(int vabIndex);
typedef void(*SOUNDLIB_FreeVABList_t)(int vabIndex);
typedef int(*SOUNDLIB_LoadSound_t)(int soundIndex);
typedef void(*writeSoundData_t)(int* param_1, int param_2, int param_3, int param_4);
typedef void(*SOUNDLIB_FreeSound_t)(int param_1);
typedef int(*SOUNDLIB_Play_t)(int param_1, int param_2, int param_3);
typedef void(*SOUNDLIB_Play2_t)(int param_1, int param_2, int param_3);
typedef void(*SOUNDLIB_SetVolume_t)(int voice, int volLeft, int volRight);
typedef void(*SOUNDLIB_SetPitch_t)(int voice, int pitch);
typedef int(*SOUNDLIB_GetPitch_t)(int voice);
typedef void(*SOUNDLIB_Stop_t)(int voice);
typedef void(*SOUNDLIB_Pause_t)(int voice);
typedef void(*SOUNDLIB_StopAll_t)();
typedef void(*SOUNDLIB_PauseAll_t)();
typedef void(*SOUNDLIB_UnPauseAll_t)();

static const SOUNDLIB_Init_t		SOUNDLIB_Init = (SOUNDLIB_Init_t)0x4ef8b0;
static const SOUNDLIB_Shutdown_t	SOUNDLIB_Shutdown = (SOUNDLIB_Shutdown_t)0x4ef990;
static const SOUNDLIB_LoadVABList_t SOUNDLIB_LoadVABList = (SOUNDLIB_LoadVABList_t)0x4efa50;
static const SOUNDLIB_FreeVABList_t SOUNDLIB_FreeVABList = (SOUNDLIB_FreeVABList_t)0x4efbc0;
static const SOUNDLIB_LoadSound_t	SOUNDLIB_LoadSound = (SOUNDLIB_LoadSound_t)0x4efc30;
static const writeSoundData_t		writeSoundData = (writeSoundData_t)0x4efd60;
static const SOUNDLIB_FreeSound_t	SOUNDLIB_FreeSound = (SOUNDLIB_FreeSound_t)0x4efe90;
static const SOUNDLIB_Play_t		SOUNDLIB_Play = (SOUNDLIB_Play_t)0x4eff10;
static const SOUNDLIB_Play2_t		SOUNDLIB_Play2 = (SOUNDLIB_Play2_t)0x4f02f0;
static const SOUNDLIB_SetVolume_t	SOUNDLIB_SetVolume = (SOUNDLIB_SetVolume_t)0x4f05a0;
static const SOUNDLIB_SetPitch_t	SOUNDLIB_SetPitch = (SOUNDLIB_SetPitch_t)0x4f0780;
static const SOUNDLIB_GetPitch_t	SOUNDLIB_GetPitch = (SOUNDLIB_GetPitch_t)0x4f0810;
static const SOUNDLIB_Stop_t		SOUNDLIB_Stop = (SOUNDLIB_Stop_t)0x4f08b0;
static const SOUNDLIB_Pause_t		SOUNDLIB_Pause = (SOUNDLIB_Pause_t)0x4f0960;
static const SOUNDLIB_StopAll_t		SOUNDLIB_StopAll = (SOUNDLIB_StopAll_t)0x4f09c0;
static const SOUNDLIB_PauseAll_t	SOUNDLIB_PauseAll = (SOUNDLIB_PauseAll_t)0x4f09f0;
static const SOUNDLIB_UnPauseAll_t	SOUNDLIB_UnPauseAll = (SOUNDLIB_UnPauseAll_t)0x4f0a30;