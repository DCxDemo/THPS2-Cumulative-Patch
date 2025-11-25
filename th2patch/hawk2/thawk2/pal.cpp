#include "stdafx.h"
#include "thawk2\Mem.h"
#include "thawk2\pal.h"
#include "types.h"
#include "..\patch\hook.h"
#include "thawk2\_old.h"

namespace Pal {

    int* TotalPaletteUsage = (int*)0x00568364;
    SPalette* pPaletteList = (SPalette*)0x00567f50;

    int* Pal16Max = (int*)0x00532dac;
    int* Pal256Max = (int*)0x00532db0;

    bool* Pal16Usage = (bool*)0x00568054;
    bool* Pal256Usage = (bool*)0x00567f54;

    // creates a new palette entry
    SPalette* NewPaletteEntry(uint Checksum) {

        printf_s("DECOMP Pal_CreateNew(): %i\n", Checksum);

        // allocate new palette
        SPalette* pPal = (SPalette*)NsMem::Mem_New(0x18, 0, 1, 0);

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
    void RemovePaletteEntry(SPalette* pPal)
    {
        printf_s("DECOMP Pal_Free()\n");

        if (pPal->pPrev != NULL)
            pPal->pPrev->pNext = pPal->pNext;

        if (pPal->pNext != NULL)
            pPal->pNext->pPrev = pPal->pPrev;

        if (pPal == pPaletteList)
            pPaletteList = pPal->pPrev;

        NsMem::Mem_Delete(pPal);

        *TotalPaletteUsage -= 0x1c;
    }

    // iterates over the palette list until checksum is found.
    SPalette* Pal_FindPaletteEntry(uint Checksum) {

        printf_s("DECOMP Pal_FindPaletteEntry(): %i\n", Checksum);

        if (pPaletteList == NULL) return NULL;

        SPalette* pPal = pPaletteList;

        do {
            // got a match?
            if (pPal->Checksum == Checksum)
                return pPal;

            // go to the next palette
            pPal = pPal->pPrev;

        } while (pPal != NULL);

        return pPal;
    }

    int GetFree16Slot()
    {
        for (int i = 0; i < *Pal16Max; i++)
            if (Pal16Usage[i])
            {
                Pal16Usage[i] = false;
                return i;
            }

        printf_s("Ran out of Pal16 slots!\n");

        Pal16Usage[*Pal16Max - 1] = false;

        return *Pal16Max - 1;
    }

    int GetFree256Slot()
    {
        for (int i = 0; i < *Pal256Max; i++)
            if (Pal256Usage[i])
            {
                Pal256Usage[i] = false;
                return i;
            }

        printf_s("Ran out of Pal256 slots!\n");

        Pal16Usage[*Pal256Max - 1] = false;

        return *Pal256Max - 1;
    }



    void Pal_RemoveUnusedPalettes()
    {
        if (pPaletteList == NULL) return;

        SPalette* pPal = pPaletteList;
        SPalette* pPrev = pPal->pPrev;

        do {
            if (pPal->Usage == 0) {

                D3DTEX_FreePaletteEntry(pPal->pD3DPalette, 0);

                pPal->pD3DPalette = NULL;

                if (pPal->flags & 1)
                    Pal16Usage[pPal->slot] = true;

                if (pPal->flags & 2)
                    Pal256Usage[pPal->slot] = true;

                RemovePaletteEntry(pPal);
            }

            pPal = pPrev;

        } while (pPrev != NULL);
    }


    // === hook stuff ===

    Hook::Reroute hookList[] = {

        { 0x004880dc,   NewPaletteEntry },

        { 0x004b0143,   Pal_FindPaletteEntry },
        { 0x004b01e8,   Pal_FindPaletteEntry },
        { 0x004b05be,   Pal_FindPaletteEntry },

        { 0x00487d62,   RemovePaletteEntry },

        { 0x00449d05,   GetFree16Slot },
        { 0x0048824b,   GetFree16Slot },
        { 0x00488034,   GetFree256Slot },
        { 0x004882f3,   GetFree256Slot },
        { 0x004ad751,   GetFree256Slot },



        //=========================
        { NULL, NULL }
    };

    Hook::Reroute* pHookList = &hookList[0];
}