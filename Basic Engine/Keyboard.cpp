#include "Keyboard.h"
#include <Windows.h>
#include <WinUser.h>

bool Keyboard::KeyIsPressed( char key ) const
{
	return( GetAsyncKeyState( key ) != 0 );
}
