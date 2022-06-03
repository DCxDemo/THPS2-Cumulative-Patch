#include "stdafx.h"
#include "mess.h"

typedef struct {
	int R;
	int G;
	int B;
} SMessColor;

SMessColor* Mess_Color = (SMessColor*)0x567614;
int* Mess_Scale = (int*)0x567630;
eTextJustify* Mess_Justify = (eTextJustify*)0x567604;
SMessage* pMessages = (SMessage*)0x567770;

/// <summary>
/// Sets default Mess text color.
/// </summary>
/// <param name="r">Red</param>
/// <param name="g">Green</param>
/// <param name="b">Blue</param>
void Mess_SetRGB(int r, int g, int b)
{
	Mess_Color->R = (char)r;
	Mess_Color->G = (char)g;
	Mess_Color->B = (char)b;
}

void Mess_SetRGB(SMessColor* color)
{
	Mess_Color->R = (char)color->R;
	Mess_Color->G = (char)color->G;
	Mess_Color->B = (char)color->B;
}

void Mess_SetScale(int scale) { 
	*Mess_Scale = scale << 4; 
}

int Mess_GetScale() { 
	return *Mess_Scale >> 4; 
}

void Mess_SetTextJustify(eTextJustify justify) {
	*Mess_Justify = justify;
}