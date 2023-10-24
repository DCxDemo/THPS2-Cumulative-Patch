#include "stdafx.h"
#include "thawk2.h"
#include "types.h"


//demo viewport, final is different
struct SViewport {
	int xR;
	int yB;
	int xL;
	int yT;
	int Hither;
	int Yon;
	int TanHalf;
};

typedef struct SViewport SViewport;


uint* Camera_RandA = (uint*)0x0055c418;
uint* Camera_RandB = (uint*)0x0055c41c;
uint* Camera_RandSeed = (uint*)0x0055c608;

#define RANDOM_SEED 0x9f6ad

void Camera_InitialRand(uint seed)
{
	*Camera_RandA = 0x12b9b0a1;
	*Camera_RandB = 0xaa2fb3f;
	*Camera_RandSeed = seed;
}


int* PCMemBuffer = (int*)0x0055ec78;

#define RAM_SIZE 32 * 1024 * 1024 //original is 6 * 1000 * 1024 for whatever reason

//SViewport, missing for now
int* pCurrentViewport = (int*)0x00560698;

/// <summary>
/// Initialize various stuff, including memory space and game systems.
/// </summary>
void Init_AtStart()
{
	printf("decomp Init_AtStart called...");

	//something like this?

	//allocate buffer
	*PCMemBuffer = (int)malloc(RAM_SIZE);

	if (!*PCMemBuffer) throw;

	//clear memory
	memset((void*)(*PCMemBuffer), 0, RAM_SIZE);

	//_ResetCallback();

	//init memory card stuff
	MMU_Init();

	//set default viewport
	*pCurrentViewport = 0x00530da8; //&_ApocalypseViewport;

	//initialize mem stuff
	Init_ResetMemory(0x10); //heap0size? sup?

	//initialize pad system
	Pad_InitAtStart();



	//_InitGeom();
	//_ResetGraph(0);
	//_SetGraphDebug(0);

	//sets psyq draw callback, not needed
	//Db_InitAtStart();

	 //not required in the port
	//local_8 = 0;
	//local_6 = 0;
	//local_4 = 0x400;
	//local_2 = 0x200;
	//_ClearImage(&local_8, 0, 0, 0);

	//_VSyncCallback(MyVSync);
	//_SetDispMask(1);

	//empty func
	//Init_DebugStuff();

	//only sets up random values
	Camera_InitialRand(RANDOM_SEED);

	//does nothing in the port
	//SFX_InitAtStart();

	FileIO_Init();

	//empty func, must be something on psx
	//GameFMV_Init();

	//inits m3d stuff, sets resolution
	M3dInit_InitAtStart();

	//resets redbook globals
	Redbook_XAInit();

	Career_SaveCharacterStates();

	Career_Init();

	Front_ClearGVideoRestartData();

	printf("done\n");
}


#define HARD_CLEANUP 0
#define SOFT_CLEANUP 1
#define EDITOR_CLEANUP 2

int* TitleTimeout = (int*)0x00528cac;

void Init_Restart()
{
	printf("decomp Init_Restart called\n");

	Init_Cleanup(HARD_CLEANUP);

	Db_Reset();

	Spool_Init();

	*TitleTimeout = 0x14;

	Flash_Reset();

	//unused in the port
	//Pack_Init();
	
	//unused in the port
	//SFX_InitAtStart();

	Pal_Init(0x100, 0x50);
}


void TH2Main()
{
	printf("th2 main here!\n");

	//psyq call
	//_SetDispMask(0);
	 
	//not used in the port, init relocatable modules
	//Reloc_Init();

	Options_Init();

	Init_AtStart();

	Init_Restart();  //the params were passed to init_resetmemory inside, but it was removed in the port i guess - ( 0, 0x10);

	Db_Init(0, 0, 1, 0);

	//does nothing in release
	//Mem_SuperDebugUsage();

	if (!options.SkipIntro)
		IntroMovies();

	//show title screen
	LogoScreen();

	//and load into the main menu
	FrontEnd2_Main();

	/*
	//this is just to show "shutting down" string, removed
	FontManager::LoadFont(s_s2tricks.fnt_005224d0);
	Pause(2);
	*/

	//memory card related, calls 2 empty funcs in the port
	//MMU_Uninit();
	
	Init_AtEnd();
}

int* CamPtIndex = (int*)0x0055c744;

void CamPt_Init(void)
{
	*CamPtIndex = 0;
}

void Init_ForGame()
{
	printf("decomp Init_ForGame\n");

	*pCurrentViewport = 0x00530da8; //&_ApocalypseViewport;

	Front_Init();

	Video_InitOnce();

	CamPt_Init();
}