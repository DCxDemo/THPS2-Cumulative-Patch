#include "stdafx.h"
#include "..\patch\hook.h"

namespace Redbook
{
    typedef struct {
        int slot;
        string artist;
        string title;
        string filename;
    } Song;

    typedef struct SONG_POS
    {
        int Channel;
        int Group;
        int Sector;
    } SONG_POS;

    extern Hook::Reroute* pHookList;

    extern string playingName;
    extern string playingFile;
    extern Song song;



    //some unused func 0x4a9290 Redbook_SetXAMode?
    //typedef void(*Redbook_XABeginFade_t)();
    //typedef void(*Redbook_XAUpdateVolume_t)();
    //typedef void(*Redbook_XAInit_t)();
    //some unused func 0x4a93c0 Redbook_XASeek?
    typedef void(*Redbook_XAPlay_t)(int group, int channel);
    //typedef void(*Redbook_XAStop_t)();
    //typedef void(*Redbook_XANextTrack_t)(int num); //tracks to skip?
    //typedef void(*Redbook_XAPause_t)(bool state);
    //typedef void(*Redbook_XAUpdate_t)();
    //typedef bool(*Redbook_XAPlayingAmbient_t)();
    //typedef void(*Redbook_XARemember_t)(void* songPos); //SONG_POS struct
    //typedef void(*Redbook_XARestore_t)(void* songPos); //SONG_POS struct
    //typedef int(*Redbook_XACurrentTrack_t)();


    //some unused func 0x4a9290, sets xa mode to 1
    //static const Redbook_XABeginFade_t Redbook_XABeginFade = (Redbook_XABeginFade_t)0x4a92a0;
    //static const Redbook_XAUpdateVolume_t Redbook_XAUpdateVolume = (Redbook_XAUpdateVolume_t)0x4a92c0;
    //static const Redbook_XAInit_t Redbook_XAInit = (Redbook_XAInit_t)0x4a9370;
    //some unused func 0x4a93c0, sets seek to 0
    //static const Redbook_XAPlay_t Redbook_XAPlay = (Redbook_XAPlay_t)0x4a93e0;
    //static const Redbook_XAStop_t Redbook_XAStop = (Redbook_XAStop_t)0x4a9560;
    //static const Redbook_XANextTrack_t Redbook_XANextTrack = (Redbook_XANextTrack_t)0x4a9590;
    //static const Redbook_XAPause_t Redbook_XAPause = (Redbook_XAPause_t)0x4a9700;
    //static const Redbook_XAUpdate_t Redbook_XAUpdate = (Redbook_XAUpdate_t)0x4a9730;
    //static const Redbook_XAPlayingAmbient_t Redbook_XAPlayingAmbient = (Redbook_XAPlayingAmbient_t)0x4a97b0;
    //static const Redbook_XARemember_t Redbook_XARemember = (Redbook_XARemember_t)0x4a97f0;
    //static const Redbook_XARestore_t Redbook_XARestore = (Redbook_XARestore_t)0x4a9860;
    //static const Redbook_XACurrentTrack_t Redbook_XACurrentTrack = (Redbook_XACurrentTrack_t)0x4a98f0;

    void Redbook_XABeginFade();
    void Redbook_XAUpdateVolume();
    void Redbook_XAInit();
    void Redbook_XAPlay();
    //
    void Redbook_XAStop();
    void Redbook_XANextTrack(int num);
    void Redbook_XAPause(bool state);
    void Redbook_XAUpdate();
    bool Redbook_XAPlayingAmbient();
    void Redbook_XARemember(SONG_POS* pSongPos);
    void Redbook_XARestore(SONG_POS* pSongPos);
    int Redbook_XACurrentTrack();
}