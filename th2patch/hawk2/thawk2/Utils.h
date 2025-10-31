#pragma once
#include "types.h"

//temporary, move to vectors

typedef struct SVector3i {
    int X;
    int Y;
    int Z;
} SVector3i;

typedef struct SVector3s {
    short X;
    short Y;
    short Z;
} SVector3s;


typedef void(*Utils_StartFade_t)();
typedef void(*Utils_StopFade_t)();
//typedef void(*Utils_VblankProcessing_t)();
typedef void(*MyVSync_t)();
typedef void(*Pause_t)(int frames);
typedef void(*Utils_InitialRand_t)();
typedef void(*Rnd_t)();
typedef void(*Utils_RotateY_t)();
typedef void(*FUN_004c6660_t)();
//typedef void(*Utils_CalcUnit_t)();
//typedef void(*Utils_GetVecFromMagDir_t)();
//typedef void(*Utils_Dist_t)();
typedef void(*Utils_XZDist_t)();
typedef void(*Utils_CrapDist_t)();
typedef void(*FUN_004c6930_t)();
typedef void(*Utils_CalcAim_t)();
typedef void(*Utils_TurnTowards_t)();
typedef void(*FUN_004c6b60_t)();
typedef void(*FUN_004c6c30_t)();
typedef void(*FUN_004c6dd0_t)();
typedef void(*FUN_004c6e60_t)();
typedef void(*FUN_004c6ef0_t)();
typedef void(*Utils_ClearExplosionStack_t)();
typedef void(*FUN_004c6f20_t)();
typedef void(*FUN_004c7000_t)();
typedef void(*FUN_004c70b0_t)();
typedef void(*FUN_004c7160_t)();
//typedef void(*Utils_CompareStrings_t)();
typedef void(*Utils_CopyString__unused_t)();
typedef void(*FUN_004c7230_t)();
typedef void(*Utils_ArcCos__apparently_t)();
typedef void(*Utils_LineOfSight_t)();
typedef void(*Utils_GetGroundHeight_t)();
typedef int(*Utils_KillObjectsInBox_t)(SVector3i* min, SVector3i* max, void* pList, bool useDie);
//typedef void(*Utils_KillEverythingInBox_t)();
typedef void(*Utils_SetVisibilityInBox_t)(void*, void*, char, char);
typedef void(*FUN_004c7880_objectIsInEnviroList__unused_t)();
typedef void(*FUN_004c78b0_t)();
typedef void(*Utils_CalculateSpatialAttenuation_t)();
//typedef void(*Utils_Pulse_t)();
//typedef void(*Utils_LimitRange_t)();

static const Utils_StartFade_t Utils_StartFade = (Utils_StartFade_t)0x004c6170;
static const Utils_StopFade_t Utils_StopFade = (Utils_StopFade_t)0x004c6190;
//static const Utils_VblankProcessing_t Utils_VblankProcessing = (Utils_VblankProcessing_t)0x004c61a0;
void Utils_VblankProcessing();
static const MyVSync_t MyVSync = (MyVSync_t)0x004c6510;
static const Pause_t Pause = (Pause_t)0x004c6560;
static const Utils_InitialRand_t Utils_InitialRand = (Utils_InitialRand_t)0x004c6580;
static const Rnd_t Rnd = (Rnd_t)0x004c65a0;
static const Utils_RotateY_t Utils_RotateY = (Utils_RotateY_t)0x004c65f0;
static const FUN_004c6660_t FUN_004c6660 = (FUN_004c6660_t)0x004c6660;
//static const Utils_CalcUnit_t Utils_CalcUnit = (Utils_CalcUnit_t)0x004c66d0;
SVector3i* Utils_CalcUnit(SVector3i* unit, SVector3i* vec);
//static const Utils_GetVecFromMagDir_t Utils_GetVecFromMagDir = (Utils_GetVecFromMagDir_t)0x004c6760;
void Utils_GetVecFromMagDir(SVector3i* angles, int magnitude, SVector3s* velocity);
//static const Utils_Dist_t Utils_Dist = (Utils_Dist_t)0x004c67f0;
uint Utils_Dist(SVector3i* a, SVector3i* b);
static const Utils_XZDist_t Utils_XZDist = (Utils_XZDist_t)0x004c6840;
static const Utils_CrapDist_t Utils_CrapDist = (Utils_CrapDist_t)0x004c6880;
static const FUN_004c6930_t FUN_004c6930 = (FUN_004c6930_t)0x004c6930;
static const Utils_CalcAim_t Utils_CalcAim = (Utils_CalcAim_t)0x004c69d0;
static const Utils_TurnTowards_t Utils_TurnTowards = (Utils_TurnTowards_t)0x004c6ae0;
static const FUN_004c6b60_t FUN_004c6b60 = (FUN_004c6b60_t)0x004c6b60;
static const FUN_004c6c30_t FUN_004c6c30 = (FUN_004c6c30_t)0x004c6c30;
static const FUN_004c6dd0_t FUN_004c6dd0 = (FUN_004c6dd0_t)0x004c6dd0;
static const FUN_004c6e60_t FUN_004c6e60 = (FUN_004c6e60_t)0x004c6e60;
static const FUN_004c6ef0_t FUN_004c6ef0 = (FUN_004c6ef0_t)0x004c6ef0;
static const Utils_ClearExplosionStack_t Utils_ClearExplosionStack = (Utils_ClearExplosionStack_t)0x004c6f10;
static const FUN_004c6f20_t FUN_004c6f20 = (FUN_004c6f20_t)0x004c6f20;
static const FUN_004c7000_t FUN_004c7000 = (FUN_004c7000_t)0x004c7000;
static const FUN_004c70b0_t FUN_004c70b0 = (FUN_004c70b0_t)0x004c70b0;
static const FUN_004c7160_t FUN_004c7160 = (FUN_004c7160_t)0x004c7160;
//static const Utils_CompareStrings_t Utils_CompareStrings = (Utils_CompareStrings_t)0x004c71b0;
bool Utils_CompareStrings(char* pSrc, char* pDst, int num);
static const Utils_CopyString__unused_t Utils_CopyString__unused = (Utils_CopyString__unused_t)0x004c7210;
static const FUN_004c7230_t FUN_004c7230 = (FUN_004c7230_t)0x004c7230;
static const Utils_ArcCos__apparently_t Utils_ArcCos__apparently = (Utils_ArcCos__apparently_t)0x004c7300;
static const Utils_LineOfSight_t Utils_LineOfSight = (Utils_LineOfSight_t)0x004c7320;
static const Utils_GetGroundHeight_t Utils_GetGroundHeight = (Utils_GetGroundHeight_t)0x004c73a0;
static const Utils_KillObjectsInBox_t Utils_KillObjectsInBox = (Utils_KillObjectsInBox_t)0x004c7440;
//static const Utils_KillEverythingInBox_t Utils_KillEverythingInBox = (Utils_KillEverythingInBox_t)0x004c74d0;
void Utils_KillEverythingInBox(SVector3i* min, SVector3i* max);
static const Utils_SetVisibilityInBox_t Utils_SetVisibilityInBox = (Utils_SetVisibilityInBox_t)0x004c7530;
static const FUN_004c7880_objectIsInEnviroList__unused_t FUN_004c7880_objectIsInEnviroList__unused = (FUN_004c7880_objectIsInEnviroList__unused_t)0x004c7880;
static const FUN_004c78b0_t FUN_004c78b0 = (FUN_004c78b0_t)0x004c78b0;
static const Utils_CalculateSpatialAttenuation_t Utils_CalculateSpatialAttenuation = (Utils_CalculateSpatialAttenuation_t)0x004c78f0;
//static const Utils_Pulse_t Utils_Pulse = (Utils_Pulse_t)0x004c7af0;
int Utils_Pulse(int time, int period, int amplitude);
//static const Utils_LimitRange_t Utils_LimitRange = (Utils_LimitRange_t)0x004c7b30;
void Utils_LimitRange(int* value, int min, int max);






//degree here is in 0-4096 range, masked by 0xFFF is outside the range
uint Sine(uint deg);
uint Cosine(uint deg);

uint ScreenScaledSine(uint deg);
uint ScreenScaledCosine(uint deg);


/*

known Utils namespace function names, lots of unused stuff from apocalypse it seems

Utils_StartFade
Utils_StopFade
Utils_VblankProcessing
MyVSync
Pause
Utils_InitialRand
Rnd
Utils_RotateY
    Utils_LessAccurateRotateY // here????
Utils_CalcUnit
Utils_GetVecFromMagDir
Utils_Dist
Utils_XZDist
Utils_CrapDist
?
Utils_CalcAim
Utils_TurnTowards
?
?
?
?
? used!
Utils_ClearExplosionStack
?
?
Utils_SineSquaredInterpolate //
Utils_SineSquaredInterpolate //overload
Utils_CompareStrings
Utils_CopyString
? used!
Utils_ArcCos
Utils_LineOfSight
Utils_GetGroundHeight
Utils_KillObjectsInBox
Utils_KillEverythingInBox
Utils_SetVisibilityInBox
Utils_IsInEnviro
?
Utils_CalculateSpatialAttenuation
Utils_Pulse
Utils_LimitRange




Utils_CanSee
Utils_FadeTrails
Utils_CheckObjectCollision
Utils_InBetween
Utils_ShuffleArray
Utils_AnglesFromMatrix
Utils_SendExplosionEvent
Utils_GenerateCRC
Utils_SendDamage
Utils_SimpleCollision
Utils_AutoAim
Utils_SelectTarget
Utils_WobblePartDisps
Utils_WobblePartAngles
Utils_GetCos

*/