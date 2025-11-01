#include "stdafx.h"
#include "decomp.h"

namespace Decomp {

	// writes a single value to destination stream
	unsigned char* Decompress_AllSame(unsigned char* pSource, short* pDest, int StepSize, int StreamLength) {

		//printf("Decompress_AllSame called!\n");

		// read value to fill with
		short value = pSource[1] | pSource[2] << 8;

		while (StreamLength > 0) {
			*pDest = value;
			pDest += StepSize;
			StreamLength--;
		}

		return pSource + 3;
	}

	// writes zeroes to destination stream
	unsigned char* Decompress_AllZero(unsigned char* pSource, short* pDest, int StepSize, int StreamLength) {

		//printf("Decompress_AllZero called!\n");

		while (StreamLength > 0) {
			*pDest = 0;
			pDest += StepSize;
			StreamLength--;
		}

		return pSource + 1;
	}

	unsigned char* Decompress_Trivial(unsigned char* pSource, short* pDest, int StepSize, int StreamLength) {
		//printf("Decompress_Trivial called!\n");

		unsigned char headerByte = pSource[0];
		unsigned char* pData = pSource + 1;
		short bitStuff = headerByte >> 4;
		short numBits = bitStuff + 1;

		short opCode = headerByte & 0x0F;
		short bitsToTake = opCode + 1;

		int _streamLen = StreamLength - 1;
		int lenDiff = 0;

		if (numBits > 1) {
			_streamLen /= numBits;
			lenDiff = (StreamLength - _streamLen * numBits) - 1;
		}

		// read base value
		short baseValue = pData[0] | pData[1] << 8;
		pData = pSource + 3;

		// write base value to dst stream
		*pDest = baseValue;
		pDest += StepSize;

		short deltaValue = 0;
		short nextValue = 0;
		short bitsTaken = 0;

		short srcValue = baseValue;

		for (int i = 0; i < _streamLen; i++) {

			deltaValue = pData[0] | pData[1] << 8;
			pData += 2;

			srcValue = baseValue;

			for (int j = 0; j < bitStuff; j++) {
				baseValue += (deltaValue - srcValue) / numBits;
				*pDest = baseValue;
				pDest += bitsToTake;
			}

			*pDest = deltaValue;
			pDest += bitsToTake;

			baseValue = deltaValue;
		}

		if (lenDiff > 0) {

			srcValue = pData[0] | pData[1] << 8;
			pData += 2;

			short deltaValue2 = deltaValue;
			for (int i = 0; i < lenDiff - 1; i++) {
				deltaValue += (srcValue - deltaValue2) / lenDiff;
				*pDest = deltaValue;
				pDest += bitsToTake;
			}

			*pDest = srcValue;
		}

		return pData;
	}

	unsigned char* Decompress_PackDelta(unsigned char* pSource, short* pDest, int StepSize, int StreamLength) {

		//printf("Decompress_PackDelta called!\n");

		unsigned char headerByte = pSource[0];
		unsigned char* pData = pSource + 1;
		short bitStuff = headerByte >> 4;
		short numBits = bitStuff + 1;

		short opCode = headerByte & 0x0F;
		short bitsToTake = opCode + 1;

		int _streamLen = StreamLength - 1;
		int lenDiff = 0;

		if (numBits > 1) {
			_streamLen /= numBits;
			lenDiff = (StreamLength - _streamLen * numBits) - 1;
		}

		// read base value
		short baseValue = pData[0] | pData[1] << 8;
		pData = pSource + 3;

		// write base value to dst stream
		*pDest = baseValue;
		pDest += StepSize;

		short deltaValue = 0;
		short nextValue = 0;
		short bitsTaken = 0;

		short shift = 32 - bitsToTake & 0x1F;


		short srcValue = baseValue;

		for (int i = 0; i < _streamLen; i++) {

			deltaValue = ((pData[2] | pData[1] << 8 | pData[0] << 16) << bitsTaken + 8) >> shift;

			baseValue = deltaValue + srcValue;

			bitsTaken = bitsTaken + bitsToTake;
			pData += bitsTaken >> 3;
			bitsTaken = bitsTaken & 7;

			for (int j = 0; j < bitStuff; j++) {
				srcValue += deltaValue / numBits;
				*pDest = srcValue;
				pDest += StepSize;
			}

			*pDest = baseValue;
			pDest += StepSize;

			srcValue = baseValue;
		}

		if (lenDiff > 0) {

			deltaValue = ((pData[2] | pData[1] << 8 | pData[0] << 16) << bitsTaken + 8) >> shift;

			bitsTaken += bitsToTake;
			pData += bitsTaken >> 3;
			bitsTaken &= 7;

			int x = deltaValue + baseValue;

			for (int i = 0; i < lenDiff - 1; i++) {
				baseValue += deltaValue / lenDiff;
				*pDest = baseValue;
				pDest += StepSize;
			}

			*pDest = x;
		}

		if (bitsTaken > 0) pData++;

		return pData;
	}

	unsigned char* DecompressStream(unsigned char* pSource, short* pDest, int StepSize, int StreamLength) {

		Compression opcode = (Compression)(*pSource & 0xF);

		//printf("DecompressStream type = %i\n", opcode);

		switch (opcode) {

			case Compression::Trivial:
				return Decompress_Trivial(pSource, pDest, StepSize, StreamLength);

			case Compression::AllSame:
				return Decompress_AllSame(pSource, pDest, StepSize, StreamLength);

			case Compression::AllZero:
				return Decompress_AllZero(pSource, pDest, StepSize, StreamLength);

			case Compression::PackDelta2:
			case Compression::PackDelta3:
			case Compression::PackDelta4:
			case Compression::PackDelta5:
			case Compression::PackDelta6:
			case Compression::PackDelta7:
			case Compression::PackDelta8:
			case Compression::PackDelta9:
			case Compression::PackDelta10:
			case Compression::PackDelta11:
			case Compression::PackDelta12:
			case Compression::PackDelta13:
			case Compression::PackDelta14:
				return Decompress_PackDelta(pSource, pDest, StepSize, StreamLength);

			default:
				// should never happen
				throw "unsupported compression type";
		}
	}




	// === hook stuff ===

	Hook::Reroute hookList[] = {

		{ 0x00430e4b, DecompressStream },
		{ 0x00430e57, DecompressStream },
		{ 0x00430e60, DecompressStream },
		{ 0x00430e6c, DecompressStream },
		{ 0x00430e7b, DecompressStream },
		{ 0x00430e87, DecompressStream },

		//=========================
		{ NULL, NULL }
	};

	Hook::Reroute* pHookList = &hookList[0];
}