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

struct MsgType
{
	short duration;
	short unknown;
	short startSize;
	short endSize;
	ColorRGB startColor;
	ColorRGB endColor;

	short unk1;
	short unk2; 

	short size1;
	short size2;
	short size3;
	short size4;

	short shouldGoEpileptic;
	short shouldDisco;
	short shouldFadeout;
};


struct SMessageProg
{
	MsgType m1;
	MsgType m2;
	MsgType m3;
	MsgType m4;
	MsgType m5;
};


void SetupMessage(MsgType &message, int d, int ss, int es, ColorRGB sc, ColorRGB ec)
{
	message.duration = d;
	message.startSize = ss;
	message.endSize = es;
	message.startColor = sc;
	message.endColor = ec;
}

SMessageProg DefaultMessage()
{
	return *(SMessageProg*)0x531CC8;
}

SMessageProg ms; 

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
	Mess_Message(msgText, (int)&ms, 1, 0, -24);
}