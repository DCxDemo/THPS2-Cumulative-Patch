#include "stdafx.h"
#include "PKR.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <direct.h>

Pkr2::~Pkr2()
{
	free(data);
}

/// <summary>
/// Loads PKR file to memory and initializes required pointers.
/// </summary>
/// <param name="filename"></param>
/// <returns></returns>
PkrError Pkr2::Load(char* filename)
{
	if (data)
		free(data);

	printf_s("trying to open\n");

	FILE* file = fopen(filename, "rb");

	if (file == NULL)
		return PkrError::FileDoesntExist;


	fseek(file, 0, SEEK_END);
	long fsize = ftell(file);
	fseek(file, 0, SEEK_SET);  /* same as rewind(f); */

	data = malloc(fsize);

	if (data == 0)
		return PkrError::ZeroFile;


	fread(data, fsize, 1, file);
	fclose(file);


	Header = (Pkr2Header*)data;
	Folders = (Pkr2Folder*)(Header + 1);
	Files = (Pkr2File*)(Folders + Header->numFolders);

	for (int i = 0; i < Header->numFiles; i++)
	{
		Files[i].pData += (int)data;
	}

	//we're all good
	return PkrError::Success;
}

/// <summary>
/// Exports all files to a given directory.
/// </summary>
/// <param name="path"></param>
void Pkr2::ExportAll(char* path)
{
	char buf[MAX_BUFFER_SIZE];
	char bufpath[MAX_BUFFER_SIZE];
	FILE* file;
	int curFile = 0;

	for (unsigned int i = 0; i < Header->numFolders; i++)
	{
		sprintf_s(bufpath, sizeof(bufpath), "%s%s", path, Folders[i].Name);
		_mkdir(bufpath);

		for (unsigned int j = 0; j < Folders[i].NumFiles; j++)
		{
			sprintf_s(buf, sizeof(buf), "%s%s", bufpath, Files[curFile].Name);

			file = fopen(buf, "wb");
			fwrite((void*)Files[curFile].pData, 1, Files[curFile].Size, file);
			fclose(file);

			curFile++;

			printf_s(".");
		}
	}

	printf_s("PKR export done!\n");
}

/// <summary>
/// Debug print for PKR file contents
/// </summary>
void Pkr2::DebugPrint()
{
	char buf[MAX_BUFFER_SIZE];

	printf_s("PKR Folders:\n");

	for (int i = 0; i < Header->numFolders; i++)
	{
		sprintf_s(buf, sizeof(buf), "Folder: %s NumFiles: %i\n", Folders[i].Name, Folders[i].NumFiles);
		printf_s(buf);
	}

	printf_s("PKR Files:\n");

	for (int i = 0; i < Header->numFiles; i++)
	{
		sprintf_s(buf, sizeof(buf), "Folder: %s Size: %i\n", Files[i].Name, Files[i].Size);
		printf_s(buf);
	}
}