#include "stdafx.h"

typedef void	(*Pad_InitAtStart_t)();
typedef void	(*Pad_ClearAllOne_t)(int param_1);
typedef void	(*Pad_ClearAll_t)();
typedef void	(*Pad_Clear_t)(int param_1);
typedef void	(*Pad_ClearTriggers_t)(int param_1);
//unknown name of pad func, dummied out		00486f80
typedef void	(*Pad_ActuatorOn_t)(int param_1, int param_2, int param_3, int param_4);
typedef void	(*Pad_ActuatorOff_t)(int padIndex, int motorIndex);
typedef void	(*Pad_Button_t)(char* param_1, int param_2);
typedef int		(*Pad_Analog_t)(int param_1, int param_2, int param_3, int param_4);
typedef void	(*Pad_Update_t)();
typedef void	(*ReadControllers_t)();
typedef void	(*Pad_Restore_t)();
typedef void	(*Pad_Remap_t)();
//possibly one more unrecognized func in the end

static const Pad_InitAtStart_t		Pad_InitAtStart = (Pad_InitAtStart_t)0x486d90;
static const Pad_ClearAllOne_t		Pad_ClearAllOne = (Pad_ClearAllOne_t)0x00486eb0;
static const Pad_ClearAll_t			Pad_ClearAll = (Pad_ClearAll_t)0x00486f00;
static const Pad_Clear_t			Pad_Clear = (Pad_Clear_t)0x00486f20;
static const Pad_ClearTriggers_t	Pad_ClearTriggers = (Pad_ClearTriggers_t)0x00486f60;
//unknown name of pad func, dummied out		00486f80
static const Pad_ActuatorOn_t		Pad_ActuatorOn = (Pad_ActuatorOn_t)0x00486f90;
static const Pad_ActuatorOff_t		Pad_ActuatorOff = (Pad_ActuatorOff_t)0x00487140;
static const Pad_Button_t			Pad_Button = (Pad_Button_t)0x00487220;
static const Pad_Analog_t			Pad_Analog = (Pad_Analog_t)0x00487280;
static const Pad_Update_t			Pad_Update = (Pad_Update_t)0x00487300;
static const ReadControllers_t		ReadControllers = (ReadControllers_t)0x004875b0; //just calls ReadDirectInput
static const Pad_Restore_t			Pad_Restore = (Pad_Restore_t)0x004875c0;
static const Pad_Remap_t			Pad_Remap = (Pad_Remap_t)0x00487760;
//possibly one more unrecognized func in the end