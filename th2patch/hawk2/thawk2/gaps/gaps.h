#pragma once
#include "thawk2/Career.h"

extern SGapTrick* pGapListThps1;
extern SGapTrick* pGapListThps2;
extern SGapTrick* pGapListThps3;
extern SGapTrick* pGapListThps4;

void PrintGap(SGapTrick* pGap);
void CopyGaps(SGapTrick* src, SGapTrick* dst);
void WipeGaps();