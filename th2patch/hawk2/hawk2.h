#pragma once

#include <dinput.h>

// exports
HRESULT WINAPI DirectInputCreateA(HINSTANCE hinst, DWORD dwVersion, LPDIRECTINPUTA *ppDI, LPUNKNOWN punkOuter);

void LoadDll(char* filename);
void Init(HANDLE hModule);
void Exit();
bool InitPatches();