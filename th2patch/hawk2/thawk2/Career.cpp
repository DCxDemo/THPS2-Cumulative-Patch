#include "stdafx.h"

#include "globals.h"
#include "career.h"
#include "mess.h"
#include "types.h"
#include "SkatMgr.h"
#include "hawk2_utils.h"
#include "sfx.h"
#include "CBruce.h"
#include "_old.h"

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


//new func
void* Career_GetCurrentCharacterProgress()
{
    return Career_GetCharacterProgress(GetSkaterID(GSkaterManager));
}



// goal gap logic
void Career_AwardGoalGap(SGapTrick* pGap)
{
    SLevel* level = &Levels[*GLevel];

    Career_GiveGoalGap(pGap);

    int numGoalGaps = Career_NumGoalGapsGot();

    //if got enough goal gaps
    if (numGoalGaps >= *Career_GoalGaps)
    {
        //award goal
        Career_GiveGoalType(EGoalType::Gaps);
    }
    else
    {
        //print "X out of X items" message
        sprintf(
            AwardGoalGapMessage,    //text buffer
            "%d of %d %s",          //message
            numGoalGaps,             //got gaps
            *Career_GoalGaps,       //out of gaps
            level->Goals[Career_GoalIndex(EGoalType::Gaps)].stringParam    //level specific gap name
        );

        printf("%s\r\n", AwardGoalGapMessage);

        Mess_Message(AwardGoalGapMessage, Messprog_Goal, 1, 0, 0);
    }
}

// trick gap logic
void Career_AwardTrickGap(SGapTrick* pGap)
{
    printf("decomp Career_AwardTrickGap called...\n");

    //oopsie, not a gap trick
    if (!Career_GapIsTrick(pGap)) return;

    //oopsie, already got this goal gap
    if (Career_GotTrickGap(pGap)) return;

    //oopsie, already awarded this goal
    if (Career_GotGoalType(EGoalType::Trick)) return;


    //remember we got this trick gap
    Career_GiveTrickGap(pGap);

    //if got all trick gaps
    if (Career_NumTrickGapsGot() == *Career_TrickGaps)
    {
        //award goal
        Career_GiveGoalType(EGoalType::Trick);

        printf("\tawarded %s goal", pGap->Name);
    }
    else //if not
    {
        //but this never happens?
        //trick goal usually is just 1 trick, so...

        //print "X out of X items" message
        sprintf(
            AwardTrickGapMessage,       //text buffer
            "%d of %d Trick Gaps",      //message
            Career_NumGoalGapsGot(),    //got gaps
            *Career_GoalGaps            //out of gaps
        );

        printf("\t%s\r\n", AwardTrickGapMessage);

        Mess_Message(AwardTrickGapMessage, Messprog_Goal, 1, 0, 0);
    }
}

// career gap logic 
void Career_AwardGap(SGapTrick* pGap)
{
    printf("decomp Career_AwardGap called...\n");

    CBruce* pSkater = new CBruce(GSkater);

    if (!Career_GapActive(pGap)) return;

    //get last hit gaps
    SGapTrick* lastTrickGap = (SGapTrick*)pSkater->GetValue(0x3024);
    SGapTrick* lastGoalGap = (SGapTrick*)pSkater->GetValue(0x3028);

    //if th2 level and not level generator? whats level 13?
    if ((*GLevel > 10 && *GLevel != 13) || *GenerateLevel) return;


    //if not a single player game mode, leave
    if (*GGame != EGameMode::Career && *GGame != EGameMode::Single && *GGame != EGameMode::Practice) return;

    //contribute to unlocked gaps list
    Career_GiveGap(pGap);

    //if career mode, process goals
    if (*GGame == EGameMode::Career)
    {
        //is this gap a goal gap?
        if (Career_GapIsGoal(pGap))
        {
            //if havent got this gaptrick yet
            if (!Career_GotGoalGap(pGap))

                //validate goal by type
                if (!Career_GotGoalType(EGoalType::Gaps)) {

                    if (lastGoalGap != NULL) Career_AwardGoalGap(pGap);

                    pSkater->SetValue(0x3028, (int)pGap);
                }
        }
        else if (Career_GapIsTrick(pGap))
        {
            if (!Career_GotTrickGap(pGap))
                if (!Career_GotGoalType(EGoalType::Trick))
                    pSkater->SetValue(0x3024, (int)pGap);
        }
        else
        {
            printf("\tneither goal nor trick, wtf\n");
        }
    }

    delete pSkater;

    Career_PrintGoals();
}



// level specific item pickup logic
void Career_GetLevelPickup()
{
    SLevel* level = &Levels[*GLevel];

    (*Career_LevelPickupsGot)++;

    int goalIndex = Career_GoalIndex(EGoalType::Pickups);

    if (goalIndex == NS_NULL)
        return;

    if (*Career_LevelPickupsGot == *Career_LevelPickups) {
        Career_GiveGoal(goalIndex);
    }
    else
    {
        sprintf(
            AwardLevelPickupMessage,    //text buffer
            "%d of %d %s",              //message
            *Career_LevelPickupsGot,    //got items
            *Career_LevelPickups,       //out of items
            level->Goals[Career_GoalIndex(EGoalType::Gaps)].stringParam     //level specific item name
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

    return goalIndex == NS_NULL ? false : Career_Got(goalIndex);
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
    printf("decomp Career_NumGoalGapsGot called...\n");

    return Career_CountBits(*Career_GapGoalGotMask);
}

// calculates the amount of obtained trick gaps
int Career_NumTrickGapsGot(void)
{
    printf("decomp Career_NumTrickGapsGot called...\n");

    return Career_CountBits(*Career_GapTrickGotMask);
}

// adds goal gap to mask
void Career_GiveGoalGap(SGapTrick* pGap)
{
    printf("decomp Career_GiveGoalGap called...\n");

    *Career_GapGoalGotMask |= 1 << Career_GapGoalNumber(pGap);
}

// adds trick gap to mask
void Career_GiveTrickGap(SGapTrick* pGap)
{
    printf("decomp Career_GiveTrickGap called...\n");

    *Career_GapTrickGotMask |= 1 << Career_GapTrickNumber(pGap);
}

// checks goal gap mask
bool Career_GotGoalGap(SGapTrick* pGap)
{
    printf("decomp Career_GotGoalGap called...\n");

    return (*Career_GapGoalGotMask & (1 << Career_GapGoalNumber(pGap))) > 0;
}

// checks trick gap mask
bool Career_GotTrickGap(SGapTrick* pGap)
{
    printf("decomp Career_GotTrickGap called...\n");

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
    CBruce* pSkater = new CBruce(GSkater);
    SGoal* pGoal = Levels[*GLevel].Goals;

    //loop through all goals
    for (int goalIndex = 0; goalIndex < NUMGOALS_TH2; goalIndex++)
    {
        //if havent got the goal yet
        if (!Career_Got(goalIndex))        
            //if it is a score goal
            if (pGoal->goalType == EGoalType::Score)
                //our total score is higher than the requirement
                if (pSkater->TotalScore() >= pGoal->intParam)
                {
                    //award the goal
                    Career_GiveGoal(goalIndex);

                    printf("Career_CheckScore(): got %s - %i\r\n", pGoal->goalText, pGoal->intParam);
                }

        //next goal
        pGoal++;
    }

    delete pSkater;
}

#define NUM_SKATERS 20

// clears the game, used by the unlock everything cheat
void Career_ClearGameWithEveryone(void)
{
    for (int i = 0; i < NUM_SKATERS; i++)
        Career_ClearGame(i);
}

// checks if gap is a trick gap (hit 1 gap like nosegrind over the pipe)
bool Career_GapIsTrick(SGapTrick* pGap)
{
    printf("decomp Career_GapIsTrick called...\n");

    return pGap->Type == (short)EGapFlag::TrickGap ? Career_GapActive(pGap) : false;
}

// checks if gap is a goal gap (collect N gaps like roll call rails)
bool Career_GapIsGoal(SGapTrick* pGap)
{
    printf("decomp Career_GapIsGoal called...\n");

    return pGap->Type == (short)EGapFlag::GoalGap ? Career_GapActive(pGap) : false;
}

// checks if gap belongs to this level gap range
bool Career_GapActive(SGapTrick* pGap)
{
    SLevel* level = &Levels[*GLevel];
    int val = pGap->Value % 10000;

    return level->gapFirst <= val && val <= level->gapLast;
}

// finds gap index of current level in the gap table
int Career_GapNumber(SGapTrick* pGap)
{
    printf("decomp Career_GapNumber called\n");

    SGapTrick* cursor = pGaps;
    int gapIndex = 0;

    //loop through the gap table until index hits 0xFFFF
    while (cursor->Value != -1) {

        //if gap belongs to this level
        if (Career_GapActive(cursor)) {
            
            //if match, get gap index
            if (cursor == pGap) 
            {
                printf("\tGap found: %s %i\n", pGap->Name, gapIndex);
                return gapIndex;
            }

            //increment if belongs to the level, but doesnt match
            gapIndex++;
        }

        //next gap
        cursor++;
    }

    printf("\t!!! GapTrick not found: %s\n", pGap->Name);
    
    return 0;
}

// finds trick gap index in a gap table
int Career_GapTrickNumber(SGapTrick* pGap)
{
    printf("decomp Career_GapTrickNumber called...\n");

    SGapTrick* cursor = pGaps;
    int gapIndex = 0;

    //loop through the gap table until index hits 0xFFFF
    while (cursor->Value != -1) {

        //if gap belongs to this level and is trick
        if (Career_GapActive(cursor) && Career_GapIsTrick(pGap)) {

            //if match, get gap index
            if (cursor == pGap)
            {
                printf("\tGap found: %s %i\n", pGap->Name, gapIndex);
                return gapIndex;
            }

            gapIndex++;
        }

        cursor++;
    }

    printf("\t!!! GapTrick not found: %s\n", pGap->Name);

    return 0;
}

// finds goal gap index in a gap table
int Career_GapGoalNumber(SGapTrick* pGap)
{
    SGapTrick* cursor = pGaps;
    int gapIndex = 0;

    //loop through the gap table until index hits 0xFFFF
    while (cursor->Value != -1) {

        //if gap belongs to this level and is trick
        if (Career_GapActive(cursor) && Career_GapIsGoal(pGap)) {

            //if match, get gap index
            if (cursor == pGap)
            {
                printf("Gap found: %s %i\r\n", pGap->Name, gapIndex);
                return gapIndex;
            }

            gapIndex++;
        }

        cursor++;
    }

    printf("!!! GapTrick not found: %s\r\n", pGap->Name);

    return 0;
}

/*
void Career_ToggleCheat(ECheat cheat, bool state)
{
    Career_SetCheat(cheat, Career_CheatState(cheatType) == false, state);
}
*/

// returns the amount needed to unlock the level for message in level selection menu
int Career_LevelNeeds(int levelIndex)
{
    void* charProg = Career_GetCurrentCharacterProgress();

    //if level is already open
    if (Career_LevelOpenCareerMode(levelIndex, charProg))
        return 0;

    //if requires medals be unlocked (minus sign encodes medal requirements)
    if (Levels[levelIndex].medalsToUnlock != 0)
        return -Levels[levelIndex].medalsToUnlock;
    
    //if regular level
    return Levels[levelIndex].cashToUnlock;
}


int* Career_GapBits = (int*)0x00566e9c;

char bufx[256];

void Career_GiveGap(SGapTrick* pGapTrick)
{
    // It stores 3 uints per level in the array, meaning 96 gaps per level total cap
    // first it gets the unlocked gap index in the current level
    // 0x1f is 32 bit mask. >> 5 calculates the exact data index to write the gap bit
    // once found it ORs it with 1 shifted by gapnum lower value
    // array is hardcoded for 11 levels

    int gapNum = Career_GapNumber(pGapTrick);

    int loVal = gapNum & 0x1f;
    int hiVal = gapNum >> 5;

    if ((Career_GapBits[*GLevel * 3 + hiVal] & (1 << loVal)) == 0)
    {
        printf("!!!New gap awarded!!! %s\n", pGapTrick->Name);
        //print mess message here, maybe sound too

        sprintf(bufx, "new gap found %s", pGapTrick->Name);
        DrawMessage(bufx);
        SFX_PlayX(0, 0x2000, 0);

        Career_GapBits[*GLevel * 3 + hiVal] |= (1 << loVal);
    }
}


bool Career_AnyoneGotGap(SGapTrick* pGapTrick)
{
    int gapNum = Career_GapNumber(pGapTrick);

    int loVal = gapNum & 0x1f;
    int hiVal = gapNum >> 5;

    return Career_GapBits[*GLevel * 3 + hiVal] & (1 << loVal);
}


//count total gaps player got so far
int Career_CountGaps()
{
    int numGaps = 0;

    for (int* p = Career_GapBits; p < Career_GapBits + 11 * 3; p++)
        numGaps += Career_CountBits(*p);

    printf("counting gaps: got %i gaps!\n", numGaps);

    return numGaps;
}



int* Career_MoneyPickups = (int*)0x0055ca68;

//checks the 100% level and cash goal
void Career_CheckClear(void)
{
    printf("decomp Career_CheckClear called...\n");

    //if picked up all money in the level (or more?)
    if (Career_CountMoney() >= *Career_MoneyPickups) {

        printf("\tgot all money\n");

        //if it's a competition level
        if (Levels[*GLevel].isCompetition) {

            void* charProg = Career_GetCurrentCharacterProgress();

            //set career progress money flag?
            *(ushort*)((char*)charProg + 0xC + *GLevel * 2) |= 0x8000;

            printf("\t! ! ! in a comp, money flag set ! ! !\n");
        }
        else //if not a comp
        {
            //if level got 9 goals (to exclude secret levels i guess)
            if (Career_NumLevelGoals() == 9)
                //if not awarded already
                if (!Career_GotGoalType(EGoalType::Clear))
                {
                    //award
                    Career_GiveGoalType(EGoalType::Clear);

                    printf("\t! ! ! not in a comp, awarded 100%% goal ! ! !\n");
                }
        }
    }
}


int* Career_TotalGaps = (int*)0x0055ca34;

/// <summary>
/// Checks whether player got all gaps or not. Used to unlock carrera.
/// </summary>
/// <returns></returns>
bool Career_GotAllGaps()
{
    return Career_CountGaps() >= *Career_TotalGaps;
}


int Career_NumLevelGoals()
{
    void* charProg = Career_GetCurrentCharacterProgress();

    return Career_LevelTapes(charProg, *GLevel);
}


/*
/// <summary>
/// Give money to the current player.
/// </summary>
/// <param name="nodeIndex"></param>
/// <param name="amount"></param>
void Career_GiveMoney(int nodeIndex, int amount)
{
    //we dont award money if it's replay mode
    if (!Video_Playing())
    {
        //get current char progress
        void* charProg = Career_GetCurrentCharacterProgress();

        //??? same logic as gap bits
        int moneyNum = Career_MoneyNumber(nodeIndex);

        int moneyHi = (moneyNum >> 5) + GLevel * 2;
        int moneyLo = ((byte)moneyNum & 0x1f);

        //write "picked up node index" flag?
        *(uint*)(&charProg->field_0x44 + moneyHi * 4) |= (1 << moneyLo);

        //award career money
        //i dont have this struct covered yet its from ghidra partial def
        charProg->totalCash += amount;
        charProg->availableCash += amount;

        //check if 100%
        Career_CheckClear();

        //some weird logic that ensures that cash icons message is not displayed 
        //if we already have 100% goals, but also handles it different for comp levels

        //if got all money
        if (Career_CountMoney() >= *Career_MoneyPickups)
        {
            //if not comp level
            if (!&Levels[*GLevel].isCompetition)
                //if already cleared level
                if (Career_GotGoalType(EGoalType::Clear))
                    //do nothing
                    return;

            //display message
            Mess_Message("Cash Icons Cleared", Messprog_Goal, true, 0, 0);
        }
    }
}
*/



//set all gaps state
void Career_SetAllGaps(bool value)
{
    //wipe all gaps bits array with 0
    for (int* p = Career_GapBits; p < Career_GapBits + 11 * 3; p++) *p = value ? -1 : 0;
}

//print all goals
void Career_PrintGoals()
{
    printf("Goal checklist:\n");

    SLevel* level = &Levels[*GLevel];
    SGoal* goal = &(level->Goals[0]);

    for (int i = 0; i < NUMGOALS_TH2; i++)
    {
        printf(
            "%s\t%i\t%i\t%i\t%s\t%i\n",
            goal->goalText,
            goal->goalType,
            goal->cashAward,
            goal->intParam,
            goal->stringParam,
            goal->unk
        );

        goal++;
    }
}
