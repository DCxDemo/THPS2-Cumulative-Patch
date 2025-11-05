#include "stdafx.h"
#include "flash.h"

namespace Flash {


	int* dR = (int*)0x0055e250;
	int* dG = (int*)0x0055e254;
	int* dB = (int*)0x0055e258;
	int* CurrentR = (int*)0x0055e25c;
	int* CurrentG = (int*)0x0055e260;
	int* CurrentB = (int*)0x0055e264;
	int* CurrentImportance = (int*)0x0055e268;
	int* FlashSort = (int*)0x0055e26c;
	int* FlashCountdown = (int*)0x0055e270;
	bool* Fading = (bool*)0x0055e274;
	int* FadeCountdown = (int*)0x0055e278;


	void Flash_Reset() {

		printf_s("DECOMP Flash_Reset()\n");

		*FlashCountdown = 0;
		*FadeCountdown = 0;
		*Fading = false;
		*CurrentImportance = 0;
	}

	bool Flash_FadeFinished() {
		printf_s("DECOMP Flash_FadeFinished() = \n");

		return *FadeCountdown == 0;
	}

	void Flash_Screen(char r, char g, char b, int time, int importance, int sort) {

		printf_s("DECOMP Flash_Screen()\n");

		if (*CurrentImportance > importance) return;
		if (time == 0) return;

		*FlashCountdown = time;
		*FlashSort = sort;
		*CurrentImportance = importance;

		// assign color
		*CurrentR = r << 0x10;
		*CurrentG = g << 0x10;
		*CurrentB = b << 0x10;

		// calculate color delta
		*dR = *CurrentR / time;
		*dG = *CurrentG / time;
		*dB = *CurrentB / time;
	}



	void Flash_Fade(int time, int sort) {

		printf_s("DECOMP Flash_Fade()\n");

		*Fading = true;

		*CurrentB = 0;
		*CurrentG = 0;
		*CurrentR = 0;

		*FadeCountdown = time;
		*CurrentImportance = 255;

		*dR = (int)(0xff0000 / time);
		*FlashSort = sort;
	}



	void Flash_Update() {
		if (!*Fading) {
			if (*FlashCountdown > 0) {
				(*FlashCountdown)--;

				if (*FlashCountdown == 0) {
					*CurrentImportance = 0;
					return;
				}

				*CurrentR -= *dR;
				*CurrentG -= *dB;
				*CurrentB -= *dG;
			}
		}
		else if (*FadeCountdown > 0) {
			(*FadeCountdown)--;

			if (*FadeCountdown == 0) {
				*CurrentB = 0xff0000;
				*CurrentG = 0xff0000;
				*CurrentR = 0xff0000;
			} else {
				*CurrentR += *dR;
				*CurrentG += *dR;
				*CurrentB += *dR;
			}
		}
	}






    // === hook stuff ===

    Hook::Reroute hookList[] = {

		{ 0x00458597, Flash_Reset },
		{ 0x0045867b, Flash_Reset },
		{ 0x0046974c, Flash_Reset },
		{ 0x0046a2d2, Flash_Reset },

		{ 0x0041a036, Flash_FadeFinished },
		{ 0x0041a606, Flash_FadeFinished },
		{ 0x00451c31, Flash_FadeFinished },
		{ 0x00451c5b, Flash_FadeFinished },

		{ 0x0040253a, Flash_Screen }, //ExecuteCommand

		{ 0x0041a206, Flash_Fade },
		{ 0x0041a6e2, Flash_Fade },
		{ 0x0044f917, Flash_Fade },
		{ 0x0044fc5b, Flash_Fade },
		{ 0x0044ff62, Flash_Fade },
		{ 0x0045008a, Flash_Fade },
		{ 0x004511f6, Flash_Fade },
		{ 0x00451648, Flash_Fade },
		{ 0x00451755, Flash_Fade },
		{ 0x00451888, Flash_Fade },
		{ 0x00451b68, Flash_Fade },

		{ 0x0041a031, Flash_Update },
		{ 0x0041a601, Flash_Update },
		{ 0x00451c2c, Flash_Update },
		{ 0x00451c56, Flash_Update },
		{ 0x00469df8, Flash_Update },

        //=========================
        { NULL, NULL }
    };

    Hook::Reroute* pHookList = &hookList[0];
}