#pragma once

namespace Hook
{
	typedef struct Reroute {
		unsigned int pMem;
		void* pFunc;
	} FuncRedirection;

	void ProcessList(Reroute* pList);

	void SetHooks();
}