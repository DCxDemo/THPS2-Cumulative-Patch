#include "stdafx.h"
#include "..\cpatch.h"
#include "hook.h"
#include "..\thawk2\thawk2.h"

namespace Hook
{
	// The idea behind this is to collect all hooks within the namespace it belongs to.
	// just define pHookList in the namespace and add to the array.
	// the sethooks is called in main patching func.

	Reroute* pHookLists[] = {
		Career::pHookList,
		Decomp::pHookList, // short for decmopression, not decompilation
		FileIO::pHookList,
		Flash::pHookList,
		Init::pHookList,
		gte::pHookList,
		M3d::pHookList,
		Rail::pHookList,
		Redbook::pHookList,
		//Pal::pHookList,
		Physics::pHookList,
		PCIO::pHookList,
		Trig::pHookList
	};

	void SetHooks() {

		for (int i = 0; i < sizeof(pHookLists) / 4; i++)
			ProcessList(pHookLists[i]);
	}

	void ProcessList(Reroute* pList) {

		while (pList->pMem != NULL)
		{
			CPatch::RedirectCall(pList->pMem, pList->pFunc);

			printf_s("DECOMP DEBUG: patched %X at %X\n", (unsigned int)pList->pFunc, pList->pMem);

			pList++;
		}
	}
}