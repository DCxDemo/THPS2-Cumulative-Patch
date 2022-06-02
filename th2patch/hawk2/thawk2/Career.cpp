#include "stdafx.h"

#include "globals.h"
#include "career.h"
#include "mess.h"
#include "types.h"

uint* Career_GapGoalGotMask = (uint*)0x55c990;
uint* Career_GapTrickGotMask = (uint*)0x55ca40;

int* Career_LevelPickupsGot = (int*)0x55c9e0;
int* Career_LevelPickups = (int*)0x0055c750;

int* Career_GoalGaps = (int*)0x55ca38;

char* AwardGoalGapMessage = (char*)0x55ca44;
char* AwardLevelPickupMessage = (char*)0x55c994;

void* Messprog_Goal = (void*)0x531d68;


void Career_AwardGoalGap(void* goalGap)
{
    Career_GiveGoalGap(goalGap);

    //if got enough goal gaps
    if (Career_NumGoalGapsGot() == *Career_GoalGaps)
    {
        //award goal
        Career_GiveGoalType(EGoalType::GoalGap);
    }
    else
    {
        char** itemName = (char**)(0x5390b8 + *GLevel * 0x1ac /*sizeof level struct*/ + Career_GoalIndex(EGoalType::GoalGap) * 0x18 /*sizeof level goal struct*/);

        //print "X out of X items" message
        sprintf(
            AwardGoalGapMessage,    //text buffer
            "%d of %d %s",          //message
            Career_NumGoalGapsGot(),//got gaps
            *Career_GoalGaps,       //out of gaps
            &(*itemName)[0]         //level specific gap name
        );

        Mess_Remove(AwardGoalGapMessage);
        Mess_Message(AwardGoalGapMessage, Messprog_Goal, 1, 0, 0);
    }
}


void Career_GetLevelPickup()
{
    (*Career_LevelPickupsGot)++;

    int goalIndex = Career_GoalIndex(EGoalType::Collect1);

    if (goalIndex == NS_NULL)
        return;

    if (*Career_LevelPickupsGot == *Career_LevelPickups) {
        //Career_GiveGoal(goalIndex);
        Career_GiveGoalType(EGoalType::Collect1);
    }
    else
    {
        char** itemName = (char**)(0x5390b8 + *GLevel * 0x1ac /*sizeof level struct*/ + goalIndex * 0x18 /*sizeof level goal struct*/);

        sprintf(
            AwardLevelPickupMessage,//text buffer
            "%d of %d %s",          //message
            *Career_LevelPickupsGot,//got items
            *Career_LevelPickups,   //out of items
            &(*itemName)[0]         //level specific item name
        );

        Mess_Remove(AwardLevelPickupMessage);
        Mess_Message(AwardLevelPickupMessage, Messprog_Goal, 1, 0, 0);
    }
}



#define NUM_LEVELS 12

int Career_HighestOpenLevel(int param_1)
{
    if (*Cheat_LevelSelect) {
        return NUM_LEVELS;
    }

    int open = 0;

    for (; open <= NUM_LEVELS; open++)
    {
        if (!Career_LevelOpen(open, param_1))
            break;
    }

    return open;
}

//enum ECheat

int Career_CheatType(int cheat)
{
    if (0 <= cheat && cheat < 3)
        return 0;

    if (cheat == 8)
        return 2;

    return 1;
}

// looks up goal index by type and awards goal by index
void Career_GiveGoalType(EGoalType goalType)
{
    printf("giving goal type... %i\r\n", goalType);

    uint goalIndex = Career_GoalIndex(goalType);

    if (goalIndex == NS_NULL) return;

    Career_GiveGoal(goalIndex);
}

// Checks whether current skater got specific goal type
bool Career_GotGoalType(EGoalType goalType)
{
    uint goalIndex = Career_GoalIndex(goalType);

    return goalIndex == -1 ? false : Career_Got(goalIndex);
}

// Counts amount of 1 bits in a binary value
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

// Calculates amount of obtained goal gaps
int Career_NumGoalGapsGot(void)
{
    return Career_CountBits(*Career_GapGoalGotMask);
}

// Calculates amount of obtained trick gaps
int Career_NumTrickGapsGot(void)
{
    return Career_CountBits(*Career_GapTrickGotMask);
}

// Gets career goal index by goal type
uint Career_GoalIndex(EGoalType goalType)
{
    uint goalIndex = 0;

    //this points to the goal array in the level array
    //smth like Levels[GLevel].Goals[goalIndex]->goalType
    SGoal *pGoal = (SGoal*)(0x5390b0 + *GLevel * 0x6b /*sizeof level struct*/);
    
    do {
        if (pGoal->goalType == goalType)
            return goalIndex;

        goalIndex++;
        pGoal++;
    } while (goalIndex < 10);

    return NS_NULL;
}