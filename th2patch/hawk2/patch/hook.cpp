#include "stdafx.h"
#include "..\cpatch.h"
#include "hook.h"
#include "..\thawk2\thawk2.h"

namespace Hook
{
	void ProcessList(Reroute* pList)
	{
		while (pList->pMem != NULL)
		{
			CPatch::RedirectCall(pList->pMem, pList->pFunc);

			printf("DECOMP DEBUG: patched %i at %i\n", (unsigned int)pList->pFunc, pList->pMem);

			pList++;
		}
	}


	void SetHooks()
	{
		ProcessList(gte::pHookList);
		ProcessList(Career::pHookList);
		ProcessList(Rail::pHookList);
		ProcessList(FileIO::pHookList);
		ProcessList(Flash::pHookList);
		ProcessList(Physics::pHookList);
		//ProcessList(Pal::pHookList);
	}
}