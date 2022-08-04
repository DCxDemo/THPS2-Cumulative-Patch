#pragma once

typedef struct
{
	char R;
	char G;
	char B;
} ColorRGB;

typedef struct
{
	char R;
	char G;
	char B;
	char A;
} ColorRGBA;

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