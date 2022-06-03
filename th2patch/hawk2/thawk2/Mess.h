#pragma once

/*
	Mess.h
	======
	- Mess namespace handles message queue
	- message queue is a linked list of SMessage instances
	- messages are drawn on the screen using "message programs", which is a set of states (color, position, scale, etc).
*/

enum class eTextJustify : int {
	Left = 0,
	Center = 1,
	Middle = 1,
	Right = 2
};

typedef struct SMessage {
	char* text;
	short unk1;
	short unk2;
	short x;
	short y;
	int unk5;
	void* messProg;
	SMessage* next;
	SMessage* prev;
} SMessage;

	//typedef void	(*Mess_SetTextJustify_t)(eTextJustify justify);
	//typedef void(*Mess_SetScale_t)(int scale);
	//typedef int(*Mess_GetScale_t)();
typedef void	(*Mess_SetSort_t)(int sort);
	//typedef void(*Mess_SetRGB_t)(int r, int g, int b);
typedef void	(*Mess_DrawPanelText_t)(int param_1, int param_2, int param_3, int param_4);
typedef void	(*Mess_DeleteMessage_t)(void* message);
typedef void	(*Mess_DeleteAll_t)();
	//unknown unused Mess func	0x473620
typedef void	(*Mess_Remove_t)(void* message);
typedef void	(*Mess_Message_t)(char* text, void* messProg, int param_3, int x, int y);
typedef void	(*CreateMessage_t)();
typedef void	(*Mess_Update_t)();
typedef void	(*Mess_Display_t)();
	//unknown unused Mess func	00473960
typedef void	(*Mess_DrawText_t)(int x, int y, char* text);
typedef void*	(*Mess_LoadFont_t)(char* filename, int param_2, int param_3);
typedef void	(*Mess_UnloadFont_t)();
typedef void	(*Mess_SetCurrentFont_t)();

//static const Mess_SetTextJustify_t	Mess_SetTextJustify = (Mess_SetTextJustify_t)0x473440;
void								Mess_SetTextJustify(eTextJustify justify);
//static const Mess_SetScale_t		Mess_SetScale = (Mess_SetScale_t)0x473480;
void								Mess_SetScale(int scale);
//static const Mess_GetScale_t		Mess_GetScale = (Mess_GetScale_t)0x473490;
int									Mess_GetScale();	
static const Mess_SetSort_t			Mess_SetSort = (Mess_SetSort_t)0x4734a0;
//static const Mess_SetRGB_t			Mess_SetRGB = (Mess_SetRGB_t)0x473510;
void								Mess_SetRGB(int r, int g, int b);	
static const Mess_DrawPanelText_t	Mess_DrawPanelText = (Mess_DrawPanelText_t)0x473540;
static const Mess_DeleteMessage_t	Mess_DeleteMessage = (Mess_DeleteMessage_t)0x473560;
static const Mess_DeleteAll_t		Mess_DeleteAll = (Mess_DeleteAll_t)0x4735E0;
//unknown unused Mess func	0x473620
static const Mess_Remove_t			Mess_Remove = (Mess_Remove_t)0x473650;
static const Mess_Message_t			Mess_Message = (Mess_Message_t)0x473680;
static const CreateMessage_t		CreateMessage = (CreateMessage_t)0x4736c0;
static const Mess_Update_t			Mess_Update = (Mess_Update_t)0x4736f0;
static const Mess_Display_t			Mess_Display = (Mess_Display_t)0x473750;
//unknown unused Mess func	00473960
static const Mess_DrawText_t		Mess_DrawText = (Mess_DrawText_t)0x473970;
static const Mess_LoadFont_t		Mess_LoadFont = (Mess_LoadFont_t)0x473990;
static const Mess_UnloadFont_t		Mess_UnoadFont = (Mess_UnloadFont_t)0x473b10;
static const Mess_SetCurrentFont_t	Mess_SetCurrentFont = (Mess_SetCurrentFont_t)0x473b70;