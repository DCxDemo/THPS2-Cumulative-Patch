#pragma once

#include "types.h"

//these are the old random messy unsorted mappings
//put here random declarations that dont have separate headers yet
//remove once sorted and available via other files

typedef void(*ASSERTER_t)(bool condition, char *text, ...);
static const ASSERTER_t ASSERTER = (ASSERTER_t)0x4011E0;

typedef int(__thiscall *RunAnim_t)(void* pSkater, __int16 animIndex, int a3, int a4, char a5);
static const RunAnim_t CSuper_RunAnim = (RunAnim_t)0x47E020;

typedef int(__thiscall *CycleAnim_t)(void* pSkater, __int16 animIndex, char a3);
static const CycleAnim_t CSuper_CycleAnim = (CycleAnim_t)0x47E180;

typedef void(*CreateSkatersAndCameras_t)();
static const CreateSkatersAndCameras_t CreateSkatersAndCameras = (CreateSkatersAndCameras_t)0x469170;


typedef int(*D3DTIMER_CalcSystemSpeed_t)();
static const D3DTIMER_CalcSystemSpeed_t D3DTIMER_CalcSystemSpeed = (D3DTIMER_CalcSystemSpeed_t)0x4D7FC0;


typedef void(*D3DPOLY_DrawOTag_t)(void* ot);
/// This function renders PSX OT list.
/// Call from Db_DisplayDraw draws Frontend menus.
/// Call from Db_Vblank draws level polygons.
static const D3DPOLY_DrawOTag_t D3DPOLY_DrawOTag = (D3DPOLY_DrawOTag_t)0x004d0370;

typedef void (*D3D_BeginScene_t)(uint param_1, uint backColor);
static const D3D_BeginScene_t D3D_BeginScene = (D3D_BeginScene_t)0x4cddd0;

typedef void (*D3DPOLY_StartScene_t)(uint param_1, uint param_2);
static const D3DPOLY_StartScene_t D3DPOLY_StartScene = (D3DPOLY_StartScene_t)0x4d0d50;


typedef char (*StartBinkMovie_t)(const char *a1, int a2, int a3);
static const StartBinkMovie_t StartBinkMovie = (StartBinkMovie_t)0x4E3760;


typedef void (*Front_Update_t)();
static const Front_Update_t Front_Update = (Front_Update_t)0x0044ea50;

	


typedef int (__thiscall *WheelElementList_t)(void* a1, int a2, int a3, int a4, int a5);
static const WheelElementList_t WheelElementList = (WheelElementList_t)0x46B800;



typedef void(*Front_Display_t)();
static const Front_Display_t Front_Display = (Front_Display_t)0x44CA00;

typedef int(*VectorNormal_t)(void* pVector);
static const VectorNormal_t VectorNormal = (VectorNormal_t)0x4E5650;

//WINMAIN stuff

typedef int(*WINMAIN_SaveSetting_t)(LPCSTR lpAppName, LPCSTR lpKeyName, LPCSTR lpString);
static const WINMAIN_SaveSetting_t WINMAIN_SaveSetting = (WINMAIN_SaveSetting_t)0x4F3D80;

typedef int(*WINMAIN_LoadSetting_t)(LPCSTR lpAppName, LPCSTR lpKeyName, LPCSTR lpDefault, LPSTR lpReturnedString);
static const WINMAIN_LoadSetting_t WINMAIN_LoadSetting = (WINMAIN_LoadSetting_t)0x4F3D50;

typedef void(*WINMAIN_SwitchResolution_t)(int mode);
static const WINMAIN_SwitchResolution_t WINMAIN_SwitchResolution = (WINMAIN_SwitchResolution_t)0x4F3F10;

typedef int(__stdcall* WinMain2_t)(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
static const WinMain2_t WinMain2 = (WinMain2_t)0x4F4EC0;

typedef LRESULT(__stdcall* WindowProc_t)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
static const WindowProc_t WindowProc = (WindowProc_t)0x4F4BA0;

//typedef void(*WinYield_t)();
//use this to avoid freezing
//static const WinYield_t WinYield = (WinYield_t)0x004f4d70;


//VIDMENU stuff

typedef int(*VIDMENU_Load_t)();
static const VIDMENU_Load_t VIDMENU_Load = (VIDMENU_Load_t)0x4CC240;

typedef int(*VIDMENU_Save_t)();
static const VIDMENU_Save_t VIDMENU_Save = (VIDMENU_Save_t)0x4CC510;


typedef void (*ExecuteCommandList_t)(short* node, int p2, int p3);
static const ExecuteCommandList_t ExecuteCommandList = (ExecuteCommandList_t)0x4C3020;



typedef int (__thiscall *Vibrate2_t)(int a1, int a2, int a3, int a4);
static const Vibrate2_t Vibrate2 = (Vibrate2_t)0x48D8B0;

typedef void (*RenderSuperItemShadow_t)(void* superItem);
static const RenderSuperItemShadow_t RenderSuperItemShadow = (RenderSuperItemShadow_t)0x00460480;

typedef LONGLONG(*systemclock_t)();
static const systemclock_t systemclock = (systemclock_t)0x004ffbc1;



//PCMOVIE stuff

typedef char(__cdecl* PCMOVIE_StartMusic_t)(char* a1);
static const PCMOVIE_StartMusic_t PCMOVIE_StartMusic = (PCMOVIE_StartMusic_t)0x4E4430;

typedef int(__cdecl* PCMOVIE_SetXAVolume_t)(int a1, int a2);
static const PCMOVIE_SetXAVolume_t PCMOVIE_SetXAVolume = (PCMOVIE_SetXAVolume_t)0x4E44A0;

typedef bool(__cdecl* PCMOVIE_Pause_t)(bool a1);
static const PCMOVIE_Pause_t PCMOVIE_Pause = (PCMOVIE_Pause_t)0x4E4040;

typedef char(__cdecl* PCMOVIE_XAStop_t)();
static const PCMOVIE_XAStop_t PCMOVIE_XAStop = (PCMOVIE_XAStop_t)0x4E4540;

typedef bool(__cdecl* PCMOVIE_XADone_t)();
static const PCMOVIE_XADone_t PCMOVIE_XADone = (PCMOVIE_XADone_t)0x4e45b0;

typedef bool(__cdecl* PCMOVIE_XAPlay_t)(int group, int channel);
static const PCMOVIE_XAPlay_t PCMOVIE_XAPlay = (PCMOVIE_XAPlay_t)0x4e44e0;

typedef bool(__cdecl* PCMOVIE_PlayMovieFile_t)(int group, int channel);
static const PCMOVIE_PlayMovieFile_t PCMOVIE_PlayMovieFile = (PCMOVIE_PlayMovieFile_t)0x004e3090;




//these are in CBruce.h. !!remove!!

/// CBruce: snaps to rail and begins a grind trick
typedef void(__thiscall *CBruce_StartGrind_t)(void* _this, int param);
static const CBruce_StartGrind_t CBruce_StartGrind = (CBruce_StartGrind_t)0x0048e7e0;

typedef void(__thiscall *CBruce_HandleJump_t)(void* _this);
/// CBruce: jump/ollie, called every frame, but only trigger proper scenario if pressed jump/no comply/boneless
static const CBruce_HandleJump_t CBruce_HandleJump = (CBruce_HandleJump_t)0x00497b70;

typedef void(__thiscall *CBruce_BoardOn_t)(void* _this);
/// CBruce: switches board on
static const CBruce_BoardOn_t CBruce_BoardOn = (CBruce_BoardOn_t)0x0046c5c0;

typedef void(__thiscall*CBruce_BoardOff_t)(void* _this);
/// CBruce: switches board off
static const CBruce_BoardOff_t CBruce_BoardOff = (CBruce_BoardOff_t)0x0046c580;

typedef void(__thiscall *CBruce_Trick_Land_t)(void* _this);
/// CBruce: lands trick
static const CBruce_Trick_Land_t CBruce_Trick_Land = (CBruce_Trick_Land_t)0x0048d1e0;




typedef void(*Game_Init_t)();
//game initialization func, called once at the beginning of the run
static const Game_Init_t Game_Init = (Game_Init_t)0x4698a0;

typedef void(*Game_Logic_t)();
//main game logic update func, called once per frame
static const Game_Logic_t Game_Logic = (Game_Logic_t)0x469d70;

typedef void(*Game_Display_t)();
//main game render func, called once per frame
static const Game_Display_t Game_Display = (Game_Display_t)0x46a080;


typedef void(*Panel_Line_t)(short param_1, short param_2, short param_3, short param_4, int param_5);
//simply draws a line on the screen.
static const Panel_Line_t Panel_Line = (Panel_Line_t)0x00488410;

typedef void(*Utils_SetVisibilityInBox_t)(void*, void*, char, char);
//takes bbox, objects list and state bool, loops through all objects and toggles visibility for those 
static const Utils_SetVisibilityInBox_t Utils_SetVisibilityInBox = (Utils_SetVisibilityInBox_t)0x004c7530;



typedef int(*Panel_Display_t)();
//draws user interface
static const Panel_Display_t Panel_Display = (Panel_Display_t)0x48a980;

typedef void(*Panel_Bail_t)();
//called once, triggers when player bails
static const Panel_Bail_t Panel_Bail = (Panel_Bail_t)0x0048b0a0;


typedef void(*Backgrnd_On_t)(short param);
//Turns skybox on
static const Backgrnd_On_t Backgrnd_On = (Backgrnd_On_t)0x401000;

typedef void(*Backgrnd_Off_t)(short param);
//Turns skybox off
static const Backgrnd_Off_t Backgrnd_Off = (Backgrnd_Off_t)0x401030;



typedef void(__thiscall* SlicedImage2_screenWidth_t)(void* _this);
static const SlicedImage2_screenWidth_t SlicedImage2_screenWidth = (SlicedImage2_screenWidth_t)0x00457790;

typedef void(__thiscall* SlicedImage2_screenHeight_t)(void* _this);
static const SlicedImage2_screenHeight_t SlicedImage2_screenHeight = (SlicedImage2_screenHeight_t)0x004577a0;


typedef void*(*FontManger_LoadFont2_t)(void* stuff, char* name);
static const FontManger_LoadFont2_t FontManger_LoadFont2 = (FontManger_LoadFont2_t)0x0044ae40;

typedef void(__thiscall *Font_Draw_t)(void* _this, int x, int y, char* pMessage, int Angle);
static const Font_Draw_t Font_Draw = (Font_Draw_t)0x44a010;


typedef void(__thiscall *FallingTextEffect_SetScale_t)(void* _this, int scale);
static const FallingTextEffect_SetScale_t FallingTextEffect_SetScale = (FallingTextEffect_SetScale_t)0x001126c8;




typedef void (*MMU_Init_t)();
static const MMU_Init_t MMU_Init = (MMU_Init_t)0x00477de0;

typedef void (*Init_ResetMemory_t)(int heap0size);
static const Init_ResetMemory_t Init_ResetMemory = (Init_ResetMemory_t)0x00458600;

typedef void (*Pad_InitAtStart_t)();
static const Pad_InitAtStart_t Pad_InitAtStart = (Pad_InitAtStart_t)0x00486d90;

typedef void (*M3dInit_InitAtStart_t)();
static const M3dInit_InitAtStart_t M3dInit_InitAtStart = (M3dInit_InitAtStart_t)0x00464580;

typedef void (*Front_ClearGVideoRestartData_t)();
//just reset replay related values
static const Front_ClearGVideoRestartData_t Front_ClearGVideoRestartData = (Front_ClearGVideoRestartData_t)0x004a9cd0;

typedef void (*Db_Init_t)(int param_1, int param_2, char param_3, int param_4);
static const Db_Init_t Db_Init = (Db_Init_t)0x00430290;

typedef void (*IntroMovies_t)();
static const IntroMovies_t IntroMovies = (IntroMovies_t)0x0046a490;

typedef void (*LogoScreen_t)();
static const LogoScreen_t LogoScreen = (LogoScreen_t)0x0046a510;

typedef void (*FrontEnd2_Main_t)();
static const FrontEnd2_Main_t FrontEnd2_Main = (FrontEnd2_Main_t)0x00452f60;

typedef void (*Init_AtEnd_t)();
static const Init_AtEnd_t Init_AtEnd = (Init_AtEnd_t)0x004587b0;

typedef void (*Init_Cleanup_t)(int cleanupType);
static const Init_Cleanup_t Init_Cleanup = (Init_Cleanup_t)0x00458470;

typedef void (*Db_Reset_t)();
static const Db_Reset_t Db_Reset = (Db_Reset_t)0x00430180;

typedef void (*Spool_Init_t)();
static const Spool_Init_t Spool_Init = (Spool_Init_t)0x004af3a0;

typedef void (*Pal_Init_t)(int numPal4, int numPal8);
static const Pal_Init_t Pal_Init = (Pal_Init_t)0x004879a0;

typedef void (*Front_Init_t)();
static const Front_Init_t Front_Init = (Front_Init_t)0x0044bdf0;

typedef void (*Video_InitOnce_t)();
static const Video_InitOnce_t Video_InitOnce = (Video_InitOnce_t)0x004c8c90;

typedef bool (*Video_Playing_t)();
static const Video_Playing_t Video_Playing = (Video_Playing_t)0x004cb0c0;
