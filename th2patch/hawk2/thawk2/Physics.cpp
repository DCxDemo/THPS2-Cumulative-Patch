#include "stdafx.h"
#include "types.h"
#include "thawk2\thawk2.h"
#include "_old.h"

namespace Physics {

    void** GTricks = reinterpret_cast<void**>(0x005674f4);

    void** GTricksKeys = reinterpret_cast<void**>(0x005652e8);
    void** GGrindTricksList = reinterpret_cast<void**>(0x005674a0);
    void** GBailsList = reinterpret_cast<void**>(0x00565250);
    void** GTrickTable1 = reinterpret_cast<void**>(0x005656b0);
    void** GTrickTable2 = reinterpret_cast<void**>(0x005656ac);
    void** GAllTricks = reinterpret_cast<void**>(0x005674a4);
    void** GMcSqueebTricks = reinterpret_cast<void**>(0x005674b0);

    
    /// <summary>
    /// Loads TrickDatabase file to memory if it wasn't loaded yet.
    /// </summary>
    /// <returns></returns>
    unsigned int EnsureGTricksLoaded() {

        printf("DECOMP: EnsureGTricksLoaded()\n");

        if (!*GTricks) {

            *GTricks = FileIO::FileIO_OpenLoad("tricks.bin", 1);

            short* ptrs = (short*)*GTricks;

            *GTricksKeys = (void*)((int)*GTricks + ptrs[0]);
            *GGrindTricksList = (void*)((int)*GTricks + ptrs[1]);
            *GBailsList = (void*)((int)*GTricks + ptrs[2]);
            *GTrickTable1 = (void*)((int)*GTricks + ptrs[3]);
            *GTrickTable2 = (void*)((int)*GTricks + ptrs[4]);
            *GAllTricks = (void*)((int)*GTricks + ptrs[5]);
            *GMcSqueebTricks = (void*)((int)*GTricks + ptrs[6]);

            return true;
        }

        return false;
    }

    

    void UnloadGTricks() {

        printf("DECOMP: UnloadGTricks()\n");

        if (*GTricks) {
            Mem_Delete(*GTricks);
            *GTricks = NULL;
            *GAllTricks = NULL;
        }
    }


    void ExtraAnims_AddSkatersAnims() {

        printf("DECOMP: ExtraAnims_AddSkatersAnims()\n");

        bool gTricksLoaded = EnsureGTricksLoaded();

        ExtraAnims_Reset();
        UpdateTrickTables(); //TrickDatabase namespace

        ExtraAnims_AddTrickTable(*GTrickTable1);

        if (*GNumberOfPlayers == 2) {
            ExtraAnims_AddTrickTable(*GTrickTable2);
        }
        
        if (gTricksLoaded) {
            UnloadGTricks();
        }
    }




    // === hook stuff ===

    Hook::Reroute hookList[] = {

        
        { 0x004b8782, EnsureGTricksLoaded },
        { 0x004906d3, EnsureGTricksLoaded },
        { 0x0046a2c3, EnsureGTricksLoaded },
        { 0x00468dfb, EnsureGTricksLoaded },
        

        { 0x004b2046, ExtraAnims_AddSkatersAnims },

        //=========================
        { NULL, NULL }
    };

    Hook::Reroute* pHookList = &hookList[0];
}