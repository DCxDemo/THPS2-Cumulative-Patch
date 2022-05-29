#pragma once

struct ColorRGB
{
	char R;
	char G;
	char B;
};

struct ColorRGBA
{
	char R;
	char G;
	char B;
	char A;
};

ColorRGB Color_Black() { ColorRGB c = {0,0,0}; return c; }
ColorRGB Color_DarkGray() { ColorRGB c = {0x40,0x40,0x40}; return c; }
ColorRGB Color_Gray() { ColorRGB c = {0x80,0x80,0x80}; return c; }
ColorRGB Color_LightGray() { ColorRGB c = {0xC0,0xC0,0xC0}; return c; }
ColorRGB Color_White() { ColorRGB c = {0xFF,0xFF,0xFF}; return c; }

ColorRGB Color_Red() { ColorRGB c = {0xFF,0,0}; return c; }
ColorRGB Color_Green() { ColorRGB c = {0,0xFF,0}; return c; }
ColorRGB Color_Blue() { ColorRGB c = {0,0,0xFF}; return c; }
ColorRGB Color__Magenta() { ColorRGB c = {0xFF,0,0xFF}; return c; }
ColorRGB Color_Cyan() { ColorRGB c = {0,0xFF,0xFF}; return c; }
ColorRGB Color_Yellow() { ColorRGB c = {0xFF,0xFF,0}; return c; }