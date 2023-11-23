#pragma once
#include "thawk2.h"

void RenderModel(void* pModel);
void RenderModelFast(void* pModel);
void RenderBackgroundModel(void* pModel);
//void RenderModelInSuper
void RenderModelInSuperFast(void* pModel, uint flags);
void RenderModelNonRotated(void* pModel);
void RenderBackgroundModelNonRotated(void* pModel);