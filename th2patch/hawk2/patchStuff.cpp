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
#include "thawk2/IO/Wad.h"
//#include "thawk2/qb/qb.h"

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
	// end level command, used in mall and jam to finish the level
	// TODO: should execute main restart instead
	if (*node == 158)
	{
		Trig::Trig_ExecuteRestart();
		return;
	}

	// turn teleport into killing zone, used in thps4 alcatraz and london
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






#define LINE_COLOR 0xff
#define MARKER_COLOR 0xff00

#define SINGLEPLAYER 0
#define MULTIPLAYER_HORIZONTAL 1
#define MULTIPLAYER_VERTICAL 2
#define MULTIPLAYER_CORNER 3
#define MULTIPLAYER_CORNER_BIG 4

#define TOP_BIT 0x80000000


inline void SetCameraValues(short dist, short pitch, short yOffset) {

	// wonder if original code uses this for both p1 and p2 cameras
	*camDist = dist;
	*camPitch = pitch;
	*camYOffset = yOffset;
}


// fills rectangle with black
inline void BlackOut(int x, int y, int w, int h) {
	Draw_Rect(x, y, w + x, y, w + x, h + y, x, h + y, 0x40000000);
}



inline void DisplayViewPort_Singleplayer() {

	if (!*GameFrozen) {
		if (!*closeCam) {
			SetCameraValues(290, 150, -108);
		}
		else {
			SetCameraValues(386, 30, -160);
		}
	}

	Display_Viewport(DefaultViewport, 0); //gNetGame
}

inline void DisplayViewport_SplitscreenHorizontal() {

	if (!*GameFrozen) {
		SetCameraValues(286, 118, -140);
	}

	BlackOut(options.ResX / 2 + -2, 0, 4, options.ResY);

	Display_Viewport(LeftViewport, 0);
	Display_Viewport(RightViewport, 1);
}

inline void DisplayViewport_SplitscreenVertical() {

	if (!*GameFrozen) {
		SetCameraValues(450, 60, -120);
	}

	BlackOut(0, options.ResY / 2 + -2, options.ResX, 4);

	Display_Viewport(TopViewport, 0);
	Display_Viewport(BottomViewport, 1);
}

inline void DisplayViewport_SplitscreenCorner() {

	if (!*GameFrozen) {
		SetCameraValues(642, 32, -172);
	}

	BlackOut(options.ResX / 2, 0, options.ResX / 2, options.ResY / 2);
	BlackOut(0, options.ResY / 2, options.ResX / 2, options.ResY / 2);

	Display_Viewport(TopLeftViewport, 0);
	Display_Viewport(BottomRightViewport, 1);
}

inline void DisplayViewport_SplitscreenCornerBig() {

	if (!*GameFrozen) {
		SetCameraValues(610, 0, -200);
	}

	BlackOut(options.ResX / 2 + 0x30, 0, options.ResX / 2 - 0x30, options.ResY / 2 - 0x20);
	BlackOut(0, options.ResY / 2 + 0x20, options.ResX / 2 - 0x30, options.ResY / 2 - 0x20);

	Display_Viewport(TopLeftBigViewport, 0);
	Display_Viewport(BottomRightBigViewport, 1);
}

inline void DoWibblyTextures() {

	// preprocess wibbly textures for Taxi and Bull models
	// are there wibbly textures though? maybe smoke or smth?

	void* pTaxi = (void*)Spool_FindRegion("c_taxi");

	if ((uint)pTaxi != NS_NULL) {
		M3d_PreprocessWibblyTextures(pTaxi);
	}

	void* pBull = (void*)Spool_FindRegion("c_bull");

	if ((uint)pBull != NS_NULL) {
		M3d_PreprocessWibblyTextures(pBull);
	}
}


void Panel_Display_Patch()
{
	CBruce skater = new CBruce(GSkater);

	if (options.ShowHUD)
	{
		Panel_Display();

		if (!*GamePaused)
		{
			if (skater.InManual() > 0)
			{
				Panel_BalanceRail(skater.ManualBalance(), 0x1000,
					30, 6,
					(int)(512 / 2.7), 240 / 2,
					COLOR_RED, COLOR_GREEN,	//BGR color
					false); // vertical
			}

			if (options.RailBalanceBar)
			{
				if ((EPhysicsState)skater.PhysicsState() == EPhysicsState::PHYSICS_ON_RAIL)
				{
					Panel_BalanceRail(skater.RailBalance(), 0x1000,
						30, 6,
						512 / 2, 240 / 3,
						COLOR_RED, COLOR_GREEN,	//BGR color
						true); // horizontal
				}
			}
		}
	}

	PrintDebugStuff();

	/*
	if (menu != NULL)
		delete menu;

	menu = new CMenu((SMenu*)0x0055e8a0);
	//menu->DebugPrint();
	*/
}






bool* CloseCamToggle = (bool*)0x00530e84;


void Display() {

	// draw the info rectangle, if autotest restart exists
	// most likely it was removed, probably can wipe it out
	/*
	if (*pAutoTestRestartName != NULL) {
		Mess::Mess_SetRGB(0xff,0,0,0);
		Mess::Mess_SetScale(0x100);
		Mess::Mess_SetTextJustify(Mess::eTextJustify::Left);
		Mess::Mess_DrawText(0x100, 0x3c, *pAutoTestRestartName);
	}
	*/

	/*
	// ??? force black sky? probably unnecessary. maybe put toggle sky cheat here?
	if (_Cheat_30 != 0) {
		_M3d_FadeColour = TOP_BIT;
		_Db_SkyColor = 0;
		Db_UpdateSky();
	}
	*/

	// huh, changes fog distance based on zoom?
	//DefaultViewport->fogDist = (short)CCamera::GetZoom(_CameraList);

	if (!*GameFrozen) {

		// updates cameras
		Ob_AI(CameraList);

		// here it handles camera change on select
		if (!(Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK))
		{
			*CloseCamToggle = true;
		}
		else
		{
			if (*CloseCamToggle)
			{
				*closeCam ^= 1;
				*CloseCamToggle ^= 1;
			}
		}
	}

	// probably toggles closecam if allowed to? (select)
	// depending on closecam value, it assigns different camera values
	/*
	if (((_GameFrozen != 0) && (_Cheat_ScreenShots == 0)) ||
		(.Ob_AI__FPP5CBody(&_CameraList), _Cheat_ScreenShots == 0)) {
		if (pad1._240_1_ == '\0') {
			DAT_00530e84 = 1;
		}
		else if ((DAT_00530e84 != 0) && (((DAT_00530e84 = 0, _GNumberOfPlayers != 2 || (_GGame == Horse)) || (_GGame == Contest)
						 ))) {
			_CloseCam = _CloseCam ^ 1;
		}

		if (DAT_00567eb4._1_1_ != '\0') {
			DAT_00567eb4._1_1_ = '\0';
		}
	}
	*/

	// is this like PC only hack? seems it always resets it to single player 
	// PC version doesnt really use any other modes, as there is no splitscreen modes at all
	// the rest of it seems to be working fine though, if set manually
	*ViewportMode = SINGLEPLAYER;

	MENUPC_DrawMouseCursor();


	DoWibblyTextures();


	// draw viewport based on selected mode
	switch (*ViewportMode) {

		case SINGLEPLAYER:
			DisplayViewPort_Singleplayer();
			break;

		case MULTIPLAYER_HORIZONTAL:
			DisplayViewport_SplitscreenHorizontal();
			break;

		case MULTIPLAYER_VERTICAL:
			DisplayViewport_SplitscreenVertical();
			break;

		case MULTIPLAYER_CORNER:
			DisplayViewport_SplitscreenCorner();
			break;

		case MULTIPLAYER_CORNER_BIG:
			DisplayViewport_SplitscreenCornerBig();
			break;

		default:
			printf("Unknown viewport mode in Display()!");
			break;
	}


	// draw HUD
	if (!*Cheat_Light && options.ShowHUD) {

		// okay what
		// i call it here and then once again in the patched call
		// remove any and it crashes...
		Panel_Display();

		// additional patch drawing
		Panel_Display_Patch();
	}

	Pad::Pad_Restore();
	Front_Update();
	Pad::Pad_Remap();

	// draw mouse cursor
	if (*GamePaused) {
		// display frontend menus
		Front_Display();
	}

	// display message queue
	Mess::Mess_Display();


	// draw manual balance bar
	// should add horizonal here as well
	// if single player
	/*
	if (GSkater2 == NULL) {
		// if skater 1 in manual
		if ((GSkater->mManual != 0) && (*(int *)&GSkater->set_by_opcode_0x59! != 0)) {
			Panel_BalanceUD(GSkater->manualBalance, 4000, 30, 200, 0x78, LINE_COLOR, MARKER_COLOR);
		}
	}
	// if splitscreen
	else {

		// if skater 1 in manual
		if ((GSkater->mManual != 0) && (*(int *)&GSkater->set_by_opcode_0x59! != 0)) {
			Panel_BalanceUD(GSkater->manualBalance, 4000, 0x19, 0x50, 0x78, LINE_COLOR, MARKER_COLOR);
		}

		// if skater 2 in manual, skip
		if ((GSkater2->mManual != 0) && (*(int *)&GSkater2->set_by_opcode_0x59! != 0)) {
			Panel_BalanceUD(GSkater2->manualBalance, 4000, 25, 336, 0x78, LINE_COLOR, MARKER_COLOR);
		}
	}
	*/


	/*
	if ((*GamePaused == 0) || (*Status == 0x2a)) {
		*Mick_Darkness = 0;
	}
	else {
		Mick_Darken();
	}
	*/

	// render flash (xrays, thunder - white, blood - red, etc)
	// not working properly on pc as well?
	Flash::Flash_Display();

	// calculate poly buffer size, not really needed i guess? maybe for memory handling
	//__PolyBufferBytesUsed = (_pPoly & 0x7fffffff) - (*(uint *)(pDoubleBuffer + 0xb0) & 0x7fffffff);
}





#pragma endregion


/*
void System_Logic() {
	Pad_Restore();
	Pad_Update();
	Pad_Remap();

	if (*_GClear1) {
		Pad_ClearAllOne(0);
	}

	if (*_GClear2) {
		Pad_ClearAllOne(1);
	}
}
*/



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

// changes skater costume models. slot 1 to 4
void PatchSkater(SkaterProfile* p, int slot, char* hi, char* lo)
{
	// im lazy to fix all calls...
	slot--;

	if (slot < 0)
		throw new exception("slot < 0");

	if (slot > 3)
		throw new exception("slot << 0> 3");

	p->Outfits[slot].hi = hi;
	p->Outfits[slot].lo = lo;

	/*
	char buf[256];

	if (hi != NULL)
	{
		printf("looking for %s\n", hi);

		sprintf(buf, "%s.%s", hi, "psx");

		if (!FileIO::Exists("data\\", buf))
		{
			p->Outfits[slot].hi = NULL;
			p->Outfits[slot].lo = NULL;
			return;
		}
	}

	if (lo != NULL)
	{
		printf("looking for %s\n", lo);

		sprintf(buf, "%s.%s", lo, "psx");

		if (!FileIO::Exists("data\\", buf))
			p->Outfits[slot].lo = NULL;
	}
	*/
}

void PatchSkaters()
{
	SkaterProfile* p = &profiles[0];

	PatchSkater(p, 3, "hawk3", "hawk3b");
	PatchSkater(p, 4, "hawk4", "hawk4b");

	printf("hello\n");

	p++;
	PatchSkater(p, 3, "burnq4", "burnq4b");
	//burnquist wasnt in thps3, so no style D model

	p++;

	PatchSkater(p, 3, "ca3", "ca3b");
	PatchSkater(p, 4, "ca4", "ca4b");

	p++;

	PatchSkater(p, 3, "campb3", "campb3b");
	PatchSkater(p, 4, "campb4", "campb4b");

	p++;

	PatchSkater(p, 3, "glif3", "glif3b");
	PatchSkater(p, 4, "glif4", "glif4b");

	p++;

	PatchSkater(p, 3, "koston3", "koston3b");
	PatchSkater(p, 4, "koston4", "koston4b");

	p++;

	PatchSkater(p, 3, "lasek3", "lasek3b");
	PatchSkater(p, 4, "lasek4", "lasek4b");

	p++;

	PatchSkater(p, 3, "mullen3", "mullen3b");
	PatchSkater(p, 4, "mullen4", "mullen4b");

	p++;

	PatchSkater(p, 3, "muska3", "muska3b");
	PatchSkater(p, 4, "muska4", "muska4b");

	p++;

	PatchSkater(p, 3, "rynld3", "rynld3b");
	PatchSkater(p, 4, "rynld4", "rynld4b");

	p++;

	PatchSkater(p, 3, "rowley3", "rowley3b");
	PatchSkater(p, 4, "rowley4", "rowley4b");

	p++;

	PatchSkater(p, 3, "steam3", "steam3b");
	PatchSkater(p, 4, "steam4", "steam4b");

	p++;

	PatchSkater(p, 3, "thomas3", "thomas3b");
	PatchSkater(p, 4, "thomas4", "thomas4b");



	if (options.DickSwap != "none")
	{
		//now patch secret skater depending on the selected option

		p = &profiles[SKATER_SECRET1];


		//since we can't have a switch case by string in C, lets just calculate string checksum, used a lot in later games.
		uint hash = checksum(&options.DickSwap[0]);

		printf("%s = 0x%08x\n", &options.DickSwap[0], hash);


		switch (hash)
		{
			// "bam", margera + fry cook
			case 0x680b1a5b: {
				sprintf_s(p->FullName, sizeof(p->FullName), "Bam Margera");
				p->pShortName = "Bam";

				PatchSkater(p, 1, "ba3", "ba3b");
				PatchSkater(p, 2, "ba4", "ba4b");
				PatchSkater(p, 3, "fry", "fryb");

				p->pFaceName = "s2fbam.bmp";

				//memcpy(&p->boards, BamBoards, sizeof(BamBoards));

				break;
			}

			// "wolve", wolverine from th3
			case 0xe4f32b33: {
				sprintf_s(p->FullName, sizeof(p->FullName), "Wolverine");
				p->pShortName = "wolve";

				PatchSkater(p, 1, "wolve", "wolve");
				PatchSkater(p, 2, NULL, NULL);

				break;
			}

			//"lilper", Little Person from th4
			case 0xadf13666: {
				sprintf_s(p->FullName, sizeof(p->FullName), "Little Person");
				p->pShortName = "lilper";

				PatchSkater(p, 1, "lilper", "lilper");
				PatchSkater(p, 2, NULL, NULL);

				//memcpy(&p->boards, LilPerBoards, sizeof(LilPerBoards));

				break;
			}

			//kor1, fin k l band style A
			case 0xfd91275c: {
				sprintf_s(p->FullName, sizeof(p->FullName), "Fin K. L.");
				p->pShortName = "finkl";
				p->flags |= 1; // sets female sfx bank

				PatchSkater(p, 1, "white", "white");
				PatchSkater(p, 2, "red", "red");
				PatchSkater(p, 3, "blue", "blue");
				PatchSkater(p, 4, "black", "black");

				break;
			}

			//kor2, fin k l band style B
			case 0x4ff07f11: {
				sprintf_s(p->FullName, sizeof(p->FullName), "Fin K. L.");
				p->pShortName = "finkl";
				p->flags |= 1; // sets female sfx bank

				PatchSkater(p, 1, "white2", "white2");
				PatchSkater(p, 2, "red2", "red2");
				PatchSkater(p, 3, "blue2", "blue2");
				PatchSkater(p, 4, "black2", "black2");

				break;
			}

			// mcsqueeb, since tony already has 4 styles, bring this back in
			case 0x92af0067: {
				sprintf_s(p->FullName, sizeof(p->FullName), "McSqueeb");
				p->pShortName = "mcsqueeb";

				PatchSkater(p, 1, "secret4", "secret4b");
				PatchSkater(p, 2, NULL, NULL);

				break;
			}

			default:
				printf("Unknown secret skater swap! %s", &options.DickSwap[0]);
		}
	}
	else
	{
		PatchSkater(p, 3, "dick3", "dick3b");
		// there was no dick in thps4
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
	
	// wad extraction example
	//Wad::Load("cd.hed", "cd.wad");

	/*
	HedFile* file = Wad::FindFile("aaskil.psx");
	Wad::DumpFile(file, "somewhere\aaskil.psx");
	Wad::DumpFile(Wad::FindFile("aaskil_2.psx"), "aaskil_2.psx");
	Wad::DumpFile(Wad::FindFile("aaskil_t.trg"), "aaskil_t.trg");
	*/

	//QB::LoadScript("mods\\scripts\\goals.qb");
	//int value = QB::GetInt(QB::crc32ns("goaltype_gaps"));

	/*
	//pkr extraction example
	pkr = new Pkr2();

	if (pkr->Load(".\\all.pkr") == PkrError::Success)
	{
		pkr->ExportAll(".\\data_winmobile");
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
	// 



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

	// remove video_sfx_play call for 
	//if (options.CurrentGame == "THPS3")
	//	CPatch::Nop(0x4aafba, 29);


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
	CPatch::Nop(0x4f5149, 6);

	
	

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

	char local[MAX_BUFFER_SIZE];

	if (Name != NULL)
	{
		sprintf_s(local, MAX_BUFFER_SIZE, ".\\newbmp\\%s", Name);

		//original game accounts for leading slashes in the name
	} 
	else if (Checksum != NULL)
	{
		// there is some additional comparison routine here in the original game

		sprintf_s(local, MAX_BUFFER_SIZE, ".\\newtex\\%08x.bmp", Checksum);

		int file = PCIO::PCopen(&local[0], 0);
		if (file != NS_NULL) return file;

		sprintf_s(local, MAX_BUFFER_SIZE, ".\\newtex\\%s\\%08x.bmp", ShortLevName, Checksum);
	}
	else
	{
		printf("now what?\n");
		return NS_NULL;
	}

	return PCIO::PCopen(&local[0], 0);
}



void SFX_PlayX_hook(int index, int p1, int p2)
{
	//printf("SFX_PlayX = %i %i %i\n", index, p1, p2);

	// a crude patch for th3 crashes (canada, airport)
	// just dont play sounds above 400
	if (index > 400) {
		printf("sound index too high\n");
		return;
	}

	SFX_PlayX(index, p1, p2);
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
    { 0x0046a71b, Init_Restart },	//th2main
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

	{ 0x46a085, Display },



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


{ 0x004020ce, SFX_PlayX_hook },
{ 0x00403568, SFX_PlayX_hook },
{ 0x004132d8, SFX_PlayX_hook },
{ 0x004132e5, SFX_PlayX_hook },
{ 0x004132ff, SFX_PlayX_hook },
{ 0x004134b3, SFX_PlayX_hook },
{ 0x004134f7, SFX_PlayX_hook },
{ 0x0041359f, SFX_PlayX_hook },
{ 0x0041366e, SFX_PlayX_hook },
{ 0x0041367b, SFX_PlayX_hook },
{ 0x0041369e, SFX_PlayX_hook },
{ 0x00413895, SFX_PlayX_hook },
{ 0x00414449, SFX_PlayX_hook },
{ 0x00417e6a, SFX_PlayX_hook },
{ 0x00417e8b, SFX_PlayX_hook },
{ 0x00417f55, SFX_PlayX_hook },
{ 0x0041a314, SFX_PlayX_hook },
{ 0x0041a322, SFX_PlayX_hook },
{ 0x0041a88b, SFX_PlayX_hook },
{ 0x0041aaf9, SFX_PlayX_hook },
{ 0x0041ab07, SFX_PlayX_hook },
{ 0x0041ac2a, SFX_PlayX_hook },
{ 0x0041ac37, SFX_PlayX_hook },
{ 0x0041b0b2, SFX_PlayX_hook },
{ 0x0041b65b, SFX_PlayX_hook },
{ 0x0041b764, SFX_PlayX_hook },
{ 0x0041b8c9, SFX_PlayX_hook },
{ 0x0041bb29, SFX_PlayX_hook },
{ 0x0041ceaa, SFX_PlayX_hook },
{ 0x0041d10e, SFX_PlayX_hook },
{ 0x0041d38d, SFX_PlayX_hook },
{ 0x0041d500, SFX_PlayX_hook },
{ 0x0041d546, SFX_PlayX_hook },
{ 0x0041d65e, SFX_PlayX_hook },
{ 0x0041d676, SFX_PlayX_hook },
{ 0x0041d711, SFX_PlayX_hook },
{ 0x0041d741, SFX_PlayX_hook },
{ 0x004262fe, SFX_PlayX_hook },
{ 0x00426363, SFX_PlayX_hook },
{ 0x0042639f, SFX_PlayX_hook },
{ 0x00429537, SFX_PlayX_hook },
{ 0x0042962a, SFX_PlayX_hook },
{ 0x00429712, SFX_PlayX_hook },
{ 0x004298b2, SFX_PlayX_hook },
{ 0x0042a9b4, SFX_PlayX_hook },
{ 0x0042a9e1, SFX_PlayX_hook },
{ 0x0042aa48, SFX_PlayX_hook },
{ 0x0042ab32, SFX_PlayX_hook },
{ 0x0042c961, SFX_PlayX_hook },
{ 0x0042c9ab, SFX_PlayX_hook },
{ 0x0042ca17, SFX_PlayX_hook },
{ 0x0042ca52, SFX_PlayX_hook },
{ 0x0042e9cf, SFX_PlayX_hook },
{ 0x0042ea63, SFX_PlayX_hook },
{ 0x0042eb13, SFX_PlayX_hook },
{ 0x0042eb28, SFX_PlayX_hook },
{ 0x0042eb5e, SFX_PlayX_hook },
{ 0x0042eb9b, SFX_PlayX_hook },
{ 0x0042ec29, SFX_PlayX_hook },
{ 0x0042ed00, SFX_PlayX_hook },
{ 0x0042ed37, SFX_PlayX_hook },
{ 0x0042ee5e, SFX_PlayX_hook },
{ 0x0042f2ff, SFX_PlayX_hook },
{ 0x0042f58a, SFX_PlayX_hook },
{ 0x0042f606, SFX_PlayX_hook },
{ 0x0042f610, SFX_PlayX_hook },
{ 0x0042f625, SFX_PlayX_hook },
{ 0x0042f644, SFX_PlayX_hook },
{ 0x0042f6a9, SFX_PlayX_hook },
{ 0x0042f6c4, SFX_PlayX_hook },
{ 0x0042f741, SFX_PlayX_hook },
{ 0x0042f799, SFX_PlayX_hook },
{ 0x0042f7b6, SFX_PlayX_hook },
{ 0x00434092, SFX_PlayX_hook },
{ 0x004341c7, SFX_PlayX_hook },
{ 0x0043420c, SFX_PlayX_hook },
{ 0x00434251, SFX_PlayX_hook },
{ 0x00434296, SFX_PlayX_hook },
{ 0x004345ce, SFX_PlayX_hook },
{ 0x00434665, SFX_PlayX_hook },
{ 0x00435c16, SFX_PlayX_hook },
{ 0x00435c96, SFX_PlayX_hook },
{ 0x00435dad, SFX_PlayX_hook },
{ 0x00435e4c, SFX_PlayX_hook },
{ 0x00435e91, SFX_PlayX_hook },
{ 0x00435ed5, SFX_PlayX_hook },
{ 0x00437352, SFX_PlayX_hook },
{ 0x004450ed, SFX_PlayX_hook },
{ 0x0044512a, SFX_PlayX_hook },
{ 0x00445395, SFX_PlayX_hook },
{ 0x004453de, SFX_PlayX_hook },
{ 0x0044546d, SFX_PlayX_hook },
{ 0x00445535, SFX_PlayX_hook },
{ 0x0044740e, SFX_PlayX_hook },
{ 0x0044742c, SFX_PlayX_hook },
{ 0x00448746, SFX_PlayX_hook },
{ 0x00448795, SFX_PlayX_hook },
{ 0x0044bca4, SFX_PlayX_hook },
{ 0x0044bd18, SFX_PlayX_hook },
{ 0x0044e06b, SFX_PlayX_hook },
{ 0x0044e45b, SFX_PlayX_hook },
{ 0x0044e6de, SFX_PlayX_hook },
{ 0x0044ed83, SFX_PlayX_hook },
{ 0x0044f3b5, SFX_PlayX_hook },
{ 0x0044f473, SFX_PlayX_hook },
{ 0x0044f5e6, SFX_PlayX_hook },
{ 0x0044f61e, SFX_PlayX_hook },
{ 0x0044f680, SFX_PlayX_hook },
{ 0x0044f69e, SFX_PlayX_hook },
{ 0x0044f6b8, SFX_PlayX_hook },
{ 0x0044f734, SFX_PlayX_hook },
{ 0x0044f766, SFX_PlayX_hook },
{ 0x0044f780, SFX_PlayX_hook },
{ 0x0044f7d6, SFX_PlayX_hook },
{ 0x0044f7e8, SFX_PlayX_hook },
{ 0x0044f85c, SFX_PlayX_hook },
{ 0x0044f90a, SFX_PlayX_hook },
{ 0x0044fc4e, SFX_PlayX_hook },
{ 0x0044fd87, SFX_PlayX_hook },
{ 0x0044fdd8, SFX_PlayX_hook },
{ 0x0044fed9, SFX_PlayX_hook },
{ 0x0044ff55, SFX_PlayX_hook },
{ 0x00450023, SFX_PlayX_hook },
{ 0x0045007d, SFX_PlayX_hook },
{ 0x004501a7, SFX_PlayX_hook },
{ 0x00450385, SFX_PlayX_hook },
{ 0x004503af, SFX_PlayX_hook },
{ 0x00450429, SFX_PlayX_hook },
{ 0x00450650, SFX_PlayX_hook },
{ 0x004506df, SFX_PlayX_hook },
{ 0x004509d5, SFX_PlayX_hook },
{ 0x00450be2, SFX_PlayX_hook },
{ 0x00450e09, SFX_PlayX_hook },
{ 0x0045104c, SFX_PlayX_hook },
{ 0x004511ed, SFX_PlayX_hook },
{ 0x00451250, SFX_PlayX_hook },
{ 0x004512be, SFX_PlayX_hook },
{ 0x00451314, SFX_PlayX_hook },
{ 0x00451372, SFX_PlayX_hook },
{ 0x004513bf, SFX_PlayX_hook },
{ 0x004513fd, SFX_PlayX_hook },
{ 0x004514fb, SFX_PlayX_hook },
{ 0x0045163f, SFX_PlayX_hook },
{ 0x0045174c, SFX_PlayX_hook },
{ 0x0045187f, SFX_PlayX_hook },
{ 0x004518e2, SFX_PlayX_hook },
{ 0x00451ad3, SFX_PlayX_hook },
{ 0x00451b1b, SFX_PlayX_hook },
{ 0x00451b5f, SFX_PlayX_hook },
{ 0x00451c13, SFX_PlayX_hook },
{ 0x00451d68, SFX_PlayX_hook },
{ 0x00451e5d, SFX_PlayX_hook },
{ 0x00451f3f, SFX_PlayX_hook },
{ 0x00452acc, SFX_PlayX_hook },
{ 0x004546bb, SFX_PlayX_hook },
{ 0x00455498, SFX_PlayX_hook },
{ 0x004554ce, SFX_PlayX_hook },
{ 0x0045553f, SFX_PlayX_hook },
{ 0x00455589, SFX_PlayX_hook },
{ 0x004596d5, SFX_PlayX_hook },
{ 0x00459910, SFX_PlayX_hook },
{ 0x00459948, SFX_PlayX_hook },
{ 0x00459a06, SFX_PlayX_hook },
{ 0x00459a2d, SFX_PlayX_hook },
{ 0x00459a5c, SFX_PlayX_hook },
{ 0x00459aab, SFX_PlayX_hook },
{ 0x0045af56, SFX_PlayX_hook },
{ 0x0045afbe, SFX_PlayX_hook },
{ 0x0045e253, SFX_PlayX_hook },
{ 0x0045e28b, SFX_PlayX_hook },
{ 0x0046afe7, SFX_PlayX_hook },
{ 0x0046b7c3, SFX_PlayX_hook },
{ 0x0046b7e8, SFX_PlayX_hook },
{ 0x0046ba57, SFX_PlayX_hook },
{ 0x0046bad4, SFX_PlayX_hook },
{ 0x0046c27b, SFX_PlayX_hook },
{ 0x0046e06e, SFX_PlayX_hook },
{ 0x0046e1a4, SFX_PlayX_hook },
{ 0x0046e1c1, SFX_PlayX_hook },
{ 0x00470791, SFX_PlayX_hook },
{ 0x004707d2, SFX_PlayX_hook },
{ 0x004707e8, SFX_PlayX_hook },
{ 0x00472c78, SFX_PlayX_hook },
{ 0x00472d28, SFX_PlayX_hook },
{ 0x00472d44, SFX_PlayX_hook },
{ 0x00472e57, SFX_PlayX_hook },
{ 0x004732f0, SFX_PlayX_hook },
{ 0x00473359, SFX_PlayX_hook },
{ 0x004733ca, SFX_PlayX_hook },
{ 0x00476f6b, SFX_PlayX_hook },
{ 0x00476fc0, SFX_PlayX_hook },
{ 0x00477015, SFX_PlayX_hook },
{ 0x00477083, SFX_PlayX_hook },
{ 0x004770fb, SFX_PlayX_hook },
{ 0x00477391, SFX_PlayX_hook },
{ 0x00477506, SFX_PlayX_hook },
{ 0x00477564, SFX_PlayX_hook },
{ 0x00477578, SFX_PlayX_hook },
{ 0x004775c3, SFX_PlayX_hook },
{ 0x00477d92, SFX_PlayX_hook },
{ 0x00479dbf, SFX_PlayX_hook },
{ 0x00479df6, SFX_PlayX_hook },
{ 0x00479e1c, SFX_PlayX_hook },
{ 0x0047bec5, SFX_PlayX_hook },
{ 0x0047bf13, SFX_PlayX_hook },
{ 0x0047c097, SFX_PlayX_hook },
{ 0x0047c0d7, SFX_PlayX_hook },
{ 0x0047c186, SFX_PlayX_hook },
{ 0x0047c1bd, SFX_PlayX_hook },
{ 0x0047cb20, SFX_PlayX_hook },
{ 0x0048044f, SFX_PlayX_hook },
{ 0x0048088a, SFX_PlayX_hook },
{ 0x004808c1, SFX_PlayX_hook },
{ 0x0048091f, SFX_PlayX_hook },
{ 0x00480943, SFX_PlayX_hook },
{ 0x00480c92, SFX_PlayX_hook },
{ 0x00480cc9, SFX_PlayX_hook },
{ 0x00480cf7, SFX_PlayX_hook },
{ 0x00480df7, SFX_PlayX_hook },
{ 0x00480e2e, SFX_PlayX_hook },
{ 0x00480e5c, SFX_PlayX_hook },
{ 0x00481047, SFX_PlayX_hook },
{ 0x004810f7, SFX_PlayX_hook },
{ 0x00481305, SFX_PlayX_hook },
{ 0x00481338, SFX_PlayX_hook },
{ 0x00481376, SFX_PlayX_hook },
{ 0x00482a35, SFX_PlayX_hook },
{ 0x004838b5, SFX_PlayX_hook },
{ 0x004840c3, SFX_PlayX_hook },
{ 0x00484146, SFX_PlayX_hook },
{ 0x004841e3, SFX_PlayX_hook },
{ 0x0048496f, SFX_PlayX_hook },
{ 0x00484a53, SFX_PlayX_hook },
{ 0x00484af2, SFX_PlayX_hook },
{ 0x00484b21, SFX_PlayX_hook },
{ 0x00484b51, SFX_PlayX_hook },
{ 0x004857f6, SFX_PlayX_hook },
{ 0x00485bc5, SFX_PlayX_hook },
{ 0x00485c94, SFX_PlayX_hook },
{ 0x00485cc8, SFX_PlayX_hook },
{ 0x00486771, SFX_PlayX_hook },
{ 0x004867b0, SFX_PlayX_hook },
{ 0x00486abf, SFX_PlayX_hook },
{ 0x00486b01, SFX_PlayX_hook },
{ 0x00486b15, SFX_PlayX_hook },
{ 0x00489ff5, SFX_PlayX_hook },
{ 0x0048d25d, SFX_PlayX_hook },
{ 0x0048d278, SFX_PlayX_hook },
{ 0x0048e6ff, SFX_PlayX_hook },
{ 0x0048e78a, SFX_PlayX_hook },
{ 0x0048ec0b, SFX_PlayX_hook },
{ 0x0048ec2d, SFX_PlayX_hook },
{ 0x0048ec4f, SFX_PlayX_hook },
{ 0x0048ec6e, SFX_PlayX_hook },
{ 0x0048ec7d, SFX_PlayX_hook },
{ 0x004919a9, SFX_PlayX_hook },
{ 0x004919c5, SFX_PlayX_hook },
{ 0x004919d0, SFX_PlayX_hook },
{ 0x004919ef, SFX_PlayX_hook },
{ 0x00491a09, SFX_PlayX_hook },
{ 0x00493bc1, SFX_PlayX_hook },
{ 0x00496581, SFX_PlayX_hook },
{ 0x0049689a, SFX_PlayX_hook },
{ 0x00497ab5, SFX_PlayX_hook },
{ 0x00497ac0, SFX_PlayX_hook },
{ 0x00497aed, SFX_PlayX_hook },
{ 0x00497b02, SFX_PlayX_hook },
{ 0x00497b17, SFX_PlayX_hook },
{ 0x00497b29, SFX_PlayX_hook },
{ 0x0049871d, SFX_PlayX_hook },
{ 0x00498c33, SFX_PlayX_hook },
{ 0x0049a287, SFX_PlayX_hook },
{ 0x0049a301, SFX_PlayX_hook },
{ 0x0049a316, SFX_PlayX_hook },
{ 0x0049a33c, SFX_PlayX_hook },
{ 0x0049a354, SFX_PlayX_hook },
{ 0x0049a37d, SFX_PlayX_hook },
{ 0x0049a395, SFX_PlayX_hook },
{ 0x0049a3be, SFX_PlayX_hook },
{ 0x0049a3d3, SFX_PlayX_hook },
{ 0x0049a4ea, SFX_PlayX_hook },
{ 0x0049a512, SFX_PlayX_hook },
{ 0x0049a542, SFX_PlayX_hook },
{ 0x0049a55e, SFX_PlayX_hook },
{ 0x0049a589, SFX_PlayX_hook },
{ 0x0049a5b1, SFX_PlayX_hook },
{ 0x0049a5cd, SFX_PlayX_hook },
{ 0x0049a5f5, SFX_PlayX_hook },
{ 0x0049a611, SFX_PlayX_hook },
{ 0x0049a636, SFX_PlayX_hook },
{ 0x0049a64f, SFX_PlayX_hook },
{ 0x0049a674, SFX_PlayX_hook },
{ 0x0049a757, SFX_PlayX_hook },
{ 0x0049b41f, SFX_PlayX_hook },
{ 0x0049b560, SFX_PlayX_hook },
{ 0x0049b5b4, SFX_PlayX_hook },
{ 0x0049bb3a, SFX_PlayX_hook },
{ 0x0049bbc7, SFX_PlayX_hook },
{ 0x0049be09, SFX_PlayX_hook },
{ 0x0049ce82, SFX_PlayX_hook },
{ 0x0049cf2b, SFX_PlayX_hook },
{ 0x0049cf49, SFX_PlayX_hook },
{ 0x0049d44c, SFX_PlayX_hook },
{ 0x0049e731, SFX_PlayX_hook },
{ 0x004a0b3b, SFX_PlayX_hook },
{ 0x004a0b85, SFX_PlayX_hook },
{ 0x004a0bf7, SFX_PlayX_hook },
{ 0x004a0c6a, SFX_PlayX_hook },
{ 0x004a0c8f, SFX_PlayX_hook },
{ 0x004a0e81, SFX_PlayX_hook },
{ 0x004a3761, SFX_PlayX_hook },
{ 0x004a37e0, SFX_PlayX_hook },
{ 0x004a4f66, SFX_PlayX_hook },
{ 0x004a4f8e, SFX_PlayX_hook },
{ 0x004a606d, SFX_PlayX_hook },
{ 0x004a60b2, SFX_PlayX_hook },
{ 0x004a60d8, SFX_PlayX_hook },
{ 0x004a60ff, SFX_PlayX_hook },
{ 0x004a6129, SFX_PlayX_hook },
{ 0x004a6193, SFX_PlayX_hook },
{ 0x004acf22, SFX_PlayX_hook },
{ 0x004b3b50, SFX_PlayX_hook },
{ 0x004b3c86, SFX_PlayX_hook },
{ 0x004b3df2, SFX_PlayX_hook },
{ 0x004baca1, SFX_PlayX_hook },
{ 0x004bad32, SFX_PlayX_hook },
{ 0x004bad8b, SFX_PlayX_hook },
{ 0x004bc283, SFX_PlayX_hook },
{ 0x004bc2a5, SFX_PlayX_hook },
{ 0x004bc2d0, SFX_PlayX_hook },
{ 0x004bc30c, SFX_PlayX_hook },
{ 0x004c0165, SFX_PlayX_hook },
{ 0x004c01d8, SFX_PlayX_hook },
{ 0x004c0293, SFX_PlayX_hook },
{ 0x004c02e8, SFX_PlayX_hook },
{ 0x004c04cb, SFX_PlayX_hook },
{ 0x004c0543, SFX_PlayX_hook },
{ 0x004c055f, SFX_PlayX_hook },
{ 0x004c0593, SFX_PlayX_hook },
{ 0x004c069f, SFX_PlayX_hook },
{ 0x004c0765, SFX_PlayX_hook },
{ 0x004c0817, SFX_PlayX_hook },
{ 0x004c0902, SFX_PlayX_hook },
{ 0x004c0a6d, SFX_PlayX_hook },
{ 0x004c0ab1, SFX_PlayX_hook },
{ 0x004c0d18, SFX_PlayX_hook },
{ 0x004c0ddd, SFX_PlayX_hook },
{ 0x004c0eac, SFX_PlayX_hook },
{ 0x004c0f30, SFX_PlayX_hook },
{ 0x004c3966, SFX_PlayX_hook },
{ 0x004c3aa2, SFX_PlayX_hook },
{ 0x004c3ba7, SFX_PlayX_hook },
{ 0x004c3be3, SFX_PlayX_hook },
{ 0x004ca436, SFX_PlayX_hook },
{ 0x004cc206, SFX_PlayX_hook },
{ 0x004cc230, SFX_PlayX_hook },


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