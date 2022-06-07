#pragma once
#include "GameOptions.h"
#include "thawk2/Career.h"

extern GameOptions options;

// should be moved to a separate file
typedef struct HookFunc {
	int address;
	void* func;
} HookFunc;

// defines basic level data like name, career unlock stuff, etc.
typedef struct SLevel
{
    char name[64];
    char* subname;
    char* shortname;
    int isCompetition; //bool
    char* trgfile;
    int compScore[3];
    int compAward[3];
    char* renderthumb;
    int u2;
    int globeX;
    int globeY;
    char* thumb;
    int cashtounlock;
    int medalstounlock;
    int isCompetition2; //bool
    int somedata[4];
    int index;
    int somedata2[5];
    int gapStart;
    int gapEnd;
    SGoal Goals[10];
    int killers;
} SLevel;


void Patch();
void PatchSkaters();
void SetHooks();
int CountSongs();