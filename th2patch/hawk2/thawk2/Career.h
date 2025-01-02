#pragma once

/*
	Carrer.h
	======
	- Career namespace handles everything related to the career mode
*/

#include "types.h"
#include "mess.h"
#include "..\patch\hook.h"

namespace Career {

	extern Hook::Reroute* pHookList;

	//TODO: map params for the lower half of funcs

#define NUMGOALS_TH2 10
#define NUMGOALS_TH1 5

#define NUMCAREERLEVELS_TH2 12

	enum class ELevel : int {
		Hangar = 0,
		School2 = 1,
		Marseille = 2,
		NewYork = 3,
		Venice = 4,
		SkateStreet = 5,
		Philly = 6,
		Bullring = 7,
		ChopperDrop = 8,
		SkateHeaven = 9,
		Warehouse = 10,
		Vans = 11,
		DownhillJam = 12,
		CustomPark = 13,
		First = 0,
		Last = 13
	};

	// it swaps airport and suburbia due to hardcoded slot 4 night sky for new york, makes suburbia weird
	// also swaps back canada and los angeles as in next gen versions, due to LA crash in slot 2
	enum class ELevelThps3
	{
		Foundry = 0,
		Canada = 1,
		Rio = 2,
		Airport = 3,
		Suburbia = 4,
		SkaterIsland = 5,
		LosAngeles = 6,
		Tokyo = 7,
		DownhillBrazil = 8,
		First = 0,
		Last = 13
	};

	enum class ECheat : int {
		McSqueeb = 0,
		Spiderman = 1,
		OfficerDick = 2,
		SkipToRestart = 3,
		KidMode = 4,
		PerfectBalance = 5,
		AlwaysSpecial = 6,
		Stud = 7,
		Weight = 8,
		Wireframe = 9,
		SlowNic = 10,
		BigHead = 11,
		SimMode = 12,
		Smooth = 13,
		MoonPhysics = 14,
		DiscoMode = 15,
		LevelFlip = 16,
		First = 0,
		Last = 16
	};

	//original game used defines for this enum
	enum class EGoalType : int {
		Score = 0,		//High score, pro score or sick score (insane in demo)
		Skate = 1,		//Collect SKATE letters
		Gaps = 2,		//Collect gaps
		Pickups = 3,	//Collect level pickups
		Destroy = 4,	//Destroy objects (like barrels)
		Trick = 5,		//Get a gap with a specific trick
		Hidden = 6,		//Find the hidden tape
		Clear = 7,		//Beat the level (100% goals and cash)

		First = 0,
		Last = 7
	};


	enum class EGapFlag : short {
		RegularGap = 0,
		GoalGap = 1,
		TrickGap = 2
	};

	/// <summary>
	/// Defines a gap trick aka "blue text transfer".
	/// </summary>
	typedef struct SCheat {
		bool Unlocked;		// cheat unlock state
		bool SkaterIndex;	// skater index unlocked? probably unused
		bool State;			// cheat state
		bool pad;			// apparently just padding
	} SCheat;

	/// <summary>
	/// Defines a gap trick aka "blue text transfer".
	/// </summary>
	typedef struct SGapTrick {
		short Flags;		// gap type flags (stuff like CANCEL_GRIND CANCEL_WALL, etc)
		short Type;			// defines whether the gap is used in goal checks ( EGapFlag enum )
		short Value;		// gap index, 2 values - index / 10000 and index % 10000
		short Score;		// score points to award
		char Name[0x24];	// gap name
	} SGapTrick;

	/// <summary>
	/// Defines a single level goal.
	/// </summary>
	typedef struct SGoal {
		EGoalType goalType;	// goal type
		int intParam;		// score value, num items or gap checksum
		char* stringParam;	// pointer to item text, like "pilot wings" or trick match
		int cashAward;		// amount of cash to award
		char* goalText;		// pointer to goal text for level goals screen
		int unk;
	} SGoal;


	extern uint* Career_UnlockFlags;
	extern SGapTrick* pGaps;


	typedef void(*Career_Init_t)();
	typedef void(*Options_SetPreferences_t)();
	typedef void(*Options_LoadPreferences_t)();
	typedef void(*Options_RemapControllers_t)();
	typedef void(*Options_ResetControllerDefaults_t)();
	typedef void(*Options_Init_t)();
	//typedef bool(*Career_Got_t)(int goalIndex);
	//typedef bool(*Career_JustGot_t)(int param_1);
	//typedef int(*Career_LevelTapes_t)(void* param_1, int param_2); //param_1 type = SCharacterProgress
	//typedef int(*Career_NumLevelGoals_t)();
	typedef int(*Career_CountMoney_t)();
	//typedef void(*Career_CheckScore_t)();
	typedef void(*Career_GiveGoal_t)(int param_1);
	//typedef uint(*Career_GoalIndex_t)(EGoalType goalType);
	//typedef void(*Career_GiveGoalType_t)(EGoalType goalType);
	//typedef void(*Career_CheckClear_t)();
	//typedef bool(*Career_GotGoalType_t)(EGoalType goalType);
	typedef void(*Career_GiveMedal_t)(int param_1, char medalType); //param_2 = EMedalType
	//typedef bool(*Career_GapActive_t)(SGapTrick* gapTrick); //param_1 = SGapTrick
	//typedef bool(*Career_GapIsGoal_t)(void* param_1); //param_1 = SGapTrick
	//typedef bool(*Career_GapIsTrick_t)(void* param_1); //param_1 = SGapTrick
	//typedef int(*Career_GapGoalNumber_t)(void* param_1); //param_1 = SGapTrick
	//typedef int(*Career_GapTrickNumber_t)(void* param_1); //param_1 = SGapTrick
	//typedef int(*Career_GapNumber_t)(void* param_1); //param_1 = SGapTrick
	//typedef bool(*Career_GotGoalGap_t)(void* param_1); //param_1 = SGapTrick
	//typedef bool(*Career_GotTrickGap_t)(void* param_1); //param_1 = SGapTrick
	//typedef void(*Career_GiveGoalGap_t)(void* param_1); //param_1 = SGapTrick
	//typedef void(*Career_GiveTrickGap_t)(void* param_1); //param_1 = SGapTrick
	//typedef bool(*Career_AnyoneGotGap_t)(SGapTrick* pGap);
	//typedef void(*Career_GiveGap_t)(SGapTrick* pGap);
	//typedef int(*Career_CountBits_t)(int param_1);
	//typedef int(*Career_NumGoalGapsGot_t)();
	//typedef int(*Career_NumTrickGapsGot_t)(int param_1);
	//typedef void(*Career_AwardGoalGap_t)(SGapTrick* pGap);
	//typedef void(*Career_AwardGap_t)(SGapTrick* pGap);
	//typedef void(*Career_AwardTrickGap_t)(SGapTrick* pGap);
	typedef short(*Career_MoneyNumber_t)(int param_1);
	typedef void(*Career_GotMoney_t)(int param_1);
	typedef void(*Career_GiveMoney_t)(int param_1, int amount);
	//typedef void(*Career_GetLevelPickup_t)();
	typedef void(*Career_CountThings_t)();
	//typedef int(*Career_CountGaps_t)();
	//typedef bool(*Career_GotAllGaps_t)();
	typedef bool(*Career_BuyPoint_t)(int statIndex, int param_2);
	typedef bool(*Career_SellPoint_t)(int statIndex);
	typedef int(*Career_GetPointCost_t)();
	//typedef void(*Career_NumLevelsWithMedals_t)();
	typedef bool(*Career_LevelOpenCareerMode_t)(int levelIndex, void* charProg); //is it? it is
	typedef bool(*Career_LevelOpen_t)(int param_1, bool param_2);
	//typedef int(*Career_HighestOpenLevel_t)(int param_1);
	//typedef void(*Career_LevelNeeds_t)();
	typedef void(*Career_LoadingScreen_t)();
	typedef void* (*Career_GetCharacterProgress_t)(int skaterID);
	typedef void(*Career_IsTrickPurchased_t)();
	typedef void(*Career_PurchaseTrick_t)();
	typedef void(*Career_AssignTrick_t)();
	typedef void(*Career_SpecialTrickAssigned_t)();
	typedef void(*Career_AssignSpecialTrick_t)();
	//typedef void(*Career_CountGoldMedals_t)();
	//typedef void(*Career_CountMedals_t)();
	typedef void(*Career_PostLoad_t)();
	typedef void(*Career_PreSave_t)();
	typedef void(*Career_GameCleared_t)();
	typedef void(*Career_ClearGame_t)(int skaterIndex);
	typedef void(*Career_ClearGameWithEveryone_t)();
	typedef void(*Career_UnlockCheat_t)();
	//typedef bool(*Career_CheatUnlocked_t)(ECheat cheat);
	typedef void(*Career_CheatState_t)();
	typedef void(*Career_GetCheat_t)();
	typedef void(*Career_SetCheat_t)(ECheat cheat, bool state, int skaterIndex);
	//typedef void(*Career_ToggleCheat_t)(ECheat cheat, int skaterIndex);
	typedef void(*Career_NewCheat_t)();
	//typedef void(*Career_CountUnlockedCheats_t)();
	//typedef char*(*Career_CheatName_t)(int cheat);
	//typedef void(*Career_CheatType_t)();
	typedef void(*Career_UnlockCharacter_t)(int character); //?
	typedef void(*Career_CharacterIsUnlocked_t)();
	//typedef void(*Career_ApplyCheats_t)();
	typedef void(*Career_InitProgress_t)();
	typedef void(*Career_TakeSnapShot_t)();
	typedef void(*Career_RestoreSnapShot_t)();
	typedef void(*Career_SaveCharacterStates_t)();
	typedef void(*Career_ResetCheats_t)();

	static const Career_Init_t Career_Init = (Career_Init_t)0x004138f0;
	static const Options_SetPreferences_t Options_SetPreferences = (Options_SetPreferences_t)0x00413c10;
	static const Options_LoadPreferences_t Options_LoadPreferences = (Options_LoadPreferences_t)0x00413d60;
	static const Options_RemapControllers_t Options_RemapControllers = (Options_RemapControllers_t)0x00413ed0;
	static const Options_ResetControllerDefaults_t Options_ResetControllerDefaults = (Options_ResetControllerDefaults_t)0x00413f30;
	static const Options_Init_t Options_Init = (Options_Init_t)0x00413f70;
	//static const Career_Got_t Career_Got = (Career_Got_t)0x00414030;
	bool Career_Got(int goalIndex);
	//static const Career_JustGot_t Career_JustGot = (Career_JustGot_t)0x004140c0;
	bool Career_JustGot(int goalIndex);
	//static const Career_LevelTapes_t Career_LevelTapes = (Career_LevelTapes_t)0x00414130;
	int Career_LevelTapes(void* pProg, int levelIndex);
	//static const Career_NumLevelGoals_t Career_NumLevelGoals = (Career_NumLevelGoals_t)0x004141a0;
	int Career_NumLevelGoals();
	static const Career_CountMoney_t Career_CountMoney = (Career_CountMoney_t)0x004141d0;
	//static const Career_CheckScore_t Career_CheckScore = (Career_CheckScore_t)0x00414280;
	void Career_CheckScore();
	static const Career_GiveGoal_t Career_GiveGoal = (Career_GiveGoal_t)0x004142e0;
	//static const Career_GoalIndex_t Career_GoalIndex = (Career_GoalIndex_t)0x00414540;
	uint Career_GoalIndex(EGoalType goalType);
	//static const Career_GiveGoalType_t Career_GiveGoalType = (Career_GiveGoalType_t)0x00414570;
	void Career_GiveGoalType(EGoalType goalType);
	//static const Career_CheckClear_t Career_CheckClear = (Career_CheckClear_t)0x004145e0;
	void Career_CheckClear();
	//static const Career_GotGoalType_t Career_GotGoalType = (Career_GotGoalType_t)0x00414650;
	bool Career_GotGoalType(EGoalType goalType);
	static const Career_GiveMedal_t Career_GiveMedal = (Career_GiveMedal_t)0x00414670;
	//static const Career_GapActive_t Career_GapActive = (Career_GapActive_t)0x00414770;
	bool Career_GapActive(SGapTrick* pGap);
	//static const Career_GapIsGoal_t Career_GapIsGoal = (Career_GapIsGoal_t)0x004147b0;
	bool Career_GapIsGoal(SGapTrick* pGap);
	//static const Career_GapIsTrick_t Career_GapIsTrick = (Career_GapIsTrick_t)0x004147e0;
	bool Career_GapIsTrick(SGapTrick* pGap);
	//static const Career_GapGoalNumber_t Career_GapGoalNumber = (Career_GapGoalNumber_t)0x00414810;
	int Career_GapGoalNumber(SGapTrick* pGap);
	//static const Career_GapTrickNumber_t Career_GapTrickNumber = (Career_GapTrickNumber_t)0x004148f0;
	int Career_GapTrickNumber(SGapTrick* pGap);
	//static const Career_GapNumber_t Career_GapNumber = (Career_GapNumber_t)0x004149d0;
	int Career_GapNumber(SGapTrick* pGap);
	//static const Career_GotGoalGap_t Career_GotGoalGap = (Career_GotGoalGap_t)0x00414a50;
	bool Career_GotGoalGap(SGapTrick* pGap);
	//static const Career_GotTrickGap_t Career_GotTrickGap = (Career_GotTrickGap_t)0x00414a80;
	bool Career_GotTrickGap(SGapTrick* pGap);
	//static const Career_GiveGoalGap_t Career_GiveGoalGap = (Career_GiveGoalGap_t)0x00414ab0;
	void Career_GiveGoalGap(SGapTrick* pGap);
	//static const Career_GiveTrickGap_t Career_GiveTrickGap = (Career_GiveTrickGap_t)0x00414ae0;
	void Career_GiveTrickGap(SGapTrick* pGap); // SGapTrick*
	//static const Career_AnyoneGotGap_t Career_AnyoneGotGap = (Career_AnyoneGotGap_t)0x00414b10;
	bool Career_AnyoneGotGap(SGapTrick* pGapTrick);
	//static const Career_GiveGap_t Career_GiveGap = (Career_GiveGap_t)0x00414b50;
	void Career_GiveGap(SGapTrick* pGap);
	//static const Career_CountBits_t Career_CountBits = (Career_CountBits_t)0x00414b90;
	int Career_CountBits(uint value);
	//static const Career_NumGoalGapsGot_t Career_NumGoalGapsGot = (Career_NumGoalGapsGot_t)0x00414bb0;
	int Career_NumGoalGapsGot();
	//static const Career_NumTrickGapsGot_t Career_NumTrickGapsGot = (Career_NumTrickGapsGot_t)0x00414bc0;
	int Career_NumTrickGapsGot();
	//static const Career_AwardGoalGap_t Career_AwardGoalGap = (Career_AwardGoalGap_t)0x00414bd0;
	void Career_AwardGoalGap(SGapTrick* pGap); //ptr goal gap i assume
	//static const Career_AwardGap_t Career_AwardGap = (Career_AwardGap_t)0x00414c50;
	void Career_AwardGap(SGapTrick* pGap);
	//static const Career_AwardTrickGap_t Career_AwardTrickGap = (Career_AwardTrickGap_t)0x00414d90;
	void Career_AwardTrickGap(SGapTrick* pGap);
	static const Career_MoneyNumber_t Career_MoneyNumber = (Career_MoneyNumber_t)0x00414fa0;
	static const Career_GotMoney_t Career_GotMoney = (Career_GotMoney_t)0x00415060;
	static const Career_GiveMoney_t Career_GiveMoney = (Career_GiveMoney_t)0x00415180;
	//static const Career_GetLevelPickup_t Career_GetLevelPickup = (Career_GetLevelPickup_t)0x004152f0;
	void Career_GetLevelPickup();
	static const Career_CountThings_t Career_CountThings = (Career_CountThings_t)0x00415380;
	//static const Career_CountGaps_t Career_CountGaps = (Career_CountGaps_t)0x00415560;
	int Career_CountGaps();
	//static const Career_GotAllGaps_t Career_GotAllGaps = (Career_GotAllGaps_t)0x00415590;
	bool Career_GotAllGaps();
	static const Career_BuyPoint_t Career_BuyPoint = (Career_BuyPoint_t)0x004155a0;
	static const Career_SellPoint_t Career_SellPoint = (Career_SellPoint_t)0x004156f0;
	static const Career_GetPointCost_t Career_GetPointCost = (Career_GetPointCost_t)0x00415820;
	//static const Career_NumLevelsWithMedals_t Career_NumLevelsWithMedals = (Career_NumLevelsWithMedals_t)0x004158d0;
	int Career_NumLevelsWithMedals(void* pProg);
	static const Career_LevelOpenCareerMode_t Career_LevelOpenCareerMode = (Career_LevelOpenCareerMode_t)0x00415910;
	static const Career_LevelOpen_t Career_LevelOpen = (Career_LevelOpen_t)0x004159d0;
	//static const Career_HighestOpenLevel_t Career_HighestOpenLevel = (Career_HighestOpenLevel_t)0x00415a90;
	int Career_HighestOpenLevel(int param_1);
	//static const Career_LevelNeeds_t Career_LevelNeeds = (Career_LevelNeeds_t)0x00415ad0;
	int Career_LevelNeeds(int levelIndex);
	static const Career_LoadingScreen_t Career_LoadingScreen = (Career_LoadingScreen_t)0x00415b20;
	static const Career_GetCharacterProgress_t Career_GetCharacterProgress = (Career_GetCharacterProgress_t)0x00416040;
	static const Career_IsTrickPurchased_t Career_IsTrickPurchased = (Career_IsTrickPurchased_t)0x00416060;
	static const Career_PurchaseTrick_t Career_PurchaseTrick = (Career_PurchaseTrick_t)0x00416130;
	static const Career_AssignTrick_t Career_AssignTrick = (Career_AssignTrick_t)0x00416220;
	static const Career_SpecialTrickAssigned_t Career_SpecialTrickAssigned = (Career_SpecialTrickAssigned_t)0x00416330;
	static const Career_AssignSpecialTrick_t Career_AssignSpecialTrick = (Career_AssignSpecialTrick_t)0x00416370;
	//static const Career_CountGoldMedals_t Career_CountGoldMedals = (Career_CountGoldMedals_t)0x004164a0;
	int Career_CountGoldMedals(void* pProg);
	//static const Career_CountMedals_t Career_CountMedals = (Career_CountMedals_t)0x00416520;
	int Career_CountMedals(void* pProg);
	static const Career_PostLoad_t Career_PostLoad = (Career_PostLoad_t)0x004165c0;
	static const Career_PreSave_t Career_PreSave = (Career_PreSave_t)0x004166e0;
	static const Career_GameCleared_t Career_GameCleared = (Career_GameCleared_t)0x00416730;
	static const Career_ClearGame_t Career_ClearGame = (Career_ClearGame_t)0x00416780;
	//static const Career_ClearGameWithEveryone_t Career_ClearGameWithEveryone = (Career_ClearGameWithEveryone_t)0x00416880;
	void Career_ClearGameWithEveryone();
	static const Career_UnlockCheat_t Career_UnlockCheat = (Career_UnlockCheat_t)0x004168a0;
	//static const Career_CheatUnlocked_t Career_CheatUnlocked = (Career_CheatUnlocked_t)0x00416930;
	bool Career_CheatUnlocked(ECheat cheat);
	//static const Career_CheatState_t Career_CheatState = (Career_CheatState_t)0x00416950;
	bool Career_CheatState(ECheat cheat);
	static const Career_GetCheat_t Career_GetCheat = (Career_GetCheat_t)0x00416970;
	static const Career_SetCheat_t Career_SetCheat = (Career_SetCheat_t)0x004169f0;
	//static const Career_ToggleCheat_t Career_ToggleCheat = (Career_ToggleCheat_t)0x00416c80;
	void Career_ToggleCheat(ECheat cheat, int skaterIndex);
	static const Career_NewCheat_t Career_NewCheat = (Career_NewCheat_t)0x00416cc0;
	//static const Career_CountUnlockedCheats_t Career_CountUnlockedCheats = (Career_CountUnlockedCheats_t)0x00416dd0;
	int Career_CountUnlockedCheats();
	//static const Career_CheatName_t Career_CheatName = (Career_CheatName_t)0x00416e20;
	char* Career_CheatName(ECheat cheat);
	//static const Career_CheatType_t Career_CheatType = (Career_CheatType_t)0x00416f40;
	int Career_CheatType(ECheat cheat);
	static const Career_UnlockCharacter_t Career_UnlockCharacter = (Career_UnlockCharacter_t)0x00416f70;
	static const Career_CharacterIsUnlocked_t Career_CharacterIsUnlocked = (Career_CharacterIsUnlocked_t)0x00416fa0;
	//static const Career_ApplyCheats_t Career_ApplyCheats = (Career_ApplyCheats_t)0x00417050;
	void Career_ApplyCheats();
	static const Career_InitProgress_t Career_InitProgress = (Career_InitProgress_t)0x004170c0;
	static const Career_TakeSnapShot_t Career_TakeSnapShot = (Career_TakeSnapShot_t)0x004171d0;
	static const Career_RestoreSnapShot_t Career_RestoreSnapShot = (Career_RestoreSnapShot_t)0x00417250;
	static const Career_SaveCharacterStates_t Career_SaveCharacterStates = (Career_SaveCharacterStates_t)0x004172f0;
	static const Career_ResetCheats_t Career_ResetCheats = (Career_ResetCheats_t)0x00417320;

	//additional functions
	void Career_SetAllGaps(bool value);
	void Career_PrintGoals();
	void* Career_GetCurrentCharacterProgress();
	SGoal* GetGoal(int level, int goal);
}