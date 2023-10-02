#pragma once
#include "thawk2/Career.h"

//category headlines, used to divide gaps per type in gap list
extern SGapTrick catAir;
extern SGapTrick catGrind;
extern SGapTrick catManual;
extern SGapTrick catLip;
extern SGapTrick catOther;

extern SGapTrick* pGapListThps1;
extern SGapTrick* pGapListThps2;
extern SGapTrick* pGapListThps3;
extern SGapTrick* pGapListThps4;

void PrintGap(SGapTrick* pGap);
void CopyGaps(SGapTrick* src, SGapTrick* dst);
void WipeGaps();