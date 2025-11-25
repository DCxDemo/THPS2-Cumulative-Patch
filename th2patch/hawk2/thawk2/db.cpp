#include "stdafx.h"
#include "db.h"
#include "mem.h"
#include "Thawk2.h"

#define DEFAULT_PRIM_ALLOC 4096 // 1 << 12

// DB is short for double buffer, not database
namespace Db
{
    int* pPolyBuffer = (int*)0x0055dcf0;

    int* pDb1 = (int*)0x0055dcc4;
    int* pDb2 = (int*)0x0055dd7c;

    int* POLYBUFFERSIZE = (int*)0x0055ddb0;
    int* CurrentOTSize = (int*)0x0055ddb4;

    int Db_OTSize() {

        //n printf_s("Current OT size = %i, current POLYBUFFERSIZE = %i\n", *CurrentOTSize, *POLYBUFFERSIZE);

        return *CurrentOTSize;
    }



    // allocates memory for 3d stuff
    // mostly called in Db_Init
    void Db_AllocateBuffers(int param_1, int param_2, bool extra) {

        *CurrentOTSize = DEFAULT_PRIM_ALLOC * *GNumberOfPlayers + 2; // whats + 2 here?

        // if some extra alloc, add 200. check usage
        if (extra) *CurrentOTSize += 200;

        printf_s("before = %i\n", *POLYBUFFERSIZE);

        *POLYBUFFERSIZE = /*Levels[*GLevel].alloc[*GNumberOfPlayers - 1] + */ 0x12c000; // 1200 * 1024

        printf_s("after = %i\n", *POLYBUFFERSIZE);


        //void* pPolyBuf = (void*)*pPolyBuffer;

       // if (!pPolyBuf) {

            *pPolyBuffer = (int)NsMem::Mem_New(*POLYBUFFERSIZE * 2, 1, 1, 0);

            // this one is seemingly never used?
            int* x = (int*)0x0055dda4;
            *x = (int)*pPolyBuffer + *POLYBUFFERSIZE;

            // allocate first buffer
            *pDb1 = (int)NsMem::Mem_New(*CurrentOTSize * 8 + 2, 1, 1, 0);

            // allocate second buffer
            *pDb2 = (int)NsMem::Mem_New(*CurrentOTSize * 8 + 2, 1, 1, 0);

            // guess unused psx leftovers? save pointer to some data
            //_DAT_0055dcc8 = (int)DAT_0055dcc4_pDbBuffer1 + 0x10;
            //_DAT_0055dd7c = (int)DAT_0055dd78_pDbBuffer2 + 0x10;
       // }
    }


    /*
    void Db_DisplayDraw()
    {
        D3D_BeginScene(_M3d_FadeColour >> 0x10 & 0xff | (_M3d_FadeColour & 0xff) << 0x10 | _M3d_FadeColour & 0xff00ff00, _Db_SkyColor);

        //__ResetGraph(1);
        //__PutDispEnv(pDoubleBuffer + 0x5c);
        //__PutDrawEnv(pDoubleBuffer);

        OTSize = Db_OTSize();

        //__CompactOTagR(*(undefined4*)(pDoubleBuffer + 0x84), OTSize);

        if (Db_Background != 0) {
            __DrawSync(0);
        }

        OTSize2 = Db_OTSize();

        D3DPOLY_DrawOTag(pDoubleBuffer, (int*)(*(int*)(pDoubleBuffer + 0x84) + -8 + OTSize2 * 8));
        D3D_EndSceneAndFlip();
    }
    */


    /*
    void Db_Reset()
    {
        //__DrawSync(0);

        if (pPolyBuffer == NULL) return;

        Mem_Delete(pPolyBuffer);
        Mem_Delete(DAT_0055dcc4_pDbBuffer1);
        Mem_Delete(DAT_0055dd78_pDbBuffer2);
        pPolyBuffer = NULL;
    }
    */



    // === hook stuff ===

    Hook::Reroute hookList[] = {

        { 0x0042fe60, Db_OTSize },
        { 0x0042ff53, Db_OTSize },
        { 0x004300fb, Db_OTSize },
        { 0x0043023a, Db_OTSize },
        { 0x00430262, Db_OTSize },
        { 0x004303b1, Db_OTSize },
        { 0x004304a5, Db_OTSize },
        { 0x0043052e, Db_OTSize },
        { 0x0043055c, Db_OTSize },
        { 0x004675a4, Db_OTSize },

        //{ 0x004302c8, Db_AllocateBuffers },
        //{ 0x00452ff0, Db_AllocateBuffers },

        //=========================
        { NULL, NULL }
    };

    Hook::Reroute* pHookList = &hookList[0];
}