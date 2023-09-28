#pragma once

#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720
#define DEFAULT_DEADZONE 10000

using namespace std;

class GameOptions
{
private:
	string iniPath;

public:
	//patch
	string CurrentGame = "THPS2";
	bool SeparateSaves = true;
	bool SkipIntro = false;
	bool AddSkins = false;
	string DickSwap = "";
	bool FreeStats = false;
	bool DisableVisToggle = false;
	bool DisableSky = false;

	//video
	bool ShowHUD = true;
	bool DrawShadow = true;
	bool Force32bpp = true;
	bool UnlockFPS = true;
	bool DisableNewTex = false;
	float FOV = 0.83f;
	int ResX = DEFAULT_WIDTH;
	int ResY = DEFAULT_HEIGHT;
	float FontScale = 1.0;

	//input
	bool XInput = true;
	int StickDeadzone = DEFAULT_DEADZONE;
	bool Vibration = true;
	bool BigDrop = true;
	bool Manuals = true;

	//music
	bool Fade = true;
	bool PlayRandom = true;
	bool ShowTitle = true;
	bool PlayAmbience = true;
	bool SeparateTracks = true;

	int totalTracks = 0;

	GameOptions();
	void Save();
	void Load();
};