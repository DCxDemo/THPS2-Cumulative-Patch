#include "stdafx.h"

#include <iostream>
#include <fstream>
#include "string.h"


#include "hawk2_utils.h"
#include "cpatch.h"
#include "GameOptions.h"
#include "mydebug.h"
#include "patchStuff.h"

#include "lib/sqlite/sqlite3.h"
#include "lib/xinput/CXBOXController.h"

#include "thawk2/_old.h"
#include "thawk2/FileIO.h"
#include "thawk2/Mess.h"
#include "thawk2/Career.h"
#include "thawk2/Redbook.h"
#include "thawk2/Sfx.h"
#include "thawk2/globals.h"
#include "thawk2/PCInput.h"

//the old bigass all-in-one file, that should be cut into pizzas. this is my plastic fork!


using namespace std;

GameOptions options;

//ofstream fout1("log_redbook.txt");

typedef struct HookFunc {
	int address;
	void* func;
} HookFunc;

void ParseLevels();
void GetSong(int num);
int CountSongs();


void Proxify(int offs[], int count, void* func)
{
	for (int i = 0; i < count; i++)
		CPatch::RedirectCall(offs[i], func);
}





int* SFXLEVEL = (int*)0x528CA4;
int* XALEVEL = (int*)0x528CA8;

//int totalTracks = 0;
int playingTrack = -1;

string playingName;
string playingFile;

int* Redbook_XAFadeScale			= (int*)0x53458C;
int* gMusicPlaying					= (int*)0x5674E0;
int* Redbook_XAFading				= (int*)0x5684F8;
int* Redbook_XACurrentChannel		= (int*)0x5684E8;
int* Redbook_XACurrentGroup			= (int*)0x5684EC;
int* Redbook_XACurrentSector		= (int*)0x5684C8;
int* Redbook_XACheckSectorOnVSync	= (int*)0x5684DC;
int* Redbook_XAModeSet				= (int*)0x5684DD;
int* Redbook_XACompleteTimer		= (int*)0x5684D8;
int* Redbook_XAPaused				= (int*)0x5684E0;


int* _Cheat_Light = (int*)0x005674c8;




int* spriteX = (int*)0x69D184;
int* spriteY = (int*)0x69D188;



void PatchSkaters();

//string playlistPath = "patch\\tracklist.ini";
string playlistPath; // = (string)(char*)0x521168;

struct SONG_POS
{
	int Channel;
	int Group;
	int Sector;
};


typedef struct
{
    int slot;
    string artist;
	string title;
    string filename;
} Song;

Song song;

int Redbook_XARemember2(SONG_POS *pos)
{
	pos->Channel = *Redbook_XACurrentChannel;
	pos->Group = *Redbook_XACurrentGroup;
	pos->Sector = *Redbook_XACurrentSector;
	return *Redbook_XACurrentGroup;
}

bool __cdecl Redbook_XAPause2(int a1)
{
	bool result = *Redbook_XAPaused != 0;

	if ( a1 != result )
	{
		result = PCMOVIE_Pause(a1);
		*Redbook_XAPaused = a1;
	}
	return result;
}

bool Redbook_XAStop2()
{
	PCMOVIE_XAStop();
	*Redbook_XACheckSectorOnVSync = 0;
	*Redbook_XACompleteTimer = 30;
	*Redbook_XAModeSet = 0;
	return Redbook_XAPause2(1);
}


void Redbook_XARestore2(SONG_POS *pos)
{
	if ( pos->Channel != *Redbook_XACurrentChannel || 
		pos->Group != *Redbook_XACurrentGroup )
	{
		Redbook_XAStop2();
		Redbook_XAPlay(pos->Channel, pos->Group);
	}
	else
	{
		*Redbook_XACurrentSector = pos->Sector;
	}
}


void Redbook_XAUpdateVolume2()
{
	if ( *Redbook_XAFading )
	{
		*Redbook_XAFadeScale -= 3;
		if ( *Redbook_XAFadeScale < 0 ) *Redbook_XAFadeScale = 0;
    }

	int v = *XALEVEL * *Redbook_XAFadeScale / 255;
	if ( v > 255 ) v = 255;

	//fout1 << v << endl;

	PCMOVIE_SetXAVolume(v, v);
}

void Redbook_XABeginFade2()
{
	if (options.Fade)
	{
		*Redbook_XAFadeScale = 255;
		*Redbook_XAFading = 1;
	}
}

/*
void GetTrackInfo(int x)
{	
		ifstream plist(playlistPath);
		string a = "default";
		string b = a; 

		if (plist)
		{
			if (totalTracks > 0)
			for (int i = -1; i < x; i++)
			{
				if ( getline(plist, a) && getline(plist, b))
				{
					playingName = a;
					playingFile = b;
				}
			}
		}
}

void GetTotalTracks()
{	
	//fout1 << &playlistPath[0u] << endl;
	FILE* file = fopen(&playlistPath[0u], "r");

	if (file)
	{
		fclose(file);

		ifstream plist(playlistPath);
		string a;
		int count = -1;

		do count++;
		while(getline(plist, a) && getline(plist, a));
			
		totalTracks = count;
	}
	else
	{
		totalTracks = 0;
	}

	//fout1 << totalTracks << endl;
}
*/

void Redbook_XANextTrack2(int inc)
{
	if (options.totalTracks <= 0) 
	{
		*XALEVEL = 0;
	}

	if ( *XALEVEL && (options.totalTracks > 0) )
	{

		if (!options.PlayRandom)
		{
			playingTrack = playingTrack + inc;
			if (playingTrack >= options.totalTracks) playingTrack = 0;
			if (playingTrack < 0) playingTrack = options.totalTracks - 1;
		}
		else
		{
			int newTrack;
			do newTrack = rand()%options.totalTracks;
			while (newTrack == playingTrack);

			playingTrack = newTrack;
		}

		int newXA = playingTrack + 16;

		//GetTrackInfo(playingTrack);

		GetSong(playingTrack+1);

		playingName = song.artist + " - " + song.title;
		playingFile = song.filename;

		//printf("Now playing: %s\n", playingName);

		if (options.ShowTitle)
		{
			//add file check here
			//FileIO_SetSubDir("D:\\Games\\THPS2\\data\\music\\");

			//if (FileIO_Exists(&playingFile[0]))
			//{
				Mess_DeleteAll();
				DrawMessage(&playingName[0]);
			//}
		}

		Redbook_XAPlay(newXA / 8, newXA % 8);
	}
	else
	{
		//if (totalTracks <= 0) shouldPlayAmbience = true;

		//fout1 << "now wtf " << *XALEVEL << " " << totalTracks << endl;

		if (options.PlayAmbience)
		{
			int ambience = *GLevel > 10 ? 10 : *GLevel;

			//if (!dword_5674E0)
			Redbook_XAPlay(ambience / 8, ambience % 8);
			PCMOVIE_SetXAVolume(*SFXLEVEL*20, *SFXLEVEL*20);
		}
	}
}




void PCMOVIE_XAPlay2(int a1, int a2)
{
	char *cstr = &playingFile[0u];

	char lal[256] = "";

	int curTrack = a2 + a1*8;

	if (curTrack < 15)
	{
		sprintf(lal, "%s%02i%s", "ltix", a2 + 8 * a1, ".dat");
		PCMOVIE_StartMusic(lal);
		return;
	}

	PCMOVIE_StartMusic(cstr);
}






void Redirect_PCMOVIE_XAPlay()
{
	int offs[] = {
		0x4A93EE //xa_play
	};

	Proxify(offs, sizeof(offs) / 4, PCMOVIE_XAPlay2);
}

void Redirect_Redbook_XAUpdateVolume()
{
	int offs[] = { 
		0x451CDE,  //front_update
		0x451F6F,  //front_update
		0x484A0C,  //???
		0x4A9525,  //redbook xa play
		0x4A9739   //xaupdate?
	};

	Proxify(offs, sizeof(offs) / 4, Redbook_XAUpdateVolume2);
}

void Redirect_Redbook_XABeginFade()
{
	int offs[] = {
		0x427130, //credits
		0x466BA7  //game_over
	};

	Proxify(offs, sizeof(offs) / 4, Redbook_XABeginFade2);
}

void Redirect_Redbook_XANextTrack()
{
	int offs[] = {
		0x451DCF,	//front_update
		0x451EC6,	//front_update
		0x451F29,
		0x46A3CA,	//playaway
		0x48474F,	//??
		0x4A978F,	//XAUpdate
		0x4A97A3
	};

	Proxify(offs, sizeof(offs) / 4, Redbook_XANextTrack2);
}






short OllieConcrete = 0x400;
short OllieWood = 0x401;
short OllieMetal = 0x402;
short OllieWater = 0x403;

short LandConc = 0x404;
short LandWood = 0x405;
short LandMetal = 0x406;
short LandWater = 0x407;
short LandDirt = 0x408;

short SND_LANDWOOD = 200;
short SND_LANDDIRT = 202;
short SND_LANDMETAL = 203;
short SND_LAND = 5;


enum class Terrain : int
{
	Concrete = 0,
	Tile = 1,
	Wood = 2,
	Dirt = 3,
	Asphalt = 4,
	Grass = 5,
	Water = 6,
	Chainlink = 7,
	Brick = 8,
	MetalPole = 9,
	Generic1 = 10,
	Generic2 = 11,
	Metal = 12,
	Rock = 13,
	Gravel = 14,
	Sidewalk = 15
};


string kek = "Tile";


signed int Ollie_Sound(Terrain terrain)
{
	switch (terrain)
	{
		case Terrain::Concrete: SFX_PlayX(OllieConcrete, 0x2000);
		case Terrain::Tile:
		case Terrain::Wood: SFX_PlayX(OllieWood, 0x2000);		//ollieWoodA
		case Terrain::Dirt:
		case Terrain::Grass: SFX_PlayX(LandDirt, 0x2000);
		case Terrain::Metal: SFX_PlayX(OllieMetal, 0x2000);	//C7 00
		case Terrain::Water: SFX_PlayX(OllieWater, 0x2000);	//water --
		default: SFX_PlayX(OllieConcrete, 0x2000);	//CollieD
	}
}

void Land_Sound(Terrain terrain)
{
	switch (terrain)
	{
		case Terrain::Wood:
		case Terrain::Gravel: SFX_PlayX(LandWood, 0x2000); break;
		case Terrain::Metal: SFX_PlayX(LandMetal, 0x2000); break;
		case Terrain::Dirt:
		case Terrain::Grass: SFX_PlayX(LandDirt, 0x2000); break;
		case Terrain::Water: SFX_PlayX(LandWater, 0x2000); break;
		default: SFX_PlayX(LandConc, 0x2000);
	}
}

void Redirect_Ollie_Sound()
{
	int offs[] = {
		0x46DFB8, //cbruce::Ai
		0x4987F4  //cbruce::handlejump
	};

	Proxify(offs, sizeof(offs) / 4, Ollie_Sound);
}





/*
//int* LevelVABListNum = (int*)0x53472C;
int LevelVABListNum = -1;

int totalLevels = 14;

string levelName[] =
{
	"hangar", "school2", "mar", "ny", "venice", 
	"ss", "philly", "bullring", "b1",
	"heaven", "sked", "ware", "comp", "JAM"
};

void __cdecl SFX_SpoolInLevelSFX(const char *a1)
{
	for (int i = 0; i<totalLevels; i++) 
		if (!strcmp(a1, &(levelName[i])[0])) 
			LevelVABListNum = i+4;

	if (LevelVABListNum != -1) SOUNDLIB_LoadVABList(LevelVABListNum);
}


int SFX_SpoolOutLevelSFX()
{
	int result = LevelVABListNum;

	if ( LevelVABListNum != -1 )
	{
		result = SOUNDLIB_FreeVABList(LevelVABListNum);
		LevelVABListNum = -1;
	}

	return result;
}
*/



void VIDMENU_Save_Hook()
{
	VIDMENU_Save();
	options.Save();
}


void VIDMENU_Load_Hook()
{
    VIDMENU_Load();
	options.Load();
}


int* hW = (int*)0x4f3f30;
int* hH = (int*)0x4f3f37;

int* hW2 = (int*)0x4f5496;
int* hH2 = (int*)0x4f54a0;

short* _Xres = (short*)0x55ed00;
short* _Yres = (short*)0x55ed18;

int* _PixelAspectX = (int*)0x5606cc;
int* _PixelAspectY = (int*)0x5606d0;




bool* GamePaused = (bool*)0x55e864;

int* ScreenWidth = (int*)0x29D6FE4;
int* ScreenHeight = (int*)0x29D6FE8;


void WINMAIN_ScreenDimensions(int* width, int* height)
{
	*width = *ScreenWidth;
	*height = *ScreenHeight;
}


void _cdecl M3dInit_SetResolution(int width, int height)
{
	WINMAIN_ScreenDimensions(&width, &height);

	*_Xres = width;
	*_Yres = height;

	//if (height * w < width * h) 
	//{
		//*_PixelAspectX = 0x900;
		//*_PixelAspectY = 0x900;// *((width * h) / (height * w));
	//}
	//else
	{
		*_PixelAspectX = 0x1000 * options.FOV; // (1 - diff / width43); //* ((height * w) / (width * h));
		*_PixelAspectY = 0x1000 * options.FOV; // (1 - diff / width43);
	}
}


//can probably just nop it?
void WINMAIN_SwitchResolution_Hook(int a1)
{
	//WINMAIN_SwitchResolution(a1);
}


typedef unsigned short ushort;

//this stuff should be moved to pad entirely

enum class PadButton : unsigned short
{
	L2			= 0x0001,
	R2			= 0x0002,
	L1			= 0x0004,
	R1			= 0x0008,
	Triangle	= 0x0010,
	Circle		= 0x0020,
	Cross		= 0x0040,
	Square		= 0x0080,
	Select		= 0x0100,
	Start		= 0x0800,
	PovUp		= 0x1000,
	PovRight	= 0x2000,
	PovDown		= 0x4000,
	PovLeft		= 0x8000,
	PovUpRight	= PovUp | PovRight,
	PovDownRight= PovDown | PovRight,
	PovUpLeft	= PovUp | PovLeft,
	PovDownLeft	= PovDown | PovLeft
};

ushort* p1pad = (ushort*)0x6A0B6C;
int* gJoyEnabled = (int*)0x547a78;
int* gAnalogsEnabled = (int*)0x6a1024; //??

int angleAllowance = 22.5;

CXBOXController* Player1;

void XInput_Press(PadButton button)
{
	*p1pad |= (ushort)button;
}

void GenPsxPadData_Hook()
{
	if (options.XInput)
	{
		*gJoyEnabled = false;
		*gAnalogsEnabled = false;
	}

	//normal game input processing
	GenPsxPadData();

	//maybe poll xinput?
	if (!options.XInput) return;

	if (Player1->UpdateState())
	{
		XINPUT_STATE state = Player1->GetState();

		//start+select: fast quit, get out of here!
		if (Player1->PressedBack() && Player1->PressedStart())
		{
			Player1->Vibrate(0, 0, options.Vibration);
			exit(0);
		}

		//process buttons
		if (Player1->PressedA()) XInput_Press(PadButton::Cross);
		if (Player1->PressedB()) XInput_Press(PadButton::Circle);
		if (Player1->PressedX()) XInput_Press(PadButton::Square);
		if (Player1->PressedY()) XInput_Press(PadButton::Triangle);

		//process pov and left stick
		if (Player1->PressedPOVUp()) XInput_Press(PadButton::PovUp);
		if (Player1->PressedPOVRight()) XInput_Press(PadButton::PovRight);
		if (Player1->PressedPOVDown()) XInput_Press(PadButton::PovDown);
		if (Player1->PressedPOVLeft()) XInput_Press(PadButton::PovLeft);

		//process stick a bit smarter than linear
		int x = state.Gamepad.sThumbLX;
		int y = state.Gamepad.sThumbLY;

		int magnitude = sqrt(x * x + y * y);
		int stickAngle = atan2(x, y) * 180 / 3.1415f;

		if (magnitude > options.StickDeadzone)
		{
			if (  0 - angleAllowance < stickAngle && stickAngle <=   0 + angleAllowance) { *p1pad |= (unsigned short)PadButton::PovUp;		}
			if (-45 - angleAllowance < stickAngle && stickAngle <= -45 + angleAllowance) { *p1pad |= (unsigned short)PadButton::PovUpLeft;	}
			if (-90 - angleAllowance < stickAngle && stickAngle <= -90 + angleAllowance) { *p1pad |= (unsigned short)PadButton::PovLeft;		}
			if (-135 - angleAllowance < stickAngle && stickAngle <= -135 + angleAllowance) { *p1pad |= (unsigned short)PadButton::PovDownLeft; }
			if ( 45 - angleAllowance < stickAngle && stickAngle <=  45 + angleAllowance) { *p1pad |= (unsigned short)PadButton::PovUpRight;	}
			if ( 90 - angleAllowance < stickAngle && stickAngle <=  90 + angleAllowance) { *p1pad |= (unsigned short)PadButton::PovRight;	}
			if (135 - angleAllowance < stickAngle && stickAngle <= 135 + angleAllowance) { *p1pad |= (unsigned short)PadButton::PovDownRight; }
			if (180 - angleAllowance < stickAngle && stickAngle <= 180) { *p1pad |= (unsigned short)PadButton::PovDown; }
			if (-180 < stickAngle && stickAngle <= -180 + angleAllowance) { *p1pad |= (unsigned short)PadButton::PovDown; }
		}
		

		//process start and select
		if (Player1->PressedBack()) XInput_Press(PadButton::Select);
		if (Player1->PressedStart()) XInput_Press(PadButton::Start);

		//process shoulders and triggers
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) XInput_Press(PadButton::L1);
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) XInput_Press(PadButton::R1);

		if (state.Gamepad.bLeftTrigger > 1) XInput_Press(PadButton::L2);
		if (state.Gamepad.bRightTrigger > 1) XInput_Press(PadButton::R2);

		//R3 - skip track
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
			if (!(Player1->GetOldState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB))
				Redbook_XANextTrack2(1);

		//L3
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
		{

		}
	}
}

//silly cheat, sets point cost to 0
int Career_GetPointCost_Hook()
{
	return options.FreeStats ? 0 : Career_GetPointCost();
}


void Panel_Display_Hook()
{
	if (options.ShowHUD)
		Panel_Display();

	PrintDebugStuff();
}

void RenderSuperItemShadow_Hook(void* superItem) //CSuper
{
	if (options.DrawShadow)
		RenderSuperItemShadow(superItem);
}


int* GGame = (int*)0x530d38;
int* prevTicks = (int*)0x29d4fbc;
int* Vblanks = (int*)0x56af7c;
int* Xblanks = (int*)0x56af80;
int* GameFrozen = (int*)0x567540;


void SimVblank(void)
{
	int iVar1;
	char cVar2;
	LONGLONG iVar3;

	//Sleep(100);

	//cVar2 = _D3DTIMER_IsActive();

	/*
	iVar3 = systemclock();

	if (*prevTicks == 0) {
		*prevTicks = (int)iVar3;
	}

	iVar1 = ((iVar3 - *prevTicks) * 60) / 1000;

	*prevTicks = iVar3;

	if (((0 < iVar1) && (*Vblanks = *Vblanks + iVar1, *GamePaused == 0)) && (*GameFrozen == 0)) {
		*Xblanks = *Xblanks + iVar1;
	}
	*/
}


void _fastcall CBruce_StartGrind_Hook(void* _this, void* _edx, int param)
{
	CBruce_StartGrind(_this, param);
	//DrawMessage("Grinding!");
}


void _fastcall CBruce_HandleJump_Hook(void* _this, void* _edx)
{
	CBruce_HandleJump(_this);
	//DrawMessage("Jumping!");
}

void VibrationTest(CXBOXController* Player1)
{
	if (Player1)
	{

		Player1->Vibrate(2000, 0, true);

		double timer = 0;
		do
		{
			Sleep(16);
			WinYield();
			timer += 16.666 * 2;
			//printf("timer: %f\r\n", timer / 1000);
		} while (timer < 16.66666 * 120 * 5);

		Player1->Vibrate(0, 2000, true);

		timer = 0;
		do
		{
			Sleep(16);
			WinYield();
			timer += 16.666 * 2;
			//printf("timer: %f\r\n", timer / 1000);
		} while (timer < 16.66666 * 120 * 5);


		Player1->Vibrate(65535, 0, true);

		timer = 0;
		do
		{
			Sleep(16);
			WinYield();
			timer += 16.666 * 2;
			//printf("timer: %f\r\n", timer / 1000);
		} while (timer < 16.66666 * 120 * 5);

		Player1->Vibrate(0, 65535, true);

		timer = 0;
		do
		{
			Sleep(16);
			WinYield();
			timer += 16.666 * 2;
			//printf("timer: %f\r\n", timer / 1000);
		} while (timer < 16.66666 * 120 * 5);
	}
}

void Game_Init_Hook()
{
	Game_Init();
	//VibrationTest(Player1);
}

void Game_Display_Hook()
{
	Game_Display();
}

bool skipframe = false;

int playsshatter = 0;

int* ViewportMode = (int*)0x567588;

void Game_Logic_Hook()
{
	skipframe = !skipframe;

	*ViewportMode = -1;

	if (skipframe)
		return;

	Game_Logic();

	if (playsshatter > 0)
	{
		Player1->Vibrate(18000, 18000, 1);
		playsshatter--;
	}
}



void Utils_SetVisibilityInBox_Hook(void* p1, void* p2, bool p3, bool vis)
{
	//maybe skip visibility in box entirely
	if (!options.DisableVisToggle)
		Utils_SetVisibilityInBox(p1, p2, p3, vis);
}

int* ShatterSound = (int*)0x5691a4;
#define GLASS_SHATTER 0x2A
#define DEFAULT_VOLUME 0x2000

void Shatter_MaybeMakeGlassShatterSound()
{
	if (*ShatterSound)
	{
		SFX_PlayX(GLASS_SHATTER, DEFAULT_VOLUME);
		playsshatter = 15;
		*ShatterSound = 0;
	}
}

void Panel_Bail_Hook()
{
	playsshatter = 30;
	Panel_Bail();
}

#define HOOK_LIST_SIZE 128

//list of all hooks
HookFunc hookList[HOOK_LIST_SIZE] = {
	{ 0x458564, SFX_SpoolOutLevelSFX },
	{ 0x452570, SFX_SpoolInLevelSFX },

	{ 0x451F79, Redbook_XARestore2 },
	{ 0x44F41F, Redbook_XARemember2 },
	{ 0x4A94D5, Redbook_XARemember2 },

	{ 0x4CB27E, VIDMENU_Load_Hook },
	{ 0x4CB455, VIDMENU_Load_Hook },
	{ 0x4F3CFA, VIDMENU_Load_Hook },

	{ 0x4CB3E3, VIDMENU_Save_Hook },
	{ 0x4CC4C3, VIDMENU_Save_Hook },
	{ 0x4F3D3E, VIDMENU_Save_Hook },

	//hook input func
	{ 0x4E1CC6, GenPsxPadData_Hook },

	//{ 0x46DFEC, Land_Sound },
	//{ 0x497DC8, Land_Sound },

	{ 0x453903,	WINMAIN_SwitchResolution_Hook },
	{ 0x45391B, WINMAIN_SwitchResolution_Hook },
	{ 0x46A8E7, WINMAIN_SwitchResolution_Hook },
	{ 0x46AE23, WINMAIN_SwitchResolution_Hook },

	{ 0x4645b8, M3dInit_SetResolution },
	{ 0x430466, M3dInit_SetResolution },

	{ 0x468823, Panel_Display_Hook },
	{ 0x460bf7, RenderSuperItemShadow_Hook },
	{ 0x4b4a24, Career_GetPointCost_Hook },
	{ 0x4707b0, Career_GetPointCost_Hook },
	{ 0x41580c, Career_GetPointCost_Hook },
	{ 0x48ef74, CBruce_StartGrind_Hook },
	{ 0x49c288, CBruce_HandleJump_Hook },

	//all calls from PlayAway
	{ 0x46a331, Game_Init_Hook },
	{ 0x46a3ef, Game_Logic_Hook },
	{ 0x46a407, Game_Display_Hook },

	{ 0x004c3608, Utils_SetVisibilityInBox_Hook },
	{ 0x004c3632, Utils_SetVisibilityInBox_Hook },

	{ 0x469f4c, Shatter_MaybeMakeGlassShatterSound },

	{ 0x48d4a5, Panel_Bail_Hook },

	{ 0x00414d2d, Career_AwardGoalGap }, //from Career_AwardGap
	{ 0x0048c12d, Career_AwardGoalGap }, //from Panel_Land
};


//loops through the list of hooks and redirects the call
void SetHooks()
{
	for (int i = 0; i < HOOK_LIST_SIZE; i++)
		if (hookList[i].address != NULL)
			CPatch::RedirectCall(hookList[i].address, hookList[i].func);
}




int __cdecl ExecuteCommandListProxy(unsigned __int16 *a1, int a2, int a3)
{
	//fout1 << *a1 << ", " << a2 << ", " << a3 << endl;

	//turn teleport into killing zone
	if (*a1 == 300) *a1 = 152;

	//DrawMessage(f, true);
	return ExecuteCommandList(a1, a2, a3);
}


void Redirect_ExecuteCommandList()
{
	int offs[] = { 
		0x4C1E8C,
		0x4C2240,
		0x4C2C13,
		0x4C52FC,
		0x4C5337
	};

	Proxify(offs, sizeof(offs) / 4, ExecuteCommandListProxy);
}





/*
int __fastcall Vibrate_New(int a1, int a2, int a3, int a4, int a5)
{
	printf("%i\t%i\t%i\t%i\t%i\t\n", a1, a2, a3, a4, a5);
	//printf("motor - %i, power - %i\t", a4, a5);
	//printf("values %i - %i\n", (a4 == 0)*a5*255, (a4 == 1)*a5*255);
	Player1->Vibrate(255*100, 255*100);
	return Vibrate2(a1, a2, a3, a4);
}







void Redirect_Vibrate()
{
	int offs[] = { 
0x413000+0x2B7,
0x413000+0x5C3,
0x48D410+0xB4 ,
0x491B00+0x5A ,
0x4933E0+0x1B2,
0x497B70+0x26A,
0x49CDA0+0xFF ,
0x49CDA0+0x1BC,
0x4BB6B0+0xB00
	};

	Proxify(offs, sizeof(offs) / 4, Vibrate_New);
}

*/


//move to pad.cpp

char _cdecl Pad_ActuatorOn1(int index, int a2, int motor, int a4)
{
	//printf("Pad_ActuatorOn: index=%i\ta2=%i\tmotor=%i\ta4=%i\t\n", index, a2, motor, a4);
	//printf("motor - %i, power - %i\t", a4, a5);
	//printf("values %i - %i\n", (a4 == 0)*a5*255, (a4 == 1)*a5*255);

	Player1->Vibrate(255*100, 255*100, options.Vibration);
	//Vibrate2(index, a2, motor, a4);

	return 0;
}


void Redirect_ActuatorOn1()
{
	int offs[] = { 
		0x48D8EB
	};

	Proxify(offs, sizeof(offs) / 4, Pad_ActuatorOn1);
}


char _cdecl Pad_ActuatorOff1(int a1, int a2)
{
	//printf("Pad_ActuatorOff: %i\t%i\n", a1, a2);
	//printf("motor - %i, power - %i\t", a4, a5);
	//printf("values %i - %i\n", (a4 == 0)*a5*255, (a4 == 1)*a5*255);
	Player1->Vibrate(0, 0, options.Vibration);
	return 0;//Vibrate2(a1, a2, a3, a4);
}


void Redirect_ActuatorOff1()
{
	int offs[] = { 
0x41A020+0x53,
0x41A020+0x5C,
0x41A5F0+0x70,
0x41A5F0+0x79,
0x44DF30+0x11F,
0x44DF30+0x128,
0x44E3B0+0x8F,
0x44E3B0+0x98,
0x44EA50+0x33A,
0x44EA50+0x342,
0x487300+0x16,
0x487300+0x1F,
0x487300+0x38,
0x487300+0x41
	};

	Proxify(offs, sizeof(offs) / 4, Pad_ActuatorOff1);
}








/*
char *__cdecl Spool_LoadPSH(const char *a1, int a2, int a3, int a4, int a5)
{
	char v7[256];
	char path[] = "skaters\\";
	sprintf(v7, "%s%s.psh", path, a1);
	int v5 = FileIO_OpenLoad(v7, 1);
	return Spool_LoadPSHBuffer(v5, a1, a2, a3, a4, a5);
}
*/


LRESULT __stdcall ProxyWinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{

	//fout1 << Msg << " " << wParam << " " << lParam << endl;

	if (GetAsyncKeyState(VK_F4) < 0)
	{
		//fout1 << "got alt...";

		if (GetAsyncKeyState( VK_F4 ) < 0)
		{
			//fout1 << "and shift!";
			PostQuitMessage(0);
			Msg = WM_CLOSE;
		}

		//fout1 << endl;
	}

	//if (Msg == WM_SYSKEYDOWN) fout1 << "keyup" << endl;
	//if (Msg == WM_SYSKEYUP) fout1 << "keydown" << endl;
	//fout1 << Msg << endl;
	return DefWindowProc(hWnd, Msg, wParam, lParam);

	//return WindowProc(hWnd, Msg, wParam, lParam);
}


/*
WPARAM WinYield_Messages()
{
  WPARAM result; // eax@7
  struct tagMSG Msg; // [sp+10h] [bp-1Ch]@1

  if ( PeekMessageA(&Msg, hWND, 0, 0, 0) )
  {
    while ( GetMessageA(&Msg, hWND, 0, 0) )
    {
      if ( Msg.message != 260 && Msg.message != 261 )
      {
        TranslateMessage(&Msg);
        DispatchMessageA(&Msg);
      }
      if ( !PeekMessageA(&Msg, hWND, 0, 0, 0) )
        goto LABEL_7;
    }
    result = Msg.wParam;
  }
  else
  {
LABEL_7:
    result = 117;
  }
  return result;
}
*/
/*
void PatchWinMessages()
{
	CPatch::RedirectCall(0x4F4D70, WinYield_Messages);
}
*/


const string skaters[] = {
	"hawk3", "hawk4",
	"burnq4", "",
	"ca3", "ca4",
	"campb3", "campb4",
	"glif3", "glif4",
	"koston3", "koston4",
	"lasek3", "lasek4",
	"mullen3", "mullen4",
	"muska3", "muska4",
	"rynld3", "rynld4",
	"rowley3", "rowley4",
	"steam3", "steam4",
	"thomas3", "thomas4",
	"", "",
	"", "",
	"", "",
	"", "",
	"dick3", "",
	"", ""
};

/*
struct Costume
{
	char* style;
	char* styleLow;
}


struct Board
{
	char* image_name;
	char* name;
	int u1;
	int stat1;
	int stat2;
	int stat3;
	int u2;
	int u3;
}

//should be 0x170 bytes long
struct SkaterProfile
{
	Costume style[4];   //24
	char name[32];      //32
	char* short_name;   //4
	Board board[8];     //256
	byte stats[10];     //10
	bool unknown;       //1
    bool unknown2;      //1
	char* face;			//4
	int* bioPtr;		//4
}
*/

/*
void OldPatchSkaters()
{
	int profilesPtr = 0x5371B8;

	for (int i = 0; i<19; i++)
	{
		CPatch::SetInt(profilesPtr + i*0x170 + 16, skaters[i*2] == "" ? 0 : (int)&skaters[i*2][0u]);
		CPatch::SetInt(profilesPtr + i*0x170 + 16 + 8, skaters[i*2 + 1] == "" ? 0 : (int)&skaters[i*2 + 1][0u]);
	}

}
*/


/*


typedef struct
{
	short gapType;
	short careerFlag;
	short index;
	short score;
	char name[64];

} GapEntry;

int gapsPtr = 0x53E718;

GapEntry * gapPtr = (GapEntry*)gapsPtr;



*/

	string bam1 = "ba3";
	string bam2 = "ba4";
	string bam3 = "fry";
	string wolve = "wolve";
	string lilper = "lilper";

	string kor1a = "white";
	string kor1b = "white2";
	string kor2a = "red";
	string kor2b = "red2";
	string kor3a = "blue";
	string kor3b = "blue2";
	string kor4a = "black";
	string kor4b = "black2";

	string mcsqueeb = "secret4";



string ba3 = "ba3";
string ba4 = "ba4";

const int numSkaters = 19;
int Skater[numSkaters];

void PatchSkaters()
{
	Skater[0] = 0x5371B8;

	for (int i = 1; i<numSkaters; i++) 
		Skater[i] = Skater[i-1]+0x170; 

	for (int i = 0; i<numSkaters; i++)
	{
		CPatch::SetInt(Skater[i] + 16, skaters[i*2] == "" ? 0 : (int)&skaters[i*2][0u]);
		CPatch::SetInt(Skater[i] + 16 + 8, skaters[i*2 + 1] == "" ? 0 : (int)&skaters[i*2 + 1][0u]);
	}



	int k = 17;

	if (options.DickSwap == "bam")
	{
		CPatch::SetInt(Skater[k], (int)&bam1[0]);
		CPatch::SetInt(Skater[k] + 8, (int)&bam2[0]);
		CPatch::SetInt(Skater[k] + 16, (int)&bam3[0]);
		CPatch::SetInt(Skater[k] + 24, 0);

		char *bamname = (char*)(Skater[k] + 32);
		sprintf(bamname, "Bam Margera");
	}

	if (options.DickSwap == "wolve")
	{
		CPatch::SetInt(Skater[k], (int)&wolve[0]);
		CPatch::SetInt(Skater[k] + 8, 0);
		CPatch::SetInt(Skater[k] + 16, 0);
		CPatch::SetInt(Skater[k] + 24, 0);

		char *bamname = (char*)(Skater[k] + 32);
		sprintf(bamname, "Wolverine");
	}

	if (options.DickSwap == "lilper")
	{
		CPatch::SetInt(Skater[k], (int)&lilper[0]);
		CPatch::SetInt(Skater[k] + 8, 0);
		CPatch::SetInt(Skater[k] + 16, 0);
		CPatch::SetInt(Skater[k] + 24, 0);

		char *bamname = (char*)(Skater[k] + 32);
		sprintf(bamname, "Little Pesron");
	}

	if (options.DickSwap == "kor1")
	{
		CPatch::SetInt(Skater[k], (int)&kor1a[0]);
		CPatch::SetInt(Skater[k] + 8, (int)&kor2a[0]);
		CPatch::SetInt(Skater[k] + 16, (int)&kor3a[0]);
		CPatch::SetInt(Skater[k] + 24, (int)&kor4a[0]);

		char *bamname = (char*)(Skater[k] + 32);
		sprintf(bamname, "Fin K. L.");

		int *sex = (int*)(Skater[k] + 32 + 0x13C);
		*sex = 0x61;
	}

	if (options.DickSwap == "kor2")
	{
		CPatch::SetInt(Skater[k], (int)&kor1b[0]);
		CPatch::SetInt(Skater[k] + 8, (int)&kor2b[0]);
		CPatch::SetInt(Skater[k] + 16, (int)&kor3b[0]);
		CPatch::SetInt(Skater[k] + 24, (int)&kor4b[0]);

		char *bamname = (char*)(Skater[k] + 32);
		sprintf(bamname, "Fin K. L.");

		int *sex = (int*)(Skater[k] + 32 + 0x13C);
		*sex = 0x61;
	}

	if (options.DickSwap == "mcsqueeb")
	{
		CPatch::SetInt(Skater[k], (int)&mcsqueeb[0]);
		CPatch::SetInt(Skater[k] + 8, 0);
		CPatch::SetInt(Skater[k] + 16, 0);
		CPatch::SetInt(Skater[k] + 24, 0);

		char *bamname = (char*)(Skater[k] + 32);
		sprintf(bamname, "McSqueeb");
	}

}

int __cdecl AppendExt(char *a1, char* a2)
{
	char lol[256];
	sprintf(lol, "%s%s%s", "parks\\", a1, a2);
	a1 = lol;
	//fout1 << a1 << endl;
	return 0;
}

void Redirect_AppendExt()
{
	int offs[] = { 
		0x4F31F7,
		0x4F3335,
		0x4F344E,
		0x4F35C9
	};

	Proxify(offs, sizeof(offs) / 4, AppendExt);
}


//main patch func

void Patch()
{
	if (!options.BigDrop)
		CPatch::Nop(0x48F419, 0x48F430 - 0x48F419); //nops whole bail/award big drop path

	if (options.UnlockFPS)
	{
		CPatch::SetChar(0x004cddd7, 0); //sets vblank difference to 0 in D3D_BeginScene
		//CPatch::SetChar(0x004CDDE0, (char)0xEB); //0x73 original, jumps over Sleep()

		//main menu patch, changes 2 frames to 1, gotta find a better way to make it for all menus
		CPatch::SetChar(0x46af9c + 2, 1);
		CPatch::SetChar(0x46afb4 + 2, 1);
	}

	if (options.SkipIntro)
		CPatch::Nop(0x46A732, 5); //nops IntroMovies func

	if (options.AddSkins)
		PatchSkaters();  // adds skater styles

	if (options.SeparateSaves)
	{
		char* savename = (char*)0x52fa30;
		memcpy(savename, &options.CurrentGame[0], options.CurrentGame.length()); //replaces THPS2 in saves with currentgame
	}

	ParseLevels(); //changes levels


	Player1 = new CXBOXController(1);

	//CPatch::SetChar(0x498707, 0x92);

	//enlarges available Fog range
	CPatch::SetChar(0x4CC4A4, 10);
	CPatch::SetInt(0x4CC49C, 750);

	//removes "shutting down thps2" delay
	CPatch::SetInt(0x4F5145, 0);

	//should remove polylimit error
	int* polyLimit = (int*)0x4301EF;
	int polyLimitVal = *polyLimit;
	CPatch::SetInt(0x4301EF, polyLimitVal + 0x10000);


	//DirectDrawCreateEx(NULL, (VOID *)&lpDD, 0x29D6FD0, NULL);
	//lpDD->SetDisplayMode(640, 480, 16);


	if (options.Force32bpp)
	{
		//changes hardcoded 16bpp ddraw values to 32
		CPatch::SetChar(0x004F4004, 32); //in WINMAIN_SwitchResolution
		CPatch::SetChar(0x004F4026, 32); //in WINMAIN_SwitchResolution
		//CPatch::SetChar(0x004F4AC1, 32); //in ??
		CPatch::SetChar(0x004F54B0, 32); //in InitDirectDraw7
		CPatch::SetChar(0x004F54D2, 32); //in InitDirectDraw7
	}

	//silly sets random initial seed. probably better replace rnd func
	//CPatch::SetInt(0x4524BE, rand());
	//CPatch::SetInt(0x458586, rand());
	//CPatch::SetInt(0x468DE4, rand());

	if (options.DisableNewTex)
	{
		//change newbmp pointers null
		CPatch::SetInt(0x4d60b5, 0);

		//change newtex pointers null
		CPatch::SetInt(0x4d6051, 0);
		CPatch::SetInt(0x4d607b, 0);
	}


	//this patches resolution, probably not needed anymore
	//CPatch::SetInt(0x0046A891, 2);

	int* hW2 = (int*)0x4f5496;
	int* hH2 = (int*)0x4f54a0;

	CPatch::SetInt((int)hW2, options.ResX);
	CPatch::SetInt((int)hH2, options.ResY);

	CPatch::SetInt((int)hW, options.ResX);
	CPatch::SetInt((int)hH, options.ResY);

	CPatch::SetInt((int)ScreenWidth, options.ResX);
	CPatch::SetInt((int)ScreenHeight, options.ResY);

	*ScreenWidth = options.ResX;
	*ScreenHeight = options.ResY;


	//hooks related to soundtrack, revisit
	Redirect_Redbook_XAUpdateVolume();
	Redirect_Redbook_XABeginFade();
	Redirect_Redbook_XANextTrack();
	Redirect_PCMOVIE_XAPlay();

	SetHooks();

	//Redirect_Ollie_Sound();
	//Redirect_Land_Sound();

	Redirect_ExecuteCommandList();


	Redirect_ActuatorOn1();
	Redirect_ActuatorOff1();
	//Redirect_Vibrate();
	//Redirect_SwitchResolution();
}


int levelsPtr = 0x538FF8;
int numLevels = 15;

typedef struct
{
	char name[64];
	char * subname;
	char * shortname;
	int isCompetition; //bool
    char* trgfile;
	int compScore[3];
	int compAward[3];
	char* renderthumb;
    int u2;
    int u3;
    int u4;
    char* thumb;
    int cashtounlock;
    int medalstounlock;
    int isCompetition2; //bool
    int somedata[4];
    int index;
    int somedata2[5];
    int u5;
    int u6;
    char goal[10*0x18];
    int killers;
} LevelProfile;

LevelProfile * levPtr = (LevelProfile*)levelsPtr;

string SQLite_GetString(sqlite3_stmt* stmt, int col, string def)
{
	if (sqlite3_column_type(stmt, col) != SQLITE_NULL)
		return string((char*)sqlite3_column_text(stmt, col));

	return def;
}

void ParseLevels()
{

	//levPtr[8] = levPtr[0];
	//levPtr[8].shortname = "mall";


	sqlite3 *db;
    sqlite3_stmt* stmt;
	
    if(sqlite3_open("patch/thps.db", &db) != SQLITE_OK) {
		printf("ERROR: can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
		return;
    }

	string query = "select * \nfrom LevelProfile \nwhere game = lower('" + options.CurrentGame + "') \norder by slot limit 15\n";
	printf("Query:\n%s\n", query);

	// compile sql statement to binary
    if(sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
		printf("ERROR: while compiling sql: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		sqlite3_finalize(stmt);
		return;
    }

   int cnt = 0;

   int ret_code = 0;

    while((ret_code = sqlite3_step(stmt)) == SQLITE_ROW) {

		sprintf(levPtr[cnt].name, (char*)sqlite3_column_text(stmt, 3));

		//short name actually used for VAB loading, workaround needed
		//levPtr[cnt].shortname = (char *)&(new string((char*)sqlite3_column_text(stmt, 1)))[0];

		levPtr[cnt].subname = (char *)(new string(SQLite_GetString(stmt, 4, "")));
		levPtr[cnt].trgfile = (char *)(new string(SQLite_GetString(stmt, 5, "skhan_t")));

		levPtr[cnt].thumb = (char *)&(new string((char*)sqlite3_column_text(stmt, 6)))[0];
		levPtr[cnt].renderthumb = (char *)&(new string((char*)sqlite3_column_text(stmt, 7)))[0];
		levPtr[cnt].isCompetition = sqlite3_column_int(stmt, 8);
		levPtr[cnt].isCompetition2 = levPtr[cnt].isCompetition;
		//levPtr[cnt].isCompetition = 1;
		//levPtr[cnt].isCompetition2 = 1;

		printf("Level %i is %s %s\n", cnt, levPtr[cnt].name, levPtr[cnt].subname);

		//fout1 << (char*)sqlite3_column_text(stmt, 4) << "|" << levPtr[cnt].subname << endl;
		cnt++;

	}
    if(ret_code != SQLITE_DONE) {
        //this error handling could be done better, but it works
        printf("ERROR: while performing sql: %s\n", sqlite3_errmsg(db));
        printf("ret_code = %d\n", ret_code);
    }
	
	sqlite3_close(db);	
}

char query[256];

void GetSong(int num)
{
	sqlite3 *db;
    sqlite3_stmt* stmt;
	
    if(sqlite3_open("patch/music.db", &db) != SQLITE_OK) {
		printf("ERROR: can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
		return;
    }



	sprintf(query,
		"select * from ( SELECT * FROM SoundTrack where lower(game) like lower('%s') order by game, slot limit %i ) order by  game desc, slot desc limit 1", 
		options.SeparateTracks ? options.CurrentGame.c_str() : "%", num);

	printf("%s\n", query);

    if(sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
		printf("ERROR: while compiling sql: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		sqlite3_finalize(stmt);
		return;
    }


	int ret = 0;


    while((ret = sqlite3_step(stmt)) == SQLITE_ROW) {
		song.slot = sqlite3_column_int(stmt, 1);

		string* kek = new string((char*)sqlite3_column_text(stmt, 2));
		song.artist = *kek;

		string* kek2 = new string((char*)sqlite3_column_text(stmt, 3));
		song.title = *kek2;

	    string* kek3 = new string((char*)sqlite3_column_text(stmt, 4));
		song.filename = *kek3;
	}
    if(ret != SQLITE_DONE) {
        //this error handling could be done better, but it works
        printf("ERROR: while performing sql: %s\n", sqlite3_errmsg(db));
        printf("ret_code = %d\n", ret);
    }
	
	//printf("Random song: %s - %s - %s\n", &song.artist[0], &song.title[0], &song.filename[0]);

	sqlite3_close(db);
}

int CountSongs()
{
	sqlite3 *db;
    sqlite3_stmt* stmt;
	
    if(sqlite3_open("patch/music.db", &db) != SQLITE_OK) {
		printf("ERROR: can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
		return 0;
    }

	sprintf(
		query, 
		"select count(*) from soundtrack where lower(game) like lower('%s')", 
		options.SeparateTracks ? options.CurrentGame.c_str() : "%");

	printf("%s\n", query);

    if(sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
		printf("ERROR: while compiling sql: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		sqlite3_finalize(stmt);
		return 0;
    } 


	int ret = 0;

	int nums = 0;


    while((ret = sqlite3_step(stmt)) == SQLITE_ROW) {

		//there should be 1 row, you know.
		nums = sqlite3_column_int(stmt, 0);
	}
    if(ret != SQLITE_DONE) {
        //this error handling could be done better, but it works
        printf("ERROR: while performing sql: %s\n", sqlite3_errmsg(db));
        printf("ret_code = %d\n", ret);
    }
	
	sqlite3_close(db);

	printf("count songs : %i", nums);

	return nums;
}