#include "stdafx.h"

#include "globals.h"
#include "career.h"
#include "mess.h"
#include "types.h"

SGapTrick* pGapTrickTable = (SGapTrick*)0x53E718;

uint* Career_UnlockFlags = (uint*)0x5672ec;

uint* Career_GapGoalGotMask = (uint*)0x55c990;
uint* Career_GapTrickGotMask = (uint*)0x55ca40;

int* Career_LevelPickupsGot = (int*)0x55c9e0;
int* Career_LevelPickups = (int*)0x0055c750;

int* Career_GoalGaps = (int*)0x55ca38;

char* AwardGoalGapMessage = (char*)0x55ca44;
char* AwardLevelPickupMessage = (char*)0x55c994;

void* Messprog_Goal = (void*)0x531d68;

// goal gap logic
void Career_AwardGoalGap(void* gapTrick)
{
    Career_GiveGoalGap(gapTrick);

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

// add goal gap to mask
void Career_GiveGoalGap(void* gapTrick)
{
    *Career_GapGoalGotMask |= 1 << Career_GapGoalNumber(gapTrick);
}

// add trick gap to mask
void Career_GiveTrickGap(void* gapTrick)
{
    *Career_GapTrickGotMask |= 1 << Career_GapTrickNumber(gapTrick);
}

// check goal gap mask
bool Career_GotGoalGap(void* gapTrick)
{
    return (*Career_GapGoalGotMask & (1 << Career_GapGoalNumber(gapTrick))) > 0;
}

bool Career_GotTrickGap(void* gapTrick)
{
    return (*Career_GapTrickGotMask & (1 << Career_GapTrickNumber(gapTrick))) > 0;
}

// get career goal index by goal type
uint Career_GoalIndex(EGoalType goalType)
{
    //this points to the goal array in the level array
    //smth like Levels[GLevel].Goals[goalIndex]->goalType
    SGoal* pGoal = (SGoal*)(0x5390b0 + *GLevel * 0x1ac /*sizeof level struct*/);

    for (int goalIndex = 0; goalIndex < NUMGOALS_TH2; goalIndex++)
    {
        if (pGoal->goalType == goalType)
            return goalIndex;

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

    SGoal* pGoal = (SGoal*)(0x5390b0 + *GLevel * 0x1ac /*sizeof level struct*/);

    //loop through all goals
    for (int goalIndex = 0; goalIndex < NUMGOALS_TH2; goalIndex++)
    {
        //if it is a score taget goal
        if (pGoal->goalType == EGoalType::Score)
        {
            //did we beat the target?
            if (*score >= pGoal->intParam)
                //maybe we beat it already?
                if (!Career_Got(goalIndex))
                {
                    //award new goal
                    Career_GiveGoal(goalIndex);
                    printf("got %s - %i\r\n", pGoal->goalText, pGoal->intParam);
                }
        }

        //next goal
        pGoal++;
    }
}

#define NUM_SKATERS 20


void Career_ClearGameWithEveryone(void)
{
    for (int i = 0; i < NUM_SKATERS; i++)
        Career_ClearGame(i);
}

bool Career_GapIsTrick(SGapTrick* gapTrick)
{
    return gapTrick->careerFlag == 2 ? Career_GapActive(gapTrick) : false;
}

bool Career_GapIsGoal(SGapTrick* gapTrick)
{
    return gapTrick->careerFlag == 1 ? Career_GapActive(gapTrick) : false;
}


SGapTrick* gapTable = (SGapTrick*)0x53E718;

//finds gap index in gap table
int Career_GapNumber(SGapTrick* gapTrick)
{
    int myresult = ((int)gapTrick - (int)gapTable) / sizeof(SGapTrick);

    SGapTrick* cursor = gapTable;
    int gapIndex = 0;

    while (cursor->index != -1) {

        //this isolates gap groups somehow, maybe used to split by levels
        //if (Career_GapActive(cursor)) {
        if (true) {

            if (cursor == gapTrick) 
            {
                printf("Gap found: %s %i %i\r\n", gapTrick->name, gapIndex, myresult);
                return gapIndex;
            }

            gapIndex++;
        }

        cursor++;
    }

    printf("!!! GapTrick not found: %s\r\n", gapTrick->name);
    
    return 0;

}