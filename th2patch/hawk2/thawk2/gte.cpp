#include "stdafx.h"
#include "gte.h"

// === input registers ===

short* reg_dp = (short*)0x006a0a84;

//matrices -> short[3,3]
short* reg_rt = (short*)0x006a0a60; //rotation matrix
short* reg_ll = (short*)0x006a0ad0; //light source direction
short* reg_lc = (short*)0x006a0b18; //light source color

Vector3s* reg_v0 = (Vector3s*)0x006a0aa8;
Vector3s* reg_v1 = (Vector3s*)0x006a0ab0;
Vector3s* reg_v2 = (Vector3s*)0x006a0ab8;

Vector3i* reg_tr = (Vector3i*)0x006a0af0;
Vector3i* reg_bk = (Vector3i*)0x006a0a98;

// === output registers ===

Vector3s* reg_sv = (Vector3s*)0x006a0b00;
Vector3i* reg_lv = (Vector3i*)0x006a0b08;


//better precision buffer
Vector3f reg_fv_data;
Vector3f* reg_fv = &reg_fv_data;

// copies float vector to long vector using round
void mygte_fvtolv()
{
    reg_lv->X = round(reg_fv->X);
    reg_lv->Y = round(reg_fv->Y);
    reg_lv->Z = round(reg_fv->Z);
}


//macros to load data in registers

void gte_ldv0(Vector3s* v)
{
    reg_v0->X = v->X;
    reg_v0->Y = v->Y;
    reg_v0->Z = v->Z;
}

void gte_ldv1(Vector3s* v)
{
    reg_v1->X = v->X;
    reg_v1->Y = v->Y;
    reg_v1->Z = v->Z;
}

void gte_ldv2(Vector3s* v)
{
    reg_v2->X = v->X;
    reg_v2->Y = v->Y;
    reg_v2->Z = v->Z;
}

void gte_ldsv(Vector3s* v)
{
    reg_sv->X = v->X;
    reg_sv->Y = v->Y;
    reg_sv->Z = v->Z;
}

void gte_ldtr(Vector3i* v)
{
    reg_tr->X = v->X;
    reg_tr->Y = v->Y;
    reg_tr->Z = v->Z;
}

//gte functions

// rotation matrix * vertex0
void gte_rtv0()
{
    int x = reg_v0->X;
    int y = reg_v0->Y;
    int z = reg_v0->Z;

    reg_fv->X = (reg_rt[0, 0] * x + reg_rt[0, 1] * y + reg_rt[0, 2] * z) / 4096.0f;
    reg_fv->Y = (reg_rt[1, 0] * x + reg_rt[1, 1] * y + reg_rt[1, 2] * z) / 4096.0f;
    reg_fv->Z = (reg_rt[2, 0] * x + reg_rt[2, 1] * y + reg_rt[2, 2] * z) / 4096.0f;

    mygte_fvtolv();
    mygte_lvtosv();
}

void gte_rtv1()
{
    int x = reg_v1->X;
    int y = reg_v1->Y;
    int z = reg_v1->Z;

    reg_fv->X = (reg_rt[0, 0] * x + reg_rt[0, 1] * y + reg_rt[0, 2] * z) / 4096.0f;
    reg_fv->Y = (reg_rt[1, 0] * x + reg_rt[1, 1] * y + reg_rt[1, 2] * z) / 4096.0f;
    reg_fv->Z = (reg_rt[2, 0] * x + reg_rt[2, 1] * y + reg_rt[2, 2] * z) / 4096.0f;

    mygte_fvtolv();
    mygte_lvtosv();
}

void gte_rtv2()
{
    int x = reg_v2->X;
    int y = reg_v2->Y;
    int z = reg_v2->Z;

    reg_fv->X = (reg_rt[0, 0] * x + reg_rt[0, 1] * y + reg_rt[0, 2] * z) / 4096.0f;
    reg_fv->Y = (reg_rt[1, 0] * x + reg_rt[1, 1] * y + reg_rt[1, 2] * z) / 4096.0f;
    reg_fv->Z = (reg_rt[2, 0] * x + reg_rt[2, 1] * y + reg_rt[2, 2] * z) / 4096.0f;

    mygte_fvtolv();
    mygte_lvtosv();
}

// short vector squared
void gte_sqr0()
{
    reg_fv->X = reg_sv->X * reg_sv->X;
    reg_fv->Y = reg_sv->Y * reg_sv->Y;
    reg_fv->Z = reg_sv->Z * reg_sv->Z;

    mygte_fvtolv();
    mygte_lvtosvU();
}

//MUL: local light matrix * vertex 0
void gte_llv0()
{
    int x = reg_v0->X;
    int y = reg_v0->Y;
    int z = reg_v0->Z;

    reg_fv->X = (reg_ll[0, 0] * x + reg_ll[0, 1] * y + reg_ll[0, 2] * z) / 4096.0f;
    reg_fv->Y = (reg_ll[1, 0] * x + reg_ll[1, 1] * y + reg_ll[1, 2] * z) / 4096.0f;
    reg_fv->Z = (reg_ll[2, 0] * x + reg_ll[2, 1] * y + reg_ll[2, 2] * z) / 4096.0f;

    mygte_fvtolv();
    mygte_lvtosv();
}

// light color matric * vertex 0
void gte_lcv0()
{
    int x = reg_v0->X;
    int y = reg_v0->Y;
    int z = reg_v0->Z;

    reg_fv->X = (reg_lc[0, 0] * x + reg_lc[0, 1] * y + reg_lc[0, 2] * z) / 4096.0f;
    reg_fv->Y = (reg_lc[1, 0] * x + reg_lc[1, 1] * y + reg_lc[1, 2] * z) / 4096.0f;
    reg_fv->Z = (reg_lc[2, 0] * x + reg_lc[2, 1] * y + reg_lc[2, 2] * z) / 4096.0f;

    mygte_fvtolv();
    mygte_lvtosv();
}

//outer product
void gte_op0()
{
    int x = reg_sv->X;
    int y = reg_sv->Y;
    int z = reg_sv->Z;

    reg_fv->X = z * reg_rt[1, 1] - y * reg_rt[2, 2];
    reg_fv->Y = x * reg_rt[2, 2] - z * reg_rt[0, 0];
    reg_fv->Z = y * reg_rt[0, 0] - x * reg_rt[1, 1];

    mygte_fvtolv();
    mygte_lvtosv();
}

//outer product shifted
void gte_op12()
{
    int x = reg_sv->X;
    int y = reg_sv->Y;
    int z = reg_sv->Z;

    reg_fv->X = (z * reg_rt[1, 1] - y * reg_rt[2, 2]) / 4096.0f;
    reg_fv->Y = (x * reg_rt[2, 2] - z * reg_rt[0, 0]) / 4096.0f;
    reg_fv->Z = (y * reg_rt[0, 0] - x * reg_rt[1, 1]) / 4096.0f;

    mygte_fvtolv();
    mygte_lvtosv();
}


void gte_lcir()
{
    int x = reg_sv->X;
    int y = reg_sv->Y;
    int z = reg_sv->Z;

    reg_fv->X = (reg_lc[0,0] * x + reg_lc[0,1] * y + reg_lc[0,2] * z) / 4096.0;
    reg_fv->Y = (reg_lc[1,0] * x + reg_lc[1,1] * y + reg_lc[1,2] * z) / 4096.0;
    reg_fv->Z = (reg_lc[2,0] * x + reg_lc[2,1] * y + reg_lc[2,2] * z) / 4096.0;

    mygte_fvtolv();
    mygte_lvtosv();
}

//light matrix * small vector
void gte_llir_sf0()
{
    int x = reg_sv->X;
    int y = reg_sv->Y;
    int z = reg_sv->Z;

    reg_fv->X = reg_ll[0, 0] * x + reg_ll[0, 1] * y + reg_ll[0, 2] * z;
    reg_fv->Y = reg_ll[1, 0] * x + reg_ll[1, 1] * y + reg_ll[1, 2] * z;
    reg_fv->Z = reg_ll[2, 0] * x + reg_ll[2, 1] * y + reg_ll[2, 2] * z;

    mygte_fvtolv();
    mygte_lvtosv();
}

//rotation matrix * small vector >> 12 + translation vector
//not really used? not on mac os at least. pc uses in some weird unused function
void gte_rtirtr()
{
    int x = reg_sv->X;
    int y = reg_sv->Y;
    int z = reg_sv->Z;

    reg_fv->X = (reg_rt[0,0] * x + reg_rt[0,1] * y + reg_rt[0,2] * z) / 4096.0 + reg_tr->X;
    reg_fv->Y = (reg_rt[1,0] * x + reg_rt[1,1] * y + reg_rt[1,2] * z) / 4096.0 + reg_tr->Y;
    reg_fv->Z = (reg_rt[2,0] * x + reg_rt[2,1] * y + reg_rt[2,2] * z) / 4096.0 + reg_tr->Z;

    mygte_fvtolv();
    mygte_lvtosv();
}

//rotation matrix * small vector >> 12
void gte_rtir()
{
    int x = reg_sv->X;
    int y = reg_sv->Y;
    int z = reg_sv->Z;

    reg_fv->X = (reg_rt[0, 0] * x + reg_rt[0, 1] * y + reg_rt[0, 2] * z) / 4096.0;
    reg_fv->Y = (reg_rt[1, 0] * x + reg_rt[1, 1] * y + reg_rt[1, 2] * z) / 4096.0;
    reg_fv->Z = (reg_rt[2, 0] * x + reg_rt[2, 1] * y + reg_rt[2, 2] * z) / 4096.0;

    mygte_fvtolv();
    mygte_lvtosv();
}

//rotation matrix * small vector
void gte_rtir_sf0()
{
    int x = reg_sv->X;
    int y = reg_sv->Y;
    int z = reg_sv->Z;

    reg_fv->X = (reg_rt[0, 0] * x + reg_rt[0, 1] * y + reg_rt[0, 2] * z);
    reg_fv->Y = (reg_rt[1, 0] * x + reg_rt[1, 1] * y + reg_rt[1, 2] * z);
    reg_fv->Z = (reg_rt[2, 0] * x + reg_rt[2, 1] * y + reg_rt[2, 2] * z);

    mygte_fvtolv();
    mygte_lvtosv();
}


void gte_gpf12()
{
    reg_fv->X = reg_sv->X * *reg_dp / 4096.0;
    reg_fv->Y = reg_sv->Y * *reg_dp / 4096.0;
    reg_fv->Z = reg_sv->Z * *reg_dp / 4096.0;

    mygte_fvtolv();
    mygte_lvtosv();
    mygte_svtorgb();
}

void gte_gpl0()
{
    reg_fv->X = reg_lv->X + reg_sv->X * *reg_dp;
    reg_fv->Y = reg_lv->Y + reg_sv->Y * *reg_dp;
    reg_fv->Z = reg_lv->Z + reg_sv->Z * *reg_dp;

    mygte_fvtolv();
    mygte_lvtosv();
    mygte_svtorgb();
}

void gte_gpl12()
{
    reg_fv->X = reg_lv->X + (reg_sv->X * *reg_dp / 4096.0);
    reg_fv->Y = reg_lv->Y + (reg_sv->Y * *reg_dp / 4096.0);
    reg_fv->Z = reg_lv->Z + (reg_sv->Z * *reg_dp / 4096.0);

    mygte_fvtolv();
    mygte_lvtosv();
    mygte_svtorgb();
}

void gte_rtv0tr()
{
    int x = reg_v0->X;
    int y = reg_v0->Y;
    int z = reg_v0->Z;

    reg_fv->X = (reg_rt[0, 0] * x + reg_rt[0, 1] * y + reg_rt[0, 2] * z) / 4096.0f + reg_tr->X;
    reg_fv->Y = (reg_rt[1, 0] * x + reg_rt[1, 1] * y + reg_rt[1, 2] * z) / 4096.0f + reg_tr->Y;
    reg_fv->Z = (reg_rt[2, 0] * x + reg_rt[2, 1] * y + reg_rt[2, 2] * z) / 4096.0f + reg_tr->Z;

    mygte_fvtolv();
    mygte_lvtosv();
}

void gte_rtv0_sf0()
{
    int x = reg_v0->X;
    int y = reg_v0->Y;
    int z = reg_v0->Z;

    reg_fv->X = (reg_rt[0, 0] * x + reg_rt[0, 1] * y + reg_rt[0, 2] * z);
    reg_fv->Y = (reg_rt[1, 0] * x + reg_rt[1, 1] * y + reg_rt[1, 2] * z);
    reg_fv->Z = (reg_rt[2, 0] * x + reg_rt[2, 1] * y + reg_rt[2, 2] * z);

    mygte_fvtolv();
    mygte_lvtosv();
}

void gte_rt()
{
    int x = reg_v0->X;
    int y = reg_v0->Y;
    int z = reg_v0->Z;

    reg_fv->X = (reg_rt[0,0] * x + reg_rt[0,1] * y + reg_rt[0,2] * z) / 4096.0 + reg_tr->X;
    reg_fv->Y = (reg_rt[1,0] * x + reg_rt[1,1] * y + reg_rt[1,2] * z) / 4096.0 + reg_tr->Y;
    reg_fv->Z = (reg_rt[2,0] * x + reg_rt[2,1] * y + reg_rt[2,2] * z) / 4096.0 + reg_tr->Z;
    
    mygte_fvtolv();
    mygte_lvtosv();
}

void gte_lcirtr()
{
    int x = reg_sv->X;
    int y = reg_sv->Y;
    int z = reg_sv->Z;

    reg_lv->X = (reg_lc[0,0] * x + reg_lc[0,1] * y + reg_lc[0,2] * z) / 4096.0 + reg_tr->X;
    reg_lv->Y = (reg_lc[1,0] * x + reg_lc[1,1] * y + reg_lc[1,2] * z) / 4096.0 + reg_tr->Y;
    reg_lv->Z = (reg_lc[2,0] * x + reg_lc[2,1] * y + reg_lc[2,2] * z) / 4096.0 + reg_tr->Z;

    mygte_fvtolv();
    mygte_lvtosv();
}

void gte_llirbk()
{
    int x = reg_sv->X;
    int y = reg_sv->Y;
    int z = reg_sv->Z;

    reg_lv->X = (reg_ll[0,0] * x + reg_ll[0,1] * y + reg_ll[0,2] * z) / 4096.0 + reg_bk->X;
    reg_lv->Y = (reg_ll[1,0] * x + reg_ll[1,1] * y + reg_ll[1,2] * z) / 4096.0 + reg_bk->Y;
    reg_lv->Z = (reg_ll[2,0] * x + reg_ll[2,1] * y + reg_ll[2,2] * z) / 4096.0 + reg_bk->Z;

    mygte_fvtolv();
    mygte_lvtosv();
}