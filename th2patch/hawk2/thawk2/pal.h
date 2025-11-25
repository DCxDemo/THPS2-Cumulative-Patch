#include "stdafx.h"
#include "types.h"
#include "..\patch\hook.h"

namespace Pal {

    extern Hook::Reroute* pHookList;

    typedef struct SPalette {
        ushort Clut;
        char slot;
        char flags;
        ushort Usage;
        bool InVRAM;
        char RemapIndex;
        uint Checksum;
        void* pD3DPalette;
        SPalette* pPrev;
        SPalette* pNext;
    } SPalette;


    typedef void(*Pal_Init_t)();
    typedef void(*Pal_Cleanup_t)();
    // typedef void(*NewPaletteEntry_t)();
    // typedef void(*RemovePaletteEntry_t)();
    // typedef void(*Pal_FindPaletteEntry_t)();
    // typedef void(*Pal_RemoveUnusedPalettes_t)();
    // typedef void(*GetFree16Slot_t)();
    typedef void(*Free16Slot_t)();
    // typedef void(*GetFree256Slot_t)();
    typedef void(*_free256slot_t)();
    typedef void(*_calcPaletteUsageStats_t)();
    typedef void(*Get256SlotNumber_t)();
    typedef void(*Get16SlotNumber_t)();
    typedef void(*_psxUploadtoVRAM_t)();
    typedef void(*_psxUploadtoVRam2_t)();
    typedef void(*Pal_LoadPalette_t)();
    typedef void(*Pal_CopyToMemory_t)();
    typedef void(*Pal_StoreFromMemory_t)();

    static const Pal_Init_t Pal_Init = (Pal_Init_t)0x004879a0;
    static const Pal_Cleanup_t Pal_Cleanup = (Pal_Cleanup_t)0x00487c10;
    // static const NewPaletteEntry_t NewPaletteEntry = (NewPaletteEntry_t)0x00487c50;
    SPalette* NewPaletteEntry(uint Checksum);
    // static const RemovePaletteEntry_t RemovePaletteEntry = (RemovePaletteEntry_t)0x00487ca0;
    void RemovePaletteEntry(SPalette* pPal);
    // static const Pal_FindPaletteEntry_t Pal_FindPaletteEntry = (Pal_FindPaletteEntry_t)0x00487cf0;
    SPalette* Pal_FindPaletteEntry(uint Checksum);
    // static const Pal_RemoveUnusedPalettes_t Pal_RemoveUnusedPalettes = (Pal_RemoveUnusedPalettes_t)0x00487d10;
    void Pal_RemoveUnusedPalettes();
    // static const GetFree16Slot_t GetFree16Slot = (GetFree16Slot_t)0x00487d80;
    int GetFree16Slot();
    static const Free16Slot_t Free16Slot = (Free16Slot_t)0x00487df0;
    // static const GetFree256Slot_t GetFree256Slot = (GetFree256Slot_t)0x00487e80;
    int GetFree256Slot();
    static const _free256slot_t _free256slot = (_free256slot_t)0x00487ef0;
    static const _calcPaletteUsageStats_t _calcPaletteUsageStats = (_calcPaletteUsageStats_t)0x00487f80;
    static const Get256SlotNumber_t Get256SlotNumber = (Get256SlotNumber_t)0x00487fe0;
    static const Get16SlotNumber_t Get16SlotNumber = (Get16SlotNumber_t)0x00487ff0;
    static const _psxUploadtoVRAM_t _psxUploadtoVRAM = (_psxUploadtoVRAM_t)0x00488000;
    static const _psxUploadtoVRam2_t _psxUploadtoVRam2 = (_psxUploadtoVRam2_t)0x00488070;
    static const Pal_LoadPalette_t Pal_LoadPalette = (Pal_LoadPalette_t)0x004880d0;
    static const Pal_CopyToMemory_t Pal_CopyToMemory = (Pal_CopyToMemory_t)0x004883c0;
    static const Pal_StoreFromMemory_t Pal_StoreFromMemory = (Pal_StoreFromMemory_t)0x004883f0;
}