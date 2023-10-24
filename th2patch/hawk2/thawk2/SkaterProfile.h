#pragma once

/// <summary>
/// Board struct, defines name, texture and board stats.
/// Board array is stored in the skater profile.
/// </summary>
struct SBoardInfo
{
	char* pBitmapName;	//board graphics
	char* pImage;		//board name

	int unk0;

	int Weight;		//board stats
	int Speed;
	int Durability;

	int unk1;
	int unk2;
};

typedef struct SBoardInfo SBoardInfo;


/// <summary>
/// Skater profile struct, describes various skater related data
/// </summary>
struct SkaterProfile
{
	char* styleA_hi;	//array of pointers to model PSX file names, 4 styles * hi and lo models
	char* styleA_lo;	//pc port doesn't seem to be using low models, maybe in netplay?
	char* styleB_hi;
	char* styleB_lo;
	char* styleC_hi;
	char* styleC_lo;
	char* styleD_hi;
	char* styleD_lo;

	char FullName[32];	//full skater name, i.e. "Tony Hawk"
	char* pShortName;	//short skater name, i.e. "Tony"

	SBoardInfo boards[8];	//board structs array
	char stats[10];		//skater stats, byte per stat
	char style;			//currently selected style
	char stance;		//switch or regular
	char* pFaceName;	//UI face preview bitmap
	char** pBioLines;	//list of char bio lines, ends with nullptr
	int unlocked;		//unlocked flag
	int flags;			//1 = female sfx, rest some unlockables
	int unk1;			//only accessed once in LoadAllSkaters
	int animIndex;		//animation index used in frontend
	int videoIndex;		//video index (negative) to play at the end of the loop for this profile
	void* pDynamicLogos;	//ptr to level dynamic logo
};

typedef struct SkaterProfile SkaterProfile;