#include "stdafx.h"
#include "types.h"
#include "Utils.h"
#include "Spool.h"
#include "IO\\FileIO.h"

#define MAX_PSX_SLOTS 14

void* PSXRegion = (void*)0x0056a088;


// skips all extensions
void* Spool_SkipPackets(void* pPsx)
{
    // read offset to pointers and jump there
    int* p = (int*)((int)pPsx + *(int*)((int)pPsx + 4));

    // read initial packet type
    uint packetType = *p;

    // while not end of list
    while (packetType != NS_NULL) {
        
        // skip packet
        p = (int*)((int)p + p[1] + 8);
        
        // read next packet type
        packetType = *p;
    }

    // get the address
    return p + 1;
}




int Spool_FindRegion(char* pName)
{
    char* pPsxName = (char*)PSXRegion;
    
    for (int region = 0; region < MAX_PSX_SLOTS; region++)
    {
        if (Utils_CompareStrings(pName, pPsxName, NS_NULL) != 0)
            return region;

        //just ++ for psx file slot struct
        pPsxName = pPsxName + 0x44;
    }

    return NS_NULL;
}


// find a free slot in regions list
int Spool_FreeRegion()
{
    // this is a pointer to region struct
    // as we dont have this struct yet, treat first field as string
    // game bascially checks if name is ""
    char* psxSlot = (char*)PSXRegion;

    for (int region = 0; region < MAX_PSX_SLOTS; region++)
    {
        if (psxSlot == NULL) return region;

        //just ++ for psx file slot struct
        psxSlot += 0x44; // sizeof(SRegion)
    }

    printf_s("Spool_FreeRegion: No free PSX regions left!");

    return NS_NULL;
}


/*
void Spool_ClearPSX(char* pName)
{
    int region = Spool_FindRegion(pName);

    if (*(int*)((int)PSXRegion + region * 0x44 + 0xa) != '\0') {
        Spool_ClearRegion(region, 1, 0);
    }
}
*/

void Spool_LoadPSH(char* pName, int param_2, int param_3, int* param_4, int param_5)
{
    char buf[256];

    sprintf(buf, "%s.PSH", pName);
    void* block = FileIO::FileIO_OpenLoad(buf, 1);
    Spool_LoadPSHBuffer(block, pName, param_2, param_3, param_4, param_5);
}

/*
int Spool_CountColors(uint hash) {
    
    throw "Spool_CountColors not implemented!";

    void* textureEntry = Spool_FindTextureEntry(hash);

    if (textureEntry == NULL) {
        printf_s("Board texture not found");
        return 0;
    }

    return D3DTEX_TextureCountColors(*(undefined4*)(textureEntry + 0x14));
}*/

/*
void Spool_Init()
{
    // clear spooler queue
    puVar2 = &SpoolQ;

    do {
        *puVar2 = 0;
        puVar2 = puVar2 + 0x11; // sizeof (queue entry)
    } while ((int)puVar2 < 0x56a789); //end of queue entry
 
    _SpoolPos = 0;
    _FreePos = 0;


    // basically this
    // just gotta implement init region by index now
    // original game inlined init here and no param method just find free region to initialize
    for (int i = 0; i < MAX_PSX_SLOTS; i++)
        Spool_InitRegion(i);


    AnimPackets = 0; // null?

    // null texture checksum table
    // can just use memset (512*4)
    puVar9 = &TextureChecksumHashTable;
    for (i = 512; i != 0; i--) {
        *puVar9 = 0;
        puVar9 = puVar9 + 1;
    }

    EnviroList = NULL;
    OtherEnvIndex = 0;
    EnvRegions = 0xffffffff;
    DAT_00534a84_SomeRegions = 0xffffffff;
}
*/