#include "stdafx.h"
#include "mess.h"
#include "mem.h"
#include "thawk2/_old.h"

typedef struct {
	int R;
	int G;
	int B;
} SMessColor;

void*			GMessFont		= (void*)0x567600;
eTextJustify*	Mess_Justify	= (eTextJustify*)0x567604;
SMessColor*		Mess_Color		= (SMessColor*)0x567614;
int*			Mess_Scale		= (int*)0x567630;
bool			GMessFontExists = (bool*)0x56776c;
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
void Mess_SetScale(int scale) { 
	*Mess_Scale = scale << 4; 
}


//gets scale
int Mess_GetScale() { 
	return *Mess_Scale >> 4; 
}


//sets text justify
void Mess_SetTextJustify(eTextJustify justify) {
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

	if (*pMessages == NULL) return;

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

	pMess->pPrevious = 0;
	pMess->pNext = *pMessages;

	*pMessages = pMess;

	if (pMess->pNext != 0)
		pMess->pNext->pPrevious = pMess;

	return pMess;
}


//creates new message entry
void Mess_Message(char* pText, void* pProg, bool recenter, short xOffset, short yOffset)
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

void Mess_SetCurrentFont()
{
	printf("Mess_SetCurrentFont is no longer used.\r\n");
}


void __fastcall Font_Draw_Wrap(void* _this, void* _edx, int x, int y, char* pMessage, int Angle)
{
	Font_Draw(_this, x, y, pMessage, Angle);
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