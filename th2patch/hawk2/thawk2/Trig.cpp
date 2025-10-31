#include "stdafx.h"
#include "Trig.h"
#include "Globals.h"

namespace Trig {

	bool* numTrackSpoolingBuffers = (bool*)0x0055cbf4;
	ushort* unkVal = (ushort*)0x00544574;

	void Trig_InitialParseTRGFile() {

		printf("DECOMP: Trig_InitialParseTRGFile()\n");

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

					printf("node %i is autoexec2!\n", i);

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

					printf("node %i is autoexec!\n", i);

					// execute command list
					return ExecuteCommandList( (void*)(((int)offset[i]) + 2), i, 1);
				}
			}
		}

		// and if not a single return hit, we have no autoexec in the file!
		printf("autoexec not found!!!");
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
			printf(s_ % s.trg_Not_a__TRG_file_005446c8);
			return;
		}

		if (_TrigFile[1] & 0xFFFF != 2) {
			printf(s_Wrong_trigger_file_version._ % s.t_005446a4);
			return;
		}

		if (_TrigFile[1] & 0xFFFF0000 != 0) {
			printf(s_Not_a_Skate_trigger_file, _ % s.trg_00544680);
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




    // === hook stuff ===

    Hook::Reroute hookList[] = {

        { 0x004527d5,   Trig_InitialParseTRGFile },

        //=========================
        { NULL, NULL }
    };

    Hook::Reroute* pHookList = &hookList[0];

}