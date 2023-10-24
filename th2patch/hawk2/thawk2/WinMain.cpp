#include "stdafx.h"
#include "types.h"
#include "Globals.h"

HWND hWnd = (HWND)0x029d4fc4;

tagMSG msg;

uint WinYield()
{
    printf("WinYield()\r\n");

    while (true) {

        // maybe we processed all messages?
        if (!PeekMessageA(&msg, hWnd, 0, 0, 0)) return 0x75; //is this some win value?

        // null message?
        if (!GetMessageA(&msg, hWnd, 0, 0)) break;

        // process message: this blocks alt in the original game
        if (msg.message != WM_SYSKEYDOWN && 
            msg.message != WM_SYSKEYUP) {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
    }

    return msg.wParam;
}

void WINMAIN_ScreenDimensions(int* width, int* height)
{
    *width = *ScreenWidth;
    *height = *ScreenHeight;
}


char* lpFileName = (char*)0x29d4fc8;

void WINMAIN_LoadSetting(LPCSTR lpAppName, LPCSTR lpKeyName, LPCSTR lpDefault, LPSTR lpReturnedString)
{
    GetPrivateProfileStringA(lpAppName, lpKeyName, lpDefault, lpReturnedString, 256, lpFileName);
}


/*
void WINMAIN_ShutDown(void)
{
    printf("WinMain_Shutdown()\n");

    NETGAME_ShutDown();
    D3DTIMER_Kill();
    PCINPUT_ShutDown();
    PCMOVIE_StopFMV();
    PCMOVIE_XAStop();
    D3D_ShutDown(1);
}*/