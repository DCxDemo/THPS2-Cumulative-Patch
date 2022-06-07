#pragma once

/*
	Crowd.h
	======
	- Crowd reaction logic in competition levels
*/

typedef void(*Crowd_Reset_t)(); //never called?
typedef void(*Crowd_Init_t)(); //empty
typedef void(*Crowd_Start_t)();
typedef void(*Crowd_Stop_t)();
typedef bool(*Crowd_MoveTowards_t)(int* value, int target, int step);
typedef void(*Crowd_Update_t)();
typedef void(*Crowd_Cheer_t)(int score);
typedef void(*Crowd_Oww_t)(int speed);
typedef void(*Crowd_Ahh_t)(int score);
typedef void(*Crowd_Boo_t)(int amount);

static const Crowd_Reset_t Crowd_Reset = (Crowd_Reset_t)0x42f2b0;
static const Crowd_Init_t Crowd_Init = (Crowd_Init_t)0x42f2c0;
static const Crowd_Start_t Crowd_Start = (Crowd_Start_t)0x42f2d0;
static const Crowd_Stop_t Crowd_Stop = (Crowd_Stop_t)0x42f340;
//unknown, never called, maybe Crowd_Excitement? 42f390
static const Crowd_MoveTowards_t Crowd_MoveTowards = (Crowd_MoveTowards_t)0x42f3b0;
static const Crowd_Update_t Crowd_Update = (Crowd_Update_t)0x42f400;
static const Crowd_Cheer_t Crowd_Cheer = (Crowd_Cheer_t)0x42f510;
static const Crowd_Oww_t Crowd_Oww = (Crowd_Oww_t)0x42f650;
static const Crowd_Ahh_t Crowd_Ahh = (Crowd_Ahh_t)0x42f6d0;
static const Crowd_Boo_t Crowd_Boo = (Crowd_Boo_t)0x42f7d0;
