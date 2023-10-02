#include "stdafx.h"

unsigned int checksum(char* a1)
{
    unsigned int result;
    char v2;
    char* i;
    char v4;
    signed int v5;

    result = -1;
    v2 = *a1;
    for (i = a1 + 1; v2; ++i)
    {
        v4 = result ^ v2;
        v5 = 8;
        do
        {
            result = (result >> 31) | 2 * result;
            if (v4 & 1)
                result ^= 0xEDB88320;
            v4 >>= 1;
            --v5;
        } while (v5);
        v2 = *i;
    }
    return result;
}

/*
//some other checksum from demo, check for textures?
unsigned int checksum2(uint param_1, uint param_2, int param_3)

{
    uint uVar1;
    int iVar2;

    uVar1 = 0;
    param_1 = param_1 ^ (param_2 & 0xff) * 0xf26d;
    iVar2 = 0;
    do {
        uVar1 = uVar1 << 1 | uVar1 >> 0x1f;
        if ((param_1 & 1) != 0) {
            uVar1 = uVar1 ^ 0x4517215a;
        }
        iVar2 = iVar2 + 1;
        param_1 = param_1 >> 1;
    } while (iVar2 < 0x20);
    uVar1 = uVar1 & 0xfffffe00 | param_2 & 0xff;
    if (param_3 != 0) {
        uVar1 = uVar1 ^ 0x100;
    }
    return uVar1 ^ 0xaf350f23;
}
*/