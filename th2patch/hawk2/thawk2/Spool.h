#pragma once

//typedef int(*Spool_FreeRegion_t)();
//typedef int(*Spool_FindRegion_t)(char* pName);
typedef void(*Spool_ClearRegion_t)(char* pName);
//typedef void(*Spool_LoadPSH_t)(char* pName, int param_2, int param_3, int param_4, int param_5);
typedef void*(*Spool_LoadPSHBuffer_t)(void* pBlock, char* pName, int param_3, int param_4, int* param_5, int param_6);


//static const Spool_FreeRegion_t Spool_FreeRegion = (Spool_FreeRegion_t)0x4af490;
int Spool_FreeRegion();
//static const Spool_FindRegion_t Spool_FindRegion = (Spool_FindRegion_t)0x4b0b10;
int Spool_FindRegion(char* pName);
static const Spool_ClearRegion_t Spool_ClearRegion = (Spool_ClearRegion_t)0x4b0bd0;
static const Spool_LoadPSHBuffer_t Spool_LoadPSHBuffer = (Spool_LoadPSHBuffer_t)0x004b2220;
//static const Spool_LoadPSH_t Spool_LoadPSH = (Spool_LoadPSH_t)0x4b2080;
void Spool_LoadPSH(char* pName, int param_2, int param_3, int* param_4, int param_5);

typedef int(*D3DTEX_TextureCountColors_t)(int**);
static const D3DTEX_TextureCountColors_t D3DTEX_TextureCountColors = (D3DTEX_TextureCountColors_t)0x004d7430;

typedef void*(*Spool_FindTextureEntry_t)(uint hash);
static const Spool_FindTextureEntry_t Spool_FindTextureEntry = (Spool_FindTextureEntry_t)0x004af910;