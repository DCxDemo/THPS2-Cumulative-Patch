#include "stdafx.h"
#include "rail.h"
#include "globals.h"
#include "Mem.h"
#include "types.h"
#include "trig.h"

namespace Rail {

    // switches rail on by index
    void Rail_SwitchOn(ushort nodeIndex)
    {
        printf("rail created\n");
        Rail_Active(nodeIndex, true);
    }

    // switches rail off by index
    void Rail_KillRail(ushort nodeIndex)
    {
        printf("rail killed\n");
        Rail_Active(nodeIndex, false);
    }

    // TODO: causes issues in mall and downtown.
    // checks whether passed nodeIndex is rail
    bool Rail_IsRailNode(ushort nodeIndex)
    {
        int* offset = (int*)*Trig_OffsetList;
        short value = *(short*)offset[nodeIndex];

        // read node type (1st short)
        ENodeType nodeType = (ENodeType)value;

        // if it's rail
        if (nodeType == ENodeType::RailDef || nodeType == ENodeType::RailPoint)
        {
            // get flags
            short railFlags = Rail_Flags(nodeIndex);

            // check flags
            if (((railFlags >> 4 & 3) == 0) || (((railFlags >> 4 & 3) & *GNumberOfPlayers) != 0))
            {
                // it's a valid rail node for current num player
                return true;
            }
        }

        // not a valid rail node
        return false;
    }


    // returns number of links
    short Rail_NumLinks(ushort nodeIndex)
    {
        return *Trig::Trig_GetLinksPointer(nodeIndex);
    }
    
    // returns next rail node index
    int Rail_NextNode(ushort nodeIndex)
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
    int Rail_PrevNode(ushort nodeIndex)
    {
        // check node index (maybe refactor this to a separate func and add to other rail funcs as well)
        if (nodeIndex > *NumNodes)
        {
            printf("Wrong node index");
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
                        printf("Rail_PrevNode(): found node %i\n", i);

                        // we have found the previous node
                        return i;
                    }
                }
            }
        }

        printf("Rail_PrevNode(): not found\n");

        return 0;
    }

    // return rail type
    uint Rail_Type(ushort nodeIndex)
    {
        return Rail_Flags(nodeIndex) & 0xf;
    }


    typedef struct RailLookupEntry {
        int nodeIndex;
        int prevIndex;
    } RailLookupEntry;

    // finds node index in the lookup array
    uint GetIndexOfNode(ushort nodeIndex)
    {
        if (nodeIndex == 0) {
            return 0;
        }

        if (*TotalRailNodes > 0) {

            RailLookupEntry* lookup = (RailLookupEntry*)RailNodeLookup;

            // foreach rail node, starting with 1
            for (int i = 1; i < *TotalRailNodes; i++)
            {
                // if lookup nodeIndex matches
                if (lookup[i].nodeIndex == nodeIndex) {

                    printf("GetIndexOfNode(): index of %i is %i", nodeIndex, i);

                    // we have found it, return index
                    return i;
                }
            }
        }

        return 0;
    }


    // additional function, not in the source
    /*
    int Rail_GetNumRails()
    {
        int numRails = 0;

        for (int i = 0; i < *NumNodes; i++)
        {
            if (Rail_IsRailNode(i))
                numRails++;
        }

        *TotalRailNodes = numRails;
        return numRails;
    }
    */

    // a lookup table cache for rail stuff
    void SetupLookup()
    {
        // originally it allocated 2000 fixed, but we won't need more than num nodes anyways
        RailNodeLookup = Mem_New(*NumNodes * sizeof(RailLookupEntry), 1, 1, 0);

        RailLookupEntry* rails = (RailLookupEntry*)RailNodeLookup;

        printf("allocated railnodelookup\n");

        // i guess 1st index is reserved for "no link found" situation, hence initialize it
        uint numRails = 1;

        // if we have any nodes, first pass
        if (*NumNodes > 0)
        {
            // loop over all the nodes
            for (int i = 0; i < *NumNodes; i++)
            {
                // if the node is rail
                if (Rail_IsRailNode(i))
                {
                    if (numRails > 2000)
                        printf("Out of space in rail node lookup table!");

                    // remember the rail index
                    rails[numRails].nodeIndex = i;
                    rails[numRails].prevIndex = 0;

                    // we got another rail
                    numRails++;

                    printf("found rail!\n");
                }
                else
                {
                    printf("not a rail\n");
                }
            }
        }

        printf("pass 1 done\n");


        *TotalRailNodes = numRails;
        rails[0].nodeIndex = 0;
        rails[0].prevIndex = 0;


        // if we got any rails
        if (numRails > 1)
        {
            // loop over rail lookup table entries 
            for (uint i = 1; i < numRails; i++)
            {
                printf("index: %i\n", i);

                // get next node of the rail
                uint nextNode = Rail_NextNode(rails[i].nodeIndex);

                printf("nextnode: %i\n", nextNode);

                // find index of the nex node in the lookup table
                uint lookupIndex = GetIndexOfNode(nextNode);

                printf("lookupIndex: %i\n", lookupIndex);

                // if it's not 0, save to table
                if (lookupIndex != 0)
                {
                    rails[lookupIndex].prevIndex = i;
                    printf("found lookup match!\n");
                }
            }
        }

        printf("pass 2 done\n");
    }




    // === hook stuff ===

    Hook::Reroute hookList[] = {
        
        //doesnt work, what a surprise
        //{ 0x004a7faf, SetupLookup },
        
        /*
        { 0x004a7fd3, Rail_IsRailNode }, // Rail_CreateRails
        { 0x004a7dc1, Rail_IsRailNode }, // SetupLookup
        { 0x004a7bd4, Rail_IsRailNode }, // Rail_PrevNode
        { 0x004a7b33, Rail_IsRailNode }, // Rail_NextNode
        { 0x0043bccc, Rail_IsRailNode }, // LoadRails
        */

        { 0x0043bce3, Rail_NumLinks	}, // LoadRails
        { 0x004a7b05, Rail_NumLinks	}, // Rail_NextNode


        { 0x004a7e7d, GetIndexOfNode }, // SetupLookup

        { 0x0049202c, Rail_Type }, // DoOnRailPhysics
        { 0x004921df, Rail_Type }, // DoOnRailPhysics
        { 0x004a8e5d, Rail_Type }, // Rail_Update
        
        { 0x004c2c2f, Rail_SwitchOn }, // Trig_SendPulseToNode
        { 0x004c4e07, Rail_KillRail }, // SendKillFromNode

        { 0x004a8d95, Rail_PrevNode }, // Rail_Update
        
        { NULL, NULL }
    };

    Hook::Reroute* pHookList = &hookList[0];
}