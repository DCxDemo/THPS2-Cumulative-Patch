#pragma once
#include "Checksum.h"

namespace Wad {

	typedef struct HedFile {
		unsigned int Hash;
		void* pData;
		unsigned int Size;
	} HedFile;

	void Load(char* hed, char* wad);
	void Unload();
	HedFile* FindFile(char* filename);
	void DumpFile(HedFile* what, char* where);
}