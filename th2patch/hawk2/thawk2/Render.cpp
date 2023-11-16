#include "stdafx.h"
#include "thawk2.h"

bool* M3d_WireframeMode = (bool*)0x00560fdc;
bool* M3d_WireframeLast = (bool*)0x00560fe0;
unsigned int* RenderModelFlags = (unsigned int*)0x0055ed04;


void RenderModel(void* pModel)
{
    //printf("DECOMP RenderModel()\n");

    D3DMODEL_RenderModel(pModel, *RenderModelFlags | (*M3d_WireframeMode ? 0x200 : 0));
    *M3d_WireframeMode = *M3d_WireframeLast;
}

void RenderModelFast(void* pModel)
{
    //printf("DECOMP RenderModelFast()\n");

    RenderModel(pModel);
}

void RenderBackgroundModel(void* pModel)
{
    //printf("DECOMP RenderBackgroundModel()\n");

    D3DMODEL_RenderModel(pModel, *RenderModelFlags | (*M3d_WireframeMode ? 0x210 : 0x10));
    *M3d_WireframeMode = *M3d_WireframeLast;
}

//void RenderModelInSuper

void RenderModelInSuperFast(void* pModel, uint flags)
{
    //printf("DECOMP RenderModelInSuperFast()\n");

    D3DMODEL_RenderModel(pModel, *RenderModelFlags | flags | 1);
}

void RenderModelNonRotated(void* pModel)
{
    //printf("DECOMP RenderModelNonRotated()\n");

    RenderModel(pModel);
}

void RenderBackgroundModelNonRotated(void* pModel)
{
    //printf("DECOMP RenderBackgroundModelNonRotated()\n");

    RenderBackgroundModel(pModel);
}