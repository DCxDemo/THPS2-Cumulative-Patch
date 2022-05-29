#pragma once

// No MFC
#define WIN32_LEAN_AND_MEAN

// We need the Windows Header and the XInput Header
#include <windows.h>
#include <XInput.h>

// Now, the XInput Library
// NOTE: COMMENT THIS OUT IF YOU ARE NOT USING
// A COMPILER THAT SUPPORTS THIS METHOD OF LINKING LIBRARIES
#pragma comment(lib, "XInput.lib")

// XBOX Controller Class Definition
class CXBOXController
{
private:
    XINPUT_STATE _controllerState;
	XINPUT_STATE _controllerStateOld;
    int _controllerNum;
	bool Pressed(int x);
public:
    CXBOXController(int playerNumber);
    bool UpdateState();
    XINPUT_STATE GetState();
	XINPUT_STATE GetOldState();
    bool IsConnected();
    void Vibrate(int leftVal = 0, int rightVal = 0,  bool enable = true);

	bool PressedA();
	bool PressedB();
	bool PressedX();
	bool PressedY();
	bool PressedPOVUp();
	bool PressedPOVDown();
	bool PressedPOVLeft();
	bool PressedPOVRight();
	bool PressedBack();
	bool PressedStart();
};