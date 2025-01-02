#include "stdafx.h"
#include "types.h"
#include "Utils.h"
#include "Spool.h"
#include "IO\\FileIO.h"

#define PSX_SLOTS 14

void* PSXRegion = (void*)0x0056a088;





int Spool_FindRegion(char* pName)
{
    char* psxSlot = (char*)PSXRegion;
    
    for (int region = 0; region < PSX_SLOTS; region++)
    {
        if (Utils_CompareStrings(pName, psxSlot, NS_NULL) != 0)
            return region;

        //just ++ for psx file slot struct
        psxSlot = psxSlot + 0x44;
    }

    return NS_NULL;
}



int Spool_FreeRegion()
{
    char* psxSlot = (char*)PSXRegion;

    int freeSlot = 0;

    for (int region = 0; region < PSX_SLOTS; region++)
    {
        if (psxSlot == NULL) return region;

        //just ++ for psx file slot struct
        psxSlot = psxSlot + 0x44;
    }

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
        printf("Board texture not found");
        return 0;
    }

    return D3DTEX_TextureCountColors(*(undefined4*)(textureEntry + 0x14));
}*/