#include "stdafx.h"
#include "../patchStuff.h"


char** DefaultHighScoreInitials = (char**)0x00521ec8;

void* BaddyList = (void*)0x0055c31c;
void* EnvironmentalObjectList = (void*)0x00567ba0;
void* PowerUpList = (void*)0x00568490;
void* SuspendedList = (void*)0x00567ba4;

int* GStatus = (int*)0x0055e85c;
bool* gotNewStatus = (bool*)0x0055e338;
char** statusNames = (char**)0x00528cb0;

SLevel* Levels = (SLevel*)0x538FF8;

void* GSkater = (void*)0x5674b8;
void* GSkater2 = (void*)0x5674bc;

int* GNumberOfPlayers = (int*)0x00530d3c;

int* ViewportMode = (int*)0x00567588;

EGameMode* GGame = (EGameMode*)0x530d38;
bool* GamePaused = (bool*)0x55e864;

bool* Loading = (bool*)0x0055e230;
int* LoadingTime = (int*)0x0055e8b0;
int* ProcessingTime = (int*)0x0055e8b4;

bool* GenerateLevel = (bool*)0x55e124;


int* ScreenWidth = (int*)0x29D6FE4;
int* ScreenHeight = (int*)0x29D6FE8;

int* hardcodedWidth = (int*)0x4f3f30;
int* hardcodedHeight = (int*)0x4f3f37;

int* prevTicks = (int*)0x29d4fbc;
int* Vblanks = (int*)0x56af7c;
int* Xblanks = (int*)0x56af80;
int* GameFrozen = (int*)0x567540;
int* TTime = (int*)0x567534;

int* gJoyEnabled = (int*)0x547a78;
int* gAnalogsEnabled = (int*)0x6a1024; //??

int* GLevel = (int*)0x5674F8;
int* InFrontEnd = (int*)0x5674e0;

int* SFXLEVEL = (int*)0x528CA4;
int* XALEVEL = (int*)0x528CA8;

int* Redbook_XAFadeScale = (int*)0x53458C;


int* Redbook_XAFading = (int*)0x5684F8;
int* Redbook_XACurrentChannel = (int*)0x5684E8;
int* Redbook_XACurrentGroup = (int*)0x5684EC;
int* Redbook_XACurrentSector = (int*)0x5684C8;
bool* Redbook_XACheckSectorOnVSync = (bool*)0x5684DC;
int* Redbook_XAModeSet = (int*)0x5684DD;
int* Redbook_XACompleteTimer = (int*)0x5684D8;
int* Redbook_XAPaused = (int*)0x5684E0;
bool* Redbook_XAValid = (bool*)0x5684e4;
int* Redbook_XATryAgain = (int*)0x5684f0;
int* Redbook_XASeeking = (int*)0x5684f4;

int* Redbook_XAGroupStartingSector = (int*)0x5344fc;

int* Redbook_XAStartSector = (int*)0x5684d4;
int* Redbook_XAEndSector = (int*)0x5684c4;

int* Redbook_PausedSongPos = (int*)0x55e350;

int* Cheat_LevelSelect = (int*)0x567544;
int* Cheat_Light = (int*)0x5674c8;
int* Cheat_FlipScreen = (int*)0x005674ec;



int* Trig_OffsetList = (int*)0x0056ae70;
int* NumNodes = (int*)0x0056ae74;

int* TotalRailNodes = (int*)0x005684bc;
void* RailNodeLookup = (void*)0x005684b8;


bool* AutoKickSetting = (bool*)0x00567038;
bool* AutoKickState = (bool*)0x0055c88c;