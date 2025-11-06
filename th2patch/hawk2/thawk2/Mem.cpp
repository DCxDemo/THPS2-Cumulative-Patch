#include "stdafx.h"
#include "Mem.h"

namespace NsMem
{
    /// <summary>
    /// Basically memcpy wrapper.
    /// Original game implements simple for loop and copies it byte by byte.
    /// </summary>
    /// <param name="_Src">Source address</param>
    /// <param name="_Dst">Destination address</param>
    /// <param name="_Size">Buffer length</param>
    void Mem_CopyBytes(void* _Dst, void* _Src, int _Size)
    {
        printf_s("copying from %X to %X, %i bytes... ", (int)_Src, (int)_Dst, _Size);

        if (_Size > 0)
            memcpy(_Dst, _Src, _Size);

        printf_s("done!\n");
    }

    void Mem_Delete(void* pData)
    {
        printf_s("mem_delete! %X", (int)pData);

        Mem_DeleteX(
            (void*) (((int*)pData)+1 )
            );
    }
}