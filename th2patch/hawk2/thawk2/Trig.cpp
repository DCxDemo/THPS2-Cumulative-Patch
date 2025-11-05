#include "stdafx.h"
#include "Trig.h"
#include "Globals.h"
#include "mem.h"
#include "Utils.h"

namespace Trig {

	bool* numTrackSpoolingBuffers = (bool*)0x0055cbf4;
	ushort* unkVal = (ushort*)0x00544574;


	int* NumCheatRestarts = (int*)0x0056ae14;
	int* NumHorseRestarts = (int*)0x0056ae68;
	void* TrigFile = (void*)0x0056ae6c;


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
			Mem_Delete(TrigFile);
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

				int* offset = (int*)*Trig_OffsetList;
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

				int* offset = (int*)*Trig_OffsetList;
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

	/*
	void Trig_LoadTRG(char* trgName)
	{
		// copy trg extension to string?
		cVar4 = *trgName;
		puVar8 = &".trg;
			pcVar3 = local_20;
		cVar1 = DAT_005446e0;

		if (cVar4 != '\0') {
			do {
				*pcVar3 = cVar4;
				cVar4 = pcVar3[(int)(trgName + (1 - (int)local_20))];
				pcVar3 = pcVar3 + 1;
			} while (cVar4 != '\0');
		}

		while (cVar1 != '\0') {
			*pcVar3 = cVar1;
			pcVar10 = puVar8 + 1;
			pcVar3 = pcVar3 + 1;
			puVar8 = puVar8 + 1;
			cVar1 = *pcVar10;
		}

		*pcVar3 = '\0';

		// open trig file
		size = FileIO_Open(local_20);

		// allocate memory for trig file
		_TrigFile = (int*)Mem_New(size, 0, 1, 0);

		// load trig file
		FileIO_Load(_TrigFile);

		FileIO_Sync();

		if (_TrigFile[0] != 0x4752545f) {
			printf_s(s_ % s.trg_Not_a__TRG_file_005446c8);
			return;
		}

		if (_TrigFile[1] & 0xFFFF != 2) {
			printf_s(s_Wrong_trigger_file_version._ % s.t_005446a4);
			return;
		}

		if (_TrigFile[1] & 0xFFFF0000 != 0) {
			printf_s(s_Not_a_Skate_trigger_file, _ % s.trg_00544680);
			return;
		}

		*NumNodes = (uint) * (ushort*)(piVar2 + 2);
		ppiVar9 = (int**)(piVar2 + 3);
		Trig_OffsetList = ppiVar9;

		if (*NumNodes > 0) {
			for (int i = 0; i < *NumNodes; i++) {
				*ppiVar9 = (int*)((int)*ppiVar9 + (int)_TrigFile);
				ppiVar9 = ppiVar9 + 1;
				iVar7 = iVar7 + 1;
			}
		}

		/*
		// if last node is terminator, can omit the hassle maybe we have enough ram now
		if ((short)*Trig_OffsetList[NumNodes - 1] == 0xff) {
			// shrink it?
			uVar5 = (int)Trig_OffsetList[NumNodes - 1] + (5 - (int)_TrigFile) & 0xfffffffc;
			Mem_Shrink(_TrigFile,uVar5);
			_DAT_0056a910 = uVar5;
		}
			}
		*/


	short* RestartNode = (short*)0x0544574;

	/*
	void Trig_SetRestart(char* name) {

		printf_s("DECOMP: Trig_SetRestart(%s)\n", name);

		*RestartNode = -1;

		int nodeIndex = 0;

		if (NumNodes > 0) {
			for (int i = 0; i < *NumNodes; i++) {

				int* offset = (int*)*Trig_OffsetList;
				short value = *(short*)offset[i];

				//if ((short)*Trig_OffsetList[nodeIndex] == 8) {
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
  
		  if (((Node != 0xffff) && ((short)*Trig_OffsetList[Node] == 6)) &&
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

        //=========================
        { NULL, NULL }
    };

    Hook::Reroute* pHookList = &hookList[0];

}