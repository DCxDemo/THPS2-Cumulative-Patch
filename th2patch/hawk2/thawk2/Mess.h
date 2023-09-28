#pragma once
#include "../color.h"

/*
	Mess.h
	======
	- Mess namespace handles message queue
	- message queue is a doubly linked list of SMessage instances
	- messages are drawn on the screen using "message programs", which is a set of states (color, position, scale, etc).
*/

enum class eTextJustify : char {
	Left = 0,
	Center = 1,
	Middle = 1,
	Right = 2
};



//this should be moved to mess.h
typedef struct
{
	short Duration;
	char Semitrans;
	eTextJustify Justify;
	short StartScale;
	short EndScale;

	ColorRGB StartColor;
	ColorRGB EndColor;

	short StartAngle;
	short EndAngle;

	short StartX;
	short StartY;
	short EndX;
	short EndY;

	short FlashDuration;
	short ColorCycle;
	short NextOff;
} SMessageProg;


typedef struct SMessage {
	char* pText;
	short T;		//current mess prog counter
	short T_total;	//total message counter
	short xOffset;
	short yOffset;
	int recenter;
	SMessageProg* pProg;
	SMessage* pNext;
	SMessage* pPrevious;
} SMessage;

	//typedef void	(*Mess_SetTextJustify_t)(eTextJustify justify);
	//typedef void(*Mess_SetScale_t)(int scale);
	//typedef int(*Mess_GetScale_t)();
typedef void	(*Mess_SetSort_t)(int sort);
	//typedef void(*Mess_SetRGB_t)(int r, int g, int b, bool semitrans);
	//typedef void	(*Mess_DrawPanelText_t)((int x, int y, char* pMessage, int Angle);
	//typedef void	(*Mess_DeleteMessage_t)(SMessage* pMess);
	//typedef void	(*Mess_DeleteAll_t)();
typedef bool	(*Mess_MessageExists_t)(SMessage* pMess);	//never used
	//typedef void	(*Mess_Remove_t)(SMessage* pMess);
	//typedef void	(*Mess_Message_t)(char* text, void* messProg, int param_3, int x, int y);
	//typedef SMessage*	(*CreateMessage_t)();
	//typedef void	(*Mess_Update_t)();
typedef void	(*Mess_Display_t)();
typedef int		(*Mess_TextWidth_t)(char* pMessage);	//never used
	//typedef void	(*Mess_DrawText_t)(int x, int y, char* pMessage, int Angle);
typedef void*	(*Mess_LoadFont_t)(char* filename, int param_2, int param_3);
typedef void	(*Mess_UnloadFont_t)();
	//typedef void	(*Mess_SetCurrentFont_t)(void* pFont);
	//typedef void	(*Mess_SetCurrentFont2_t)(char* fontName); //overload

	//static const Mess_SetTextJustify_t	Mess_SetTextJustify = (Mess_SetTextJustify_t)0x473440;
void Mess_SetTextJustify(eTextJustify justify);
	//static const Mess_SetScale_t	Mess_SetScale = (Mess_SetScale_t)0x473480;
void Mess_SetScale(int scale);
	//static const Mess_GetScale_t	Mess_GetScale = (Mess_GetScale_t)0x473490;
int Mess_GetScale();	
static const Mess_SetSort_t			Mess_SetSort = (Mess_SetSort_t)0x4734a0;
	//static const Mess_SetRGB_t			Mess_SetRGB = (Mess_SetRGB_t)0x473510;
void Mess_SetRGB(int r, int g, int b, bool semitrans);
	//static const Mess_DrawPanelText_t	Mess_DrawPanelText = (Mess_DrawPanelText_t)0x473540;
void Mess_DrawPanelText(int x, int y, char *pMessage, int Angle);
	//static const Mess_DeleteMessage_t	Mess_DeleteMessage = (Mess_DeleteMessage_t)0x473560;
void Mess_DeleteMessage(SMessage* mess);
	//static const Mess_DeleteAll_t		Mess_DeleteAll = (Mess_DeleteAll_t)0x4735E0;
void Mess_DeleteAll();
static const Mess_MessageExists_t			Mess_MessageExists = (Mess_MessageExists_t)0x473620;	//never used
	//static const Mess_Remove_t			Mess_Remove = (Mess_Remove_t)0x473650;
void Mess_Remove(SMessage* pMess);
	//static const Mess_Message_t			Mess_Message = (Mess_Message_t)0x473680;
void Mess_Message(char* pText, SMessageProg* pProg, bool recenter, short xOffset, short yOffset);
	//static const CreateMessage_t		CreateMessage = (CreateMessage_t)0x4736c0;
SMessage* CreateMessage();
	//static const Mess_Update_t		Mess_Update = (Mess_Update_t)0x4736f0;
void Mess_Update();
static const Mess_Display_t		Mess_Display = (Mess_Display_t)0x473750;
static const Mess_TextWidth_t	Mess_TextWidth = (Mess_TextWidth_t)0x00473960;	//never used
	//static const Mess_DrawText_t		Mess_DrawText = (Mess_DrawText_t)0x473970;
void Mess_DrawText(int x, int y, char* pMessage, int Angle);
static const Mess_LoadFont_t	Mess_LoadFont = (Mess_LoadFont_t)0x473990;
static const Mess_UnloadFont_t	Mess_UnoadFont = (Mess_UnloadFont_t)0x473b10;
	//static const Mess_SetCurrentFont_t	Mess_SetCurrentFont = (Mess_SetCurrentFont_t)0x473b70;
void Mess_SetCurrentFont(void* pFont);
	//static const Mess_SetCurrentFont2_t	Mess_SetCurrentFont2 = (Mess_SetCurrentFont_t)0x473b80;
void Mess_SetCurrentFont(char* fontName);

void Mess_SetScale_Wrap(int scale);