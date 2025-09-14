#pragma once

#include "..\patch\hook.h"

namespace Decomp
{
	extern Hook::Reroute* pHookList;

	// stream compression type
	enum Compression {
		Trivial = 0,
		PackDelta2 = 1,
		PackDelta3 = 2,
		PackDelta4 = 3,
		PackDelta5 = 4,
		PackDelta6 = 5,
		PackDelta7 = 6,
		PackDelta8 = 7,
		PackDelta9 = 8,
		PackDelta10 = 9,
		PackDelta11 = 10,
		PackDelta12 = 11,
		PackDelta13 = 12,
		PackDelta14 = 13,
		AllSame = 14,
		AllZero = 15
	};

	// returns matrix
	typedef void* (*Decomp_GetAnimTransform_t)(void* pSuper);
	//typedef unsigned char* (*DecompressStream_t)(unsigned char* pSource, short* pDest, int StepSize, int StreamLength);

	static const Decomp_GetAnimTransform_t	Decomp_GetAnimTransform = (Decomp_GetAnimTransform_t)0x486d90;
	//static const DecompressStream_t			DecompressStream = (DecompressStream_t)0x4305c0;
	unsigned char* DecompressStream(unsigned char* pSource, short* pDest, int StepSize, int StreamLength);
}