#include "stdafx.h"
#include "FileIO.h"

void* FileIO_OpenLoad_Pkr(char* filename, bool heap, Pkr2* pkr)
{
    //kek
    for (char* i = filename; *i != 0; i++)
    {
        *i = toupper(*i);
    }

    if (pkr != NULL)
    {
        for (int i = 0; i < pkr->Header->numFiles; i++)
        {
            if (strcmp(filename, pkr->Files[i].Name) == 0)
            {
                printf("%s found in PKR!!!\n", filename);
                return pkr->Files[i].pData;
            }
        }
    }

    printf("%s not found in PKR, pass to the original func!!!\n", filename);
    return FileIO_OpenLoad(filename, heap);
}