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
    printf_s("called Utils_VblankProcessing() !!!\n");

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
    printf_s("decomp Utils_LimitRange... v=%i min=%i max=%i\n", *value, min, max);

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


/// <summary>
/// Calculates distance between 2 points.
/// </summary>
/// <param name="vec1"></param>
/// <param name="vec2"></param>
/// <returns></returns>
uint Utils_Dist(SVector3i* a, SVector3i* b)
{
    SVector3i t = {
        (a->X - b->X) >> 12,
        (a->Y - b->Y) >> 12,
        (a->Z - b->Z) >> 12
    };

    return (uint)sqrt(t.X * t.X + t.Y * t.Y + t.Z * t.Z);
}


/// <summary>
/// Supposedly kills all objects in bounding box.
/// </summary>
/// <param name="min">BB min point</param>
/// <param name="max">BB max point</param>
void Utils_KillEverythingInBox(SVector3i* min, SVector3i* max)
{
    //find this func

    printf_s("decomp Utils_KillEverythingInBox!\n");

    Utils_KillObjectsInBox(min, max, BaddyList, true);
    Utils_KillObjectsInBox(min, max, EnvironmentalObjectList, true);
    Utils_KillObjectsInBox(min, max, PowerUpList, true);
    Utils_KillObjectsInBox(min, max, SuspendedList, false);

    //originally it returns sum of the above, but im not sure if its ever used
}


/* 
// requires CBody to be decompiled first
int Utils_KillObjectsInBox(CVector3* min, CVector3* max, CBody* pList, char useDie)
{
    if (pList == NULL)  return 0;

    int numKilled = 0;
    CBody* pCurr = pList;
    CBody* pNext = NULL;

    do {
        // remember next item
        pNext = pCurr->nextItem;

        // check whether it's dead
        if (!pCurr->IsDead()) {

            int x = pCurr->pos.X;
            int y = pCurr->pos.Y;
            int z = pCurr->pos.Z;

            // if in bounding box between min and max
            if (
                    min->X <= x && x <= max->X && 
                    min->Y <= y && y <= max->Y &&
                    min->Z <= z && z <= max->Z
                )
            {
                // if should just get dead status
                if (useDie) {
                    pCurr->Die();
                } else {
                    // else remove physically
                    delete pCurr;
                }

                // count
                numKilled++;
            }
        }

        pCurr = pNext;

    } while (pNext != NULL);

    return numKilled;
}
*/




//this is called in front_update for level unlocked message. used to calculate text zoom
int Utils_Pulse(int time, int period, int amplitude)
{
    if ((time < period) && (time > -1)) {

        int iVar1 = period / 2;

        if (time < iVar1) return (time * amplitude) / iVar1;

        return ((period - time) * amplitude) / iVar1;
    }

    return 0;
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

int Utils_CountBits(uint value)
{
    int numBits = 0;

    if (value > 0)
        do {
            if (value & 1) numBits++;
            value >>= 1;
        } while (value > 0);

    return numBits;
}