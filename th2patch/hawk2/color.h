#pragma once

#define COLOR_BLACK		0x000000
#define COLOR_DARKGRAY	0x404040
#define COLOR_GRAY		0x808080
#define COLOR_LIGHTGRAY	0xC0C0C0
#define COLOR_WHITE		0xffffff

#define COLOR_RED		0x0000ff
#define COLOR_GREEN		0x00ff00
#define COLOR_BLUE		0xff0000
#define COLOR_YELLOW	0x00ffff
#define COLOR_MAGENTA	0xff00ff
#define COLOR_CYAN		0xffff00

#define COLOR_DARKRED	0x000080
#define COLOR_DARKGREEN	0x008000
#define COLOR_DARKBLUE	0x800000
#define COLOR_PURPLE	0x800080

typedef struct
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
} ColorRGB;

typedef struct
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char A;
} ColorRGBA;

typedef struct
{
	unsigned char B;
	unsigned char G;
	unsigned char R;
	unsigned char A;
} ColorBGRA;

ColorRGB Color_Black();
ColorRGB Color_DarkGray();
ColorRGB Color_Gray();
ColorRGB Color_LightGray();
ColorRGB Color_White();

ColorRGB Color_Red();
ColorRGB Color_Green();
ColorRGB Color_Blue();
ColorRGB Color_Magenta();
ColorRGB Color_Cyan();
ColorRGB Color_Yellow();