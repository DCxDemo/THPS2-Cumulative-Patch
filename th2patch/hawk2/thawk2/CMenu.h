#pragma once

/*
	CMenu

	originally part of front.cpp
	Handles vertical basic menu layout
*/

typedef void(*CMenu__new_t)();
typedef void(*CMenu__destruct_t)();
typedef void(*CMenu__delete_t)();
typedef void(*CMenu__CentreY_t)();
typedef void(*CMenu__SetLine_t)();
typedef void(*FUN_0x0044b750_menuReset_unused_t)();
typedef void(*CMenu__FindEntry_t)();
typedef void(*CMenu__AddEntry_t)();
typedef void(*CMenu__EntryOn_t)();
typedef void(*CMenu__EntryOff_t)();
typedef void(*CMenu__IsEntryOn_t)();
typedef void(*CMenu__Disable_t)();
typedef void(*FUN_0x0044b960_isEnabled_unused_t)();
typedef void(*FUN_0x0044b980_unused_t)();
typedef void(*CMenu__ChoiceIs_t)();
typedef void(*FUN_0x0044b9c0_unused_t)();
typedef void(*CMenu__Display_t)();
typedef void(*CMenu__Update_t)();


static const CMenu__new_t CMenu__new = (CMenu__new_t)0x0044b5e0;
static const CMenu__destruct_t CMenu__destruct = (CMenu__destruct_t)0x0044b690;
static const CMenu__delete_t CMenu__delete = (CMenu__delete_t)0x0044b6b0;
static const CMenu__CentreY_t CMenu__CentreY = (CMenu__CentreY_t)0x0044b6c0;
static const CMenu__SetLine_t CMenu__SetLine = (CMenu__SetLine_t)0x0044b710;
static const FUN_0x0044b750_menuReset_unused_t FUN_0x0044b750_menuReset_unused = (FUN_0x0044b750_menuReset_unused_t)0x0044b750;
static const CMenu__FindEntry_t CMenu__FindEntry = (CMenu__FindEntry_t)0x0044b7a0;
static const CMenu__AddEntry_t CMenu__AddEntry = (CMenu__AddEntry_t)0x0044b830;
static const CMenu__EntryOn_t CMenu__EntryOn = (CMenu__EntryOn_t)0x0044b8c0;
static const CMenu__EntryOff_t CMenu__EntryOff = (CMenu__EntryOff_t)0x0044b8e0;
static const CMenu__IsEntryOn_t CMenu__IsEntryOn = (CMenu__IsEntryOn_t)0x0044b900;
static const CMenu__Disable_t CMenu__Disable = (CMenu__Disable_t)0x0044b940;
static const FUN_0x0044b960_isEnabled_unused_t FUN_0x0044b960_isEnabled_unused = (FUN_0x0044b960_isEnabled_unused_t)0x0044b960;
static const FUN_0x0044b980_unused_t FUN_0x0044b980_unused = (FUN_0x0044b980_unused_t)0x0044b980;
static const CMenu__ChoiceIs_t CMenu__ChoiceIs = (CMenu__ChoiceIs_t)0x0044b9a0;
static const FUN_0x0044b9c0_unused_t FUN_0x0044b9c0_unused = (FUN_0x0044b9c0_unused_t)0x0044b9c0;
static const CMenu__Display_t CMenu__Display = (CMenu__Display_t)0x0044ba30;
static const CMenu__Update_t CMenu__Update = (CMenu__Update_t)0x0044bb60;


/*
typedef void* (__thiscall* CMenu__AddEntry_t)(void* _this, char* pText);
typedef void* (__thiscall* _new_CMenu_t)(void* _this, int param_2, int param_3, char param_4, short param_5, short param_6, int param_7);
static const CMenu__AddEntry_t CMenu__AddEntry = (CMenu__AddEntry_t)0x0044b830;
static const _new_CMenu_t _new_CMenu = (_new_CMenu_t)0x0044b5e0;
*/
