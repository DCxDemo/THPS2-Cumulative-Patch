#include "stdafx.h"

typedef void	(*LoadingScreen_Text_t)(char* bitmap, char* text, char param_3);
typedef void	(*LoadingScreen_GaugeOn_t)(int param_1, int param_2, int param_3, int param_4);
typedef void	(*LoadingScreen_GaugeOff_t)();
typedef void	(*LoadingScreen_UpdateProgress_t)();
typedef void	(*LoadingScreen_UpdateProgressForRailGeneration_t)(char param_1);
typedef void	(*LoadingScreen_RemoveBar_t)();
typedef void	(*LoadingScreen_StartLoading_t)(int param_1);
typedef void	(*LoadingScreen_EndLoading_t)();

static const LoadingScreen_Text_t								LoadingScreen_Text = (LoadingScreen_Text_t)0x45cf80;
static const LoadingScreen_GaugeOn_t							LoadingScreen_GaugeOn = (LoadingScreen_GaugeOn_t)0x45d550;
static const LoadingScreen_GaugeOff_t							LoadingScreen_GaugeOff = (LoadingScreen_GaugeOff_t)0x45d5f0;
static const LoadingScreen_UpdateProgress_t						LoadingScreen_UpdateProgress = (LoadingScreen_UpdateProgress_t)0x45d600;
static const LoadingScreen_UpdateProgressForRailGeneration_t	LoadingScreen_UpdateProgressForRailGeneration = (LoadingScreen_UpdateProgressForRailGeneration_t)0x45d6d0;
static const LoadingScreen_RemoveBar_t							LoadingScreen_RemoveBar = (LoadingScreen_RemoveBar_t)0x45d710;
static const LoadingScreen_StartLoading_t						LoadingScreen_StartLoading = (LoadingScreen_StartLoading_t)0x45d7a0;
static const LoadingScreen_EndLoading_t							LoadingScreen_EndLoading = (LoadingScreen_EndLoading_t)0x45dad0;