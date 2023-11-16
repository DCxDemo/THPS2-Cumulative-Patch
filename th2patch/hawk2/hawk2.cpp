#include "stdafx.h"

#include <time.h>

#include "hawk2.h"
#include "hawk2_utils.h"
#include "patchStuff.h"
#include <ddraw.h>

//LPDIRECTDRAW lpDD = *((LPDIRECTDRAW*)0x29D6FF8);

bool initialized = false;

HINSTANCE origModule;
HINSTANCE thisModule;

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			Init(hModule);
			break;
		case DLL_PROCESS_DETACH:
			Exit();
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
			break;
	}

	return TRUE;
}

//define hook type for DirectInputCreateA
typedef HRESULT(__stdcall *__DirectInputCreateA)(HINSTANCE hinst, DWORD dwVersion, LPDIRECTINPUTA *ppDI, LPUNKNOWN punkOuter);

//wrapper func for directinputcreate
HRESULT WINAPI DirectInputCreateA(HINSTANCE hinst, DWORD dwVersion, LPDIRECTINPUTA* ppDI, LPUNKNOWN punkOuter)
{
	//load dll
	if (!origModule)
		LoadDll("dinput.dll");

	//get address of DirectInputCreateA
	void* address = (void*)GetProcAddress(origModule, "DirectInputCreateA");

	//if no address - exit
	if (!address)
		::ExitProcess(0);

	//cast to function pointer 
	__DirectInputCreateA _DirectInputCreateA = (__DirectInputCreateA)address;

	//return original call result
	return _DirectInputCreateA(hinst, dwVersion, ppDI, punkOuter);
}

//load dll by name
void LoadDll(char* filename)
{
	char buffer[MAX_PATH];

	::GetSystemDirectory(buffer, MAX_PATH);
	strcat_s(buffer, "\\");
	strcat_s(buffer, filename);

	if (!origModule) 
		origModule = ::LoadLibrary(buffer);

	if (!origModule)
	{
		_trace("Failed to load dll!\n");
		::ExitProcess(0);
	}
}

void Init(HANDLE hModule)
{
	_trace("PROXY Init!!\n");

	if (!initialized)
		initialized = InitPatches();

	origModule = NULL;
	thisModule = (HINSTANCE)hModule;
}

void Exit()
{
	_trace("PROXY Exit!!\n");

	if (origModule)
	{
		::FreeLibrary(origModule);
		origModule = NULL;
	}
}

bool InitPatches()
{
	_trace("InitPatches!!\n");

	srand(time(0));

	//only allocate console in a debug build
	#ifdef _DEBUG
	if (true)
	{
		AllocConsole();
		AttachConsole( GetCurrentProcessId() );

		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
	}
	#endif

	
	options.Load();

	Patch();
	LoadMessageProg();

	return true;
}