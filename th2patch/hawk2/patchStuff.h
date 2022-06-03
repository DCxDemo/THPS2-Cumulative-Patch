#pragma once
#include "GameOptions.h"

extern GameOptions options;

//should be moved to a separate file
typedef struct HookFunc {
	int address;
	void* func;
} HookFunc;


void Patch();
void PatchSkaters();
void SetHooks();
int CountSongs();