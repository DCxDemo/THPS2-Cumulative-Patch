#pragma once
#include "..\..\patch\hook.h"

/*
    Functions to acces files on PC.
	It wraps PKR loading and fallback disk access in case PKR is missing.

    the logic is it has a static file queue of size 10.
    whenever you open a file, it finds a free slot and loads data either from PKR or disk.
    most functions use file index in the queue.

    quite possible it's some default Psy-Q mechanism emulation

    not sure what file was called originally, but it comes in between PCMOVIE and psy-q stuff
*/

namespace PCIO {

    extern bool enableLog;

    extern Hook::Reroute* pHookList;

    //typedef void(*PCinit_t)();
    //typedef void(*PCstop_t)();
    //typedef void(*PCremove_t)(char* pName);
    typedef int(*PCopen_t)(char* pName, int mode);   // returns file ID
    //typedef int(*getFreeFileIndex_t)();
    //typedef void* (*PCcreate_t)(char* pName);
    //typedef long(*PClseek_t)(int fd, int offset, int origin);
    //typedef void(*PCread_t)();
    //typedef int(*PCwrite_t)(int fd, void* ptr, size_t size);
    //typedef void(*PCclose_t)(int fd);

    // static const PCinit_t PCinit = (PCinit_t)0x004e45c0;
    void PCinit();
    // static const PCstop_t PCstop = (PCstop_t)0x004e46c0;
    void PCstop();
    // static const PCremove_t PCremove = (PCremove_t)0x004e46d0;
    int PCremove(char* pName);
    static const PCopen_t PCopen = (PCopen_t)0x004e4780;
    // static const getFreeFileIndex_t getFreeFileIndex = (getFreeFileIndex_t)0x004e4ab0;
    int getFreeFileIndex();
    // static const PCcreate_t PCcreate = (PCcreate_t)0x004e4ad0;
    int PCcreate(char* pName);
    // static const PClseek_t PClseek = (PClseek_t)0x004e4bc0;
    int PClseek(int fd, int offset, int origin);
    // static const PCread_t PCread = (PCread_t)0x004e4ca0;
    int PCread(int fd, void* dst, int size);
    // static const PCwrite_t PCwrite = (PCwrite_t)0x004e4d30;
    size_t PCwrite(int fd, void* ptr, size_t size);
    // static const PCclose_t PCclose = (PCclose_t)0x004e4d90;
    int PCclose(int fd);


    // guess it was different somehow cause doesnt crash if hook originals?

    typedef int(*ffseek_t)(FILE* file, int offset, int whence);
    static const ffseek_t ffseek = (ffseek_t)0x004ff08f;

    typedef long(*fftell_t)(FILE* file);
    static const fftell_t fftell = (fftell_t)0x004fef0c;

    typedef void(*ffree_t)(void* p);
    static const ffree_t ffree = (ffree_t)0x004fe95c;

    typedef long(*ffclose_t)(FILE* file);
    static const ffclose_t ffclose = (ffclose_t)0x004fdc6b;

    typedef long(*ffread_t)(void* p, int size, int count, FILE* file);
    static const ffread_t ffread = (ffread_t)0x004ff148;

    typedef long(*ffwrite_t)(void* p, int size, int count, FILE* file);
    static const ffwrite_t ffwrite = (ffwrite_t)0x004fe74d;

    typedef FILE*(*ffopen_t)(char* pName, char* mode);
    static const ffopen_t ffopen = (ffopen_t)0x004fe1e9;

    typedef int(*ffremove_t)(char* pName);
    static const ffremove_t ffremove = (ffremove_t)0x004fed90;
}