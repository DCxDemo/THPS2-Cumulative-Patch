#include "stdafx.h"
#include "thawk2\thawk2.h"

namespace PCMovie
{
	bool* gMusicPlaying = (bool*)0x006a3930;

	void PCMOVIE_XAPlay(int group, int channel)
	{
		printf("DECOMP PCMOVIE_XAPlay()\n");

		int curTrack = channel + group * 8;

		//ambience track?
		if (curTrack < 15)
		{
			char buf[256];
			sprintf(buf, "%s%02i%s", "ltix", curTrack, ".dat");
			PCMovie::PCMOVIE_StartMusic(buf);
		}
		else
		{
			PCMovie::PCMOVIE_StartMusic(&Redbook::playingFile[0u]);
		}
	}

	bool PCMOVIE_XADone()
	{
		return !*gMusicPlaying;
	}
}