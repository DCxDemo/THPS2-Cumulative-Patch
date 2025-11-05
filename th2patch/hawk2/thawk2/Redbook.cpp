#include "stdafx.h"

#include "types.h"
#include "thawk2\thawk2.h"
#include "_old.h"
#include "hawk2_utils.h"

namespace Redbook
{
    //int totalTracks = 0;
    extern int playingTrack = -1;

    string playingName;
    string playingFile;

    Song song;

    void Redbook_XABeginFade()
    {
        if (options.Fade)
        {
            *Redbook_XAFadeScale = 255;
            *Redbook_XAFading = true;
        }
    }

    void Redbook_XAUpdateVolume()
    {
        //spams in paused menu
        //printf("DECOMP Redbook_XAUpdateVolume()\n");

        if (*XALEVEL >= 256)
        {
            printf_s("Bad volume: %i", *XALEVEL);
            return;
        }

        if (*Redbook_XAFading) {

            *Redbook_XAFadeScale -= 3;

            if (*Redbook_XAFadeScale < 0)
                *Redbook_XAFadeScale = 0;
        }

        int vol = (*Redbook_XAFadeScale * *XALEVEL) / 255;

        //limit volume
        if (vol > 255) vol = 255;

        PCMovie::PCMOVIE_SetXAVolume(vol, vol);
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

    void Redbook_XAPlay(int group, int channel)
    {
        PCMovie::PCMOVIE_XAPlay(group, channel);

        *Redbook_XACurrentGroup = group;
        *Redbook_XACurrentChannel = channel;

        if (*Redbook_XAValid) {

            *Redbook_XAPaused = false;
            *Redbook_XAFading = false;

            Redbook_XAUpdateVolume();

            *Redbook_XATryAgain = true;
        }
    }

    void Redbook_XAStop()
    {
        printf_s("DECOMP Redbook_XAStop()\n");

        PCMovie::PCMOVIE_XAStop();
        *Redbook_XACheckSectorOnVSync = 0;
        *Redbook_XACompleteTimer = 30;
        *Redbook_XAModeSet = 0;
        Redbook_XAPause(true);
    }

    void Redbook_XANextTrack(int inc)
    {
        printf_s("DECOMP Redbook_XANextTrack()\n");

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

            GetSong(playingTrack + 1);

            playingName = song.artist + " - " + song.title;
            playingFile = song.filename;

            //printf("Now playing: %s\n", playingName);

            if (options.ShowTitle && options.ShowHUD)
            {
                printf_s("looking for %s...\n", &playingFile[0]);

                if (FileIO::Exists("music\\", &playingFile[0]))
                {
                    //printf("exists: %i", exists);

                    Mess::Mess_DeleteAll();
                    DrawMessage(&playingName[0]);
                }
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
                PCMovie::PCMOVIE_SetXAVolume(*SFXLEVEL * 20, *SFXLEVEL * 20);
            }
        }
    }

    void Redbook_XAPause(bool state)
    {
        if (*Redbook_XAPaused != state) {
            PCMovie::PCMOVIE_Pause(state);
            *Redbook_XAPaused = state;
        }
    }

    void Redbook_XAUpdate()
    {
        // sir spams a lot
        //printf("DECOMP Redbook_XAUpdate()\n");

        if (*Redbook_XAFading)
            Redbook_XAUpdateVolume();

        if (!*Redbook_XAValid || *Redbook_XAPaused) return;

        if (*Redbook_XACompleteTimer > 0) {
            (*Redbook_XACompleteTimer)--;
            return;
        }

        if (PCMovie::PCMOVIE_XADone()) {
            Redbook_XANextTrack(1);
        }
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


    // === hook stuff ===

    Hook::Reroute hookList[] = {

        { 0x427130, Redbook_XABeginFade }, //credits
        { 0x466BA7, Redbook_XABeginFade },  //game_over

        { 0x451CDE, Redbook_XAUpdateVolume },   //front_update
        { 0x451F6F, Redbook_XAUpdateVolume },   //front_update
        { 0x484A0C, Redbook_XAUpdateVolume },   //???
        { 0x4A9525, Redbook_XAUpdateVolume },   //redbook xa play
        { 0x4A9739, Redbook_XAUpdateVolume },   //xaupdate?

        // Redbook_XAInit only called from Init_AtStart

        { 0x004a98cc, Redbook_XAStop },
        { 0x0048482a, Redbook_XAStop },
        { 0x0046a3c1, Redbook_XAStop },
        { 0x0045849e, Redbook_XAStop },
        { 0x0045199c, Redbook_XAStop },
        { 0x004270e2, Redbook_XAStop },
        { 0x004265ee, Redbook_XAStop },

        { 0x451DCF,	Redbook_XANextTrack }, //front_update
        { 0x451EC6,	Redbook_XANextTrack }, //front_update
        { 0x451F29, Redbook_XANextTrack }, //front_update
        { 0x46A3CA,	Redbook_XANextTrack }, //playaway
        { 0x48474F,	Redbook_XANextTrack }, //somewhere in options menu, volume screen probably 
        //{ 0x4A978F, Redbook_XANextTrack }, //XAUpdate
        //{ 0x4A97A3, Redbook_XANextTrack }, //XAUpdate

        { 0x004ab2b7,	Redbook_XAPause	 },
        { 0x004ab2a7,	Redbook_XAPause	 },
        { 0x004a957d,	Redbook_XAPause	 },
        { 0x004848da,	Redbook_XAPause	 },
        { 0x0048489c,	Redbook_XAPause	 },
        { 0x00451f52,	Redbook_XAPause	 },
        { 0x00451f03,	Redbook_XAPause	 },

        { 0x00426b2c, Redbook_XAUpdate },
        { 0x0046a115, Redbook_XAUpdate },
        { 0x00484a11, Redbook_XAUpdate },

        // Redbook_XAPlayingAmbient only called from XAUpdate

        { 0x44F41F, Redbook_XARemember },
        { 0x4A94D5, Redbook_XARemember },

        { 0x451F79, Redbook_XARestore }, // front_update

        { 0x0044dc0f, Redbook_XACurrentTrack },
        { 0x0044dbfe, Redbook_XACurrentTrack },
        

        //=========================
        { NULL, NULL }
    };

    Hook::Reroute* pHookList = &hookList[0];
}