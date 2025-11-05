#pragma once
#include "thawk2.h"
#include "..\patch\hook.h"

namespace M3d {

	extern Hook::Reroute* pHookList;

	// maybe 2 additional in the beginning
	typedef void(*M3d_RenderSetup_t)();
	typedef void(*M3d_RenderSetupCamera_t)();
	typedef void(*M3d_RenderCleanup_t)();
	typedef void(*M3d_Render_t)();
	typedef void(*RenderSuperItemShadow_t)(void* pModel);
	typedef void(*M3d_RenderSuperQuick_t)();
	// typedef void(*FUN_0x00460c20_t)(); // empty func
	typedef void(*M3d_RenderBackground_t)();
	typedef void(*RenderSuperItem_t)();
	// typedef void(*RenderModel_t)(void* pModel);
	// typedef void(*RenderModelFast_t)(void* pModel);
	// typedef void(*RenderBackgroundModel_t)(void* pModel);
	typedef void(*RenderModelInSuper_t)(void* pModel, uint flags);
	typedef void(*RenderModelInSuperFast_t)(void* pModel, uint flags);
	typedef void(*RenderModelNonRotated_t)(void* pModel);
	typedef void(*RenderBackgroundModelNonRotated_t)(void* pModel);
	typedef void(*M3d_BuildTransform_t)();
	typedef void(*uWibble_t)();
	typedef void(*vWibble_t)();
	typedef void(*M3d_PreprocessWibblyTextures_t)(void* p);
	typedef void(*M3d_PreprocessPulsingColours_t)(void* p);

	static const M3d_RenderSetup_t M3d_RenderSetup = (M3d_RenderSetup_t)0x0045e870;
	static const M3d_RenderSetupCamera_t M3d_RenderSetupCamera = (M3d_RenderSetupCamera_t)0x0045ef10;
	static const M3d_RenderCleanup_t M3d_RenderCleanup = (M3d_RenderCleanup_t)0x0045f380;
	static const M3d_Render_t M3d_Render = (M3d_Render_t)0x0045f4c0;
	static const RenderSuperItemShadow_t RenderSuperItemShadow = (RenderSuperItemShadow_t)0x00460480;
	static const M3d_RenderSuperQuick_t M3d_RenderSuperQuick = (M3d_RenderSuperQuick_t)0x00460a20;
	// static const FUN_0x00460c20_t FUN_0x00460c20 = (FUN_0x00460c20_t)0x00460c20;
	static const M3d_RenderBackground_t M3d_RenderBackground = (M3d_RenderBackground_t)0x00460c30;
	static const RenderSuperItem_t RenderSuperItem = (RenderSuperItem_t)0x00461080;
	// static const RenderModel_t RenderModel = (RenderModel_t)0x004619e0;
	void RenderModel(void* pModel);
	// static const RenderModelFast_t RenderModelFast = (RenderModelFast_t)0x00461a20;
	void RenderModelFast(void* pModel);
	//static const RenderBackgroundModel_t RenderBackgroundModel = (RenderBackgroundModel_t)0x00461a60;
	void RenderBackgroundModel(void* pModel);
	static const RenderModelInSuper_t RenderModelInSuper = (RenderModelInSuper_t)0x00461aa0;
	// static const RenderModelInSuperFast_t RenderModelInSuperFast = (RenderModelInSuperFast_t)0x00461ae0;
	void RenderModelInSuperFast(void* pModel, uint flags);
	// static const RenderModelNonRotated_t RenderModelNonRotated = (RenderModelNonRotated_t)0x00461b00;
	void RenderModelNonRotated(void* pModel);
	// static const RenderBackgroundModelNonRotated_t RenderBackgroundModelNonRotated = (RenderBackgroundModelNonRotated_t)0x00461b40;
	void RenderBackgroundModelNonRotated(void* pModel);
	static const M3d_BuildTransform_t M3d_BuildTransform = (M3d_BuildTransform_t)0x00461b80;
	static const uWibble_t uWibble = (uWibble_t)0x00461c20;
	static const vWibble_t vWibble = (vWibble_t)0x00461c50;
	static const M3d_PreprocessWibblyTextures_t M3d_PreprocessWibblyTextures = (M3d_PreprocessWibblyTextures_t)0x00461c80;
	static const M3d_PreprocessPulsingColours_t M3d_PreprocessPulsingColours = (M3d_PreprocessPulsingColours_t)0x00462100;


	void RenderModel_Hook(void* pModel);
	void RenderSuperItemShadow_Hook(void* pModel);
}