#include "stdafx.h"

#include "lib/xinput/CXBOXController.h"

#include "thawk2/_old.h"
#include "thawk2/Mess.h"
#include "thawk2/globals.h"
#include "thawk2/WinMain.h"
#include "thawk2/CBruce.h"
#include "thawk2/physics.h"

#include "patchStuff.h"
#include "mydebug.h"

char debugText[256];

void DebugMessage(char* text, int x, int y)
{
	Mess_SetScale(95);
	Mess_SetRGB(255, 255, 32, false);
	Mess_SetTextJustify(eTextJustify::Left);
	Mess_DrawText(x, y, text, 0);
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
		if (!*InFrontEnd)
		{
			/*
			int* test = CBruce_GetTestValueInt( (int*)(*(int*)GSkater) , 0x0100);
			//*test = 64;

			sprintf(debugText, "test: %08X", *test);
			DebugMessage(debugText, 10, 10);
			*/

			//int balance = *CBruce_GetManualBalance((int*)(*(int*)GSkater));

			int railBal = *CBruce_GetRailBalance((int*)(*(int*)GSkater));
			int state = *CBruce_GetPhysicsState((int*)(*(int*)GSkater));

			//sprintf(debugText, "balance %i", railBal);
			//DebugMessage(debugText, 10, 10);

			if ((EPhysicsState)state == EPhysicsState::PHYSICS_ON_RAIL)
			{
				Panel_BalanceRail(railBal, 0x1000, 30, 200, 0x79, 0x0000ff, 0x00ff00);
			}
		}



		//sprintf(debugText, "test: %i", *GGame);
		//DebugMessage(debugText, 512 / 2, 20);

		//Panel_LineX(-1.0, -1.0, 1.0, 1.0, 255, 0, 0);
		//Panel_LineX(1.0, -1.0, -1.0, 1.0, 255, 0, 0);
	}
}


void Panel_BalanceRail(int Balance, int Max, int Length, int x, int y, uint LineColor, uint MarkerColor)
{
	int iVar1;
	int iVar2;
	uint uVar3;

	iVar2 = (Balance * Length) / Max + y;
	Panel_Line(x, iVar2, x + 6, iVar2, MarkerColor);
	iVar2 = y + Length;
	Length = y - Length;
	uVar3 = LineColor >> 3 & 0x1f1f1f;
	Panel_Line(x, Length, x, iVar2, LineColor);
	Panel_Line(x, Length, x + 6, Length, LineColor);
	Panel_Line(x, y, x + 6, y, LineColor);
	Panel_Line(x, iVar2, x + 6, iVar2, LineColor);
	Length = Length + 1;
	iVar2 = iVar2 + 1;
	iVar1 = x + 1;
	Panel_Line(iVar1, Length, iVar1, iVar2, uVar3);
	x = x + 7;
	Panel_Line(iVar1, Length, x, Length, uVar3);
	Panel_Line(iVar1, y + 1, x, y + 1, uVar3);
	Panel_Line(iVar1, iVar2, x, iVar2, uVar3);
}


void VibrationTest(CXBOXController* Player1)
{
	if (Player1)
	{

		Player1->Vibrate(2000, 0, true);

		double timer = 0;
		do
		{
			Sleep(16);
			WinYield();
			timer += 16.666 * 2;
			//printf("timer: %f\r\n", timer / 1000);
		} while (timer < 16.66666 * 120 * 5);

		Player1->Vibrate(0, 2000, true);

		timer = 0;
		do
		{
			Sleep(16);
			WinYield();
			timer += 16.666 * 2;
			//printf("timer: %f\r\n", timer / 1000);
		} while (timer < 16.66666 * 120 * 5);


		Player1->Vibrate(65535, 0, true);

		timer = 0;
		do
		{
			Sleep(16);
			WinYield();
			timer += 16.666 * 2;
			//printf("timer: %f\r\n", timer / 1000);
		} while (timer < 16.66666 * 120 * 5);

		Player1->Vibrate(0, 65535, true);

		timer = 0;
		do
		{
			Sleep(16);
			WinYield();
			timer += 16.666 * 2;
			//printf("timer: %f\r\n", timer / 1000);
		} while (timer < 16.66666 * 120 * 5);
	}
}
