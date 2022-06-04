#include "stdafx.h"
#include "CXBOXController.h"

CXBOXController::CXBOXController(int playerNumber)
{
    // Set the Controller Number
    _controllerNum = playerNumber - 1;
}

bool CXBOXController::UpdateState()
{
	memcpy(&_controllerStateOld, &_controllerState, sizeof(_controllerState));
	//save old controllerstate

    // Zeroise the state
    ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

    // Get the state
    DWORD Result = XInputGetState(_controllerNum, &_controllerState);

    if(Result == ERROR_SUCCESS) return true;
    return false;
}

XINPUT_STATE CXBOXController::GetState()
{
    return _controllerState;
}


XINPUT_STATE CXBOXController::GetOldState()
{
    return _controllerStateOld;
}

bool CXBOXController::IsConnected()
{
    // Zeroise the state
    ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

    // Get the state
    DWORD Result = XInputGetState(_controllerNum, &_controllerState);

    if(Result == ERROR_SUCCESS) return true;
    return false;
}

void CXBOXController::Vibrate(int leftVal, int rightVal, bool enabled)
{
    if (!enabled) return;

    // Create a Vibraton State
    XINPUT_VIBRATION Vibration;

    // Zeroise the Vibration
    ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

    // Set the Vibration Values
    Vibration.wLeftMotorSpeed = leftVal;
    Vibration.wRightMotorSpeed = rightVal;

    // Vibrate the controller
    XInputSetState(_controllerNum, &Vibration);
}

bool CXBOXController::Pressed(int x) { return _controllerState.Gamepad.wButtons & x; }

bool CXBOXController::PressedA() { return Pressed(XINPUT_GAMEPAD_A); }
bool CXBOXController::PressedB() { return Pressed(XINPUT_GAMEPAD_B); }
bool CXBOXController::PressedX() { return Pressed(XINPUT_GAMEPAD_X); }
bool CXBOXController::PressedY() { return Pressed(XINPUT_GAMEPAD_Y); }
bool CXBOXController::PressedPOVUp() { return Pressed(XINPUT_GAMEPAD_DPAD_UP); }
bool CXBOXController::PressedPOVDown() { return Pressed(XINPUT_GAMEPAD_DPAD_DOWN); }
bool CXBOXController::PressedPOVLeft() { return Pressed(XINPUT_GAMEPAD_DPAD_LEFT); }
bool CXBOXController::PressedPOVRight() { return Pressed(XINPUT_GAMEPAD_DPAD_RIGHT); }
bool CXBOXController::PressedBack() { return Pressed(XINPUT_GAMEPAD_BACK); }
bool CXBOXController::PressedStart() { return Pressed(XINPUT_GAMEPAD_START); }