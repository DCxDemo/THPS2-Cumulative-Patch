#pragma once
#include "GameOptions.h"

extern GameOptions options;

extern int* ScreenWidth;
extern int* ScreenHeight;
extern int* GGame;
extern bool* GamePaused;

void Patch();
int CountSongs();