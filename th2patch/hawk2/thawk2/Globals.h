#pragma once
#include "../patchStuff.h"

extern SLevel* Levels;

extern void* GSkater;
extern void* GSkater2;

extern int* ViewportMode;

extern EGameMode* GGame;
extern bool* GamePaused;

extern bool* Loading;
extern int* LoadingTime;
extern int* ProcessingTime;

extern bool* GenerateLevel;

extern int* ScreenWidth;
extern int* ScreenHeight;

extern int* hardcodedWidth;
extern int* hardcodedHeight;

extern int* prevTicks;
extern int* Vblanks;
extern int* Xblanks;
extern int* GameFrozen;
extern int* TTime;

extern int* gJoyEnabled;
extern int* gAnalogsEnabled; //??

extern int* GLevel;
extern int* InFrontEnd;

extern int* SFXLEVEL;
extern int* XALEVEL;

extern int* Redbook_XAFadeScale;
extern int* gMusicPlaying;
extern int* Redbook_XAFading;

extern int* Redbook_XACurrentChannel;
extern int* Redbook_XACurrentGroup;
extern int* Redbook_XACurrentSector;

extern bool* Redbook_XACheckSectorOnVSync;
extern int* Redbook_XAModeSet;
extern int* Redbook_XACompleteTimer;
extern int* Redbook_XAPaused;
extern bool* Redbook_XAValid;
extern int* Redbook_XATryAgain;
extern int* Redbook_XASeeking;

extern int* Redbook_XAStartSector;
extern int* Redbook_XAEndSector;

extern int* Redbook_PausedSongPos;

extern int* Cheat_LevelSelect;
extern int* Cheat_Light;