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
}
*/



/// <summary>
///  not an original name, renamed for convenience
/// </summary>
/// <param name="hWnd"></param>
/// <param name="Msg"></param>
/// <param name="wParam"></param>
/// <param name="lParam"></param>
/// <returns></returns>
LRESULT WINMAIN_WndProc(HWND hWnd, uint Msg, WPARAM wParam, LPARAM lParam)
{
    if (Msg < 0x101) { //WM_KEYUP
        switch (Msg) {

            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;

            case WM_MOVE:
            case 4: // ??
            case WM_SETFOCUS:
            case WM_KILLFOCUS:
            case 9: // ??
            case WM_ENABLE:
            case WM_SETREDRAW:
            case WM_SETTEXT:
            case WM_GETTEXT:
            case WM_GETTEXTLENGTH:
            case WM_PAINT:
                // go to next message
                break;

            case WM_SIZE:
                return 0;

            case WM_ACTIVATE:
               // remember got message or smth?
               // _DAT_029d6fec = (uint)((short)wParam != 0);
                return 0;
            case WM_CLOSE:
                // handle shutdown
                /*
                PCstop();
                WINMAIN_ShutDown();
                if (PCMemBuffer != 0) {
                    operator_free(PCMemBuffer);
                    PCMemBuffer = 0;
                }
                */
                break;

            // any other message
            default:
                //MessageBox(NULL, "test", "test", 0);

                //printf("wtf %i\n", wParam);

                //PCINPUT_DoWinKeyDown(wParam);
                switch (wParam) {
                    case VK_TAB:
                    case VK_SHIFT:
                    case VK_CONTROL:
                    case VK_MENU:
                    case VK_LWIN:
                    case VK_RWIN:
                    case VK_APPS:
                    case VK_F10:
                        // no reaction to these keys at all
                        return 0;

                    case VK_F9:
                        // take a screenshot on F9.
                        //D3D_ScreenShot();
                        MessageBox(NULL, "test", "test", 0);
                        printf("screenshot!\n");
                        return 0;
                }
        }
    }
    // handle mouse messages
    else if (Msg < 0x20a) { //WM_MOUSEWHEEL
        if (0x200 < Msg) { //WM_MOUSEMOVE
            //PCINPUT_HandleMouseMessage(Msg);
            return 0;
        }
        // handle sys keys
        if (0x103 < Msg) { // WM_DEADCHAR
            if (Msg < 0x108) { //WM_UNICHAR
                //return 0;
            }

            // ignore sys command
            if (Msg == WM_SYSCOMMAND) {
                // this is probably why you cant close the window using X, lol
               // return 0;
            }
        }
    }
    else if (Msg == WM_HOTKEY) {
        // ignore user global hotkeys i guess
        //return 0;
    }

    return DefWindowProcA(hWnd, Msg, wParam, lParam);
}



void WINMAIN_PatchWndProc()
{
    int result = SetWindowLongPtr(hWnd, GWL_WNDPROC, (LONG_PTR)WINMAIN_WndProc);
}