#include "stdafx.h"
//system includes
#include <iostream>
#include <fstream>
#include "string.h"
//lib includes
#include "lib/sqlite/sqlite3.h"
#include "lib/xinput/CXBOXController.h"
//thawk2 includes
#include "thawk2/_old.h"
#include "thawk2/Career.h"
#include "thawk2/IO/FileIO.h"
#include "thawk2/Mess.h"
#include "thawk2/Mem.h"
#include "thawk2/Redbook.h"
#include "thawk2/Sfx.h"
#include "thawk2/PCInput.h"
#include "thawk2/globals.h"
#include "thawk2/Shatter.h"
#include "thawk2/WinMain.h"
#include "thawk2/Redbook.h"
#include "thawk2/Physics.h"
//patch includes
#include "hawk2_utils.h"
#include "cpatch.h"
#include "GameOptions.h"
#include "mydebug.h"
#include "patchStuff.h"
#include "thawk2/CBruce.h"


//the old bigass all-in-one file, that should be cut into pizzas. this is my plastic fork!

using namespace std;

GameOptions options;

void ParseLevels();
void GetSong(int num);
int CountSongs();

int framesToVibrate = 0;


void Proxify(int offs[], int count, void* func)
{
	for (int i = 0; i < count; i++)
		CPatch::RedirectCall(offs[i], func);
}


#pragma region patched redbook stuff, move to redbook.cpp

//int totalTracks = 0;
int playingTrack = -1;

string playingName;
string playingFile;

typedef struct {
    int slot;
    string artist;
	string title;
    string filename;
} Song;

Song song;

void Redbook_XARemember_New(SONG_POS* pos)
{
	Redbook_XARemember(pos);
}

void Redbook_XAPause_New(bool state)
{
	Redbook_XAPause(state);
}

void Redbook_XAStop_New()
{
	Redbook_XAStop();
}

void Redbook_XARestore2(SONG_POS* pos)
{
	Redbook_XARestore(pos);
}

void Redbook_XAUpdateVolume_New()
{
	Redbook_XAUpdateVolume();
}

void Redbook_XABeginFade_New()
{
	if (!options.Fade) return;
	Redbook_XABeginFade();
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

	if (*XALEVEL > 0)
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
			do newTrack = rand() % options.totalTracks;
			while (newTrack == playingTrack);

			playingTrack = newTrack;
		}

		int newXA = playingTrack + 16;

		//GetTrackInfo(playingTrack);

		GetSong(playingTrack+1);

		playingName = song.artist + " - " + song.title;
		playingFile = song.filename;

		//printf("Now playing: %s\n", playingName);

		if (options.ShowTitle && options.ShowHUD)
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




void PCMOVIE_XAPlay2(int group, int channel)
{
	int curTrack = channel + group * 8;

	//ambience track?
	if (curTrack < 15)
	{
		char buf[256];
		sprintf(buf, "%s%02i%s", "ltix", curTrack, ".dat");
		PCMOVIE_StartMusic(buf);
	}
	else
	{
		PCMOVIE_StartMusic(&playingFile[0u]);
	}
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

	Proxify(offs, sizeof(offs) / 4, Redbook_XAUpdateVolume_New);
}

void Redirect_Redbook_XABeginFade()
{
	int offs[] = {
		0x427130, //credits
		0x466BA7  //game_over
	};

	Proxify(offs, sizeof(offs) / 4, Redbook_XABeginFade_New);
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

#pragma endregion 




void* FontManager_LoadFont(char* filename)
{
	void* pData = Mem_New(FileIO_Open(filename), 0, 1, 0);
	FileIO_Load(pData);
	FileIO_Sync();

	void* pFont = FontManger_LoadFont2(pData, filename);
	Mem_Delete(pData);

	return pFont;
}


//this is from physics.h
#pragma region terrain sound handlers

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

void Ollie_Sound(Terrain terrain)
{
	switch (terrain)
	{
		case Terrain::Concrete: SFX_PlayX(OllieConcrete, 0x2000, 0);
		case Terrain::Tile:
		case Terrain::Wood: SFX_PlayX(OllieWood, 0x2000, 0);		//ollieWoodA
		case Terrain::Dirt:
		case Terrain::Grass: SFX_PlayX(LandDirt, 0x2000, 0);
		case Terrain::Metal: SFX_PlayX(OllieMetal, 0x2000, 0);	//C7 00
		case Terrain::Water: SFX_PlayX(OllieWater, 0x2000, 0);	//water --
		default: SFX_PlayX(OllieConcrete, 0x2000, 0);	//CollieD
	}
}

void Land_Sound(Terrain terrain)
{
	switch (terrain)
	{
		case Terrain::Wood:
		case Terrain::Gravel: SFX_PlayX(LandWood, 0x2000, 0); break;
		case Terrain::Metal: SFX_PlayX(LandMetal, 0x2000, 0); break;
		case Terrain::Dirt:
		case Terrain::Grass: SFX_PlayX(LandDirt, 0x2000, 0); break;
		case Terrain::Water: SFX_PlayX(LandWater, 0x2000, 0); break;
		default: SFX_PlayX(LandConc, 0x2000, 0);
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

#pragma endregion


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


//move to globals?

int* hW2 = (int*)0x4f5496;
int* hH2 = (int*)0x4f54a0;

short* _Xres = (short*)0x55ed00;
short* _Yres = (short*)0x55ed18;

int* _PixelAspectX = (int*)0x5606cc;
int* _PixelAspectY = (int*)0x5606d0;


void M3dInit_SetResolution(int width, int height)
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

#pragma region xinput processing
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
	L3			= 0x0200, //?
	R3			= 0x0400, //?
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

CXBOXController* Player1;

void XInput_Press(PadButton button)
{
	*p1pad |= (ushort)button;
}

#define ANGLE_ALLOWANCE 22.5

bool StickInRange(int stick, int degree)
{
	return degree - ANGLE_ALLOWANCE < stick && stick <= degree + ANGLE_ALLOWANCE;
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

		//process sticks a bit smarter than linear
		int x = state.Gamepad.sThumbLX;
		int y = state.Gamepad.sThumbLY;

		int magnitude = sqrt(x * x + y * y);
		int stickAngle = atan2(x, y) * 180.f / 3.1415f;

		if (magnitude > options.StickDeadzone)
		{
			if (StickInRange(stickAngle, 0))	XInput_Press(PadButton::PovUp);
			if (StickInRange(stickAngle, -45))	XInput_Press(PadButton::PovUpLeft);
			if (StickInRange(stickAngle, -90))	XInput_Press(PadButton::PovLeft);
			if (StickInRange(stickAngle, -135)) XInput_Press(PadButton::PovDownLeft);
			if (StickInRange(stickAngle, 45))	XInput_Press(PadButton::PovUpRight);
			if (StickInRange(stickAngle, 90))	XInput_Press(PadButton::PovRight);
			if (StickInRange(stickAngle, 135))	XInput_Press(PadButton::PovDownRight);
			if (180 - ANGLE_ALLOWANCE < stickAngle && stickAngle <= 180) XInput_Press(PadButton::PovDown);
			if (-180 < stickAngle && stickAngle <= -180 + ANGLE_ALLOWANCE) XInput_Press(PadButton::PovDown);
		}

		//process start and select
		if (Player1->PressedBack()) XInput_Press(PadButton::Select);
		if (Player1->PressedStart()) XInput_Press(PadButton::Start);

		//process shoulders and triggers
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) XInput_Press(PadButton::L1);
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) XInput_Press(PadButton::R1);

		//is trigger deadzone a thing?
		if (state.Gamepad.bLeftTrigger > 1) XInput_Press(PadButton::L2);
		if (state.Gamepad.bRightTrigger > 1) XInput_Press(PadButton::R2);

		//R3 - skip track
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
		{
			XInput_Press(PadButton::R3);

			if (!*InFrontEnd && !*GamePaused)
				if (!(Player1->GetOldState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB))
					Redbook_XANextTrack2(1);
		}

		//L3
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
		{
			//CVector* pos = CBruce_GetPosition((int*)(*(int*)GSkater));
			//pos->Y -= state.Gamepad.sThumbRY * 10;

			XInput_Press(PadButton::L3);
		}
	}
}



//move to pad.cpp

void PCINPUT_ActuatorOn_Hook(int index, int time, int motor, int value)
{
	printf("index: %i time: %i motor: %i value: %i\r\n", index, time, motor, value);

	PCINPUT_ActuatorOn(index, time, motor, value);
	
	if (time > framesToVibrate)
		framesToVibrate = time * (options.UnlockFPS ? 2 : 1);

	//this is weird, fix for rails
	if (value == 1)
		value = 128;

	Player1->Vibrate(motor == 0 ? value / 255.0 * 65535.0 : 0, motor == 1 ? value / 255.0 * 65535.0 : 0, options.Vibration);
}


void PCINPUT_ActuatorOff_Hook(int index, int motor)
{
	if (framesToVibrate == 0)
	{
		//printf("PCINPUT_ActuatorOff %i %i\r\n", index, motor);
		Player1->Vibrate(0, 0, options.Vibration);
	}
}

#pragma endregion


#pragma region various hooks

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


void Game_Logic_Hook()
{
	skipframe = !skipframe;

	Game_Logic();

	if (options.DisableSky)
		Backgrnd_Off(0);

	if (framesToVibrate > 0)
		framesToVibrate--;

	//CBruce_BoardOff(&GSkater);
}



void Utils_SetVisibilityInBox_Hook(void* p1, void* p2, bool p3, bool vis)
{
	//maybe skip visibility in box entirely
	if (!options.DisableVisToggle)
		Utils_SetVisibilityInBox(p1, p2, p3, vis);
}


void Panel_Bail_Hook()
{
	//gotta add continuous vibration queue to xinput
	//playsshatter = 30;
	Panel_Bail();
}


void ExecuteCommandList_Hook(short *node, int p2, int p3)
{
	//turn teleport into killing zone
	if (*node == 300)
		*node = 152;

	ExecuteCommandList(node, p2, p3);
}



LRESULT ProxyWinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
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

#pragma endregion

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

#pragma region patch skaters

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

#pragma endregion

#pragma region patch levels

int numLevels = 15;



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
	
    if(sqlite3_open(".\\patch\\thps.db", &db) != SQLITE_OK) {
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

		sprintf(Levels[cnt].name, (char*)sqlite3_column_text(stmt, 3));

		//short name actually used for VAB loading, workaround needed
		//levPtr[cnt].shortname = (char *)&(new string((char*)sqlite3_column_text(stmt, 1)))[0];

		Levels[cnt].subname = (char *)(new string(SQLite_GetString(stmt, 4, "")));
		Levels[cnt].trgfile = (char *)(new string(SQLite_GetString(stmt, 5, "skhan_t")));

		Levels[cnt].thumb = (char *)&(new string((char*)sqlite3_column_text(stmt, 6)))[0];
		Levels[cnt].renderthumb = (char *)&(new string((char*)sqlite3_column_text(stmt, 7)))[0];
		Levels[cnt].isCompetition = sqlite3_column_int(stmt, 8);
		Levels[cnt].isCompetition2 = Levels[cnt].isCompetition;
		//levPtr[cnt].isCompetition = 1;
		//levPtr[cnt].isCompetition2 = 1;

		printf("Level %i is %s %s\n", cnt, Levels[cnt].name, Levels[cnt].subname);

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

#pragma endregion

#pragma region patch music

char query[256];

sqlite3* db;
sqlite3_stmt* stmt;

int x = 16;

void GetSong(int num)
{
	if (db == NULL)
		if(sqlite3_open_v2("patch/music.db", &db, SQLITE_OPEN_READONLY, NULL) != SQLITE_OK) {
			printf("ERROR: can't open database: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return;
		}


	if (stmt == NULL)
	{
		sprintf(query,
			"select * from ( SELECT * FROM SoundTrack where lower(game) like lower(@game) order by game, slot limit @num ) order by game desc, slot desc limit 1");
	}

	sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);

	if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
		printf("ERROR: while compiling sql: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		sqlite3_finalize(stmt);
		return;
	}

	sqlite3_bind_parameter_index(stmt, "@game");
	sqlite3_bind_parameter_index(stmt, "@num");

	if (options.SeparateTracks)
	{
		sqlite3_bind_text(stmt, 1, options.CurrentGame.c_str(), options.CurrentGame.length(), NULL);
	}
	else
	{
		sqlite3_bind_text(stmt, 1, "%", 1, NULL);
	}

	sqlite3_bind_int(stmt, 2, num);


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

	sqlite3_exec(db, "END TRANSACTION", 0, 0, 0);

    if(ret != SQLITE_DONE) {
        //this error handling could be done better, but it works
        printf("ERROR: while performing sql: %s\n", sqlite3_errmsg(db));
        printf("ret_code = %d\n", ret);
    }
	
	//printf("Random song: %s - %s - %s\n", &song.artist[0], &song.title[0], &song.filename[0]);

	//sqlite3_close(db);
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

#pragma endregion

#pragma region main patch stuff 


SGoal* GetGoal(int level, int goal)
{
	SLevel* pLevel = &Levels[level];
	SGoal* pGoal = &pLevel->Goals[goal];

	return pGoal;
}

//main patches func, sets all hooks and changes vars needed
void Patch()
{
	//doesnt seem to work
	//Career_ClearGameWithEveryone();

	if (!options.BigDrop)
		//nops entire bail/award big drop path, since its a part of a func, not a separate one
		CPatch::Nop(0x48F419, 0x48F430 - 0x48F419); 

	if (!options.Manuals)
	{
		//set instant return from thiscall MaybeManual 
		CPatch::SetInt((int)MaybeManual, 0x000008c2);
	}

	if (options.UnlockFPS)
	{
		CPatch::SetChar(0x004cddd7, 0); //sets vblank difference to 0 in D3D_BeginScene
		//CPatch::SetChar(0x004CDDE0, (char)0xEB); //0x73 original, jumps over Sleep()

		//main menu patch, changes 2 frames to 1, gotta find a better way to make it for all menus
		CPatch::SetChar(0x46af9c + 2, 1);
		CPatch::SetChar(0x46afb4 + 2, 1);
	}

	if (options.SkipIntro)
	{
		CPatch::SetChar((int)PCMOVIE_PlayMovieFile, 0xC3);
		//CPatch::Nop(0x46A732, 5); //nops IntroMovies func
	}

	if (options.AddSkins)
		PatchSkaters();  // adds skater styles

	if (options.SeparateSaves)
	{
		char* savename = (char*)0x52fa30;
		memcpy(savename, &options.CurrentGame[0], options.CurrentGame.length()); //replaces THPS2 in saves with currentgame
	}

	ParseLevels(); //changes levels

	/*
	SLevel* level = &Levels[0];

	level->trgfile = "skware_t";
	level->shortname = "ware";
	level->subname = "Woodland Hills";
	level->gapStart = 0;
	level->gapEnd = 10000;

	SGoal* goal = GetGoal(0, 4);
	goal->goalText = "Smash the boxes";
	goal->stringParam = "boxes";

	goal = GetGoal(0, 6);
	goal->goalText = "Bluntslide the big rail";
	goal->stringParam = "Bluntslide";

	goal = GetGoal(0, 7);
	goal->goalText = "Hit 3 transfers";
	goal->stringParam = "transfers";
	*/

	Player1 = new CXBOXController(1);

	//CPatch::SetChar(0x498707, 0x92);
	
	//https://sherief.fyi/post/tony-hawks-pro-cleanup/
	//https://learn.microsoft.com/en-us/windows/win32/winmsg/window-styles
	//removes title bar on win10
	CPatch::SetInt(0x4f500A, WS_VISIBLE | WS_POPUP);

	//enlarges available Fog range in VIDMENU_Load
	CPatch::SetChar(0x4CC4A4, 10);
	CPatch::SetInt(0x4CC49C, 750);

	//removes "shutting down thps2" delay
	//CPatch::SetInt(0x4F5145, 0);
	CPatch::Nop(0x4f5149, 6);

	//editor limit test
	CPatch::SetInt(0x4371f1, 0);

	//supposed to remove polylimit error
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


	//??
	CPatch::SetInt((int)0x524bb0, options.ResX);
	CPatch::SetInt((int)0x524bb4, options.ResY);

	

	CPatch::SetInt((int)hardcodedWidth, options.ResX);
	CPatch::SetInt((int)hardcodedHeight, options.ResY);

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
}




#define HOOK_LIST_SIZE 128

// list of all hooks
HookFunc hookList[HOOK_LIST_SIZE] = {
	//{ 0x458564, SFX_SpoolOutLevelSFX },
	//{ 0x452570, SFX_SpoolInLevelSFX },

	{ 0x451F79, Redbook_XARestore2 },
	{ 0x44F41F, Redbook_XARemember_New },
	{ 0x4A94D5, Redbook_XARemember_New },

	{ 0x4CB27E, VIDMENU_Load_Hook },
	{ 0x4CB455, VIDMENU_Load_Hook },
	{ 0x4F3CFA, VIDMENU_Load_Hook },

	{ 0x4CB3E3, VIDMENU_Save_Hook },
	{ 0x4CC4C3, VIDMENU_Save_Hook },
	{ 0x4F3D3E, VIDMENU_Save_Hook },

	{ 0x4E1CC6, GenPsxPadData_Hook }, //in ReadDirectInput

	//{ 0x46DFEC, Land_Sound },
	//{ 0x497DC8, Land_Sound },

	{ 0x453903,	WINMAIN_SwitchResolution_Hook },
	{ 0x45391B, WINMAIN_SwitchResolution_Hook },
	{ 0x46A8E7, WINMAIN_SwitchResolution_Hook },
	{ 0x46AE23, WINMAIN_SwitchResolution_Hook },

	{ 0x430466, M3dInit_SetResolution }, //in Db_Init
	{ 0x4645b8, M3dInit_SetResolution }, //in M3dInit_InitAtStart

	{ 0x460bf7, RenderSuperItemShadow_Hook },

	{ 0x41580c, Career_GetPointCost_Hook },
	{ 0x4707b0, Career_GetPointCost_Hook },
	{ 0x4b4a24, Career_GetPointCost_Hook },

	{ 0x48ef74, CBruce_StartGrind_Hook }, //in CBruce::HandeStickToRail
	{ 0x49c288, CBruce_HandleJump_Hook }, //in CBruce::DoPhysics

	//all calls in PlayAway
	{ 0x46a331, Game_Init_Hook },
	{ 0x46a3ef, Game_Logic_Hook },
	{ 0x46a407, Game_Display_Hook },

	//both in ExecuteCommandList
	{ 0x004c3608, Utils_SetVisibilityInBox_Hook },
	{ 0x004c3632, Utils_SetVisibilityInBox_Hook },

	{ 0x469f4c, Shatter_MaybeMakeGlassShatterSound }, //in Game_Logic

	{ 0x48d4a5, Panel_Bail_Hook },	//in CBruce::Trick_Bail

	{ 0x468823, Panel_Display_Hook }, // in Display

	/*

	{ 0x414d2d, Career_AwardGoalGap }, //in Career_AwardGap
	{ 0x48c12d, Career_AwardGoalGap }, //in Panel_Land

	{ 0x414643, Career_GiveGoalType },
	{ 0x414bf0, Career_GiveGoalType },
	{ 0x414e72, Career_GiveGoalType },
	{ 0x48b108, Career_GiveGoalType },
	{ 0x48b207, Career_GiveGoalType },
	{ 0x4a614c, Career_GiveGoalType },

	{ 0x402578, Career_GotGoalType },
	{ 0x41462b, Career_GotGoalType },
	{ 0x414d10, Career_GotGoalType },
	{ 0x414d6d, Career_GotGoalType },
	{ 0x414e4c, Career_GotGoalType },
	{ 0x414f3a, Career_GotGoalType },
	{ 0x4152ba, Career_GotGoalType },
	{ 0x469557, Career_GotGoalType },
	{ 0x46956a, Career_GotGoalType },
	{ 0x46957f, Career_GotGoalType },
	{ 0x4b6b6f, Career_GotGoalType },
	{ 0x4b6b7f, Career_GotGoalType },

	{ 0x4a626b, Career_GetLevelPickup }, //in TakeEffect

	{ 0x4166d1, Career_ApplyCheats }, // in Career_PostLoad
	{ 0x4531c7, Career_ApplyCheats }, // in FrontEnd2_Main

	{ 0x450c82, Career_CheatName },
	{ 0x486324,	Career_CheatName },
	{ 0x486387,	Career_CheatName },
	{ 0x48640c,	Career_CheatName },

	{ 0x48975b, Career_CheckScore }, // in DisplayScore

	*/

	{ 0x4C1E8C, ExecuteCommandList_Hook },
	{ 0x4C2240, ExecuteCommandList_Hook },
	{ 0x4C2C13, ExecuteCommandList_Hook },
	{ 0x4C52FC, ExecuteCommandList_Hook },
	{ 0x4C5337, ExecuteCommandList_Hook },

	/*
	{ 0x414b16, Career_GapNumber },
	{ 0x414b55, Career_GapNumber },

	{ 0x48e6ee, Career_AwardGap }, // in CheckForLipGaps
	{ 0x49b53e, Career_AwardGap }, // in HandlehysicsState 
	{ 0x49b5a4, Career_AwardGap }, // in HandlehysicsState 
	{ 0x4c3955, Career_AwardGap }, // in ExecuteCommandList

	{ 0x48c10c, Career_AwardTrickGap }, // in Panel_Land

	{ 0x45c01b, Career_LevelNeeds }, // in GoalScreenElement::setupMessage

	*/

	{ 0x48703b,	PCINPUT_ActuatorOn_Hook }, // in Pad_ActuatorOn
	{ 0x4871d0, PCINPUT_ActuatorOff_Hook }, // in Pad_ActuatorOff

		/*

	{ 0x46a746, FontManager_LoadFont },

	{ 0x0041a084	,	Mess_DeleteAll },
	{ 0x0041a258	,	Mess_DeleteAll },
	{ 0x0041a671	,	Mess_DeleteAll },
	{ 0x0041a76c	,	Mess_DeleteAll },
	{ 0x0041af29	,	Mess_DeleteAll },
	{ 0x0041b578	,	Mess_DeleteAll },
	{ 0x0044e046	,	Mess_DeleteAll },
	{ 0x0044e436	,	Mess_DeleteAll },
	{ 0x0044ed58	,	Mess_DeleteAll },
	{ 0x00458430	,	Mess_DeleteAll },
	{ 0x004a603e	,	Mess_DeleteAll },
	{ 0x004c3247	,	Mess_DeleteAll },

	{ 0x0047366a	,	Mess_DeleteMessage }, //Mess_Remove
	{ 0x00473711	,	Mess_DeleteMessage }, //Mess_Update

	{ 0x0041535f	, Mess_Remove },
	{ 0x0048b228	, Mess_Remove },
	{ 0x004b5da6	, Mess_Remove },
	{ 0x004b5db2	, Mess_Remove },

	{ 0x00469fd7 ,	Mess_Update },  //in Game_Logic

	*/

	//{ 0x473680, CreateMessage }
};

//loops through the list of hooks and redirects the call
void SetHooks()
{
	for (int i = 0; i < HOOK_LIST_SIZE; i++)
	{
		if (hookList[i].address == NULL) break;
		CPatch::RedirectCall(hookList[i].address, hookList[i].func);
	}
}

#pragma endregion