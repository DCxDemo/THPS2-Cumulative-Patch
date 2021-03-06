#include "stdafx.h"

#include "lib\ini\IniReader.h"
#include "lib\ini\IniWriter.h"

#include "GameOptions.h"
#include "patchStuff.h"

GameOptions::GameOptions()
{
	iniPath = "./th2_opt.cfg";
}

void GameOptions::Load()
{
	totalTracks = CountSongs();

	CIniReader* ini = new CIniReader(&iniPath[0]);

	printf("Loading settings from %s\r\n", iniPath.c_str());

	//patch section
	CurrentGame = ini->ReadString("PATCH", "Game", "THPS2");
	SeparateSaves = ini->ReadBool("PATCH", "SeparateSaves", true);
	SkipIntro = ini->ReadBool("PATCH", "SkipIntro", false);
	AddSkins = ini->ReadBool("PATCH", "MoreSkins", false);
	DickSwap = ini->ReadString("PATCH", "DickSwap", "");
	FreeStats = ini->ReadBool("PATCH", "FreeStats", false);
	DisableVisToggle = ini->ReadBool("PATCH", "DisableVisToggle", false);
	DisableSky = ini->ReadBool("PATCH", "DisableSky", false);

	//video section
	ShowHUD = ini->ReadBool("VIDEO", "ShowHUD", true);
	DrawShadow = ini->ReadBool("VIDEO", "DrawShadow", true);
	Force32bpp = ini->ReadBool("VIDEO", "Force32bpp", true);
	UnlockFPS = ini->ReadBool("VIDEO", "UnlockFps", true);
	DisableNewTex = ini->ReadBool("VIDEO", "DisableNewTex", false);
	ResX = ini->ReadInt("VIDEO", "ResX", DEFAULT_WIDTH);
	ResY = ini->ReadInt("VIDEO", "ResY", DEFAULT_HEIGHT);
	FOV = ini->ReadFloat("VIDEO", "FOV", 0.83f);

	//input section
	XInput = ini->ReadBool("INPUT", "XInput", true);
	StickDeadzone = ini->ReadInt("INPUT", "StickDeadzone", DEFAULT_DEADZONE);
	Vibration = ini->ReadBool("INPUT", "Vibration", true);
	BigDrop = ini->ReadBool("INPUT", "BigDrop", true);

	//music section
	PlayRandom = ini->ReadBool("MUSIC", "Random", true);
	Fade = ini->ReadBool("MUSIC", "Fade", true);
	ShowTitle = ini->ReadBool("MUSIC", "ShowTitle", true);
	PlayAmbience = ini->ReadBool("MUSIC", "PlayAmbience", true);
	SeparateTracks = ini->ReadBool("MUSIC", "SeparateTracks", true);

	delete ini;

	Save();

	printf("Settings loaded.\r\n");
}

void GameOptions::Save()
{
	CIniWriter* ini = new CIniWriter(&iniPath[0]);

	printf("Saving settings to %s\r\n", iniPath.c_str());

	//patch section
	ini->WriteString("PATCH", "Game", &CurrentGame[0]);
	ini->WriteInt("PATCH", "SeparateSaves", SeparateSaves);
	ini->WriteInt("PATCH", "SkipIntro", SkipIntro);
	ini->WriteInt("PATCH", "MoreSkins", AddSkins);
	ini->WriteString("PATCH", "DickSwap", &DickSwap[0]);
	ini->WriteInt("PATCH", "FreeStats", FreeStats);
	ini->WriteInt("PATCH", "DisableVisToggle", DisableVisToggle);
	ini->WriteInt("PATCH", "DisableSky", DisableSky);

	//video section
	ini->WriteInt("VIDEO", "ShowHUD", ShowHUD);
	ini->WriteInt("VIDEO", "DrawShadow", DrawShadow);
	ini->WriteInt("VIDEO", "Force32bpp", Force32bpp);
	ini->WriteInt("VIDEO", "UnlockFps", UnlockFPS);
	ini->WriteInt("VIDEO", "DisableNewTex", DisableNewTex);
	ini->WriteInt("VIDEO", "ResX", ResX);
	ini->WriteInt("VIDEO", "ResY", ResY);
	ini->WriteFloat("VIDEO", "FOV", FOV);

	//input section
	ini->WriteInt("INPUT", "XInput", XInput);
	ini->WriteInt("INPUT", "StickDeadzone", StickDeadzone);
	ini->WriteInt("INPUT", "Vibration", Vibration);
	ini->WriteInt("INPUT", "BigDrop", BigDrop);

	//music section
	ini->WriteInt("MUSIC", "Random", PlayRandom);
	ini->WriteInt("MUSIC", "Fade", Fade);
	ini->WriteInt("MUSIC", "ShowTitle", ShowTitle);
	ini->WriteInt("MUSIC", "PlayAmbience", PlayAmbience);
	ini->WriteInt("MUSIC", "SeparateTracks", SeparateTracks);

	delete ini;

	printf("Settings saved.\r\n");
}