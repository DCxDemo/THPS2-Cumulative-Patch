#pragma once

struct SBlockHeader {
	size_t Size;
	int ParentHeap;
	SBlockHeader* Next;
};

typedef struct SBlockHeader SBlockHeader;


typedef int		(*Mem_Init_t)();
typedef int*	(*Mem_NewX_t)(size_t size, int Heap, int AssertOnFailure, void* Location);
typedef void	(*Bang_t)(int param_1, int param_2, int param_3); //psx leftover, originally draws red rectangle in the top right
typedef int*	(*Mem_NewTop_t)(int param_1);
typedef void	(*Mem_DeleteX_t)(void* p);
typedef void	(*Mem_ShrinkX_t)(void* param_1, int param_2);
typedef int		(*Mem_GetBlockSizeX_t)(int param_1);
typedef int		(*Mem_GetFree_t)(int param_1);
typedef void	(*Mem_Copy_t)(void* src, void* dst, int size);	//assumed, check if matches
//typedef void	(*Mem_CopyBytes_t)(int src, int dst, int size);	//assumed, check if matches
typedef void	(*Mem_Swap_t)(void* src, void* dst, int size);	//assumed, check if matches
typedef void	(*Mem_SuperDebugUsage_t)();			//unused leftover
typedef void	(*Mem_NoCheck_t)(void* param_1);	//unused leftover
typedef void	(*SuperMem_CheckForLeaks_t)();		//unused leftover
typedef void*	(*Mem_New_t)(size_t size, int Heap, int AssertOnFailure, void* Location);
//typedef void	(*Mem_Delete_t)(void* p);
typedef void	(*Mem_Shrink_t)(void* param_1, int param_2);
typedef void	(*Mem_GetBlockSize_t)(int param_1);

static const Mem_Init_t					Mem_Init = (Mem_Init_t)0x0046e850;
static const Mem_NewX_t					Mem_NewX = (Mem_NewX_t)0x0046e950;
static const Bang_t						Bang = (Bang_t)0x0046edb0;
static const Mem_NewTop_t				Mem_NewTop = (Mem_NewTop_t)0x0046edd0;
static const Mem_DeleteX_t				Mem_DeleteX = (Mem_DeleteX_t)0x0046ef90;
static const Mem_ShrinkX_t				Mem_ShrinkX = (Mem_ShrinkX_t)0x0046f070;
static const Mem_GetBlockSizeX_t		Mem_GetBlockSizeX = (Mem_GetBlockSizeX_t)0x0046f1e0;
static const Mem_GetFree_t				Mem_GetFree = (Mem_GetFree_t)0x0046f250;
static const Mem_Copy_t					Mem_Copy = (Mem_Copy_t)0x0046f270;
//static const Mem_CopyBytes_t			Mem_CopyBytes = (Mem_CopyBytes_t)0x0046f340;
void Mem_CopyBytes(void* _Dst, void* _Src, int _Size);
static const Mem_Swap_t					Mem_Swap = (Mem_Swap_t)0x0046f370;
static const Mem_SuperDebugUsage_t		Mem_SuperDebugUsage = (Mem_SuperDebugUsage_t)0x0046f3f0;
static const Mem_NoCheck_t				Mem_NoCheck = (Mem_NoCheck_t)0x0046f400;
static const SuperMem_CheckForLeaks_t	SuperMem_CheckForLeaks = (SuperMem_CheckForLeaks_t)0x0046f410;
static const Mem_New_t					Mem_New = (Mem_New_t)0x0046f420;
//static const Mem_Delete_t				Mem_Delete = (Mem_Delete_t)0x0046f460;
void Mem_Delete(void* p);
static const Mem_Shrink_t				Mem_Shrink = (Mem_Shrink_t)0x0046f470;
static const Mem_GetBlockSize_t			Mem_GetBlockSize = (Mem_GetBlockSize_t)0x0046f4a0;