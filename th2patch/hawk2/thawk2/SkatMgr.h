#pragma once

//this = SkaterManager
//wonder if cdecl methods are static or global

typedef void(__thiscall * EditThisSkater_t)(void* _this, int param_1);
typedef int(__thiscall * GetSkaterID_t)(void* _this);
typedef int(__thiscall * GetCostumeID_t)(void* _this);
typedef int(__thiscall * GetCustomSkaterID_t)(void* _this);
typedef int(__thiscall * GetSkaterID2_t)(void* _this, int param_1);
typedef int(__thiscall * GetCostumeID2_t)(void* _this, int param_1);
typedef void(__thiscall * SetSkaterID_t)(void* _this, int param_1);
typedef void(__thiscall * SetSkaterID2_t)(void* _this, int param_1, int param_2);
typedef void(*num_costumes_t)(int param_1);
typedef void(__thiscall * SetCostumeID_t)(void* _this, int param_1, int param_2, bool param_3);
typedef void(__thiscall * SetCustomSkaterID_t)(void* _this, int param_1, int param_2);
typedef int(__thiscall * GetPreferredCostume_t)(void* _this, int param_1);
typedef void(__thiscall * PrintLoadBuffer_t)(); //empty func
typedef void(__thiscall * ClearLoadBuffer_t)(void* _this);
typedef void(__thiscall * ClearLoadBufferSlot_t)(void* _this);
typedef void(__thiscall * SetLoadBuffer_t)(void* _this, int param_1);
typedef void(__thiscall * GetSkaterName_t)(void* _this, int param_1, char* outName); //does not return, writes to outName
typedef char*(__thiscall * GetPortraitName_t)(void* _this, int param_1);
typedef int(__thiscall * UsesLoadBuffer_t)(void* _this, int param_1);
typedef void(__thiscall * SwapLoadBuffer_t)(void* _this, int param_1);
typedef void*(__thiscall * GetTrickConfig_t)(void* _this, int param_1);
typedef bool(__thiscall * IsRegularStance_t)(void* _this, int param_1);
typedef char*(*GetPSXName_t)(int param_1, int param_2);
typedef int(*GetCustomSkaterSlotIndex_t)(int param_1);
typedef void(*PlayerSelect_ClearState_t)();
typedef int(*Get_Selected_Skater_t)(int param_1);
typedef void(*Set_Selected_Skater_t)(int param_1, int param_2);
typedef int(*GetCustomSkaterIndex_t)(int param_1);
typedef bool(*IsInitialCustomSkaterRevision_t)(int param_1);
typedef char*(*FrontEnd2_GetSkaterName_t)(int param_1);

static const EditThisSkater_t EditThisSkater = (EditThisSkater_t)0x4ae4a0;
static const GetSkaterID_t GetSkaterID = (GetSkaterID_t)0x4ae510;
static const GetCostumeID_t GetCostumeID = (GetCostumeID_t)0x4ae520;
static const GetCustomSkaterID_t GetCustomSkaterID = (GetCustomSkaterID_t)0x4ae530;
static const GetSkaterID2_t GetSkaterID2 = (GetSkaterID2_t)0x4ae540;
static const GetCostumeID2_t GetCostumeID2 = (GetCostumeID2_t)0x4ae5b0;
static const SetSkaterID_t SetSkaterID = (SetSkaterID_t)0x4ae620;
static const SetSkaterID_t SetSkaterID2 = (SetSkaterID_t)0x4ae740;
static const num_costumes_t num_costumes = (num_costumes_t)0x4ae860;
static const SetCostumeID_t SetCostumeID = (SetCostumeID_t)0x4ae8c0;
static const SetCustomSkaterID_t SetCustomSkaterID = (SetCustomSkaterID_t)0x4ae950;
static const GetPreferredCostume_t GetPreferredCostume = (GetPreferredCostume_t)0x4aea10;
static const PrintLoadBuffer_t PrintLoadBuffer = (PrintLoadBuffer_t)0x4aea20;
static const ClearLoadBuffer_t ClearLoadBuffer = (ClearLoadBuffer_t)0x4aea30;
static const ClearLoadBufferSlot_t ClearLoadBufferSlot = (ClearLoadBufferSlot_t)0x4aea60;
static const SetLoadBuffer_t SetLoadBuffer = (SetLoadBuffer_t)0x4aeaa0;
static const GetSkaterName_t GetSkaterName = (GetSkaterName_t)0x4aeb20;
static const GetPortraitName_t GetPortraitName = (GetPortraitName_t)0x4aec40;
static const UsesLoadBuffer_t UsesLoadBuffer = (UsesLoadBuffer_t)0x4aed10;
static const SwapLoadBuffer_t SwapLoadBuffer = (SwapLoadBuffer_t)0x4aed80;
static const GetTrickConfig_t GetTrickConfig = (GetTrickConfig_t)0x4aee50;
static const IsRegularStance_t IsRegularStance = (IsRegularStance_t)0x4aef10;
static const GetPSXName_t GetPSXName = (GetPSXName_t)0x4aefe0;
static const GetCustomSkaterSlotIndex_t GetCustomSkaterSlotIndex = (GetCustomSkaterSlotIndex_t)0x4af0f0;
static const PlayerSelect_ClearState_t PlayerSelect_ClearState = (PlayerSelect_ClearState_t)0x4af170;
static const Get_Selected_Skater_t Get_Selected_Skater = (Get_Selected_Skater_t)0x4af180;
static const Set_Selected_Skater_t Set_Selected_Skater = (Set_Selected_Skater_t)0x4af1b0;
static const GetCustomSkaterIndex_t GetCustomSkaterIndex = (GetCustomSkaterIndex_t)0x4af260;
static const IsInitialCustomSkaterRevision_t IsInitialCustomSkaterRevision = (IsInitialCustomSkaterRevision_t)0x4af2d0;
static const FrontEnd2_GetSkaterName_t FrontEnd2_GetSkaterName = (FrontEnd2_GetSkaterName_t)0x4af310;