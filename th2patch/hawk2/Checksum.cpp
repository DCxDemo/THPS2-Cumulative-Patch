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