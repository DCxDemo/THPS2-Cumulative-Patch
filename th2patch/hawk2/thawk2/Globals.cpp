#include "stdafx.h"

void* GSkater = (void*)0x5674b8;
void* GSkater2 = (void*)0x5674bc;

int* GGame = (int*)0x530d38;
bool* GamePaused = (bool*)0x55e864;
int* ScreenWidth = (int*)0x29D6FE4;
int* ScreenHeight = (int*)0x29D6FE8;

int* prevTicks = (int*)0x29d4fbc;
int* Vblanks = (int*)0x56af7c;
int* Xblanks = (int*)0x56af80;
int* GameFrozen = (int*)0x567540;
int* TTime = (int*)0x567534;

int* gJoyEnabled = (int*)0x547a78;
int* gAnalogsEnabled = (int*)0x6a1024; //??

int* GLevel = (int*)0x5674F8;

int* SFXLEVEL = (int*)0x528CA4;
int* XALEVEL = (int*)0x528CA8;

int* Redbook_XAFadeScale = (int*)0x53458C;
int* gMusicPlaying = (int*)0x5674E0;
int* Redbook_XAFading = (int*)0x5684F8;
int* Redbook_XACurrentChannel = (int*)0x5684E8;
int* Redbook_XACurrentGroup = (int*)0x5684EC;
int* Redbook_XACurrentSector = (int*)0x5684C8;
int* Redbook_XACheckSectorOnVSync = (int*)0x5684DC;
int* Redbook_XAModeSet = (int*)0x5684DD;
int* Redbook_XACompleteTimer = (int*)0x5684D8;
int* Redbook_XAPaused = (int*)0x5684E0;

int* Cheat_LevelSelect = (int*)0x567544;