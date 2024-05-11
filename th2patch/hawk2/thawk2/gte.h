#pragma once
#include "..\patch\hook.h"

/*
	GTE.H
	=====
	Emulates PSX GTE chip math.
	Attempts to avoid 16 bit data loss along the way.
*/

namespace gte
{
	extern Hook::Reroute* pHookList;


	typedef struct Vector3s {
		short X;
		short Y;
		short Z;
	} Vector3s;

	typedef struct Vector3i {
		int X;
		int Y;
		int Z;
	} Vector3i;


	typedef struct Vector3f {
		float X;
		float Y;
		float Z;
	} Vector3f;


	typedef struct Vector3d {
		double X;
		double Y;
		double Z;
	} Vector3d;

	// 20/29 ~68%

	typedef void(*mygte_lvtosv_t)();
	typedef void(*mygte_lvtosvU_t)();
	typedef void(*mygte_svtorgb_t)();
	typedef void(*gte_ldlzc_t)();
	//typedef void(*gte_gpf12_t)();
	//typedef void(*gte_gpl0_t)();
	//typedef void(*gte_gpl12_t)();
	//typedef void(*gte_lcv0_t)();
	//typedef void(*gte_lcir_t)();
	//typedef void(*gte_lcirtr_t)();
	//typedef void(*gte_llir_sf0_t)();
	//typedef void(*gte_llirbk_t)();
	//typedef void(*gte_llv0_t)();
	typedef void(*gte_mvmva_t)();
	typedef void(*gte_nclip_t)();
	//typedef void(*gte_op0_t)();
	//typedef void(*gte_op12_t)();
	//typedef void(*gte_rt_t)();
	//typedef void(*gte_rtir_t)();
	//typedef void(*gte_rtirtr_t)();
	//typedef void(*gte_rtir_sf0_t)();
	typedef void(*gte_rtps_t)();
	typedef void(*gte_rtpt_t)();
	//typedef void(*gte_rtv0_t)();
	//typedef void(*gte_rtv0tr_t)();
	//typedef void(*gte_rtv0_sf0_t)();
	//typedef void(*gte_rtv1_t)();
	//typedef void(*gte_rtv2_t)();
	//typedef void(*gte_sqr0_t)();

	static const mygte_lvtosv_t mygte_lvtosv = (mygte_lvtosv_t)0x004df230;
	static const mygte_lvtosvU_t mygte_lvtosvU = (mygte_lvtosvU_t)0x004df2f0;
	static const mygte_svtorgb_t mygte_svtorgb = (mygte_svtorgb_t)0x004df3a0;
	static const gte_ldlzc_t gte_ldlzc = (gte_ldlzc_t)0x004df470;
	//static const gte_gpf12_t gte_gpf12 = (gte_gpf12_t)0x004df560;
	void gte_gpf12();
	//static const gte_gpl0_t gte_gpl0 = (gte_gpl0_t)0x004df5b0;
	void gte_gpl0();
	//static const gte_gpl12_t gte_gpl12 = (gte_gpl12_t)0x004df610;
	void gte_gpl12();
	//static const gte_lcv0_t gte_lcv0 = (gte_lcv0_t)0x004df670;
	void gte_lcv0();
	//static const gte_lcir_t gte_lcir = (gte_lcir_t)0x004df990;
	void gte_lcir();
	//static const gte_lcirtr_t gte_lcirtr = (gte_lcirtr_t)0x004dfa30;
	void gte_lcirtr();
	//static const gte_llir_sf0_t gte_llir_sf0 = (gte_llir_sf0_t)0x004dfaf0;
	void gte_llir_sf0();
	//static const gte_llirbk_t gte_llirbk = (gte_llirbk_t)0x004dfb90;
	void gte_llirbk();
	//static const gte_llv0_t gte_llv0 = (gte_llv0_t)0x004dfc50;
	void gte_llv0();
	static const gte_mvmva_t gte_mvmva = (gte_mvmva_t)0x004e00b0;
	static const gte_nclip_t gte_nclip = (gte_nclip_t)0x004e00e0;
	//static const gte_op0_t gte_op0 = (gte_op0_t)0x004e0140;
	void gte_op0();
	//static const gte_op12_t gte_op12 = (gte_op12_t)0x004e01b0;
	void gte_op12();
	//static const gte_rt_t gte_rt = (gte_rt_t)0x004e0230;
	void gte_rt();
	//static const gte_rtir_t gte_rtir = (gte_rtir_t)0x004e02f0;
	void gte_rtir();
	//static const gte_rtirtr_t gte_rtirtr = (gte_rtirtr_t)0x004e0390;
	void gte_rtirtr();
	//static const gte_rtir_sf0_t gte_rtir_sf0 = (gte_rtir_sf0_t)0x004e0450;
	void gte_rtir_sf0();
	static const gte_rtps_t gte_rtps = (gte_rtps_t)0x004e04f0;
	static const gte_rtpt_t gte_rtpt = (gte_rtpt_t)0x004e06a0;
	//static const gte_rtv0_t gte_rtv0 = (gte_rtv0_t)0x004e0b60;
	void gte_rtv0();
	//static const gte_rtv0tr_t gte_rtv0tr = (gte_rtv0tr_t)0x004e0c00;
	void gte_rtv0tr();
	//static const gte_rtv0_sf0_t gte_rtv0_sf0 = (gte_rtv0_sf0_t)0x004e0cc0;
	void gte_rtv0_sf0();
	//static const gte_rtv1_t gte_rtv1 = (gte_rtv1_t)0x004e0d60;
	void gte_rtv1();
	//static const gte_rtv2_t gte_rtv2 = (gte_rtv2_t)0x004e0e00;
	void gte_rtv2();
	//static const gte_sqr0_t gte_sqr0 = (gte_sqr0_t)0x004e0ea0;
	void gte_sqr0();

	//additional macros, that are inlined on PC ports
	void gte_ldv0(Vector3s* v);
	void gte_ldv1(Vector3s* v);
	void gte_ldv2(Vector3s* v);
	void gte_ldsv(Vector3s* v);
}