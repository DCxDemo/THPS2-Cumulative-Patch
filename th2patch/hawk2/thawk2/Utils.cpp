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


void Utils_GetVecFromMagDir(SVector3i* angles, int magnitude, SVector3s* velocity)
{
    //calculate trig stuff
    short velSinX = Sine((ushort)velocity->X & 0xfff);
    short velCosX = Cosine((ushort)velocity->X & 0xfff);
    short velSinY = Sine((ushort)velocity->Y & 0xfff);
    short velCosY = Cosine((ushort)velocity->Y & 0xfff);

    //update angles based on velocity and magnitude
    angles->X = -1 * ((velCosX * magnitude) >> 12) * velSinY;
    angles->Y = velSinX * magnitude;
    angles->Z = -1 * ((velCosX * magnitude) >> 12) * velCosY;
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


/// <summary>
/// Limits passed int* value within the min/max range. 
/// </summary>
/// <param name="value">Pointer to int value</param>
/// <param name="min">Lowest range value</param>
/// <param name="max">Highest range value</param>
void Utils_LimitRange(int* value, int min, int max)
{
    //particularly used for fatten
    printf("decomp Utils_LimitRange... v=%i min=%i max=%i\n", *value, min, max);

    if (*value < min) *value = min;
    if (*value > max) *value = max;
}



/// <summary>
/// Calculates unit vector (basically, normalize).
/// </summary>
/// <param name="unit">Target unit vector</param>
/// <param name="vec">Source vector</param>
SVector3i* Utils_CalcUnit(SVector3i* unit, SVector3i* vec)
{
    //calculate vector magnitude
    float magnitude = sqrt(
        pow(vec->X >> 12, 2) +
        pow(vec->Y >> 12, 2) +
        pow(vec->Z >> 12, 2)
    );

    if (magnitude == 0.0f) {

        //process zero edge case 
        unit->X = 0;
        unit->Y = 0;
        unit->Z = 0;
    }
    else
    {
        //otherwise, calculate unit
        unit->X = vec->X / magnitude;
        unit->Y = vec->Y / magnitude;
        unit->Z = vec->Z / magnitude;
    }

    return unit;
}






#define MATH_2PI 6.2831853f
#define FRAC_BITS 12

uint Sine(uint deg)
{
    return sin( ((deg & 0xFFF) / 4096.0) * MATH_2PI ) * 4096.0;
}

uint Cosine(uint deg)
{
    return cos( ((deg & 0xFFF) / 4096.0) * MATH_2PI ) * 4096.0;
}

// the way thirteenag fixes it, makes little sense to me atm
// check rotatesprite::draw function to figure it out

uint ScreenScaledSine(uint deg)
{
    return Sine(deg) / (*ScreenHeight / 480.0);
}

uint ScreenScaledCosine(uint deg)
{
    return Cosine(deg) / (*ScreenHeight / 480.0);
}