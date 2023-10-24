#include "stdafx.h"
#include "mess.h"
#include "mem.h"
#include "_old.h"
#include "GameOptions.h"

typedef struct {
	int R;
	int G;
	int B;
} SMessColor;

void*			GMessFont		= (void*)0x567600;
eTextJustify*	Mess_Justify	= (eTextJustify*)0x567604;
SMessColor*		Mess_Color		= (SMessColor*)0x567614;
int*			Mess_Scale		= (int*)0x567630;
char*			GMessFontFilename = (char*)0x56774c;
bool*			GMessFontExists = (bool*)0x56776c;
SMessage**		pMessages		= (SMessage**)0x567770;




// Sets default Mess text color
void Mess_SetRGB(int r, int g, int b, bool semitrans)
{
	Mess_Color->R = (char)r;
	Mess_Color->G = (char)g;
	Mess_Color->B = (char)b;
}


//sets rgb
void Mess_SetRGB(SMessColor* color)
{
	Mess_Color->R = (char)color->R;
	Mess_Color->G = (char)color->G;
	Mess_Color->B = (char)color->B;
}


//sets scale
void Mess_SetScale(int scale)
{ 
	*Mess_Scale = scale << 4; 
}


//gets scale
int Mess_GetScale()
{ 
	return *Mess_Scale >> 4; 
}


//sets text justify
void Mess_SetTextJustify(eTextJustify justify)
{
	*Mess_Justify = justify;
}


//deletes message from queue
void Mess_DeleteMessage(SMessage* pMess)
{
	if (!pMess) return;

	printf("Mess_DeleteMessage(): %s\r\n", pMess->pText);

	if (pMess->pNext)
		pMess->pNext->pPrevious = pMess->pPrevious;

	if (pMess->pPrevious)
		pMess->pPrevious->pNext = pMess->pNext;

	if (pMess == *pMessages)
		*pMessages = pMess->pNext;

	Mem_Delete(pMess);
}


//clears message queue
void Mess_DeleteAll()
{
	printf("Mess_DeleteAll()\r\n");

	if (!*pMessages) return;

	SMessage* curr = *pMessages;
	SMessage* next = (*pMessages)->pNext;

	while (true) {
		Mem_Delete(curr);

		if (next == NULL) break;

		curr = next;
		next = next->pNext;
	}

	*pMessages = NULL;
}


//pushes new message to the queue
SMessage* CreateMessage()
{
	SMessage* pMess = (SMessage*)Mem_New(sizeof(SMessage), false, true, NULL);

	pMess->pPrevious = NULL;
	pMess->pNext = *pMessages;

	*pMessages = pMess;

	if (pMess->pNext != NULL)
		pMess->pNext->pPrevious = pMess;

	return pMess;
}


//creates new message entry
void Mess_Message(char* pText, SMessageProg* pProg, bool recenter, short xOffset, short yOffset)
{
	SMessage* pMess = CreateMessage();

	pMess->pText = pText;
	pMess->T = 0;
	pMess->T_total = 0;
	pMess->pProg = pProg;
	pMess->recenter = recenter;
	pMess->xOffset = xOffset;
	pMess->yOffset = yOffset;

	printf("Mess_Message: %s\r\n", pText);
}

//looks for the message in queue and deletes it
void Mess_Remove(SMessage* pMess)
{
	if (!pMess) return;
	if (!*pMessages) return;

	printf("Mess_Remove(): %s\r\n", pMess->pText);

	SMessage* curr = *pMessages;
	SMessage* next = (*pMessages)->pNext;

	while (curr != pMess) {
		next = curr->pNext;
		curr = next;
		if (!next) return;
	}

	Mess_DeleteMessage(curr);
}

void Mess_SetCurrentFont(void* pFont)
{
	printf("Mess_SetCurrentFont is no longer used.\r\n");
}

void Mess_SetCurrentFont(char* fontName)
{
	printf("Mess_SetCurrentFont is no longer used.\r\n");
}

void __fastcall Font_Draw_Wrap(void* _this, void* _edx, int x, int y, char* pMessage, int Angle)
{
	Font_Draw(_this, x, y, pMessage, Angle);
}

void Mess_SetScale_Wrap(int scale)
{
	Mess_SetScale(scale * 0.5f);
}

//wraps font draw
void Mess_DrawText(int x, int y, char* pMessage, int Angle)
{
	Font_Draw_Wrap(GMessFont, NULL, x, y, pMessage, 0);
}


//wraps mess_drawtext
void Mess_DrawPanelText(int x, int y, char* pMessage, int Angle)
{
	printf("Mess_DrawText(): %s\r\n", pMessage);

	Mess_DrawText(x, y, pMessage, Angle);
}

//unloads mess font
void Mess_UnloadFont()
{
	printf("Mess_UnloadFont()\r\n");

	if (!*GMessFontExists) return;

	printf("unloading: %s\r\n", GMessFontFilename);

	//FontManager::UnloadFont(GMessFontFilename);
	*GMessFontExists = false;
}

//new func, encapsulated from Mess_Update
void Mess_UpdateOne(SMessage* pMess)
{
	if (pMess->T < pMess->pProg->Duration)
	{
		pMess->T++;
		pMess->T_total++;
	}
	else
	{
		if (!pMess->pProg->NextOff)
		{
			Mess_DeleteMessage(pMess);
		}
		else if (pMess->pProg->NextOff != 0x7f)
		{
			pMess->T = 0;
			pMess->pProg += pMess->pProg->NextOff & 0xFF;
			pMess->T_total++;
		}
		else
		{
			printf("ever happens? %08x\r\n", pMess->pProg->NextOff);
		}
	}
}

//updates message queue, called every frame in Game_Logic
void Mess_Update()
{
	if (!*pMessages) return;

	SMessage* curr = *pMessages;
	SMessage* next = curr->pNext;

	while (true)
	{
		Mess_UpdateOne(curr);
		if (!next) return;

		curr = next;
		next = next->pNext;
	}
}



/*
void Mess_Display()
{
	if (!*pMessages) return;

	SMessage* curr = *pMessages;
	SMessage* next = curr->pNext;

	int i = 0;

	do {
		if (!curr->recenter) i++;
		curr = curr->pNext;
	} while (curr);

	int local_c = i * 0x10 + -0x10;

	curr = *pMessages;

	do {
		SMessageProg* pProg = curr->pProg;

		//this is weird, check the condition
		if (pProg->FlashDuration == 0 || curr->T / pProg->FlashDuration & 1)
		{
			//set mess params using interpolated prog values

			Mess_SetTextJustify(pProg->Justify);


			int scale = pProg->StartScale + (pProg->EndScale - pProg->StartScale) * curr->T / pProg->Duration;

			_Sort = _Sort & 0xffff0000 | scale;

			Mess_SetScale(scale);


			int r = pProg->StartColor.R + (pProg->EndColor.R - pProg->StartColor.R) * curr->T / pProg->Duration;
			int g = pProg->StartColor.G + (pProg->EndColor.G - pProg->StartColor.G) * curr->T / pProg->Duration;
			int b = pProg->StartColor.B + (pProg->EndColor.B - pProg->StartColor.B) * curr->T / pProg->Duration;

			Mess_SetRGB(r, g, b, 0);

			//what, sets random red tint based on xblanks?
			if (pProg->ColorCycle) 
			{
				Mess_SetRGB(((uint3)((ulonglong)Xblanks / 20 >> 8) & 0xffff00) << 8 | (uint)(ushort)((char)((ulonglong)Xblanks % 20) * 12), 100, 100, 0);
			}

			//this one calculates the line to show the message on
			int local_8 = curr->yOffset + pProg->StartY + (pProg->EndY - pProg->StartY) * curr->T / curr->Duration;

			//and maybe shifts it up
			if (curr->recenter) 
			{
				local_8 += local_c;
				local_c -= 0x20;
			}

			//time to draw the message using all of the above
			Mess_DrawPanelText((int)curr->xOffset +
				(int)(short)pProg->StartX +
				(int)(((int)(short)pProg->EndX - (int)(short)pProg->StartX) * curr->T) /
				(int)uVar5, local_8, curr->pText,
				(int)(((uint)pProg->EndAngle - (uint)pProg->StartAngle) * curr->T) /
				(int)uVar5 + pProg->StartAngle);
		}

		//move to next message
		next = curr->pNext;
		curr = next;
	} 
	while (next);
}
*/