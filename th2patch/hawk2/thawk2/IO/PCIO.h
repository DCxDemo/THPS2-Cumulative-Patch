#include "stdafx.h"
#include "..\types.h"

/*
    Functions to acces files on PC.
	It wraps PKR loading and fallback disk access in case PKR is missing.

    the logic is it has a static file queue of size 10.
    whenever you open a file, it finds a free slot and loads data either from PKR or disk.
    most functions use file index in the queue.

    not sure what file was called originally
*/

typedef void(*PCinit_t)();
typedef void(*PCstop_t)();
typedef void(*PCremove_t)();
typedef int(*PCopen_t)(char* filename, int mode);   // returns file ID
typedef int(*getFreeFileIndex_t)();
typedef void*(*PCcreate_t)(char* filename);
typedef long(*PClseek_t)(int fileID, int offset, int origin);
typedef void(*PCread_t)();
typedef void(*PCwrite_t)();
typedef void(*PCclose_t)(uint file);

static const PCinit_t PCinit = (PCinit_t)0x004e45c0;
static const PCstop_t PCstop = (PCstop_t)0x004e46c0;
static const PCremove_t PCremove = (PCremove_t)0x004e46d0;
static const PCopen_t PCopen = (PCopen_t)0x004e4780;
static const getFreeFileIndex_t getFreeFileIndex = (getFreeFileIndex_t)0x004e4ab0;
static const PCcreate_t PCcreate = (PCcreate_t)0x004e4ad0;
static const PClseek_t PClseek = (PClseek_t)0x004e4bc0;
static const PCread_t PCread = (PCread_t)0x004e4ca0;
static const PCwrite_t PCwrite = (PCwrite_t)0x004e4d30;
static const PCclose_t PCclose = (PCclose_t)0x004e4d90;