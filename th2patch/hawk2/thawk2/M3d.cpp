#include "stdafx.h"
#include "thawk2.h"

namespace M3d
{


    int* M3d_WireframeMode = (int*)0x560fdc;
    int* M3d_WireframeLast = (int*)0x560fe0;

    int* RenderModelFlags = (int*)0x55ed04;


    void RenderModel(void* pModel)
    {
        //printf("DECOMP RenderModel()\n");

        D3DMODEL_RenderModel(pModel, *RenderModelFlags | (*M3d_WireframeMode ? 0x200 : 0));
        *M3d_WireframeMode = *M3d_WireframeLast;
    }

    void RenderModelFast(void* pModel)
    {
        //printf("DECOMP RenderModelFast()\n");

        RenderModel_Hook(pModel);
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

        RenderModel_Hook(pModel);
    }

    void RenderBackgroundModelNonRotated(void* pModel)
    {
        //printf("DECOMP RenderBackgroundModelNonRotated()\n");

        RenderBackgroundModel(pModel);
    }


    void RenderModel_Hook(void* pModel)
    {

        RenderModel(pModel);
    }

    // shadow rendering
    void RenderSuperItemShadow_Hook(void* pModel)
    {
        if (options.DrawShadow)
            RenderSuperItemShadow(pModel);
    }

    void RenderModel_Dummy(void* pModel)
    {
        // removed it
    }


    // === hook stuff ===

    Hook::Reroute hookList[] = {

        // some powerup models
        {  0x004603c6, RenderModel_Hook },
        {  0x0046040c, RenderModel_Hook },

        // mostly far level mesh
        {  0x0046024f, RenderModelFast },
        {  0x0046029a, RenderModelFast },

        // ??
        {  0x0046104b, RenderBackgroundModel },

        // skater shadow
        //{  0x004609a6,  RenderModelInSuper },

        // skater model
        //{  0x00461913,  RenderModelInSuper },

        // ??
        {  0x0046190c, RenderModelInSuperFast },

        // mostly closer mesh
        {  0x00460338, RenderModelNonRotated },
        {  0x00460386, RenderModelNonRotated },

        // draws sky
        {  0x00461043, RenderBackgroundModelNonRotated },

        // shadow too?
        { 0x00460bf7, RenderSuperItemShadow_Hook },


        //=========================
        { NULL, NULL }
    };

    Hook::Reroute* pHookList = &hookList[0];
}