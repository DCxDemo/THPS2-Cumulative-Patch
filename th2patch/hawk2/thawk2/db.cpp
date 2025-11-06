#include "stdafx.h"
#include "db.h"

// DB is short for double buffer

namespace Db
{
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

}