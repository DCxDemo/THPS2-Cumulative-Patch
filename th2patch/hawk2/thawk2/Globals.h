#pragma once
#include "../patchStuff.h"

//array of high score initials, NS devs
extern char** DefaultHighScoreInitials;

extern void* BaddyList;
extern void* EnvironmentalObjectList;
extern void* PowerUpList;
extern void* SuspendedList;

extern int* GStatus;
extern bool* gotNewStatus;
extern char** statusNames;

extern SLevel* Levels;

extern void* GSkater;
extern void* GSkater2;

extern int* GNumberOfPlayers;

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
extern int* Cheat_FlipScreen;


extern int* Trig_OffsetList;
extern short** ppTrig_OffsetList;
extern int* NumNodes;

extern int* TotalRailNodes;
extern void* RailNodeLookup;


extern bool* AutoKickSetting;
extern bool* AutoKickState;

extern int* camDist;
extern int* camPitch;
extern int* camYOffset;

extern SViewport** pCurrentViewport;

extern SViewport* DefaultViewport;
extern SViewport* LeftViewport;
extern SViewport* RightViewport;
extern SViewport* TopViewport;
extern SViewport* BottomViewport;
extern SViewport* TopLeftViewport;
extern SViewport* BottomRightViewport;
extern SViewport* TopLeftBigViewport;
extern SViewport* BottomRightBigViewport;

extern bool* closeCam;

extern void* CameraList;