#include "stdafx.h"
#include "CMenu.h"
#include "Utils.h"
#include "types.h"


CMenu::CMenu(SMenu* pMenu)
{
	menu = pMenu;
}

int CMenu::FindEntry(char* pText)
{
	/*
	if (menu->numEntries > 0)
		for (SMenuEntry* p = menu->entries[0]; i < menu->entries[menu->numEntries]; i++)
			if (Utils_CompareStrings(pText, *pEntry, 0xffffffff) != 0)
				return i;

	printf_s("entry not found!");
	*/

	//so we dont confuse it with the 1st line
	return NS_NULL;
}


void CMenu::MenuReset()
{
	//SetLine(0);
}


bool CMenu::ChoiceIs(char* pText)
{
	return false;
	//return Utils_CompareStrings(pText, menu->entries[menu->selectedEntry].text, -1);
}

void CMenu::EntryOn(char* pText)
{
	/*
	int index = FindEntry(_this,pText);

	if (index != NS_NULL)
		menu->entries[index].visible = true;
	*/
}


void CMenu::EntryOff(char* pText)
{
	/*
	int index = FindEntry(menu, pText);

	if (index != NS_NULL)
		menu->entries[index].visible = false;
	*/
}


bool CMenu::IsEntryOn(char* pText)
{
	/*
	int index = FindEntry(_this,pText);

	if (index != NS_NULL)
		menu->entries[index].visible = true;
		*/
	
	return false;
}

void CMenu::DebugPrint()
{
	printf_s("Menu: items=%i x=%i y=%i\n", menu->numEntries, menu->X, menu->Y);
}