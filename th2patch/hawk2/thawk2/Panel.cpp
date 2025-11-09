#include "stdafx.h"
#include "panel.h"
#include "Globals.h"


namespace Panel
{

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

	void Panel_BalanceRail(
		int Balance, int Max, int Length, int Width,
		int x, int y, uint LineColor, uint MarkerColor, bool horz)
	{
		if (horz)
		{
			Length = Length * 16 / 9;
			Width = Width * 4 / 3;

			// we have to account for level flip cheat state for horizontal balance bar !!!
			int markerX = (Balance * Length * (*Cheat_FlipScreen ? -1 : 1)) / Max + x;

			Panel_Line(markerX, y, markerX, y + Width, MarkerColor);
			Panel_DrawBalanceBarLR(x, y, Length, Width, LineColor);
			Panel_DrawBalanceBarLR(x + 1, y + 1, Length, Width, LineColor >> 3 & 0x1f1f1f);
		}
		else
		{
			//marker
			int markerY = (Balance * Length) / Max + y;
			Panel_Line(x, markerY, x + Width, markerY, MarkerColor);
			Panel_DrawBalanceBarUD(x, y, Length, Width, LineColor);
			Panel_DrawBalanceBarUD(x + 1, y + 1, Length, Width, LineColor >> 3 & 0x1f1f1f);
		}
	}

	void Panel_DrawBalanceBarUD(int x, int y, int Length, int Width, uint color)
	{
		int topY = y + Length;
		int bottomY = y - Length;
		int rightX = x + Width;

		Panel_Line(x, topY, x, bottomY, color);
		Panel_Line(x, topY, rightX, topY, color);
		Panel_Line(x, y, rightX, y, color);
		Panel_Line(x, bottomY, rightX, bottomY, color);
	}

	void Panel_DrawBalanceBarLR(int x, int y, int Length, int Width, uint color)
	{
		int leftX = x + Length;
		int rightX = x - Length;
		int bottomY = y + Width;

		Panel_Line(leftX, y, rightX, y, color);
		Panel_Line(leftX, y, leftX, bottomY, color);
		Panel_Line(x, y, x, bottomY, color);
		Panel_Line(rightX, y, rightX, bottomY, color);
	}

	/*
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
	*/


}