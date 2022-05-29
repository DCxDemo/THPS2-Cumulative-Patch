#pragma once

//sfx namespace is basically a wrapper for soundlib + game specific routines

typedef void(*SFX_InitAtStart_t)();
typedef void(*SFX_Init_t)(char* filename); //takes vab filename as param
typedef void(*SFX_SpoolInLevelSFX_t)(char* param_1);
typedef void(*SFX_SpoolOutLevelSFX_t)();
typedef void(*SFX_SpoolInMIDI_t)(); //unused
typedef void(*SFX_PlayX_t)(int sound_id, int volume); // <-- verify params number
typedef void(*SFX_PlayLR_t)(); //<--
typedef void(*SFX_PlayPos_t)(); //<--
typedef int(*SFX_GetVoicePitch_t)(int voice);
typedef void(*SFX_SetVoicePitch_t)(int voice, int pitch);
typedef void(*SFX_ModifyPos_t)(int ptr_sound, int pos); //assumed 2 pointers?
typedef void(*SFX_ModifyVol_t)(int ptr_sound, int vol_left, int vol_right);
typedef void(*SFX_LevelStart_t)();
typedef void(*SFX_Pause_t)();
typedef void(*SFX_Unpause_t)();
typedef void(*SFX_StopAll_t)();
typedef void(*SFX_Stop_t)(int ptr_sound); //is it ptr??
typedef void(*SFX_Off_t)();
typedef void(*SFX_SetReverbType_t)(char reverb_type);
typedef void(*SFX_ReverbOff_t)();
typedef void(*SFX_SetReverbDepth_t)(char depth_left, char depth_right);
typedef void(*SFX_MIDIFadeOut_t)(); //unused
typedef void(*SFX_MIDIFadeIn_t)(); //unused
typedef void(*SFX_MIDIChannelMute_t)(); //unused
typedef void(*SFX_ProcessingPerFrame_t)(); //unused

static const SFX_InitAtStart_t SFX_InitAtStart = (SFX_InitAtStart_t)0x4aa8c0;
static const SFX_Init_t SFX_Init = (SFX_Init_t)0x4aa900;
static const SFX_SpoolInLevelSFX_t SFX_SpoolInLevelSFX = (SFX_SpoolInLevelSFX_t)0x4aaa60;
static const SFX_SpoolOutLevelSFX_t SFX_SpoolOutLevelSFX = (SFX_SpoolOutLevelSFX_t)0x4aae90;
static const SFX_SpoolInMIDI_t SFX_SpoolInMIDI = (SFX_SpoolInMIDI_t)0x4aaec0;
static const SFX_PlayX_t SFX_PlayX = (SFX_PlayX_t)0x4aaf00;
static const SFX_PlayLR_t SFX_PlayLR = (SFX_PlayLR_t)0x4ab030;
static const SFX_PlayPos_t SFX_PlayPos = (SFX_PlayPos_t)0x4ab0b0;
static const SFX_GetVoicePitch_t SFX_GetVoicePitch = (SFX_GetVoicePitch_t)0x4ab150;
static const SFX_SetVoicePitch_t SFX_SetVoicePitch = (SFX_SetVoicePitch_t)0x4ab170;
static const SFX_ModifyPos_t SFX_ModifyPos = (SFX_ModifyPos_t)0x4ab190;
static const SFX_ModifyVol_t SFX_ModifyVol = (SFX_ModifyVol_t)0x4ab230;
static const SFX_LevelStart_t SFX_LevelStart = (SFX_LevelStart_t)0x4ab290;
static const SFX_Pause_t SFX_Pause = (SFX_Pause_t)0x4ab2a0;
static const SFX_Unpause_t SFX_Unpause = (SFX_Unpause_t)0x4ab2b0;
static const SFX_StopAll_t SFX_StopAll = (SFX_StopAll_t)0x4ab2c0;
static const SFX_Stop_t SFX_Stop = (SFX_Stop_t)0x4ab2d0;
static const SFX_Off_t SFX_Off = (SFX_Off_t)0x4ab2f0;
static const SFX_SetReverbType_t SFX_SetReverbType = (SFX_SetReverbType_t)0x4ab300;
static const SFX_ReverbOff_t SFX_ReverbOff = (SFX_ReverbOff_t)0x4ab470;
static const SFX_SetReverbDepth_t SFX_SetReverbDepth = (SFX_SetReverbDepth_t)0x4ab480;
static const SFX_MIDIFadeOut_t SFX_MIDIFadeOut = (SFX_MIDIFadeOut_t)0x4ab510;
static const SFX_MIDIFadeIn_t SFX_MIDIFadeIn = (SFX_MIDIFadeIn_t)0x4ab530;
static const SFX_MIDIChannelMute_t SFX_MIDIChannelMute = (SFX_MIDIChannelMute_t)0x4ab540;
static const SFX_ProcessingPerFrame_t SFX_ProcessingPerFrame = (SFX_ProcessingPerFrame_t)0x4ab550;