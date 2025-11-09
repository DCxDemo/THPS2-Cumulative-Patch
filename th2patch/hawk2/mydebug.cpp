#include "stdafx.h"
#include "mydebug.h"


char debugText[MAX_BUFFER_SIZE];

void DebugMessage(char* text, int x, int y)
{
	Mess::Mess_SetScale(95);
	Mess::Mess_SetRGB(255, 255, 32, false);
	Mess::Mess_SetTextJustify(Mess::eTextJustify::Left);
	Mess::Mess_DrawText(x, y, text);
}



void PrintDebugStuff()
{
	if (*GamePaused)
	{
		sprintf(debugText, "THPS2 Cumulative Patch r7prev");
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

			//sprintf(debugText, "balance %i", railBal);
			//DebugMessage(debugText, 10, 10);

			
			CBruce* pSkater = new CBruce(GSkater);

			sprintf(debugText, "bruce test: %i",
				pSkater->InManual()
			);

			/*
			sprintf(debugText, "bruce test: %i %i %i" ,
				pSkater->GetValue(0x12c),
				pSkater->GetValue(0x130),
				pSkater->GetValue(0x134)

			);
			*/
		
			//pSkater->SetValue(0x28, 10);

			

			DebugMessage(debugText, 10, 10);

			delete pSkater;
		}



		//sprintf(debugText, "test: %i", *GGame);
		//DebugMessage(debugText, 512 / 2, 20);

		//Panel_LineX(-1.0, -1.0, 1.0, 1.0, 255, 0, 0);
		//Panel_LineX(1.0, -1.0, -1.0, 1.0, 255, 0, 0);

		/*
		if (menu != NULL)
			delete menu;

		menu = new CMenu((SMenu*)0x0055e8a0);
		//menu->DebugPrint();
		*/
	}
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
