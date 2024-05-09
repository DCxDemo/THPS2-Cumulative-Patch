#include "stdafx.h"
#include "rail.h"
#include "globals.h"

// this should be whereever trigger file handling is located
enum class ETriggerNodeType : int {
	RailPoint = 0x0A,
	RailNode = 0x0B,
};

// switches rail on by index
void Rail_SwitchOn(int nodeIndex)
{
	Rail_Active(nodeIndex, true);
}

// switches rail off by index
void Rail_KillRail(int nodeIndex)
{
	Rail_Active(nodeIndex, false);
}

// checks whether passed nodeIndex is rail
bool Rail_IsRailNode(int nodeIndex)
{
    // get pointer to the node
    short* pNode = (short*)Trig_OffsetList[nodeIndex];

    // read node type (1st short)
    ETriggerNodeType nodeType = (ETriggerNodeType)pNode[0];

    // if it's rail
    if (nodeType == ETriggerNodeType::RailNode || nodeType == ETriggerNodeType::RailPoint) 
    {
        // get flags
        short railFlags = Rail_Flags(nodeIndex);

        // check flags
        if (((railFlags >> 4 & 3) == 0) || (((railFlags >> 4 & 3) & *GNumberOfPlayers) != 0)) {

            // it's a valid rail node for current num player
            return true;
        }
    }

    // not a valid rail node
    return false;
}

// returns number of links
int Rail_NumLinks(int nodeIndex)
{
    // check node index (maybe refactor this to a separate func and add to other rail funcs as well)
    if (nodeIndex >= *NumNodes)
    {
        printf("Wrong node index");
        return 0;
    }

    // the very 1st short is number of links
    return Trig_GetLinksPointer(nodeIndex)[0];
}

// returns next rail node index
int Rail_NextNode(int nodeIndex)
{
    // get number of links
    int numLinks = Rail_NumLinks(nodeIndex);

    // return zero early
    if (numLinks == 0) return 0;

    int linkIndex = 0;
    int result = 0;

    // foreach link in the list
    for (int i = 0; i < numLinks; i++)
    {
        // get link
        linkIndex = Rail_GetLink(nodeIndex, i);

        // if link is rail
        if (Rail_IsRailNode(linkIndex))
        {
            // and some flag is set (probably next node flag, lol)
            if ((Rail_Flags(linkIndex) & 0x8000) == 0)
            {
                // set this link as result
                result = linkIndex;
            }
        }
    }

    return result;
}

// returns previous rail node index
int Rail_PrevNode(int nodeIndex)
{
    // check node index (maybe refactor this to a separate func and add to other rail funcs as well)
    if (nodeIndex >= *NumNodes)
    {
        printf("Wrong node index");
        return 0;
    }

    // if we have more than one node on the list (which is always true in the final game anyways...)
    if (*NumNodes > 1) {

        // starting from node number 1
        for (int i = 1; i < *NumNodes; i++)
        {
            // if node is rail
            if (Rail_IsRailNode(i))
            {
                // if next node equals the target node
                if (Rail_NextNode(i) == nodeIndex)
                {
                    // we have found the previous node
                    return i;
                }
            }
        }
    }

    return 0;
}

// return rail type
uint Rail_Type(int nodeIndex)
{
    return Rail_Flags(nodeIndex) & 0xf;
}