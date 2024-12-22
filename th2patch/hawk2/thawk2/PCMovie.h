#include "stdafx.h"
#include "..\patch\hook.h"

namespace PCMovie
{
	extern bool* gMusicPlaying;

	typedef void(*SetupFullScreenMovie_t)();
	typedef void(*DrawFullScreenMovie_t)();
	typedef void(*InitBink_thunk_t)();
	typedef void(*InitBink_t)();
	typedef int(*PCMOVIE_PlayMovieFile_t)(char*);
	typedef int(*CreateBinkSurface_t)();
	typedef int(*StartBinkMovie_t)(char*, int, int);
	typedef int(*NextBinkFrame_t)();
	typedef void(*CloseBinkMovie_t)();
	typedef void(*BinkMovieUpdate_t)();
	typedef void(*PCMOVIE_Pause_t)(bool state);
	typedef void(*PCMOVIE_DrawWindow_t)(int);
	typedef char*(*PCMOVIE_GetMovieName_t)(int index);
	typedef void(*PCMOVIE_PlayGameFMV_t)();
	typedef void(*PCMOVIE_StartFMV_t)();
	typedef void(*PCMOVIE_StopFMV_t)();
	typedef void(*PCMOVIE_Update_t)();
	typedef void(*MusicThreadProc_t)();
	typedef bool(*PCMOVIE_StartMusic_t)(char*);
	typedef void(*PCMOVIE_SetXAVolume_t)(int left, int right);
	//typedef void(*PCMOVIE_XAPlay_t)(int group, int channel);
	typedef void(*PCMOVIE_XAStop_t)();
	//typedef bool(*PCMOVIE_XADone_t)();

	static const SetupFullScreenMovie_t SetupFullScreenMovie = (SetupFullScreenMovie_t)0x004e28f0;
	static const DrawFullScreenMovie_t DrawFullScreenMovie = (DrawFullScreenMovie_t)0x004e2c50;
	static const InitBink_thunk_t InitBink_thunk = (InitBink_thunk_t)0x004e3050;
	static const InitBink_t InitBink = (InitBink_t)0x004e3060;
	static const PCMOVIE_PlayMovieFile_t PCMOVIE_PlayMovieFile = (PCMOVIE_PlayMovieFile_t)0x004e3090;
	static const CreateBinkSurface_t CreateBinkSurface = (CreateBinkSurface_t)0x004e31f0;
	static const StartBinkMovie_t StartBinkMovie = (StartBinkMovie_t)0x004e3760;
	static const NextBinkFrame_t NextBinkFrame = (NextBinkFrame_t)0x004e3a60;
	static const CloseBinkMovie_t CloseBinkMovie = (CloseBinkMovie_t)0x004e3f70;
	static const BinkMovieUpdate_t BinkMovieUpdate = (BinkMovieUpdate_t)0x004e4020;
	static const PCMOVIE_Pause_t PCMOVIE_Pause = (PCMOVIE_Pause_t)0x004e4040;
	static const PCMOVIE_DrawWindow_t PCMOVIE_DrawWindow = (PCMOVIE_DrawWindow_t)0x004e40d0;
	static const PCMOVIE_GetMovieName_t PCMOVIE_GetMovieName = (PCMOVIE_GetMovieName_t)0x004e4240;
	static const PCMOVIE_PlayGameFMV_t PCMOVIE_PlayGameFMV = (PCMOVIE_PlayGameFMV_t)0x004e4260;
	static const PCMOVIE_StartFMV_t PCMOVIE_StartFMV = (PCMOVIE_StartFMV_t)0x004e42b0;
	static const PCMOVIE_StopFMV_t PCMOVIE_StopFMV = (PCMOVIE_StopFMV_t)0x004e4310;
	static const PCMOVIE_Update_t PCMOVIE_Update = (PCMOVIE_Update_t)0x004e4390;
	static const MusicThreadProc_t MusicThreadProc = (MusicThreadProc_t)0x004e43a0;
	static const PCMOVIE_StartMusic_t PCMOVIE_StartMusic = (PCMOVIE_StartMusic_t)0x004e4430;
	static const PCMOVIE_SetXAVolume_t PCMOVIE_SetXAVolume = (PCMOVIE_SetXAVolume_t)0x004e44a0;
	//static const PCMOVIE_XAPlay_t PCMOVIE_XAPlay = (PCMOVIE_XAPlay_t)0x004e44e0;
	void PCMOVIE_XAPlay(int group, int channel);
	static const PCMOVIE_XAStop_t PCMOVIE_XAStop = (PCMOVIE_XAStop_t)0x004e4540;
	//static const PCMOVIE_XADone_t PCMOVIE_XADone = (PCMOVIE_XADone_t)0x004e45b0;
	bool PCMOVIE_XADone();
}