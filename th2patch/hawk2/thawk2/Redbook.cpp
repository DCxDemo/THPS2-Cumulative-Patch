#include "stdafx.h"
#include "thawk2\Redbook.h"
#include "thawk2\Globals.h"
#include "thawk2\_old.h"

void Redbook_XAPause(bool state)
{
    if (*Redbook_XAPaused != state) {
        PCMOVIE_Pause(state);
        *Redbook_XAPaused = state;
    }
}

/*
void Redbook_XAUpdate()
{
    if (*Redbook_XAFading)
        Redbook_XAUpdateVolume();

    if (!*Redbook_XAValid || *Redbook_XAPaused) return;

    if (*Redbook_XACompleteTimer > 0) {
        *Redbook_XACompleteTimer--;
        return;
    }

    if (!*InFrontEnd) {

        if (*XALEVEL > 0) {
            if (Redbook_XAPlayingAmbient())
            {
                Redbook_XANextTrack(1);
                return;
            }

            if (*XALEVEL != 0)
            {
                if (PCMOVIE_XADone()) {
                    Redbook_XANextTrack(1);
                    return;
                }
            }
        }

        if (!Redbook_XAPlayingAmbient()) {
            Redbook_XANextTrack(1);
            return;
        }
    }
    else
    {
        if (PCMOVIE_XADone()) {
            Redbook_XANextTrack(1);
        }
    }

LAB_004a9798:

    return;
}
*/


void Redbook_XABeginFade()
{
    *Redbook_XAFadeScale = 255;
    *Redbook_XAFading = true;
}

void Redbook_XAUpdateVolume()
{
    if (*Redbook_XAFading) {

        *Redbook_XAFadeScale -= 3;

        if (*Redbook_XAFadeScale < 0)
            *Redbook_XAFadeScale = 0;
    }

    int vol = (*Redbook_XAFadeScale * *XALEVEL) / 255;

    //limit volume
    if (vol > 255) vol = 255;

    PCMOVIE_SetXAVolume(vol, vol);
}

void Redbook_XAInit()
{
    *Redbook_XAValid = true;
    *Redbook_XACompleteTimer = 30;
    *Redbook_XAPaused = false;
    *Redbook_XATryAgain = 0;
    *Redbook_XASeeking = 0;
    *Redbook_XACurrentSector = *Redbook_XAStartSector;
    *Redbook_XAEndSector = *Redbook_XAStartSector;
    *Redbook_XACheckSectorOnVSync = 0;
    *Redbook_XAModeSet = 0;
    *Redbook_XACurrentGroup = 0;
    *Redbook_XACurrentChannel = 0;
}

void Redbook_XAStop()
{
    PCMOVIE_XAStop();
    *Redbook_XACheckSectorOnVSync = 0;
    *Redbook_XACompleteTimer = 30;
    *Redbook_XAModeSet = 0;
    Redbook_XAPause(true);
}

bool Redbook_XAPlayingAmbient()
{
    // definitely not playing in menu
    if (*InFrontEnd) return false;

    //if music is disabled and th1 levels?
    if (*XALEVEL == 0 && *GLevel > 9) return true;

    return (*Redbook_XACurrentChannel + *Redbook_XACurrentGroup * 8) < 16;
}

void Redbook_XARemember(SONG_POS* pSongPos)
{
    pSongPos->Channel = *Redbook_XACurrentGroup;
    pSongPos->Group = *Redbook_XACurrentChannel;
    pSongPos->Sector = *Redbook_XACurrentSector;
}

void Redbook_XARestore(SONG_POS* pSongPos)
{
    if (*Redbook_XACurrentGroup == pSongPos->Channel && *Redbook_XACurrentChannel == pSongPos->Group)
    {
        *Redbook_XACurrentSector = pSongPos->Sector;
    }
    else
    {
        Redbook_XAStop();
        Redbook_XAPlay(pSongPos->Channel, pSongPos->Group);
    }
}

int Redbook_XACurrentTrack()
{
    return *Redbook_XACurrentChannel + *Redbook_XACurrentGroup * 8 - 15;
}