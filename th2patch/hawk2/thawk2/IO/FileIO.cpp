#include "stdafx.h"
#include "FileIO.h"
#include "PCIO.h"
#include "..\..\thawk2\mem.h"
#include "..\types.h"
#include "..\..\patch\hook.h"



namespace FileIO {

    void PrintHex(char* name, void* ptr ) {
        printf("%s  --- ", ptr);
        printf("address of %s = 0x%08x\n", name, ptr);
    }



    int* SectorsPerFrame = (int*)0x0052884c;

    char* FileSubDirName = (char*)0x0055e1d4;

    bool* Loading = (bool*)0x0055e230;
    void* Directory = (void*)0x0055e238;
    bool* LoadFromPre = (bool*)0x0055e240;

    char* FileName = (char*)0x0055e1f0;

    //char* FileSubDirName = "logos\\";

    /// <summary>
    /// Gets current subdirectory to scan files in.
    /// </summary>
    /// <returns></returns>
    char* FileIO_GetSubDir() {
        printf("DECOMP FileIO_GetSubDir -> %s\n", FileSubDirName);

        return FileSubDirName;
    }

    /// <summary>
    /// Sets current subdirectory to scan files in
    /// </summary>
    /// <param name="path"></param>
    char* FileIO_SetSubDir(char* subDir) {
        printf("DECOMP FileIO_SetSubDir -> %s\n", subDir);

        return strcpy(FileSubDirName, subDir);
    }

    /// <summary>
    /// Sets amount of sectors to read per frame. Probably unused on PC.
    /// </summary>
    /// <param name="sectorsPerFrame"></param>
    void FileIO_SetSectorsPerFrame(int sectorsPerFrame) {
        *SectorsPerFrame = sectorsPerFrame;
    }


    void __FileIO_UnloadHed() {
        if (Directory != NULL) {
            Mem_Delete(Directory);
            Directory = NULL;
        }
    }


    void FileIO_Sync() {
        printf("DECOMP FileIO_Sync()\n");

        if (*LoadFromPre) {
            *Loading = false;
            *LoadFromPre = false;
        }
        else
        {
            while (*Loading) {
                LoadingScreen_UpdateProgress();
                FileIO_Continue();
            }
        }
    }

    /// <summary>
    /// Checks where file exists. Only used once for mouse cursor...
    /// </summary>
    /// <param name="fileName"></param>
    /// <returns></returns>
    bool FileIO_Exists(char* fileName) {

        printf("DECOMP FileIO_Exists()\n");

        FileIO_AddDirToFileName(fileName);

        if (FileSubDirName != NULL) {
            FileIO_AddSubDirToFileName(fileName);
        }

        printf("checking path: %s\n", FileName);

        uint file = PCopen(FileName, 0);

        printf(" = %i\n", file);

        if (file == -1) {
            return false;
        }
        else
        {
            PCclose(file);
            return true;
        }
    }

    bool Exists(char* path, char* filename) {
        char buf[256];
        sprintf(buf, ".\\%s%s", path, filename);

        char* pChar = &buf[0];

        while (*pChar != '0')
        {
            if (*pChar == '/') *pChar = '\\';
            pChar++;
        }

        FILE* file = fopen(buf, "rb");
    
        if (file != NULL)
        {
            printf("file exists! %s", buf);
            fclose(file);
            return true;
        }
        else 
        {
            printf("file doesnt exist! %s", buf);
            return false;
        }
    }


    void* FileIO_OpenLoad_Pkr(char* filename, bool heap, Pkr2* pkr) {
        //kek
        for (char* i = filename; *i != 0; i++)
        {
            *i = toupper(*i);
        }

        if (pkr != NULL)
        {
            for (int i = 0; i < pkr->Header->numFiles; i++)
            {
                if (strcmp(filename, pkr->Files[i].Name) == 0)
                {
                    printf("%s found in PKR!!!\n", filename);
                    return pkr->Files[i].pData;
                }
            }
        }

        printf("%s not found in PKR, pass to the original func!!!\n", filename);
        return FileIO_OpenLoad(filename, heap);
    }





    // === hook stuff ===

    Hook::Reroute hookList[] = {

        { 0x0043258c, FileIO_GetSubDir },
        { 0x0042460e, FileIO_GetSubDir },
        { 0x00420879, FileIO_GetSubDir },

        { 0x004325cf,	FileIO_SetSubDir },
        { 0x004325b9,	FileIO_SetSubDir },
        { 0x00424737,	FileIO_SetSubDir },
        { 0x0042463b,	FileIO_SetSubDir },
        { 0x00420bb1,	FileIO_SetSubDir },
        { 0x004208a6,	FileIO_SetSubDir },

        { 0x00426990,	FileIO_Sync },
        { 0x00432e73,	FileIO_Sync },
        { 0x00433022,	FileIO_Sync },
        { 0x00433156,	FileIO_Sync },
        { 0x00446b31,	FileIO_Sync },
        { 0x00447cd3,	FileIO_Sync },
        { 0x00448eb5,	FileIO_Sync },
        { 0x0044ae22,	FileIO_Sync },
        { 0x00456adb,	FileIO_Sync },
        { 0x0045ba93,	FileIO_Sync },
        { 0x0046749c,	FileIO_Sync },
        { 0x00478d9c,	FileIO_Sync },
        { 0x004790dc,	FileIO_Sync },
        { 0x004a69df,	FileIO_Sync },
        { 0x004b2c0b,	FileIO_Sync },
        { 0x004c2444,	FileIO_Sync },

        { 0x004d8f99,   FileIO_Exists },

        //=========================
        { NULL, NULL }
    };

    Hook::Reroute* pHookList = &hookList[0];
}