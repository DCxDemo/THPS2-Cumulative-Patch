#include "stdafx.h"
#include "Trig.h"
#include "Globals.h"
#include "mem.h"
#include "Utils.h"
#include "IO\fileio.h"

namespace Trig {

	bool* numTrackSpoolingBuffers = (bool*)0x0055cbf4;
	ushort* unkVal = (ushort*)0x00544574;


	int* NumCheatRestarts = (int*)0x0056ae14;
	int* NumHorseRestarts = (int*)0x0056ae68;

	TrigFileHeader* TrigFile = (TrigFileHeader*)0x0056ae6c;
	int* OffsetList = (int*)0x0056ae70;
	short** ppOffsetList = (short**)0x0056ae70;
	int* NumNodes = (int*)0x0056ae74;



	// send pulse to all links
	void Trig_SendPulse(ushort* pNode) {
		printf_s("DECOMP: Trig_SendPulse()\n");

		// start by reading num links
		for (int i = (uint)*pNode; i > 0; i--) {
			pNode++;
			Trig_SendPulseToNode(*pNode);
		}
	}


	void Trig_DeleteTrigFile() {
		printf_s("DECOMP: Trig_DeleteTrigFile()\n");

		// doesnt crash, but no idea if works properly

		if (TrigFile != NULL) {
			NsMem::Mem_Delete(TrigFile);
			TrigFile = NULL;
		}

		*NumCheatRestarts = 0;
		*NumHorseRestarts = 0;
	}


	void Trig_InitialParseTRGFile() {
		printf_s("DECOMP: Trig_InitialParseTRGFile()\n");

		*numTrackSpoolingBuffers = 0;
		Trig_ScanRestart();
		*unkVal = 0xffff;

		// if in splitscreen
		// attempt to look for autoexec2
		// it may be missing in some trg files, so it's optional
		if (*GNumberOfPlayers == 2) {

			// check every node
			for (int i = 0; i < *NumNodes; i++) {

				int* offset = (int*)*OffsetList;
				short value = *(short*)offset[i];

				// if node is autoexec2
				if ((ENodeType)value == ENodeType::AutoExec2) {

					printf_s("node %i is autoexec2!\n", i);

					// execute command list
					return ExecuteCommandList((void*)(((int)offset[i]) + 2), i, 1);
				}
			}
		}
		// otherwise find autoexec1 
		else
		{
			// check every node
			for (int i = 0; i < *NumNodes; i++) {

				int* offset = (int*)*OffsetList;
				short value = *(short*)offset[i];

				// if node is autoexec
				if ((ENodeType)value == ENodeType::AutoExec) {

					printf_s("node %i is autoexec!\n", i);

					// execute command list
					return ExecuteCommandList( (void*)(((int)offset[i]) + 2), i, 1);
				}
			}
		}

		// and if not a single return hit, we have no autoexec in the file!
		printf_s("autoexec not found!!!");
	}

	void Trig_LoadTRG_Hook(char* trgName)
	{
		Trig_LoadTRG(trgName);

		printf_s("trig now %i\n", TrigFile);
		printf_s("trig_offset now %i\n", OffsetList);

		Sleep(1000);

		// it essentially looks just like "add extension", but check
		printf_s("DECOMP: Trig_LoadTRG(%s)\n", trgName);

		char buf[MAX_BUFFER_SIZE];

		sprintf_s(buf, "%s.trg\0", trgName);

		// open trig file
		int size = FileIO::FileIO_Open(&buf[0]);

		// allocate memory for trig file
		TrigFile = (TrigFileHeader*)NsMem::Mem_New(size, 0, 1, 0);

		// load trig file
		FileIO::FileIO_Load((void*)TrigFile);

		// sync
		FileIO::FileIO_Sync();


		// validate the header data
		if (!Utils_CompareStrings(TrigFile->magic, "_TRG", 4)) {
			printf_s("Not a TRG file.");
			return;
		}

		if (TrigFile->version != TRG_FILE_VERSION) {
			printf_s("Wrong trigger file version.");
			return;
		}

		if (TrigFile->project != TRG_PROJ_VERSION) {
			printf("Not a Skate trigger file.");
			return;
		}

		// convert local file pointers to absolute pointers
		if (TrigFile->numNodes > 0) {
			for (int i = 0; i < TrigFile->numNodes; i++) {

				//printf_s("node: before %i", TrigFile->Nodes[i]);

				TrigFile->Nodes[i] += (int)TrigFile;

			//	printf_s(" after %i\n", TrigFile->Nodes[i]);
			}
		}

		*OffsetList = (int)((int)TrigFile + 12);

		NsMem::Mem_Shrink(TrigFile, size);

		/*
		// if last node is terminator, can omit the hassle maybe? we have enough ram now
		// it calls mem shrink and writes end somewhere, not ever used after
		if ((short)*OffsetList[NumNodes - 1] == 0xff) {
			// shrink it?
			uVar5 = (int)OffsetList[NumNodes - 1] + (5 - (int)_TrigFile) & 0xfffffffc;
			Mem_Shrink(_TrigFile,uVar5);
			_DAT_0056a910 = uVar5;
		}
		*/

		printf_s("done loading\n");

		printf_s("trig now %i\n", TrigFile);
		printf_s("trig_offset now %i\n", OffsetList);

		Sleep(1000);
	}


	short* RestartNode = (short*)0x0544574;

	/*
	void Trig_SetRestart(char* name) {

		printf_s("DECOMP: Trig_SetRestart(%s)\n", name);

		*RestartNode = -1;

		int nodeIndex = 0;

		if (NumNodes > 0) {
			for (int i = 0; i < *NumNodes; i++) {

				int* offset = (int*)*OffsetList;
				short value = *(short*)offset[i];

				//if ((short)*OffsetList[nodeIndex] == 8) {
				if ((ENodeType)value == ENodeType::Restart)
				{
					// ...
					piVar2 = Trig_GetPosition(&local_c, nodeIndex);

					// if restart name matches
					if (Utils_CompareStrings((char*)((int)piVar2 + 6), name, -1) != 0) {
						*RestartNode = nodeIndex;
						return;
					}

				}
			}
		}

		printf_s("restart %s no found!", name);
	}
	*/



	/*
	
	// should be easy
		SCommandPoint * GetCommandPoint__Fi(uint Node)

		{
		  SCommandPoint *cp;
  
		  if (((Node != 0xffff) && ((short)*OffsetList[Node] == 6)) &&
			 (cp = _CommandPoints, _CommandPoints != NULL)) {
			do {
			  if (*(ushort *)&cp->field_0xa_Node == Node) {
				return cp;
			  }
			  cp = cp->field_0x14_prevOb;
			} while (cp != NULL);
		  }
		  return NULL;
		}

	*/



    // === hook stuff ===

    Hook::Reroute hookList[] = {

        { 0x004527d5,   Trig_InitialParseTRGFile },

		{ 0x00458550,   Trig_DeleteTrigFile },
		{ 0x0043befb,   Trig_DeleteTrigFile },

		{ 0x004c4d53,	Trig_SendPulse },
		{ 0x004c40c8,	Trig_SendPulse },
		{ 0x004c409b,	Trig_SendPulse },
		{ 0x004c3979,	Trig_SendPulse },
		{ 0x004a62fc,	Trig_SendPulse },
		{ 0x0049b5cc,	Trig_SendPulse },
		{ 0x0049b550,	Trig_SendPulse },
		{ 0x0048e70b,	Trig_SendPulse },
		{ 0x00402449,	Trig_SendPulse },
		{ 0x00401400,	Trig_SendPulse },

		// { 0x004527cd, Trig_LoadTRG_Hook },
		// { 0x0043bcad, Trig_LoadTRG_Hook },



        //=========================
        { NULL, NULL }
    };

    Hook::Reroute* pHookList = &hookList[0];

}