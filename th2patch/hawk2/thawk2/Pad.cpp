#include "stdafx.h"
#include "thawk2/pad.h"

namespace Pad
{
	#define NUM_PADS 2

	void Pad_ClearAll()
	{
		for (int i = 0; i < NUM_PADS; i++)
			Pad_ClearAllOne(i);
	}
}