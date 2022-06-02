#include "stdafx.h"

#include "globals.h"
#include "career.h"
#include "mess.h"

int* Career_GapGoalGotMask = (int*)0x55c990;
int* Career_GoalGaps = (int*)0x55ca38;

char* AwardGoalGapMessage = (char*)0x55ca44;
void* Messprog_Goal = (void*)0x531d68;

int Career_NumGoalGapsGot()
{
    return Career_CountBits(*Career_GapGoalGotMask);
}

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

        Mess_Message(AwardGoalGapMessage, Messprog_Goal, 1, 0, 0);
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

/// <summary>
/// Triggers on goal completion
/// </summary>
/// <param name="goalType"></param>
void Career_GiveGoalType(EGoalType goalType)
{
    printf("giving goal type... %i\r\n", goalType);

    Career_GiveGoal(Career_GoalIndex(goalType));
}