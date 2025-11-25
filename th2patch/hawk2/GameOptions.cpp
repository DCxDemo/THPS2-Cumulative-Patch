#include "stdafx.h"

#include "lib\ini\IniReader.h"
#include "lib\ini\IniWriter.h"

#include "GameOptions.h"
#include "patchStuff.h"

char* SectionPatch = "PATCH";
char* SectionVideo = "VIDEO";
char* SectionInput = "INPUT";
char* SectionMusic = "MUSIC";

GameOptions::GameOptions()
{
	iniPath = "./TH2_OPT.CFG";
}

void GameOptions::Load()
{
	totalTracks = CountSongs();

	CIniReader* ini = new CIniReader(iniPath);

	printf_s("Loading settings from %s\r\n", iniPath);

	//patch section
	CurrentGame = ini->ReadString(SectionPatch, "Game", "THPS2");
	DickSwap = ini->ReadString(SectionPatch, "DickSwap", "");
	SkipIntro = ini->ReadBool(SectionPatch, "SkipIntro", false);
	SeparateSaves = ini->ReadBool(SectionPatch, "SeparateSaves", true);
	AddSkins = ini->ReadBool(SectionPatch, "MoreSkins", false);

	FreeStats = ini->ReadBool(SectionPatch, "FreeStats", false);
	DisableVisToggle = ini->ReadBool(SectionPatch, "DisableVisToggle", false);
	DisableSky = ini->ReadBool(SectionPatch, "DisableSky", false);
	RailBalanceBar = ini->ReadBool(SectionPatch, "RailBalanceBar", true);
	FontScale = ini->ReadFloat(SectionPatch, "FontScale", 1.0f);
	SimulateLoading = ini->ReadInt(SectionPatch, "SimulateLoading", 0);

	//video section
	ShowHUD = ini->ReadBool(SectionVideo, "ShowHUD", true);
	DrawShadow = ini->ReadBool(SectionVideo, "DrawShadow", true);
	Force32bpp = ini->ReadBool(SectionVideo, "Force32bpp", true);
	UnlockFPS = ini->ReadBool(SectionVideo, "UnlockFps", true);
	DisableNewTex = ini->ReadBool(SectionVideo, "DisableNewTex", false);
	ResX = ini->ReadInt(SectionVideo, "ResX", DEFAULT_WIDTH);
	ResY = ini->ReadInt(SectionVideo, "ResY", DEFAULT_HEIGHT);
	DynamicLighting = ini->ReadBool(SectionVideo, "DynamicLighting", true);
	TextureFiltering = ini->ReadBool(SectionVideo, "TextureFiltering", true);

	bool overrideFov = ini->ReadBool(SectionVideo, "OverrideFov", false);
	FovScale = overrideFov ? ini->ReadFloat(SectionVideo, "FovScale", 1.0) : 1.0;

	//input section
	XInput = ini->ReadBool(SectionInput, "XInput", true);
	StickDeadzone = ini->ReadInt(SectionInput, "StickDeadzone", DEFAULT_DEADZONE);
	Vibration = ini->ReadBool(SectionInput, "Vibration", true);
	BigDrop = ini->ReadBool(SectionInput, "BigDrop", true);
	Manuals = ini->ReadBool(SectionInput, "Manuals", true);
	AutoKick = ini->ReadBool(SectionInput, "AutoKick", true);
	FastQuit = ini->ReadBool(SectionInput, "FastQuit", true);

	//music section
	PlayRandom = ini->ReadBool(SectionMusic, "Random", true);
	Fade = ini->ReadBool(SectionMusic, "Fade", true);
	ShowTitle = ini->ReadBool(SectionMusic, "ShowTitle", true);
	PlayAmbience = ini->ReadBool(SectionMusic, "PlayAmbience", true);
	SeparateTracks = ini->ReadBool(SectionMusic, "SeparateTracks", true);

	delete ini;

	Save();

	printf_s("Settings loaded.\r\n");
}

void GameOptions::Save()
{
	CIniWriter* ini = new CIniWriter(iniPath);

	printf_s("Saving settings to %s\r\n", iniPath);

	//patch section
	ini->WriteString(SectionPatch, "Game", &CurrentGame[0]);
	ini->WriteInt(SectionPatch, "SeparateSaves", SeparateSaves);
	ini->WriteInt(SectionPatch, "SkipIntro", SkipIntro);
	ini->WriteInt(SectionPatch, "MoreSkins", AddSkins);
	ini->WriteString(SectionPatch, "DickSwap", &DickSwap[0]);
	ini->WriteInt(SectionPatch, "FreeStats", FreeStats);
	ini->WriteInt(SectionPatch, "DisableVisToggle", DisableVisToggle);
	ini->WriteInt(SectionPatch, "DisableSky", DisableSky);
	ini->WriteInt(SectionPatch, "SimulateLoading", SimulateLoading);

	//video section
	ini->WriteInt(SectionVideo, "ShowHUD", ShowHUD);
	ini->WriteInt(SectionVideo, "DrawShadow", DrawShadow);
	ini->WriteInt(SectionVideo, "Force32bpp", Force32bpp);
	ini->WriteInt(SectionVideo, "UnlockFps", UnlockFPS);
	ini->WriteInt(SectionVideo, "DisableNewTex", DisableNewTex);
	ini->WriteInt(SectionVideo, "ResX", ResX);
	ini->WriteInt(SectionVideo, "ResY", ResY);
	ini->WriteInt(SectionVideo, "DynamicLighting", DynamicLighting);
	ini->WriteInt(SectionVideo, "TextureFiltering", TextureFiltering);

	//input section
	ini->WriteInt(SectionInput, "XInput", XInput);
	ini->WriteInt(SectionInput, "StickDeadzone", StickDeadzone);
	ini->WriteInt(SectionInput, "Vibration", Vibration);
	ini->WriteInt(SectionInput, "BigDrop", BigDrop);
	ini->WriteInt(SectionInput, "Manuals", Manuals);

	//music section
	ini->WriteInt(SectionMusic, "Random", PlayRandom);
	ini->WriteInt(SectionMusic, "Fade", Fade);
	ini->WriteInt(SectionMusic, "ShowTitle", ShowTitle);
	ini->WriteInt(SectionMusic, "PlayAmbience", PlayAmbience);
	ini->WriteInt(SectionMusic, "SeparateTracks", SeparateTracks);

	delete ini;

	printf_s("Settings saved.\r\n");
}