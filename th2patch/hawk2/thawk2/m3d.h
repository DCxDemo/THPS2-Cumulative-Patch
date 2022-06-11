#pragma once

int* M3d_WireframeMode = (int*)0x560fdc;
int* M3d_WireframeLast = (int*)0x560fe0;

int* RenderModelFlags = (int*)0x55ed04;

/*
void RenderModel(void* model)
{
    int flags = M3d_WireframeMode ? 0x200 : 0;

    D3DMODEL_RenderModel(model, *RenderModelFlags | uVar1);
    *M3d_WireframeMode = *M3d_WireframeLast;
}
*/