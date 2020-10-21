#include "Controller.h"
#include <Windows.h>
#include <Xinput.h>

#pragma comment( lib,"XInput.lib" )

Controller::Controller()
{
	DWORD dwResult;
	for( DWORD i = 0; i < XUSER_MAX_COUNT; ++i )
	{
		XINPUT_STATE state;
		ZeroMemory( &state,sizeof( XINPUT_STATE ) );

		dwResult = XInputGetState( i,&state );

		if( dwResult == ERROR_SUCCESS )
		{
			// controller connected

			gamepads.emplace_back();
			gamepads.back().state = ( int* )( &state );
			gamepads.back().dwIndex = i;
			connected = true;
		}
		else
		{

		}
	}
}

void Controller::Update()
{
	if( connected )
	{
		Vec2 leftStickMove = {
			float( ( ( XINPUT_STATE* )( gamepads[0].state ) )->Gamepad.sThumbLX ),
			float( ( ( XINPUT_STATE* )( gamepads[0].state ) )->Gamepad.sThumbLY )
		};

		if( leftStickMove.GetLengthSq() <
			pow( XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE,2 ) )
		{
			leftStick = leftStickMove.GetNormalized();
		}

		aButton = ( ( XINPUT_STATE* )( gamepads[0].state ) )->Gamepad.wButtons & aButtonMask;

		// todo: connected = false if controller dc'd
	}
}

void Controller::Rumble( float val )
{
	if( connected )
	{
		XINPUT_VIBRATION vibe;
		ZeroMemory( &vibe,sizeof( XINPUT_VIBRATION ) );
		vibe.wLeftMotorSpeed = int( val * 65535.0f );
		vibe.wRightMotorSpeed = int( val * 65535.0f );
		XInputSetState( DWORD( gamepads[0].dwIndex ),&vibe );
	}
}

const Vec2& Controller::GetLeftStickInput() const
{
	return( leftStick );
}

bool Controller::CheckAButtonInput() const
{
	return( aButton );
}
