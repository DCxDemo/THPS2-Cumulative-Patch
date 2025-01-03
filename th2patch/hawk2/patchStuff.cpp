#include "stdafx.h"

// system includes
#include <iostream>
#include <fstream>
#include <ddraw.h>
#include "string.h"

// lib includes
#include "lib/sqlite/sqlite3.h"
#include "lib/xinput/CXBOXController.h"

// decomp include
#include "thawk2/thawk2.h"

//patch includes
#include "hawk2_utils.h"
#include "cpatch.h"
#include "GameOptions.h"
#include "mydebug.h"
#include "patchStuff.h"
#include "color.h"
#include "checksum.h"
#include "thawk2/Utils.h"
#include "patch/hook.h"
#include "thawk2/types.h"

using namespace std;


//the old bigass all-in-one file, that should be cut into pizzas. this is my plastic fork!


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


typedef struct SWheelMenuEntry
{
	int Angle;
	int Screen;
	int Unknown;
} SWheelMenuEntry;


#pragma region patched redbook stuff, move to redbook.cpp

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




#pragma endregion 



void* FontManager_LoadFont(char* filename)
{
	void* pData = Mem_New(FileIO::FileIO_Open(filename), 0, 1, 0);
	FileIO::FileIO_Load(pData);
	FileIO::FileIO_Sync();

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


float AutoFOV(float userScale = 1.0f)
{
	float zoom = (4.0f * *_Yres) / (3.0f * *_Xres);
	zoom = zoom + (1.0f - zoom) / 2.0f;

	return zoom * userScale;
}

void M3dInit_SetResolution(int width, int height)
{
	WINMAIN_ScreenDimensions(&width, &height);

	*_Xres = width;
	*_Yres = height;

	//default pixel aspect ratio is 0x1000 (fixed point 1.0)
	//if we are in frontend, we should use calculated aspect ratio
	//if not, the fov scale from options
	//if user doesnt select fov override, it will be 1.0 by default, hence no need to bother here

	int aspect = 0x1000 * AutoFOV(*InFrontEnd ? 1.0 : options.FovScale);

	//printf("aspect: %i\n", aspect);

	*_PixelAspectX = aspect;
	*_PixelAspectY = aspect;
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
		if (options.FastQuit && Player1->PressedBack() && Player1->PressedStart())
		{
			// make sure to disable vibration before we quit
			Player1->Vibrate(0, 0, options.Vibration);

			// shutdown the game gracefully, please
			WINMAIN_ShutDown();

			// and now exit
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

			// we're in gameplay and music is not disabled
			if (!*InFrontEnd && !*GamePaused && *XALEVEL > 0)
				if (!(Player1->GetOldState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB))
					Redbook::Redbook_XANextTrack(1);
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
	//printf("index: %i time: %i motor: %i value: %i\r\n", index, time, motor, value);

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

int old_status = 0;

void Front_Update_Hook()
{
	Front_Update();

	if (old_status != *GStatus)
	{
		//char* t = (char*)*(int*)(statusNames + *GStatus * 4);

		

		printf("status: %s\n", statusNames[*GStatus]);

		old_status = *GStatus;
	}

	//CreateTestMenu();
	//CPatch::SetInt(0x0044ca6f + 2, (int)testMenu);
}


int* D3DBEGINSCENE_lastVBlank = (int*)0x0056b490;
int* gShellMode = (int*)0x006a35b4;

// on the beginning of every frame
void D3D_BeginScene_Hook(uint param_1, uint backColor)
{
	int waitframes = options.UnlockFPS ? 1 : 2;

	if (*Vblanks < *D3DBEGINSCENE_lastVBlank + waitframes) {
		do {
			//Sleep(0);
		} while (*Vblanks < *D3DBEGINSCENE_lastVBlank + waitframes);
	}
	
	*D3DBEGINSCENE_lastVBlank = *Vblanks;

	uint color = 0xff7080a0;

	if ((*gShellMode != 0) || (*GLevel != 6)) {
		color = backColor;
	}

	D3DPOLY_StartScene(param_1, color);
}


CMenu* menu;

/*
char* terrainNames[16] = {

"T_CONCRETE",
"T_TILE",
"T_WOOD",
"T_DIRT",
"T_ASPHALT",
"T_GRASS ",
"T_WATER ",
"T_CHAINLINK ",
"T_BRICK ",
"T_METALPOLE",
"T_GENERIC1 ",
"T_GENERIC2 ",
"T_METAL ",
"T_ROCK",
"T_GRAVEL",
"T_SIDEWALK"
};
*/

// whenever HUD is displayed on the screen
void Panel_Display_Hook()
{
	if (options.ShowHUD)
	{
		Panel_Display();

		if (options.RailBalanceBar)
		{
			CBruce skater = new CBruce(GSkater);

			if ((EPhysicsState)skater.PhysicsState() == EPhysicsState::PHYSICS_ON_RAIL)
			{
				Panel_BalanceRail(skater.RailBalance(), 0x1000,
					30, 6,
					512 / 2, 240 / 3,
					COLOR_RED, COLOR_GREEN,	//BGR color
					true);
			}
		}
	}

	PrintDebugStuff();

	if (menu != NULL)
		delete menu;

	menu = new CMenu((SMenu*)0x0055e8a0);
	//menu->DebugPrint();
	
}

// shadow rendering
void RenderSuperItemShadow_Hook(void* superItem) //CSuper
{
	if (options.DrawShadow)
		RenderSuperItemShadow(superItem);
}

// 
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


// on new level loading
void Game_Init_Hook()
{
	Game_Init();

	// patch autokick
	// https://github.com/PARTYMANX/partymod-thps2/blob/4f2a956ab813c2776dd33beca19edf2048c203f4/src/main.c#L51
	*AutoKickSetting = options.AutoKick;
	*AutoKickState = options.AutoKick;

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


#pragma region [patch skaters]

SkaterProfile* profiles = (SkaterProfile*)0x5371B8;


#define PROSKATER_HAWK 0
#define PROSKATER_BURNQUIST 1
#define PROSKATER_CABALLERO 2
#define PROSKATER_CAMPBELL 3
#define PROSKATER_GLIFBERG 4
#define PROSKATER_KOSTON 5
#define PROSKATER_LASEK 6
#define PROSKATER_MULLEN 7
#define PROSKATER_MUSKA 8
#define PROSKATER_REYNOLDS 9
#define PROSKATER_ROWLEY 10
#define PROSKATER_STEAMER 11
#define PROSKATER_THOMAS 12
#define CAS_SLOT1 13
#define CAS_SLOT2 14
#define CAS_SLOT3 15
#define CAS_SLOT4 16
#define SKATER_SECRET1 17	//dick
#define SKATER_SECRET2 18	//carrera
#define SKATER_SECRET3 19	//spiderman

/*
SBoardInfo BamBoards[] = {
	{ "s2dZe01n.bmp", "Animalism",		0, 1, 1, 1, 0, 0},
	{ "s2dZe02n.bmp", "Arbor",			0, 1, 2, 2, 0, 0},
	{ "s2dZe03n.bmp", "Letterman",		0, 2, 3, 2, 0, 0},
	{ "s2dZe04n.bmp", "Manimal",		0, 3, 3, 3, 0, 0},
	{ "s2dZe05n.bmp", "Squared",		0, 3, 4, 3, 0, 0},
	{ "s2dZe06n.bmp", "Trophy",			0, 4, 4, 4, 0, 0},
	{ "s2dZe07n.bmp", "FutureIsNature", 0, 4, 5, 4, 0, 0},
	{ "s2dZe08n.bmp", "Harvest",		0, 5, 5, 5, 0, 0}
};

SBoardInfo LilPerBoards[] = {
	{ "s2dlp01n.bmp", "clown dance",		0, 1, 1, 1, 0, 0},
	{ "s2dlp02n.bmp", "clown face",			0, 1, 2, 2, 0, 0},
	{ "s2dlp03n.bmp", "clown girlface",		0, 2, 3, 2, 0, 0},
	{ "s2dlp04n.bmp", "clown halfface",		0, 3, 3, 3, 0, 0},
	{ "s2dlp05n.bmp", "clown paint",		0, 3, 4, 3, 0, 0},
	{ "s2dlp06n.bmp", "clown round",		0, 4, 4, 4, 0, 0},
	{ "s2dlp07n.bmp", "clown spin",			0, 4, 5, 4, 0, 0},
	{ "s2dlp08n.bmp", "clown",				0, 5, 5, 5, 0, 0}
};
*/

void PatchSkaters()
{
	SkaterProfile* p = &profiles[0];

	p->styleC_hi = "hawk3";
	p->styleC_lo = "hawk3b";
	p->styleD_hi = "hawk4";
	p->styleD_lo = "hawk4b";

	p++;
	p->styleC_hi = "burnq4";
	p->styleC_lo = "burnq4b";
	//burnquist wasnt in thps3, so no style D model

	p++;
	p->styleC_hi = "ca3";
	p->styleC_lo = "ca3b";
	p->styleD_hi = "ca4";
	p->styleD_lo = "ca4b";

	p++;
	p->styleC_hi = "campb3";
	p->styleC_lo = "campb3b";
	p->styleD_hi = "campb4";
	p->styleD_lo = "campb4b";

	p++;
	p->styleC_hi = "glif3";
	p->styleC_lo = "glif3b";
	p->styleD_hi = "glif4";
	p->styleD_lo = "glif4b";

	p++;
	p->styleC_hi = "koston3";
	p->styleC_lo = "koston3b";
	p->styleD_hi = "koston4";
	p->styleD_lo = "koston4b";

	p++;
	p->styleC_hi = "lasek3";
	p->styleC_lo = "lasek3b";
	p->styleD_hi = "lasek4";
	p->styleD_lo = "lasek4b";

	p++;
	p->styleC_hi = "mullen3";
	p->styleC_lo = "mullen3b";
	p->styleD_hi = "mullen4";
	p->styleD_lo = "mullen4b";

	p++;
	p->styleC_hi = "muska3";
	p->styleC_lo = "muska3b";
	p->styleD_hi = "muska4";
	p->styleD_lo = "muska4b";

	p++;
	p->styleC_hi = "rynld3";
	p->styleC_lo = "rynld3b";
	p->styleD_hi = "rynld4";
	p->styleD_lo = "rynld4b";

	p++;
	p->styleC_hi = "rowley3";
	p->styleC_lo = "rowley3b";
	p->styleD_hi = "rowley4";
	p->styleD_lo = "rowley4b";

	p++;
	p->styleC_hi = "steam3";
	p->styleC_lo = "steam3b";
	p->styleD_hi = "steam4";
	p->styleD_lo = "steam4b";

	p++;
	p->styleC_hi = "thomas3";
	p->styleC_lo = "thomas3b";
	p->styleD_hi = "thomas4";
	p->styleD_lo = "thomas4b";


	//now patch secret skater depending on the selected option

	p = &profiles[SKATER_SECRET1];

	//since we can't have a switch case by string in C, lets just calculate string checksum, used a lot in later games.
	uint hash = checksum(&options.DickSwap[0]);

	printf("%s = 0x%08x\n", &options.DickSwap[0], hash);


	if (options.DickSwap != "none")
	{
		switch (hash)
		{
			//"bam", margera + fry cook
			case 0x680b1a5b: {
				sprintf(p->FullName, "%s", "Bam Margera");
				p->pShortName = "Bam";

				p->styleA_hi = "ba3";
				p->styleA_lo = "ba3b";
				p->styleB_hi = "ba4";
				p->styleB_lo = "ba4b";
				p->styleC_hi = "fry";
				p->styleC_lo = "fryb";

				p->pFaceName = "s2fbam.bmp";

				//memcpy(&p->boards, BamBoards, sizeof(BamBoards));

				break;
			}

			//"wolve", wolverine from th3
			case 0xe4f32b33: {
				sprintf(p->FullName, "%s", "Wolverine");
				p->pShortName = "wolve";

				p->styleA_hi = "wolve";
				p->styleA_lo = NULL;
				p->styleB_hi = NULL;	//since we dont have style B for it, should patch with nulls
				p->styleB_lo = NULL;

				break;
			}

			//"lilper", Little Person from th4
			case 0xadf13666: {
				sprintf(p->FullName, "%s", "Little Person");
				p->pShortName = "lilper";

				p->styleA_hi = "lilper";
				p->styleA_lo = NULL;
				p->styleB_hi = NULL;	//since we dont have style B for it, should patch with nulls
				p->styleB_lo = NULL;

				//memcpy(&p->boards, LilPerBoards, sizeof(LilPerBoards));

				break;
			}

			//kor1, fin k l band style B
			case 0xfd91275c: {
				sprintf(p->FullName, "%s", "Fin K. L.");
				p->pShortName = "finkl";

				p->styleA_hi = "white";
				p->styleA_lo = NULL;
				p->styleB_hi = "red";
				p->styleB_lo = NULL;
				p->styleC_hi = "blue";
				p->styleC_lo = NULL;
				p->styleD_hi = "black";
				p->styleD_lo = NULL;

				break;
			}

			//kor2, fin k l band style B
			case 0x4ff07f11: {
				sprintf(p->FullName, "%s", "Fin K. L.");
				p->pShortName = "finkl";

				p->styleA_hi = "white2";
				p->styleA_lo = NULL;
				p->styleB_hi = "red2";
				p->styleB_lo = NULL;
				p->styleC_hi = "blue2";
				p->styleC_lo = NULL;
				p->styleD_hi = "black2";
				p->styleD_lo = NULL;

				break;
			}

			//mcsqueeb, since tony already has 4 styles, bring this back in
			case 0x92af0067: {
				sprintf(p->FullName, "%s", "McSqueeb");
				p->pShortName = "mcsqueeb";

				p->styleA_hi = "secret4";
				p->styleA_lo = "secret4b";
				p->styleB_hi = NULL;	//since we dont have style B for it, should patch with nulls
				p->styleB_lo = NULL;

				break;
			}

			default:
				printf("Unknown secret skater swap! %s", &options.DickSwap[0]);
		}
	}
	else
	{
		p->styleC_hi = "dick3";
		p->styleC_lo = "dick3b";
	}
}

#pragma endregion


#pragma region patch levels

int numLevels = 15;

char* SQLite_GetString(sqlite3_stmt* stmt, int col, char* def)
{
	if (sqlite3_column_type(stmt, col) != SQLITE_NULL)
	{
		string* cc = new string((const char*)sqlite3_column_text(stmt, col));

		return (char*)cc->c_str();
	}

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

	printf("Query:\n%s\n", &query[0]);

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
		
		Levels[cnt].subname = SQLite_GetString(stmt, 4, "");
		Levels[cnt].trgfile = SQLite_GetString(stmt, 5, "skhan_t");
		Levels[cnt].thumb = SQLite_GetString(stmt, 6, "");
		Levels[cnt].renderthumb = SQLite_GetString(stmt, 7, "");
		
		Levels[cnt].isCompetition = sqlite3_column_int(stmt, 8);
		Levels[cnt].isCompetition2 = Levels[cnt].isCompetition;
		

		//levPtr[cnt].isCompetition = 1;
		//levPtr[cnt].isCompetition2 = 1;

		printf("Level %i is %s %s\n", cnt, Levels[cnt].name, &Levels[cnt].subname[0]);

		//fout1 << (char*)sqlite3_column_text(stmt, 4) << "|" << levPtr[cnt].subname << endl;
		cnt++;
	}

    if (ret_code != SQLITE_DONE) {
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
		Redbook::song.slot = sqlite3_column_int(stmt, 1);

		string* kek = new string((char*)sqlite3_column_text(stmt, 2));
		Redbook::song.artist = *kek;

		string* kek2 = new string((char*)sqlite3_column_text(stmt, 3));
		Redbook::song.title = *kek2;

	    string* kek3 = new string((char*)sqlite3_column_text(stmt, 4));
		Redbook::song.filename = *kek3;
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




Pkr2* pkr;


void* LoadFile(char* filename, bool heap)
{
	//check later why unresolved
	return NULL;
	//return FileIO_OpenLoad_Pkr(filename, heap, pkr);
}


void PatchThps3Gaps()
{
	int ranges[] = {
		2500, //foun
		2000, //can
		2400, //rio
		2300, //air
		2100, //sub
		2200, //si
		1000, //la
		2600, //tok
		2800, //downhill
	};

	for (int i = 0; i < 9; i++)
	{
		Levels[i].gapFirst = ranges[i];
		Levels[i].gapLast = Levels[i].gapFirst + 99;
	}

	//now this is a hacky hack for skate heaven. find proper way to hide it.
	Levels[9].gapFirst = 2500;
	Levels[9].gapLast = 2500;

	CopyGaps(pGapListThps3, pGaps);
}

void PatchThps4Gaps()
{
	int ranges[] = {
		1000, //col
		2000, //sf2
		3000, //alcatraz
		5000, //sewers
		6000, //shipyard
		7000, //kona
		8000, //london
		9000, //lil big world
		1000
	};

	for (int i = 0; i < 9; i++)
	{
		Levels[i].gapFirst = ranges[i];
		Levels[i].gapLast = Levels[i].gapFirst + 999;
	}

	//now this is a hacky hack for skate heaven. find proper way to hide it.
	Levels[9].gapFirst = 1000;
	Levels[9].gapLast = 1000;

	CopyGaps(pGapListThps4, pGaps);
}

//main patches func, sets all hooks and changes vars needed
void Patch()
{

	/*
	//pkr extraction example
	pkr = new Pkr2();

	if (pkr->Load(".\\all9.pkr") == PkrError::Success)
	{
		printf("PKR LOAD OK\n");
	}
	else
	{
		printf("Failed to load PKR...\n");
		delete pkr;
	}
	*/

	WipeGaps();

	if (options.CurrentGame == "THPS1") CopyGaps(pGapListThps1, pGaps);
	else if (options.CurrentGame == "THPS2") CopyGaps(pGapListThps2, pGaps);
	else if (options.CurrentGame == "THPS3") PatchThps3Gaps();
	else if (options.CurrentGame == "THPS4") PatchThps4Gaps();
	else CopyGaps(pGapListThps2, pGaps); //restore if mhpb


	// this is set as callback, so should put as int
	//CPatch::SetInt(0x004f4ef4 + 3, (int)WINMAIN_WndProc);


	//doesnt seem to work, maybe gets overwritten by loading routines.
	//Career_ClearGameWithEveryone();


	if (!options.BigDrop)
	{
		//nops entire bail/award big drop path, since its a part of a func, not a separate one
		CPatch::Nop(0x48F419, 0x48F430 - 0x48F419);
	}

	if (!options.Manuals)
	{
		//set instant return from thiscall MaybeManual 
		CPatch::SetInt((int)Physics::MaybeManual, 0x000008c2);
	}



	// nop draw wheel?
	//CPatch::SetInt((int)0x004578b0, 0x000008c2);



	//disable skater rendering
	//CPatch::Nop(0x00467dfa, 5);

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
		CPatch::SetChar((int)PCMovie::PCMOVIE_PlayMovieFile, 0xC3);
		//CPatch::Nop(0x46A732, 5); //nops IntroMovies func
	}

	if (options.AddSkins)
	{
		PatchSkaters();
	}

	if (options.SeparateSaves)
	{
		char* savename = (char*)0x52fa30;
		memcpy(savename, &options.CurrentGame[0], options.CurrentGame.length()); //replaces THPS2 in saves with currentgame
	}

	if (options.CurrentGame != "THPS2")
	{
		ParseLevels(); //changes levels
		CustomGoals::PatchCareerGoals(Levels);
	}



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


	// fixed properly
	/*
	if (options.DisableNewTex)
	{
		//change newbmp pointers null
		CPatch::SetInt(0x4d60b5, 0);

		//change newtex pointers null
		CPatch::SetInt(0x4d6051, 0);
		CPatch::SetInt(0x4d607b, 0);
	}
	*/

	//this patches resolution, probably not needed anymore
	//CPatch::SetInt(0x0046A891, 2);


	// hardcoded in InitDirectDraw7
	int* hW2 = (int*)0x4f5496;
	int* hH2 = (int*)0x4f54a0;

	CPatch::SetInt((int)hW2, options.ResX);
	CPatch::SetInt((int)hH2, options.ResY);

	// these are supposedly for software renderer
	//CPatch::SetInt((int)0x524bb0, options.ResX);
	//CPatch::SetInt((int)0x524bb4, options.ResY);

	CPatch::SetInt((int)hardcodedWidth, options.ResX);
	CPatch::SetInt((int)hardcodedHeight, options.ResY);

	CPatch::SetInt((int)ScreenWidth, options.ResX);
	CPatch::SetInt((int)ScreenHeight, options.ResY);

	*ScreenWidth = options.ResX;
	*ScreenHeight = options.ResY;


	//CalcAnimLeanFrame, disables turning anim if noped
	//CPatch::Nop(0x004915db, 5);


	//TO DO split this into separate hooking funcs for each namespace and move to Hook::SetHooks
	SetHooks();
	Hook::SetHooks();


	//WINMAIN_PatchWndProc();

	//CPatch::RedirectJump(0x004f4ba0, WINMAIN_WndProc);

	/*
	if (options.UnlockFPS)
	{
		// this patches menus to 60fps
		// main menu
		CPatch::SetChar(0x0046af9c + 2, 1);

		// skater selection
		CPatch::SetChar(0x004a3979 + 2, 1);

		// level selection
		CPatch::SetChar(0x004589e1 + 2, 1);

		// career selection
		CPatch::SetChar(0x004180b1 + 2, 1);
	}
	*/
}




void Dummy()
{
}


/*
//D3DMODEL FUNCS
004ce3e0	D3DMODEL_SetupDynamicLighting
004ce6e0	D3DMODEL_RenderModel
004ceac0	submitModelFaces
004ceb70	lightFaceVerts
004ceee0	applyLighting
004cef50	submitFace
004cf300	addDXPoly
004cf520	hitherClipPoly
004cf7d0	cliptozplane
004cf8c0	computeZSort
004cfbf0	transformProjectModelVertices
004cffb0	D3DMODEL_Startup
*/

//so it returns actual struct, not pointer
ColorBGRA applyLighting(ColorBGRA* vert, ColorBGRA* light)
{
	if (options.DynamicLighting)
	{
		vert->R *= light->R / 255.0;
		vert->G *= light->G / 255.0;
		vert->B *= light->B / 255.0;
	}

	return *vert;
}

char** ShortLevName = (char**)0x0069d198;

// essentially it's a PCOpen wrapper that checks 3 additional paths
// if we've got name, check NEWBMP folder
// if we've got checksum, check NEWTEX folder
// additionally checks level short name subfolder (newtex\han for hangar etc)
int openExternalTexture2(uint Checksum, char* Name)
{
	printf("openExternalTexture!\n");

	if (options.DisableNewTex) return NS_NULL;

	char local[64];

	if (Name != NULL)
	{
		sprintf(local, ".\\newbmp\\%s", Name);

		//original game accounts for leading slashes in the name
	} 
	else if (Checksum != NULL)
	{
		// there is some additional comparison routine here in the original game

		sprintf(local, ".\\newtex\\%08x.bmp", Checksum);

		int file = PCopen(&local[0], 0);
		if (file != NS_NULL) return file;

		sprintf(local, ".\\newtex\\%s\\%08x.bmp", ShortLevName, Checksum);
	}
	else
	{
		printf("now what?\n");
		return NS_NULL;
	}

	return PCopen(&local[0], 0);
}

// list of all hooks
Hook::Reroute hookList[] = {
	
	{  0x004d5f10,openExternalTexture2 },
	{  0x004d65da,openExternalTexture2 },
	{  0x004d65f0,openExternalTexture2 },
	{  0x004d6c19,openExternalTexture2 },
	//{ 0x458564, SFX_SpoolOutLevelSFX },
	//{ 0x452570, SFX_SpoolInLevelSFX },

	{  0x004603c6,RenderModel },
	{  0x0046040c,RenderModel },
	{  0x0046024f,RenderModelFast },
	{  0x0046029a,RenderModelFast },
	{  0x0046104b,RenderBackgroundModel },
	//{  0x004609a6,RenderModelInSuper},
	//{  0x00461913,RenderModelInSuper},
	{  0x0046190c,RenderModelInSuperFast },
	{  0x00460338,RenderModelNonRotated },
	{  0x00460386,RenderModelNonRotated },
	{  0x00461043,RenderBackgroundModelNonRotated },
	



	//hooks main 3 logic funcs
	//all calls in PlayAway
	{ 0x46a331, Game_Init_Hook },
	{ 0x46a3ef, Game_Logic_Hook },
	{ 0x46a407, Game_Display_Hook },

	//timer stuff
	{ 0x42ffb8,	D3D_BeginScene_Hook },
	{ 0x430508,	D3D_BeginScene_Hook },

	//in Display
	{ 0x46882d, Front_Update_Hook },


	//in WinMain
	{ 0x004f511c, TH2Main },

	//in th2main
	//{ 0x0046a712, Init_AtStart },


	{ 0x00454590, Init_Restart },	//launchthedamngame
	//{ 0x0046a71b, Init_Restart },	//th2main
	{ 0x0046a8dc, Init_Restart },	//kickit
	{ 0x0046ae11, Init_Restart },   //kickit


	{ 0x0046a8e1, Init_ForGame }, //kickit

	//lights up polygons

	{ 0x004cedae, applyLighting },
	{ 0x004cedca, applyLighting },
	{ 0x004cede6, applyLighting },
	{ 0x004cee1f, applyLighting },
	{ 0x004cee33, applyLighting },
	{ 0x004cee47, applyLighting },
	{ 0x004cee8b, applyLighting },
	{ 0x004cee9f, applyLighting },
	{ 0x004ceeb3, applyLighting },
	{ 0x004ceec7, applyLighting },



	//D3D_ClearBuffers, doesnt seem to do anything
	/*
	{ 0x0046a392, Dummy },
	{ 0x0046a67a, Dummy },
	{ 0x004e429b, Dummy },
	{ 0x004f41a1, Dummy },
	{ 0x004f50a9, Dummy },
	*/

	//hooks inputs
	//in ReadDirectInput
	{ 0x4E1CC6, GenPsxPadData_Hook },

	{ 0x4CB27E, VIDMENU_Load_Hook },
	{ 0x4CB455, VIDMENU_Load_Hook },
	{ 0x4F3CFA, VIDMENU_Load_Hook },

	{ 0x4CB3E3, VIDMENU_Save_Hook },
	{ 0x4CC4C3, VIDMENU_Save_Hook },
	{ 0x4F3D3E, VIDMENU_Save_Hook },



	{ 0x41f4c8, Spool_LoadPSH },
	{ 0x41f7bb, Spool_LoadPSH },
	{ 0x469011, Spool_LoadPSH },
	{ 0x46902d, Spool_LoadPSH },
	{ 0x4a283b, Spool_LoadPSH },
	{ 0x4b569a, Spool_LoadPSH },
	{ 0x4b56af, Spool_LoadPSH },
	{ 0x4bd1fa, Spool_LoadPSH },
	{ 0x4bd20f, Spool_LoadPSH },


	//{ 0x46DFEC, Land_Sound },
	//{ 0x497DC8, Land_Sound },

	{ 0x453903,	WINMAIN_SwitchResolution_Hook },
	{ 0x45391B, WINMAIN_SwitchResolution_Hook },
	{ 0x46A8E7, WINMAIN_SwitchResolution_Hook },
	{ 0x46AE23, WINMAIN_SwitchResolution_Hook },

	{ 0x430466, M3dInit_SetResolution }, //in Db_Init
	{ 0x4645b8, M3dInit_SetResolution }, //in M3dInit_InitAtStart

	{ 0x460bf7, RenderSuperItemShadow_Hook },

	/*
	{ 0x41580c, Career_GetPointCost_Hook },
	{ 0x4707b0, Career_GetPointCost_Hook },
	{ 0x4b4a24, Career_GetPointCost_Hook },
	*/

	//{ 0x48ef74, CBruce_StartGrind_Hook }, //in CBruce::HandeStickToRail
	//{ 0x49c288, CBruce_HandleJump_Hook }, //in CBruce::DoPhysics



	//both in ExecuteCommandList
	{ 0x004c3608, Utils_SetVisibilityInBox_Hook },
	{ 0x004c3632, Utils_SetVisibilityInBox_Hook },

	{ 0x469f4c, Shatter_MaybeMakeGlassShatterSound }, //in Game_Logic

	//{ 0x48d4a5, Panel_Bail_Hook },	//in CBruce::Trick_Bail

	{ 0x468823, Panel_Display_Hook }, // in Display





	{ 0x4C1E8C, ExecuteCommandList_Hook },
	{ 0x4C2240, ExecuteCommandList_Hook },
	{ 0x4C2C13, ExecuteCommandList_Hook },
	{ 0x4C52FC, ExecuteCommandList_Hook },
	{ 0x4C5337, ExecuteCommandList_Hook },

	//{ 0x4c654d, Utils_VblankProcessing },



	{ 0x48703b,	PCINPUT_ActuatorOn_Hook }, // in Pad_ActuatorOn
	{ 0x4871d0, PCINPUT_ActuatorOff_Hook }, // in Pad_ActuatorOff


	//called from Career_Init, Career_StoreSnapshot and Career_RestoreSnapshot
	{ 0x00413935, Mem_CopyBytes },
	{ 0x00413955, Mem_CopyBytes },
	{ 0x0041397d, Mem_CopyBytes },
	{ 0x00413996, Mem_CopyBytes },
	{ 0x00417244, Mem_CopyBytes },
	{ 0x004172d6, Mem_CopyBytes },




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

/*
{ 0x004dc28a,Mess_SetScale_Wrap },
{ 0x004dc225,Mess_SetScale_Wrap },
{ 0x004d928c,Mess_SetScale_Wrap },
{ 0x004c16df,Mess_SetScale_Wrap },
{ 0x004b67f0,Mess_SetScale_Wrap },
{ 0x004b66b8,Mess_SetScale_Wrap },
{ 0x004b666a,Mess_SetScale_Wrap },
{ 0x004b6653,Mess_SetScale_Wrap },
{ 0x004b65fc,Mess_SetScale_Wrap },
{ 0x004b65e5,Mess_SetScale_Wrap },
{ 0x0048a394,Mess_SetScale_Wrap },
{ 0x00489256,Mess_SetScale_Wrap },
{ 0x00473835,Mess_SetScale_Wrap },
{ 0x004684ce,Mess_SetScale_Wrap },
{ 0x00450f9b,Mess_SetScale_Wrap },
{ 0x00450ed7,Mess_SetScale_Wrap },
{ 0x00450eb3,Mess_SetScale_Wrap },
{ 0x00450e63,Mess_SetScale_Wrap },
{ 0x00450d42,Mess_SetScale_Wrap },
{ 0x00450963,Mess_SetScale_Wrap },
{ 0x00450912,Mess_SetScale_Wrap },
{ 0x00450898,Mess_SetScale_Wrap },
{ 0x00450834,Mess_SetScale_Wrap },
{ 0x004507c4,Mess_SetScale_Wrap },
{ 0x004507a4,Mess_SetScale_Wrap },
{ 0x0045076e,Mess_SetScale_Wrap },
{ 0x00450598,Mess_SetScale_Wrap },
{ 0x0045046a,Mess_SetScale_Wrap },
{ 0x004503ec,Mess_SetScale_Wrap },
{ 0x0045029f,Mess_SetScale_Wrap },
{ 0x0044e740,Mess_SetScale_Wrap },
{ 0x0044e712,Mess_SetScale_Wrap },
{ 0x0044d4d7,Mess_SetScale_Wrap },
{ 0x0044d49c,Mess_SetScale_Wrap },
{ 0x0044d480,Mess_SetScale_Wrap },
{ 0x0044d425,Mess_SetScale_Wrap },
{ 0x0044d407,Mess_SetScale_Wrap },
{ 0x0044d287,Mess_SetScale_Wrap },
{ 0x0044d1fe,Mess_SetScale_Wrap },
{ 0x0044d094,Mess_SetScale_Wrap },
{ 0x0044d06f,Mess_SetScale_Wrap },
{ 0x0044d02e,Mess_SetScale_Wrap },
{ 0x0044d009,Mess_SetScale_Wrap },
{ 0x0044cfca,Mess_SetScale_Wrap },
{ 0x0044cfa5,Mess_SetScale_Wrap },
{ 0x0044ce50,Mess_SetScale_Wrap },
{ 0x0044cd6f,Mess_SetScale_Wrap },
{ 0x0044cc34,Mess_SetScale_Wrap },
{ 0x0044ca44,Mess_SetScale_Wrap },
{ 0x0044c82e,Mess_SetScale_Wrap },
{ 0x0044c7f7,Mess_SetScale_Wrap },
{ 0x0044c7e0,Mess_SetScale_Wrap },
{ 0x0044c78a,Mess_SetScale_Wrap },
{ 0x0044c773,Mess_SetScale_Wrap },
{ 0x0044c706,Mess_SetScale_Wrap },
{ 0x0044ba78,Mess_SetScale_Wrap },
{ 0x0044b51b,Mess_SetScale_Wrap },
{ 0x0044b21b,Mess_SetScale_Wrap },
{ 0x0041bf6b,Mess_SetScale_Wrap },
{ 0x0041bf0f,Mess_SetScale_Wrap },
{ 0x0041beb0,Mess_SetScale_Wrap },
{ 0x0041be5d,Mess_SetScale_Wrap },
{ 0x0041bdfe,Mess_SetScale_Wrap },
{ 0x0041bdab,Mess_SetScale_Wrap },
{ 0x0041bd4d,Mess_SetScale_Wrap },
{ 0x0041bcf7,Mess_SetScale_Wrap },
{ 0x0041bc98,Mess_SetScale_Wrap },
{ 0x0041bc42,Mess_SetScale_Wrap },
{ 0x0041bbe3,Mess_SetScale_Wrap },
{ 0x0041bb8d,Mess_SetScale_Wrap },
{ 0x0041bae6,Mess_SetScale_Wrap },
{ 0x0041bab4,Mess_SetScale_Wrap },
{ 0x0041b9c8,Mess_SetScale_Wrap },
{ 0x0041b924,Mess_SetScale_Wrap },
{ 0x0041b872,Mess_SetScale_Wrap },
{ 0x0041b83f,Mess_SetScale_Wrap },
{ 0x0041b582,Mess_SetScale_Wrap },
{ 0x0041b459,Mess_SetScale_Wrap },
{ 0x0041afc8,Mess_SetScale_Wrap },
{ 0x0041af7e,Mess_SetScale_Wrap },
{ 0x0041af33,Mess_SetScale_Wrap },
{ 0x0041abe5,Mess_SetScale_Wrap },
{ 0x0041a9fc,Mess_SetScale_Wrap },
{ 0x0041a914,Mess_SetScale_Wrap },
{ 0x0041a83b,Mess_SetScale_Wrap },
{ 0x0041a262,Mess_SetScale_Wrap }
*/

//{ 0x473680, CreateMessage }


{ 0x00405323, Utils_CalcUnit },
{ 0x0040d006, Utils_CalcUnit },
{ 0x0040d0fe, Utils_CalcUnit },
{ 0x0040d121, Utils_CalcUnit },
{ 0x0040d478, Utils_CalcUnit },
{ 0x0040e12b, Utils_CalcUnit },
{ 0x0049b0bf, Utils_CalcUnit },
{ 0x004acd4c, Utils_CalcUnit },


{ 0x0040614e, Utils_GetVecFromMagDir },
{ 0x00410749, Utils_GetVecFromMagDir },
{ 0x00410844, Utils_GetVecFromMagDir },
{ 0x0041088e, Utils_GetVecFromMagDir },
{ 0x004114f1, Utils_GetVecFromMagDir },
{ 0x00411547, Utils_GetVecFromMagDir },
{ 0x0049d97f, Utils_GetVecFromMagDir },
{ 0x0049da5a, Utils_GetVecFromMagDir },
{ 0x0049dba5, Utils_GetVecFromMagDir },


{ 0x00422e29, Utils_LimitRange },
{ 0x004555b2, Utils_LimitRange },


//sine cosine patch for wheel
{ 0x457939, ScreenScaledCosine },
{ 0x457992, ScreenScaledCosine },

{ 0x457947, ScreenScaledSine },
{ 0x45795D, ScreenScaledSine },

{ 0x004c74d0, Utils_KillEverythingInBox },

{ 0x00450763, Utils_Pulse },
{ 0x004507b9, Utils_Pulse },
{ 0x00450829, Utils_Pulse },
{ 0x0045088d, Utils_Pulse },
{ 0x00450907, Utils_Pulse },
{ 0x00450958, Utils_Pulse },
{ 0x00450d3a, Utils_Pulse },
{ 0x00450e58, Utils_Pulse },
{ 0x00450ecc, Utils_Pulse },
{ 0x00450f90, Utils_Pulse },

/*
{ 0x004cb548, LoadFile },
{ 0x004bccbb, LoadFile },
{ 0x004b5054, LoadFile },
{ 0x004b21f1, LoadFile },
{ 0x004b201e, LoadFile },
{ 0x004b1d73, LoadFile },
{ 0x004a9a60, LoadFile },
{ 0x004a9a40, LoadFile },
{ 0x004a0452, LoadFile },
//{ 0x0049039a, LoadFile }, //tricks.bin, fails
{ 0x0047ebcd, LoadFile },
{ 0x0047a809, LoadFile },
{ 0x004793ea, LoadFile },
{ 0x0046b0cb, LoadFile },
{ 0x0045d2a7, LoadFile },
{ 0x00458bb3, LoadFile },
{ 0x004558b8, LoadFile },
{ 0x0044b37d, LoadFile },
{ 0x004449a8, LoadFile },
//{ 0x0042fa4b, LoadFile }, //sk2def.psx, fails
{ 0x0042f96f, LoadFile },
{ 0x0042cdf5, LoadFile },
{ 0x0042beda, LoadFile },
{ 0x00427739, LoadFile },
{ 0x0042646a, LoadFile },
{ 0x0041de92, LoadFile },
{ 0x0041c52a, LoadFile },
{ 0x00417493, LoadFile },
{ 0x00415cd0, LoadFile },
{ 0x00415c87, LoadFile }
*/

	//list terminator, do not remove
	{ NULL, NULL }

};

Hook::Reroute* pHookList1 = &hookList[0];


void SetHooks()
{
	Hook::ProcessList(pHookList1);
}

#pragma endregion



/*

uint CheatCheckA;
uint CheatCheckB;

void frug(uint valA, uint valB)
{
  CheatCheckA = ((CheatCheckA ^ valA) >> 0x1f ^ (CheatCheckA ^ valA) * 2) * 0x209;
  valB = CheatCheckA >> 8 ^ CheatCheckB ^ valB;
  CheatCheckB = valB >> 0x1f ^ valB * 2;
}

 part of shell_doCheatProcessing
 
	if (DAT_00567cf9) {
		tValA = 0x01234567;
		tValB = 0x34859f3a;
	}
	else if (DAT_00567ce8) {
		tValA = 0xab432901;
		tValB = 0x88d3a109;
	}
	else if (DAT_00567d09) {
		tValA = 0x776643d1;
		tValB = 0x0901d3e8;
	}
	else if (DAT_00567cd9) {
		tValA = 0x93fe1682;
		tValB = 0x92551072;
	}
	else if (DAT_00567c59) {
		tValA = 0x31415926;
		tValB = 0x7720de42;
	}
	else if (DAT_00567c78) {
		tValA = 0xdeadbeef;
		tValB = 0xfe3010f3;
	}
	else if (DAT_00567c88) {
		tValA = 0xb87610db;
		tValB = 0xde098401;
	}
	else if (DAT_00567c69) {
		tValA = 0x03185332;
		tValB = 0x80fe4187;
	}
	else {
		return 0;
	}

	frug(tValA, tValB);

	//then validate against cheats

*/