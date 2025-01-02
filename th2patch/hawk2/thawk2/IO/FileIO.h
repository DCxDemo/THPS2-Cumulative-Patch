#pragma once

#include "..\PKR.h"
#include "..\..\patch\hook.h"

namespace FileIO {

    extern Hook::Reroute* pHookList;

    typedef void	(*FileIO_LoadHed_t)();
    typedef void	(*FileIO_UnLoadHed_t)();
    typedef void	(*FileIO_AddDirToFileName_t)(char* filename);
    typedef void	(*FileIO_AddSubDirToFileName_t)(char* filename);
    //typedef void*   (*FileIO_OpenLoad_t)(char* filename, int heap);
    //typedef void	(*FileIO_SetSectorsPerFrame_t)(int sectorsPerFrame);
    typedef void	(*FileIO_Init_t)();
    typedef int		(*FileIO_Open_t)(char* filename);
    typedef void     (*FileIO_Load_t)(void* ptr);
    // typedef bool	(*FileIO_Exists_t)(char* filename);
    typedef void	(*FileIO_Continue_t)();
    // typedef void	(*FileIO_Sync_t)();
    // typedef char* (*FileIO_GetSubDir_t)();
    // typedef void	(*FileIO_SetSubDir_t)(char* filename);

    static const FileIO_LoadHed_t				FileIO_LoadHed = (FileIO_LoadHed_t)0x00448c00;
    static const FileIO_UnLoadHed_t				FileIO_UnloadHed = (FileIO_UnLoadHed_t)0x00448c30;
    // unused calc checksum func here 00448c50
    static const FileIO_AddDirToFileName_t		FileIO_AddDirToFileName = (FileIO_AddDirToFileName_t)0x00448ca0;
    static const FileIO_AddSubDirToFileName_t	FileIO_AddSubDirToFileName = (FileIO_AddSubDirToFileName_t)0x00448cd0;
    //static const FileIO_OpenLoad_t				FileIO_OpenLoad = (FileIO_OpenLoad_t)0x448D70;
    void* FileIO_OpenLoad(char* filename, int Heap);
    // static const FileIO_SetSectorsPerFrame_t	FileIO_SetSectorsPerFrame = (FileIO_SetSectorsPerFrame_t)0x00448ee0;
    void FileIO_SetSectorsPerFrame(int sectorsPerFrame);
    static const FileIO_Init_t					FileIO_Init = (FileIO_Init_t)0x00448ef0;
    static const FileIO_Open_t					FileIO_Open = (FileIO_Open_t)0x00448fd0;
    static const FileIO_Load_t					FileIO_Load = (FileIO_Load_t)0x004491d0;
    // unused close func here 00449390
    // static const FileIO_Exists_t				FileIO_Exists = (FileIO_Exists_t)0x00449400;
    bool FileIO_Exists(char* filename);
    static const FileIO_Continue_t				FileIO_Continue = (FileIO_Continue_t)0x00449450;
    //static const FileIO_Sync_t					FileIO_Sync = (FileIO_Sync_t)0x00449600;
    void FileIO_Sync();
    // static const FileIO_GetSubDir_t				FileIO_GetSubDir = (FileIO_GetSubDir_t)0x00449690;
    char* FileIO_GetSubDir();
    //static const FileIO_SetSubDir_t				FileIO_SetSubDir = (FileIO_SetSubDir_t)0x004496a0;
    char* FileIO_SetSubDir(char* path);

    typedef void(*LoadingScreen_UpdateProgress_t)();
    static const LoadingScreen_UpdateProgress_t LoadingScreen_UpdateProgress = (LoadingScreen_UpdateProgress_t)0x0045d600;

    //typedef bool(*tryOpenFile_t)(char* path, char* filename);
    //static const tryOpenFile_t tryOpenFile = (tryOpenFile_t)0x004f3900;
    bool Exists(char* path, char* filename);

}

//void* FileIO_OpenLoad_Pkr(char* filename, bool heap, Pkr2* pkr);
