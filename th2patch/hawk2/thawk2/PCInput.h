#pragma once

#include "windows.h"

//PCINPUT namespace handles keyboard, mouse and joystick input via DirectInput

extern int* pad1;
extern int* pad2;

typedef void(*PCINPUT_ResetGameControls_t)();
typedef void(*PCINPUT_SetShellMode_t)(int mode);
typedef void(*PCINPUT_ForceButton_t)(short param);
typedef bool(*IsDIKeyPressed_t)(int key);
typedef int(*PCINPUT_GetDIKeyPressed_t)(int param);
typedef int(*PCINPUT_GetAsciiCode_t)(int param);
typedef void(*PCINPUT_GetKeyName_t)();
typedef int(*PCINPUT_GetJoyButtonPressed_t)();
typedef void(*PCINPUT_ClearAllTriggers_t)();
typedef void(*PCINPUT_EnableJoypad_t)(int state);
typedef void(*GenPsxPadData_t)();
typedef int(*GetFakePsxPadData_t)();
typedef void(*InitDirectInput_t)(HWND hWnd, HINSTANCE hInstance); //PCINPUT_Init??
typedef void(*PCINPUT_ShutDown_t)();
typedef void(*ReadDirectInput_t)(); //PCINPUT_Update??
typedef void(*PCINPUT_DoWinKeyDown_t)(); //empty
typedef void(*PCINPUT_HandleMouseMessage_t)(int message);
typedef void(*PCINPUT_SetCursorPos_t)(int x, int y);
typedef void(*PCINPUT_ActuatorOn_t)(int param_1, int param_2, int param_3, int param_4);
typedef void(*PCINPUT_ActuatorOff_t)(int padIndex, int motorIndex);
typedef void(*PCINPUT_StopVibrations_t)();
typedef void(*PCINPUT_Load_t)();
typedef void(*PCINPUT_Save_t)();

static const PCINPUT_ResetGameControls_t	PCINPUT_ResetGameControls = (PCINPUT_ResetGameControls_t)0x4e1040;
static const PCINPUT_SetShellMode_t			PCINPUT_SetShellMode = (PCINPUT_SetShellMode_t)0x4e1140;
static const PCINPUT_ForceButton_t			PCINPUT_ForceButton = (PCINPUT_ForceButton_t)0x4e1350;
static const IsDIKeyPressed_t				IsDIKeyPressed = (IsDIKeyPressed_t)0x4e1370;
static const PCINPUT_GetDIKeyPressed_t		PCINPUT_GetDIKeyPressed = (PCINPUT_GetDIKeyPressed_t)0x4e1390;
static const PCINPUT_GetAsciiCode_t			PCINPUT_GetAsciiCode = (PCINPUT_GetAsciiCode_t)0x4e13f0;
static const PCINPUT_GetKeyName_t			PCINPUT_GetKeyName = (PCINPUT_GetKeyName_t)0x4e1420;
static const PCINPUT_GetJoyButtonPressed_t PCINTPUT_GetJoyButtonPressed = (PCINPUT_GetJoyButtonPressed_t)0x4e1430;
static const PCINPUT_ClearAllTriggers_t		PCINPUT_ClearAllTriggers = (PCINPUT_ClearAllTriggers_t)0x4e1460;
static const PCINPUT_EnableJoypad_t			PCINPUT_EnableJoypad = (PCINPUT_EnableJoypad_t)0x4e1480;
static const GenPsxPadData_t				GenPsxPadData = (GenPsxPadData_t)0x4e1490;
static const GetFakePsxPadData_t			GetFakePsxPadData = (GetFakePsxPadData_t)0x4e1820;
static const InitDirectInput_t				InitDirectInput = (InitDirectInput_t)0x4e1860;
static const PCINPUT_ShutDown_t				PCINPUT_ShutDown = (PCINPUT_ShutDown_t)0x4e1c30;
static const ReadDirectInput_t				ReadDirectInput = (ReadDirectInput_t)0x4e1c60;
static const PCINPUT_DoWinKeyDown_t			PCINPUT_DoWinKeyDown = (PCINPUT_DoWinKeyDown_t)0x4e1db0;
static const PCINPUT_HandleMouseMessage_t	PCINPUT_HandleMouseMessage = (PCINPUT_HandleMouseMessage_t)0x4e1dc0;
static const PCINPUT_SetCursorPos_t			PCINPUT_SetCursorPos = (PCINPUT_SetCursorPos_t)0x4e1de0;
static const PCINPUT_ActuatorOn_t			PCINPUT_ActuatorOn = (PCINPUT_ActuatorOn_t)0x4e1e10;
static const PCINPUT_ActuatorOff_t			PCINPUT_ActuatorOff = (PCINPUT_ActuatorOff_t)0x4e1eb0;
static const PCINPUT_StopVibrations_t		PCINPUT_StopVibrations = (PCINPUT_StopVibrations_t)0x4e1ec0;
static const PCINPUT_Load_t					PCINPUT_Load = (PCINPUT_Load_t)0x4e1ee0;
static const PCINPUT_Save_t					PCINPUT_Save = (PCINPUT_Save_t)0x4e2630;