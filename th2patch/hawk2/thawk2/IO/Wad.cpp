#include "stdafx.h"
#include "wad.h"
#include "thawk2\types.h"

namespace Wad {

	bool Loaded = false;
	int NumFiles = 0;
	HedFile* HedData;
	void* WadData;

	void Load(char* hed, char* wad)
	{
		if (Loaded) Unload();

		printf_s("trying to open HED: %s\n", hed);

		FILE* file = fopen(hed, "rb");

		if (file != NULL)
		{
			fseek(file, 0, SEEK_END);
			long fsize = ftell(file);
			fseek(file, 0, SEEK_SET);
			HedData = (HedFile*)malloc(fsize);
			fread(HedData, fsize, 1, file);
			fclose(file);

			NumFiles = fsize / sizeof(HedFile);
		}

		printf_s("trying to open WAD: %s\n", wad);

		file = fopen(wad, "rb");

		if (file != NULL)
		{
			fseek(file, 0, SEEK_END);
			long fsize = ftell(file);
			fseek(file, 0, SEEK_SET);
			WadData = malloc(fsize);
			fread(WadData, fsize, 1, file);
			fclose(file);
		}

		printf_s("patching pointers\n");

		// patch pointers
		for (int i = 0; i < NumFiles; i++)
		{
			printf_s("%i + %i\n", (int)WadData, (int)HedData[i].pData);
			HedData[i].pData = (void*)((int)WadData + (int)HedData[i].pData);
		}

		Loaded = true;

		printf_s("done!\n");
	}

	void Unload()
	{
		if (!Loaded) return;
		
		free(HedData);
		free(WadData);

		HedData = NULL;
		WadData = NULL;

		NumFiles = 0;

		Loaded = false;

		printf_s("WAD unloaded\n");
	}

	HedFile* FindFile(char* filename)
	{
		if (!Loaded) return NULL;
		if (filename == NULL) return NULL;
		if (filename[0] == '\0') return NULL;

		uint hash = checksum(filename);

		for (int i = 0; i < NumFiles; i++)
			if (HedData[i].Hash == hash) {
				printf_s("file %s found in WAD.\n", filename);
				return &HedData[i];
			}

		printf_s("file %s not found in WAD.\n", filename);
		return NULL;
	}

	void DumpFile(HedFile* what, char* where)
	{
		if (!Loaded) return;
		if (what == NULL) return;
		if (where == NULL) return;
		if (where[0] == '\0') return;
		
		FILE* file = fopen(where, "wb");
		fwrite(what->pData, 1, what->Size, file);
		fclose(file);
	}
}