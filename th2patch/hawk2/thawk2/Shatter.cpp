#include "stdafx.h"
#include "thawk2/thawk2.h"
#include "../lib/xinput/CXBOXController.h"

#define SND_GLASS_SHATTER 0x2A
#define DEFAULT_VOLUME 0x2000


bool* ShatterSound = (bool*)0x5691a4;

void Shatter_MaybeMakeGlassShatterSound()
{
	if (!*ShatterSound) return;

	//play sound
	SFX_PlayX(SND_GLASS_SHATTER, DEFAULT_VOLUME, 0);

	//and vibrate
	PCINPUT_ActuatorOn_Hook(0, 8, 0, 127);
	PCINPUT_ActuatorOn_Hook(0, 4, 0, 200);

	*ShatterSound = false;
}