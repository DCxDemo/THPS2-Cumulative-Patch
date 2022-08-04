#include "stdafx.h"
#include "hawk2_utils.h"
#include "color.h"

#include "thawk2/Mess.h"
#include "thawk2/Sfx.h"
#include "thawk2/Soundlib.h"

void PlaySpecialSound()
{
	SOUNDLIB_Play(0xA2, 0x500, 0);
	//SFX_PlayX(0xA2, 0x500);
}

//this should be moved to mess.h
struct SMessageProg
{
	SMessageProg m1;
	SMessageProg m2;
	SMessageProg m3;
	SMessageProg m4;
	SMessageProg m5;
};

SMessage mess;
SMessageProg ms;

void SetupMessage(SMessageProg &message, int d, int ss, int es, ColorRGB sc, ColorRGB ec)
{
	message.Duration = d;
	message.StartScale = ss;
	message.EndScale = es;
	message.StartColor = sc;
	message.EndColor = ec;
}

SMessageProg DefaultMessage()
{
	return *(SMessageProg*)0x531CC8;
}

void LoadMessageProg()
{
	ms = DefaultMessage();

	SetupMessage(ms.m1, 1, 0, 0, Color_Black(), Color_Black());
	SetupMessage(ms.m2, 10, 0, 150, Color_Black(), Color_White());
	SetupMessage(ms.m3, 200, 150, 150, Color_White(), Color_White());
	SetupMessage(ms.m4, 20, 100, 0, Color_White(), Color_Black());
	SetupMessage(ms.m5, 1, 0, 0, Color_Black(), Color_Black());
}

void DrawMessage(char* msgText)
{
	Mess_Message(msgText, &ms.m1, 1, 0, -24);
}