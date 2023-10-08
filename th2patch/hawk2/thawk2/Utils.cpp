#include "stdafx.h"
#include "Utils.h"
#include "Globals.h"

bool Utils_CompareStrings(char* pSrc, char* pDst, int num)
{
    char cSrc;
    char cDst;

    if (pSrc == NULL && pDst == NULL) return true;
    if (pDst == NULL) return false;

    do {

        cSrc = *pSrc;
        cDst = *pDst;

        //uppercase first
        if (('@' < cSrc) && (cSrc < '[')) cSrc += ' ';

        //uppercase second
        if (('@' < cDst) && (cDst < '[')) cDst += ' ';

        if (cSrc != cDst) return false;

        pSrc++;
        pDst++;

    } while ((cSrc != 0) && (num--, num != 0));

    if (cSrc == cDst) return true;

    return false;
}

//this func is apparently unused on PC
void Utils_VblankProcessing()
{
    printf("called Utils_VblankProcessing() !!!\n");

    if (*Loading)
        (*LoadingTime)++;
    else
        (*ProcessingTime)++;

    //<...more stuff...>
}