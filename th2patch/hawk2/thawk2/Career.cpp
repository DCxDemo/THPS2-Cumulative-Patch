#include "stdafx.h"

#include "globals.h"
#include "career.h"
#include "mess.h"

void Career_AwardGoalGap(void* goalGap)
{
    Career_GiveGoalGap(goalGap);
        
    //if goal gaps matches the target
    if (Career_NumGoalGapsGot() == *Career_GapGoalGotMask) 
    {
        //award goal
        Career_GiveGoalType(eGoalType::GoalGap);
    }
    else
    {
        char** goalText = (char**)(0x5390b8 + *GLevel * 0x1ac + Career_GoalIndex(eGoalType::GoalGap) * 0x18);

        //print "X out of X items" message
        sprintf(
            AwardGoalGapMessage, 
            "%d of %d %s",
            Career_NumGoalGapsGot(),
            *Career_GapGoalGotMask,
            &(*goalText)[0]
        );

        printf(AwardGoalGapMessage);

        Mess_Message(AwardGoalGapMessage, Messprog_Goal, 1, 0, 0);
    }




}

