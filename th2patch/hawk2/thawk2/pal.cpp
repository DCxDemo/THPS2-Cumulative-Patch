#include "stdafx.h"
#include "thawk2/Mem.h"
#include "thawk2/pal.h"
#include "types.h"
#include "..\patch\hook.h"

namespace Pal {

    int* TotalPaletteUsage = (int*)0x00568364;
    S_Pal* pPaletteList = (S_Pal*)0x00567f50;

    // creates a new palette entry
    S_Pal* NewPaletteEntry(uint Checksum) {

        printf("DECOMP Pal_CreateNew(): %i\n", Checksum);

        // allocate new palette
        S_Pal* pPal = (S_Pal*)Mem_New(0x18, 0, 1, 0);

        // increase palette memory usage counter
        *TotalPaletteUsage += 0x1c; //why not 0x18?

        // update links
        pPal->pPrev = pPaletteList;
        pPal->pNext = NULL;

        // update first
        pPaletteList = pPal;

        // if list wasnt NULL, update previous first palette
        if (pPal->pPrev != NULL) {
            pPal->pPrev->pNext = pPal;
        }

        // was uploaded to VRAM
        pPal->InVRAM = false;

        // set checksum
        pPal->Checksum = Checksum;

        // usage?
        pPal->Usage = 0;

        return pPal;
    }

    // removes a palette
    void RemovePaletteEntry(S_Pal* pPal)
    {
        printf("DECOMP Pal_Free()\n");

        if (pPal->pPrev != NULL)
            pPal->pPrev->pNext = pPal->pNext;

        if (pPal->pNext != NULL)
            pPal->pNext->pPrev = pPal->pPrev;

        if (pPal == pPaletteList)
            pPaletteList = pPal->pPrev;

        Mem_Delete(pPal);

        *TotalPaletteUsage -= 0x1c;
    }

    // iterates over the palette list until checksum is found.
    S_Pal* Pal_FindPaletteEntry(uint Checksum) {

        printf("DECOMP Pal_FindPaletteEntry(): %i\n", Checksum);

        S_Pal* pPal = pPaletteList;

        // if list is not null
        if (pPaletteList != NULL) {
            do {

                // maybe we found our palette checksum?
                if (pPal->Checksum == Checksum)
                    return pPal;

                // go to the next palette
                pPal = pPal->pPrev;

            } while (pPal != NULL);
        }

        return pPal;
    }



    // === hook stuff ===

    Hook::Reroute hookList[] = {

        { 0x004880dc,   NewPaletteEntry },

        { 0x004b0143,   Pal_FindPaletteEntry },
        { 0x004b01e8,   Pal_FindPaletteEntry },
        { 0x004b05be,   Pal_FindPaletteEntry },

        { 0x00487d62,   RemovePaletteEntry },

        //=========================
        { NULL, NULL }
    };

    Hook::Reroute* pHookList = &hookList[0];
}