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
		gte::pHookList,
		Career::pHookList,
		Rail::pHookList,
		FileIO::pHookList,
		Flash::pHookList,
		Physics::pHookList,
		Redbook::pHookList,
		PCIO::pHookList,
		Decomp::pHookList,
		Trig::pHookList,
		M3d::pHookList,
		Init::pHookList
		//Pal::pHookList
	};

	void SetHooks() {

		for (int i = 0; i < sizeof(pHookLists) / 4; i++)
			ProcessList(pHookLists[i]);
	}

	void ProcessList(Reroute* pList) {

		while (pList->pMem != NULL)
		{
			CPatch::RedirectCall(pList->pMem, pList->pFunc);

			printf_s("DECOMP DEBUG: patched %i at %i\n", (unsigned int)pList->pFunc, pList->pMem);

			pList++;
		}
	}
}