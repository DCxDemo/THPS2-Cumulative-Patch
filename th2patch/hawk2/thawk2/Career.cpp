#include "stdafx.h"

#include "globals.h"
#include "career.h"
#include "mess.h"
#include "types.h"
#include "thawk2/SkatMgr.h"

void* GSkaterManager = (void*)0x5691e0;

// this is direct pointer to th2 level gaps
// but there are 3 gap tables: th2, th1, editor
// 0056a9b8 points to currently selected gaptable
SGapTrick* pGaps = (SGapTrick*)0x53E718;

uint* Career_UnlockFlags = (uint*)0x5672ec;

uint* Career_GapGoalGotMask = (uint*)0x55c990;
uint* Career_GapTrickGotMask = (uint*)0x55ca40; 

int* Career_LevelPickupsGot = (int*)0x55c9e0;
int* Career_LevelPickups = (int*)0x0055c750;

int* Career_GoalGaps = (int*)0x55ca38;
int* Career_TrickGaps = (int*)0x55ca64;

char* AwardGoalGapMessage = (char*)0x55ca44;
char* AwardLevelPickupMessage = (char*)0x55c994;
char* AwardTrickGapMessage = (char*)0x55c9b4;

SMessageProg* Messprog_Goal = (SMessageProg*)0x531d68;


// goal gap logic
void Career_AwardGoalGap(SGapTrick* pGap)
{
    Career_GiveGoalGap(pGap);

    //if got enough goal gaps
    if (Career_NumGoalGapsGot() == *Career_GoalGaps)
    {
        //award goal
        Career_GiveGoalType(EGoalType::GoalGaps);
    }
    else
    {
        char** itemName = (char**)(0x5390b8 + *GLevel * 0x1ac /*sizeof level struct*/ + Career_GoalIndex(EGoalType::GoalGaps) * sizeof(SGoal));

        //print "X out of X items" message
        sprintf(
            AwardGoalGapMessage,    //text buffer
            "%d of %d %s",          //message
            Career_NumGoalGapsGot(),//got gaps
            *Career_GoalGaps,       //out of gaps
            &(*itemName)[0]         //level specific gap name
        );

        printf("%s\r\n", AwardGoalGapMessage);

        Mess_Message(AwardGoalGapMessage, Messprog_Goal, 1, 0, 0);
    }
}

// trick gap logic
void Career_AwardTrickGap(SGapTrick* pGap)
{
    if (!Career_GapIsTrick(pGap)) return;
    if (Career_GotTrickGap(pGap)) return;
    if (Career_GotGoalType(EGoalType::TrickGap)) return;

    Career_GiveTrickGap(pGap);

    if (Career_NumTrickGapsGot() == *Career_TrickGaps)
    {
        //award goal
        Career_GiveGoalType(EGoalType::TrickGap);
    }
    else
    {
        //this never happens?

        //print "X out of X items" message
        sprintf(
            AwardTrickGapMessage,   //text buffer
            "%d of %d Trick Gaps",          //message
            Career_NumGoalGapsGot(),//got gaps
            *Career_GoalGaps       //out of gaps
        );

        printf("%s\r\n", AwardGoalGapMessage);

        Mess_Message(AwardTrickGapMessage, Messprog_Goal, 1, 0, 0);
    }
}

// career gap logic 
void Career_AwardGap(SGapTrick* pGap)
{
    if (!Career_GapActive(pGap)) return;

    //get last hit gaps
    SGapTrick** lastTrickGap = (SGapTrick**)((int)GSkater + 0x3024);
    SGapTrick** lastGoalGap = (SGapTrick**)((int)GSkater + 0x3028);

    //if th2 level and not level generator?
    if ((*GLevel < 10 || *GLevel == 0xd) && !*GenerateLevel) {
        //if not a single player game mode, leave
        if ((*GGame < EGameMode::Career || *GGame > EGameMode::Single)) return;

        //contribute to unlocked gaps list
        Career_GiveGap(pGap);

        //if not career mode, leave
        if (*GGame != EGameMode::Career) return;

        //process goal gap
        if (Career_GapIsGoal(pGap))
            if (!Career_GotGoalGap(pGap))
                if (!Career_GotGoalType(EGoalType::GoalGaps)) {
                    if (!*lastGoalGap)
                        Career_AwardGoalGap(pGap);

                    *lastGoalGap = pGap;
                    return;
                }

        //something's off here, doesnt reward

        //process trick gap
        if (Career_GapIsTrick(pGap))
            if (!Career_GotTrickGap(pGap))
                if (!Career_GotGoalType(EGoalType::TrickGap))
                    *lastTrickGap = pGap;
    }
}

// level specific item pickup logic
void Career_GetLevelPickup()
{
    (*Career_LevelPickupsGot)++;

    int goalIndex = Career_GoalIndex(EGoalType::LevelPickups);

    if (goalIndex == NS_NULL)
        return;

    if (*Career_LevelPickupsGot == *Career_LevelPickups) {
        Career_GiveGoal(goalIndex);
    }
    else
    {
        char** itemName = (char**)(0x5390b8 + *GLevel * 0x1ac /*sizeof level struct*/ + goalIndex * sizeof(SGoal));

        sprintf(
            AwardLevelPickupMessage,//text buffer
            "%d of %d %s",          //message
            *Career_LevelPickupsGot,//got items
            *Career_LevelPickups,   //out of items
            &(*itemName)[0]         //level specific item name
        );

        printf("%s\r\n", AwardLevelPickupMessage);

        Mess_Message(AwardLevelPickupMessage, Messprog_Goal, 1, 0, 0);
    }
}

// returns the number of unlocked levels
int Career_HighestOpenLevel(int param_1)
{
    if (*Cheat_LevelSelect)
        return NUMCAREERLEVELS_TH2;

    for (int open = 0; open <= NUMCAREERLEVELS_TH2; open++)
    {
        if (!Career_LevelOpen(open, param_1))
            return open;
    }

    return 0;
}

// looks up goal index by type and awards goal by index
void Career_GiveGoalType(EGoalType goalType)
{
    uint goalIndex = Career_GoalIndex(goalType);

    if (goalIndex == NS_NULL)
    {
        printf("no goal of type %i in this level", goalType);
        return;
    }

    printf("give goal type: %i\r\n", goalType);

    Career_GiveGoal(goalIndex);
}

// checks whether current skater got specific goal type
bool Career_GotGoalType(EGoalType goalType)
{
    uint goalIndex = Career_GoalIndex(goalType);

    return goalIndex == -1 ? false : Career_Got(goalIndex);
}

// counts the amount of non-zero bits in a binary value
int Career_CountBits(uint value)
{
    int numBits = 0;

    if (value > 0)
        do {
            if (value & 1) numBits++;
            value >>= 1;
        } while (value != 0);

        return numBits;
}

// calculates the amount of obtained goal gaps
int Career_NumGoalGapsGot(void)
{
    return Career_CountBits(*Career_GapGoalGotMask);
}

// calculates the amount of obtained trick gaps
int Career_NumTrickGapsGot(void)
{
    return Career_CountBits(*Career_GapTrickGotMask);
}

// adds goal gap to mask
void Career_GiveGoalGap(SGapTrick* pGap)
{
    *Career_GapGoalGotMask |= 1 << Career_GapGoalNumber(pGap);
}

// adds trick gap to mask
void Career_GiveTrickGap(SGapTrick* pGap)
{
    *Career_GapTrickGotMask |= 1 << Career_GapTrickNumber(pGap);
}

// checks goal gap mask
bool Career_GotGoalGap(SGapTrick* pGap)
{
    return (*Career_GapGoalGotMask & (1 << Career_GapGoalNumber(pGap))) > 0;
}

// checks trick gap mask
bool Career_GotTrickGap(SGapTrick* pGap)
{
    return (*Career_GapTrickGotMask & (1 << Career_GapTrickNumber(pGap))) > 0;
}

// get career goal index by goal type
uint Career_GoalIndex(EGoalType goalType)
{
    //this points to the goal array in the level array
    SGoal* pGoal = &(Levels[*GLevel].Goals[0]);

    for (int goalIndex = 0; goalIndex < NUMGOALS_TH2; goalIndex++)
    {
        if (pGoal->goalType == goalType)
        {
            printf("got goal index: %i", goalIndex);
            return goalIndex;
        }

        pGoal++;
    }

    return NS_NULL;
}

// this is basically "give chars if unlocked" function
void Career_ApplyCheats()
{
    //is mcsqueeb unlocked?
    if (Career_CheatUnlocked(ECheat::McSqueeb))
        Career_UnlockCharacter(0x200);

    //is spidey unlocked?
    if (Career_CheatUnlocked(ECheat::Spiderman))
        Career_UnlockCharacter(0x100);

    //is officer unlocked?
    if (Career_CheatUnlocked(ECheat::OfficerDick))
        Career_UnlockCharacter(0x40);

    //if got all gaps, give carrera
    if (*Career_UnlockFlags & 4)
        Career_UnlockCharacter(0x80);
}

char* cheatNames[] = {
    "McSqueeb",
    "Spider-Man",
    "Officer Dick",
    "Skip to restart",
    "Kid mode",
    "Perfect balance",
    "Always special",
    "STUD",
    "Weight",
    "Wireframe",
    "Slow-Nic",
    "Big head",
    "Sim mode",
    "Smooth",
    "Moon physics",
    "Disco mode",
    "Level flip"
};

// returns proper cheat name based on ECheat enum, used on cheat screen in options menu
char* Career_CheatName(ECheat cheat)
{
    //is cheat out of bounds?
    if (cheat < ECheat::First || ECheat::Last < cheat)
    {
        printf("Invalid cheat: %i", cheat);
        return "?";
    }

    return cheatNames[(int)cheat];
}

// returns cheat type
int Career_CheatType(ECheat cheat)
{
    if (0 <= (uint)cheat && (uint)cheat < 3)
        return 0;

    if ((uint)cheat == 8)
        return 2;

    return 1;
}

// checks current player score
void Career_CheckScore()
{
    //what a mess
    int* score = (int*)(*((int*)GSkater) + 0x16c);
    SGoal* pGoal = Levels[*GLevel].Goals;

    //loop through all goals
    for (int goalIndex = 0; goalIndex < NUMGOALS_TH2; goalIndex++)
    {
        if (!Career_Got(goalIndex))                     //maybe we got the goal already? (skip career_got right away)
            if (pGoal->goalType == EGoalType::Score)    //if it is a score taget goal
                if (*score >= pGoal->intParam)          //did we beat the target?
                {
                    //award new goal
                    Career_GiveGoal(goalIndex);
                    printf("got %s - %i\r\n", pGoal->goalText, pGoal->intParam);
                }

        //next goal
        pGoal++;
    }
}

#define NUM_SKATERS 20

// clears the game, used by the unlock everything cheat
void Career_ClearGameWithEveryone(void)
{
    for (int i = 0; i < NUM_SKATERS; i++)
        Career_ClearGame(i);
}

// checks if gap is a trick gap
bool Career_GapIsTrick(SGapTrick* pGap)
{
    return pGap->careerFlag == EGapFlag::TrickGap ? Career_GapActive(pGap) : false;
}

// checks if gap is a trick gap
bool Career_GapIsGoal(SGapTrick* pGap)
{
    return pGap->careerFlag == EGapFlag::GoalGap ? Career_GapActive(pGap) : false;
}

// checks if gap is in this level
bool Career_GapActive(SGapTrick* pGap)
{
    SLevel* pLevel = &Levels[*GLevel];
    int iVar1 = (int)pGap->index % 10000;

    return pLevel->gapStart <= iVar1 && iVar1 <= pLevel->gapEnd;
}

// finds gap index in gap table
int Career_GapNumber(SGapTrick* pGap)
{
    SGapTrick* cursor = pGaps;
    int gapIndex = 0;

    //loop through the gap table until index hits 0xFFFF
    while (cursor->index != -1) {

        //if gap belongs to this level
        if (Career_GapActive(cursor)) {
            
            //if match, get gap index
            if (cursor == pGap) 
            {
                printf("Gap found: %s %i\r\n", pGap->name, gapIndex);
                return gapIndex;
            }

            gapIndex++;
        }

        cursor++;
    }

    printf("!!! GapTrick not found: %s\r\n", pGap->name);
    
    return 0;
}

// finds trick gap index in a gap table
int Career_GapTrickNumber(SGapTrick* pGap)
{
    SGapTrick* cursor = pGaps;
    int gapIndex = 0;

    //loop through the gap table until index hits 0xFFFF
    while (cursor->index != -1) {

        //if gap belongs to this level and is trick
        if (Career_GapActive(cursor) && Career_GapIsTrick(pGap)) {

            //if match, get gap index
            if (cursor == pGap)
            {
                printf("Gap found: %s %i\r\n", pGap->name, gapIndex);
                return gapIndex;
            }

            gapIndex++;
        }

        cursor++;
    }

    printf("!!! GapTrick not found: %s\r\n", pGap->name);

    return 0;
}

// finds goal gap index in a gap table
int Career_GapGoalNumber(SGapTrick* pGap)
{
    SGapTrick* cursor = pGaps;
    int gapIndex = 0;

    //loop through the gap table until index hits 0xFFFF
    while (cursor->index != -1) {

        //if gap belongs to this level and is trick
        if (Career_GapActive(cursor) && Career_GapIsGoal(pGap)) {

            //if match, get gap index
            if (cursor == pGap)
            {
                printf("Gap found: %s %i\r\n", pGap->name, gapIndex);
                return gapIndex;
            }

            gapIndex++;
        }

        cursor++;
    }

    printf("!!! GapTrick not found: %s\r\n", pGap->name);

    return 0;
}

/*
void Career_ToggleCheat(ECheat cheat, bool state)
{
    Career_SetCheat(cheat, state & 0xffffff00 | (uint)(!Career_CheatState(cheat, bool)));
}
*/

// returns the amount needed to unlock the level for message in main menu
int Career_LevelNeeds(int levelIndex)
{
    //get chatacter
    int skaterID = GetSkaterID(GSkaterManager);

    //get character progress
    void* charProg = Career_GetCharacterProgress(skaterID);

    //if level is closed
    if (Career_LevelOpenCareerMode(levelIndex, charProg))
        return 0;

    //if competition, minus sign encodes medal requirement
    if (Levels[levelIndex].medalstounlock != 0)
        return -Levels[levelIndex].medalstounlock;
    
    //if regular level
    return Levels[levelIndex].cashtounlock;
}