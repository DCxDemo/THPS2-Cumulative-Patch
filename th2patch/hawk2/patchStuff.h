#pragma once
#include "GameOptions.h"
#include "thawk2/Career.h"

extern GameOptions options;

enum class EGeneratorTheme : int {
    Powerplant = 0,
    Industrial = 1,
    Outdoor = 2,
    School = 3,
    First = Powerplant,
    Last = School
};

enum class EInitCleanupType : int {
    Hard = 0,
    Soft = 1,
    LevelEditor = 2
};

enum class EGameMode : int {
    None = 0,
    Career = 1,
    Practice = 2,
    Single = 3,
    Unknown4 = 4,
    Trick = 5,
    Unknown6 = 6,
    Horse = 7,
    Graffiti = 8,
    Tag = 9,
    Contest = 10,
    First = None,
    Last = Contest
};

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
    int cashToUnlock;
    int medalsToUnlock;
    int isCompetition2; //bool
    int somedata[4];
    int index;
    int somedata2[5];
    int gapFirst;
    int gapLast;
    Career::SGoal Goals[10];
    int killers;
} SLevel;

void Patch();
void PatchSkaters();
void SetHooks();
void GetSong(int num);
int CountSongs();
void PCINPUT_ActuatorOn_Hook(int index, int time, int motor, int value);