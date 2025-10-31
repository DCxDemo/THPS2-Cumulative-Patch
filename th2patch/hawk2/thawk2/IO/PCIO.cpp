#include "stdafx.h"
#include "PCIO.h"
#include <direct.h>
#include "..\..\thawk2\thawk2.h"
#include "..\..\patch\hook.h"

namespace PCIO {

    bool enableLog = false;

    void log(char* log) {
        if (enableLog)
            printf("<PCIO> %s\n", log);
    }


    #define NS_NULL 0xFFFFFFFF

    #define FILE_FREE 0
    #define FILE_PKR 1
    #define FILE_DISK 2

    #define SEEK_SET 0
    #define SEEK_CUR 1
    #define SEEK_END 2

    #define FILE_SLOTS 10

    char* FileTypes = (char*)0x006a3960;
    FILE** Files = (FILE* *)0x006a396c;
    int* PKRSizes = (int*)0x006a3994;
    int* PKROffsets = (int*)0x006a3dbc;
    int** PKRFiles = (int* *)0x006a3de4;

    char* workingDir = (char*)0x006a3e0c;
    char* PKR_Name = (char*)0x006a3f0c;


    void PCinit() {
        log("PCinit()");

        // clear arrays
        memset(PKRSizes, 0, FILE_SLOTS * sizeof(int));
        memset(PKROffsets, 0, FILE_SLOTS * sizeof(int));
        memset(PKRFiles, 0, FILE_SLOTS * sizeof(int));
        memset(Files, 0, FILE_SLOTS * sizeof(int));
        memset(FileTypes, 0, FILE_SLOTS);

        // remember working directory
        // TODO: fix warning
        _getcwd(workingDir, 256);
        printf_log("EXE RAN FROM %s\n", workingDir);

        WINMAIN_FindCD();
        WINMAIN_InstallSetup();

        // im pretty sure it bakes fullpath at PKR_Name
        sprintf(PKR_Name, "%s\\%s", workingDir, "all.pkr");

        printf("all.pkr at: %s\n", PKR_Name);

        PKR_PreLoad(PKR_Name);
    }

    size_t PCwrite(int fd, void* ptr, size_t size) {
        log("PCwrite()");

        if (fd == NS_NULL)
        {
            printf("PCwrite with fd = -1");
            return NS_NULL;
        }

        switch (FileTypes[fd])
        {
            case FILE_FREE:
                printf("PCwrite(): attempted to write an empty file!\n");
                return NS_NULL;

            case FILE_PKR:
                printf("This should never happen... PKRFILES are reandonly.");
                return size;

            case FILE_DISK:
                return ffwrite(ptr, 1, size, Files[fd]);

            default:
                printf("PCwrite(): Unknown file type!");
                return NS_NULL;
        }
    }
    
    void PCstop() {
        log("PCstop()");

        PKR_UnLoad(PKR_Name);
    }
    
    int getFreeFileIndex() {
        log("getFreeFileIndex()");

        for (int i = 0; i < 10; i++)
            if (FileTypes[i] == FILE_FREE)
                return i;

        return NS_NULL;
    }

    int PCclose(int fd) {
        log("PCClose()");

        if (fd == NS_NULL) return NS_NULL;

        switch(FileTypes[fd]) {

            case FILE_FREE:
                printf("Tried to close an empty file...");
                return NS_NULL;

            case FILE_PKR:
                if (PKRFiles[fd] != NULL)
                    ffree(PKRFiles[fd]);

                PKRFiles[fd] = NULL;
                PKROffsets[fd] = 0;
                PKRSizes[fd] = 0;
                FileTypes[fd] = FILE_FREE;
                
                return 0;
            
            case FILE_DISK: {
                FILE* file = Files[fd];

                Files[fd] = NULL;
                FileTypes[fd] = FILE_FREE;

                if (file != NULL)
                    return (ffclose(file) != -1) - 1;
                    
                return NS_NULL;
            }

            default:
                printf("PCClose: invalid file type! %i\n", fd);
                return NS_NULL; 
        }
    }

    int PClseek(int fd, int offset, int origin) {
        log("PClseek()");

        if ((fd == NS_NULL) || (FileTypes[fd] == FILE_FREE)) {
            printf_log("PClseek -1\n");
            return NS_NULL;
        }

        if (FileTypes[fd] == FILE_PKR) {

            switch (origin) {

                case SEEK_SET:
                    PKROffsets[fd] = offset;
                    break;

                case SEEK_CUR:
                    PKROffsets[fd] += offset;
                    break;

                case SEEK_END:
                    PKROffsets[fd] = PKRSizes[fd] - offset;
                    break;
            }

            return PKROffsets[fd];
        }

        if (FileTypes[fd] == FILE_DISK)
        {
            if (origin != SEEK_CUR && origin != SEEK_END && origin != SEEK_SET)
                return fftell(Files[fd]);

            ffseek(Files[fd], offset, origin);

            return fftell(Files[fd]);
        }

        return NS_NULL;
    }

    int PCcreate(char* pName) {
        log("PCcreate()");

        int i = getFreeFileIndex();
        if (i < 0) return NS_NULL;

        char buf[256];
        sprintf(buf, "%s\\%s", workingDir, pName);

        Files[i] = ffopen(buf, "wb"); // it uses some var for mode here, but why would it

        if (Files[i] == NULL) {
            printf("PCCreate failed!\n");
            return NS_NULL;
        }

        FileTypes[i] = FILE_DISK;

        return i;
    }

    int PCremove(char* pName) {
        log("PCremove() ");

        char buf[256];
        sprintf(buf, "%s\\%s", workingDir, pName);

        return ffremove(buf);
    }

    int PCread(int fd, void* dst, int size) {
        log("PCread()");

        if (fd == -1 || FileTypes[fd] == FILE_FREE)
        {
            return NS_NULL;
        }

        if (FileTypes[fd] == FILE_DISK)
            return ffread(dst, 1, size, Files[fd]);
        
        if (FileTypes[fd] == FILE_PKR)
        {
            void* p = (void*)(PKRFiles[fd] + PKROffsets[fd]);

            memcpy(dst, p, size);

            PKROffsets[fd] += size;

            return size;
        }

        return NS_NULL;
    }


    Hook::Reroute hookList[] = {
        
        { 0x00432ec0,	PCwrite },
        { 0x00478cf2,	PCwrite },
        { 0x00478d14,	PCwrite },
        { 0x004e6215,	PCwrite },
        { 0x004f348c,	PCwrite },

        { 0x004e478a,	getFreeFileIndex }, // PC Open
        { 0x004e4ad7,	getFreeFileIndex }, // PC create

        { 0x004f4c03,   PCstop },
        { 0x004f514f,   PCstop },
        
        { 0x00432e97,   PCinit },
        { 0x00448f70,   PCinit },
        { 0x00478cc8,   PCinit },
        { 0x004f4f71,   PCinit },

        { 0x00432eb2,	PClseek },
        { 0x0044913d,	PClseek },
        { 0x00449158,	PClseek },
        { 0x00478ce6,	PClseek },
        { 0x004d6ca1,	PClseek },
        { 0x004e6188,	PClseek },
        { 0x004e61f8,	PClseek },
        { 0x004eaadf,	PClseek },
        { 0x004eaaeb,	PClseek },
        { 0x004f347c,	PClseek },
        
        { 0x00432ea2,   PCcreate },
        { 0x00478cd4,   PCcreate },
        { 0x004e60d7,   PCcreate },
        { 0x004f3469,   PCcreate },

        { 0x00449561,	PCread },
        { 0x004d5f2b,	PCread },
        { 0x004d5f38,	PCread },
        { 0x004d6609,	PCread },
        { 0x004d6619,	PCread },
        { 0x004d66d6,	PCread },
        { 0x004d6c34,	PCread },
        { 0x004d6c41,	PCread },
        { 0x004d6cad,	PCread },
        { 0x004e61a5,	PCread },
        { 0x004eaaff,	PCread },
        { 0x004f336c,	PCread },

        { 0x004e60f5,	PCremove },


        { NULL, NULL }
    };

    Hook::Reroute* pHookList = &hookList[0];
}