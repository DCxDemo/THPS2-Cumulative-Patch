#include "stdafx.h"

#include "thawk2/_old.h"
#include "thawk2/Mess.h"
#include "patchStuff.h"

char debugText[256];

void DebugMessage(char* text, int x, int y)
{
	Mess_SetScale(95);
	Mess_SetRGB(255, 255, 32);
	Mess_SetTextJustify(eTextJustify::Left);
	Mess_DrawText(x, y, text);
}

#define BUFFER_WIDTH 512
#define BUFFER_HEIGHT 240

void Panel_LineX(float x1, float x2, float x3, float x4, int r, int g, int b)
{
	Panel_Line(
		(int)(BUFFER_WIDTH / 2 * (x1 + 1)),
		(int)(BUFFER_HEIGHT / 2 * (x2 + 1)),
		(int)(BUFFER_WIDTH / 2 * (x3 + 1)),
		(int)(BUFFER_HEIGHT / 2 * (x4 + 1)),
		(int)(r | g << 8 | b << 16)
	);
}

void PrintDebugStuff()
{
	if (*GamePaused)
	{
		sprintf(debugText, "THPS2 Cumulative Patch r5");
		DebugMessage(debugText, 10, BUFFER_HEIGHT - 7);
	}
	else
	{
		//sprintf(debugText, "test: %i", *GGame);
		//DebugMessage(debugText, 512 / 2, 20);

		//Panel_LineX(-1.0, -1.0, 1.0, 1.0, 255, 0, 0);
		//Panel_LineX(1.0, -1.0, -1.0, 1.0, 255, 0, 0);
	}
}