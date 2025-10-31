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

// this is wrong somehow?
#define MACRO_CHECK_BIT(VALUE, INDEX) VALUE & (1 << (INDEX & 0x1F))

namespace Career {

    

    void* GSkaterManager = (void*)0x5691e0;

    // this is direct pointer to th2 level gaps
    // but there are 3 gap tables: th2, th1, editor
    // 0056a9b8 points to currently selected gaptable
    SGapTrick* pGaps = (SGapTrick*)0x53E718;

    uint* Career_UnlockFlags = (uint*)0x5672ec;


    uint* Career_GapGoalGotMask = (uint*)0x55c990;
    uint* Career_GapTrickGotMask = (uint*)0x55ca40;

    uint* Career_LevelGoalsGot = (uint*)0x0055c9dc;

    int* Career_LevelPickupsGot = (int*)0x55c9e0;
    int* Career_LevelPickups = (int*)0x0055c750;


    int* Career_MoneyPickups = (int*)0x0055ca68;
    int* Career_TotalGaps = (int*)0x0055ca34;

    int* Career_GapBits = (int*)0x00566e9c;
    int* Career_GoalGaps = (int*)0x55ca38;
    int* Career_TrickGaps = (int*)0x55ca64;

    char* AwardGoalGapMessage = (char*)0x55ca44;
    char* AwardLevelPickupMessage = (char*)0x55c994;
    char* AwardTrickGapMessage = (char*)0x55c9b4;

    SCheat* Cheats = (SCheat*)0x00566fd4;

    Mess::SMessageProg* Messprog_Goal = (Mess::SMessageProg*)0x531d68;



    /// Checks whether skater got a goal on the current level by index.
    bool Career_Got(int goalIndex)
    {
        //sir spams a lot
        //printf("DECOMP Career_Got()\n");

        if (goalIndex < 0 || goalIndex > 9)
        {
            printf("Invalid goal index! %i\n", goalIndex);
            return false;
        }

        void* pCharProg = Career_GetCurrentCharacterProgress();
        short* pGoalsTracker = (short*)((int)(pCharProg)+0x0C);

        return MACRO_CHECK_BIT(pGoalsTracker[*GLevel], goalIndex);
    }

    // Checks if skater just got the goal (checks global current level completion)
    // Used on the end game goal list screen.
    bool Career_JustGot(int goalIndex)
    {
        // sir spams a lot
        //printf("DECOMP Career_JustGot()\n");

        if (goalIndex < 0 || goalIndex > 9)
        {
            printf("Invalid goal index! %i\n", goalIndex);
            return false;
        }

        return MACRO_CHECK_BIT(*Career_LevelGoalsGot, goalIndex);
    }

    // Retrieve number of goals given skater got in the level.
    // Called in main menu, wrapped in NumLevelGoals func
    int Career_LevelTapes(void* pCharProg, int levelIndex)
    {
        printf("DECOMP Career_LevelTapes()... ");

        // null check the charprogress
        if (pCharProg == NULL)
        {
            printf("No character progress!\n");
            return 0;
        }

        // pointer to goals tracker array
        short* pGoalsTracker = (short*)((int)(pCharProg)+0x0C);

        int tapes = 0;

        // foreach goal
        for (int i = 0; i < NUMGOALS_TH2; i++)
        {
            // if bit Nth is set
            if (MACRO_CHECK_BIT(pGoalsTracker[levelIndex], i))
            {
                // we've got a tape
                tapes++;
            }
        }

        printf("%i tapes\n", tapes);

        return tapes;
    }

    // Retrieve number of goals current skater got in the current level.
    int Career_NumLevelGoals()
    {
        return Career_LevelTapes(Career_GetCurrentCharacterProgress(), *GLevel);
    }

    // Career_CountMoney

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
            {
                //if it is a score goal
                if (pGoal->goalType == EGoalType::Score)
                {
                    //our total score is higher than the requirement
                    if (pSkater->TotalScore() >= pGoal->intParam)
                    {
                        //award the goal
                        Career_GiveGoal(goalIndex);

                        printf("Career_CheckScore(): got %s - %i\r\n", pGoal->goalText, pGoal->intParam);
                    }
                }
            }

            //next goal
            pGoal++;
        }

        delete pSkater;
    }

    // Career_GiveGoal

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

    // checks the 100% level and cash goal
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
                //if skater got 9 goals (all but 100%)
                if (Career_NumLevelGoals() == 9)
                {
                    //if 100% not awarded already
                    if (!Career_GotGoalType(EGoalType::Clear))
                    {
                        //award 100%
                        Career_GiveGoalType(EGoalType::Clear);

                        printf("\t! ! ! not in a comp, awarded 100%% goal ! ! !\n");
                    }
                }
            }
        }
    }

    // checks whether current skater got specific goal type
    bool Career_GotGoalType(EGoalType goalType)
    {
        uint goalIndex = Career_GoalIndex(goalType);

        return goalIndex == NS_NULL ? false : Career_Got(goalIndex);
    }

    // Career_GiveMedal

    // checks if gap belongs to this level gap range
    bool Career_GapActive(SGapTrick* pGap)
    {
        SLevel* level = &Levels[*GLevel];
        int val = pGap->Value % 10000;

        return level->gapFirst <= val && val <= level->gapLast;
    }

    // checks if gap is a goal gap (collect N gaps like roll call rails)
    bool Career_GapIsGoal(SGapTrick* pGap)
    {
        printf("decomp Career_GapIsGoal called...\n");

        return pGap->Type == (short)EGapFlag::GoalGap ? Career_GapActive(pGap) : false;
    }

    // checks if gap is a trick gap (hit 1 gap like nosegrind over the pipe)
    bool Career_GapIsTrick(SGapTrick* pGap)
    {
        printf("decomp Career_GapIsTrick called...\n");

        return pGap->Type == (short)EGapFlag::TrickGap ? Career_GapActive(pGap) : false;
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

    // checks if any skater got gap
    bool Career_AnyoneGotGap(SGapTrick* pGapTrick)
    {
        int gapNum = Career_GapNumber(pGapTrick);

        int loVal = gapNum & 0x1f;
        int hiVal = gapNum >> 5;

        return Career_GapBits[*GLevel * 3 + hiVal] & (1 << loVal);
    }

    char bufx[256];

    // awards a new gap
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

            Mess::Mess_Message(AwardGoalGapMessage, Messprog_Goal, 1, 0, 0);
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

            Mess::Mess_Message(AwardTrickGapMessage, Messprog_Goal, 1, 0, 0);
        }
    }

    // Carrer_MoneyNumber

    // Career_GotMoney

    // Career_GiveMoney

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

            Mess::Mess_Message(AwardLevelPickupMessage, Messprog_Goal, 1, 0, 0);
        }
    }

    // Carrer_CountThings

    //count total gaps player got so far
    int Career_CountGaps()
    {
        int numGaps = 0;

        for (int* p = Career_GapBits; p < Career_GapBits + 11 * 3; p++)
            numGaps += Career_CountBits(*p);

        printf("counting gaps: got %i gaps!\n", numGaps);

        return numGaps;
    }

    // Checks whether player got all gaps or not. Used to unlock carrera.
    bool Career_GotAllGaps()
    {
        return Career_CountGaps() >= *Career_TotalGaps;
    }

    // Career_BuyPoint

    // Career_SellPoint

    // Career_GetPointCost

    // Count unlocked competition levels (0-3)
    int Career_NumLevelsWithMedals(void* pProg)
    {
        printf("DECOMP Career_NumLevelsWithMedals()... ");

        int levelsWithMedals = 0;

        short* pGoalsTracker = (short*)((int)(pProg)+0x0C);

        for (int i = 0; i < NUMCAREERLEVELS_TH2; i++)
        {
            if (Levels[i].isCompetition && (pGoalsTracker[i] & 0x1c00) != 0) {
                levelsWithMedals++;
            }
        }

        printf("got %i levels\n", levelsWithMedals);

        return levelsWithMedals;
    }








    // returns the number of unlocked levels
    int Career_HighestOpenLevel(int levelIndex)
    {
        if (*Cheat_LevelSelect)
            return NUMCAREERLEVELS_TH2;

        for (int i = 0; i <= NUMCAREERLEVELS_TH2; i++)
        {
            if (!Career_LevelOpen(i, levelIndex))
                return i;
        }

        return 0;
    }

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

    // Career_LoadingScreen

    // just returns a pointer, easy one
    // Career_GetCharacterProgress(int skaterIndex)



    // Retrieve number of gold medals for given skater
    int Career_CountGoldMedals(void* pProg)
    {
        printf("DECOMP Career_CountGoldMedals()... ");

        int golds = 0;

        short* pGoalsTracker = (short*)((int)(pProg)+0x0C);

        for (int i = 0; i < NUMCAREERLEVELS_TH2; i++)
        {
            if (Levels[i].isCompetition && (pGoalsTracker[i] & 0x0400) != 0) {
                golds++;
            }
        }

        printf("got %i golds\n", golds);

        return golds;
    }


    // Retrieve number of levels with any medal
    // how exactly is this different from numlevelswithmedals?
    int Career_CountMedals(void* pProg)
    {
        printf("DECOMP Career_CountMedals()... ");

        return Career_NumLevelsWithMedals(pProg);
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

#define NUM_SKATERS 20

    // clears the game, used by the unlock everything cheat
    void Career_ClearGameWithEveryone()
    {
        printf("DECOMP Career_ClearGameWithEveryone()\n");

        for (int i = 0; i < NUM_SKATERS; i++)
            Career_ClearGame(i);
    }


    
    void Career_ToggleCheat(ECheat cheat, int skaterIndex)
    {
        Career_SetCheat(cheat, !Career_CheatState(cheat), skaterIndex);
    }
    

    // Retrieve the number of unlocked cheats
    // used in options menu
    int Career_CountUnlockedCheats()
    {
        printf("DECOMP Career_CountUnlockedCheats... ");

        int unlocked = 0;

        for (int i = 0; i <= 16; i++)
        {
            if (Career_CheatUnlocked((ECheat)i)) 
                unlocked++;
        }

        printf("%i cheats\n", unlocked);

        return unlocked;
    }

    // Checks if cheat is unlocked
    bool Career_CheatUnlocked(ECheat cheat)
    {
        return Cheats[(int)cheat].Unlocked;
    }

    // Checks cheat state
    bool Career_CheatState(ECheat cheat)
    {
        return Cheats[(int)cheat].State;
    }



    /*
    // Give money to the current player.
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


    // ****************** NEW FUNCTIONS *************************

    void* Career_GetCurrentCharacterProgress()
    {
        return Career_GetCharacterProgress(GetSkaterID(GSkaterManager));
    }

    void Career_SetAllGaps(bool value)
    {
        //wipe all gaps bits array with 0
        for (int* p = Career_GapBits; p < Career_GapBits + 11 * 3; p++) *p = value ? -1 : 0;
    }

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

    SGoal* GetGoal(int level, int goal)
    {
        SLevel* pLevel = &Levels[level];
        SGoal* pGoal = &pLevel->Goals[goal];

        return pGoal;
    }



    // === hook stuff ===

    Hook::Reroute hookList[] = {
        

        ///all career related hooks

        //{ 0x004147bc,	Career_GapActive },  //gapisgoal
        //{ 0x004147ec,	Career_GapActive },  //gapistrick
        { 0x00414851,   Career_GapActive },  //gapgoalnumber
        { 0x00414877,	Career_GapActive },  //gapgoalnumber
        { 0x00414931,	Career_GapActive },  //gaptricknumber
        { 0x00414957,	Career_GapActive },  //gaptricknumber
        { 0x004149e7,	Career_GapActive },  //gapnumber
        { 0x00414caf,	Career_GapActive },  //awardgap
        { 0x00414dd1,	Career_GapActive },  //awardtrickgap
        { 0x0041545a,	Career_GapActive },  //countthings
        { 0x00482619,	Career_GapActive },  //GapCheckListWindow::update
        { 0x00482688,	Career_GapActive },  //GapCheckListWindow::update

        { 0x004826dd,	Career_AnyoneGotGap }, //in GapCheckListWindow::update

        { 0x0048975b,	Career_CheckScore }, // in DisplayScore

        { 0x00414535,	Career_CheckClear }, //in Career_GiveGoal
        { 0x00415285,	Career_CheckClear }, //in Career_GiveMoney



        { 0x00414964, Career_GapIsTrick }, //gaptricknumber
        { 0x00414d52, Career_GapIsTrick }, //award gap
        { 0x00414e1d, Career_GapIsTrick }, //awardtrickgap
        { 0x00414e31, Career_GapIsTrick }, //awardtrickgap
        { 0x00415487, Career_GapIsTrick }, //countthings


        { 0x48e6ee, Career_AwardGap }, // in CheckForLipGaps
        { 0x49b53e, Career_AwardGap }, // in HandlehysicsState
        { 0x49b5a4, Career_AwardGap }, // in HandlehysicsState
        { 0x4c3955, Career_AwardGap }, // in ExecuteCommandList

        { 0x00414d2d, Career_AwardGoalGap }, //in Career_AwardGap
        { 0x0048c12d, Career_AwardGoalGap },	//in Panel_Land

        { 0x0048c10c, Career_AwardTrickGap },	//in Panel_Land

        { 0x00452a7b, Career_GotAllGaps }, //in Front_NewThing

        { 0x0045c01b, Career_LevelNeeds }, // in GoalScreenElement::setupMessage
        

        // these rely on MACRO_CHECK_BIT and it's wrong
        // TODO: fix macro
        /*
        { 0x004141b8, Career_LevelTapes }, // in carrer numlevelgoals
        { 0x00459cbd, Career_LevelTapes	}, // in level rotate
        
        { 0x0045032a, Career_JustGot }, // all in front_update
        { 0x00450403, Career_JustGot },
        { 0x004504f3, Career_JustGot },

       
        
        //{ 0x004142b2, Career_Got }, //checkscore
        //{ 0x00414666, Career_Got }, //gotgoaltype
        { 0x00415ee4, Career_Got }, //loadingscreen
        { 0x004503f2, Career_Got }, //front_update
        { 0x00450500, Career_Got }, //front_update
        { 0x0045dffd, Career_Got }, //loadingscreen_endloading
        */

        { 0x004159a4, Career_NumLevelsWithMedals },

        { 0x004842e5, Career_CountGoldMedals },
        { 0x0048430b, Career_CountGoldMedals },
        


        { 0x0047fd40, Career_CountUnlockedCheats }, //anycheatsenabled
        { 0x00450ba4, Career_CountUnlockedCheats }, //front_update

        { 0x004ad47b, Career_ClearGameWithEveryone },

        { 0x000484225, Career_CountMedals },

        

        // DECOMPILED ALL CALLS HERE

        //{ 0x00414b16,	Career_GapNumber },	//career_giveGap
        //{ 0x00414b55,	Career_GapNumber },	//carrer_anyonegotgap

        //{ 0x00414cde,	Career_GiveGap },	// in Career_AwardGap

        //{ 0x00415590,	Career_CountGaps },	//in Career_GotAllGaps

        // 00414a85	Career_GapTrickNumber , Career_GotTrickGap
        // 00414ae5	Career_GapTrickNumber, Career_GiveTrickGap
        

        /*

        { 0x414643, Career_GiveGoalType },
        { 0x414bf0, Career_GiveGoalType },
        { 0x414e72, Career_GiveGoalType },
        { 0x48b108, Career_GiveGoalType },
        { 0x48b207, Career_GiveGoalType },
        { 0x4a614c, Career_GiveGoalType },

        { 0x402578, Career_GotGoalType },
        { 0x41462b, Career_GotGoalType },
        { 0x414d10, Career_GotGoalType },
        { 0x414d6d, Career_GotGoalType },
        { 0x414e4c, Career_GotGoalType },
        { 0x414f3a, Career_GotGoalType },
        { 0x4152ba, Career_GotGoalType },
        { 0x469557, Career_GotGoalType },
        { 0x46956a, Career_GotGoalType },
        { 0x46957f, Career_GotGoalType },
        { 0x4b6b6f, Career_GotGoalType },
        { 0x4b6b7f, Career_GotGoalType },

        { 0x4a626b, Career_GetLevelPickup }, //in TakeEffect

        { 0x4166d1, Career_ApplyCheats }, // in Career_PostLoad
        { 0x4531c7, Career_ApplyCheats }, // in FrontEnd2_Main

        { 0x450c82, Career_CheatName },
        { 0x486324,	Career_CheatName },
        { 0x486387,	Career_CheatName },
        { 0x48640c,	Career_CheatName },

        { 0x45c01b, Career_LevelNeeds }, // in GoalScreenElement::setupMessage

        */

        //=========================
        { NULL, NULL }
    };

    Hook::Reroute* pHookList = &hookList[0];
}