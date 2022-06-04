#pragma once

#include "types.h"
#include "lib/xinput/CXBOXController.h"
#include "thawk2/Sfx.h"
#include "patchStuff.h"

int* ShatterSound = (int*)0x5691a4;

#define GLASS_SHATTER 0x2A
#define DEFAULT_VOLUME 0x2000

int playsshatter = 0;

void Shatter_MaybeMakeGlassShatterSound()
{
	if (*ShatterSound)
	{
		SFX_PlayX(GLASS_SHATTER, DEFAULT_VOLUME, 0);
		playsshatter = 15;
		*ShatterSound = 0;
	}
}

void CP_ShatterUpdate(CXBOXController *input)
{
	if (playsshatter > 0)
	{
		input->Vibrate(18000, 18000, options.Vibration);
		playsshatter--;
	}
}