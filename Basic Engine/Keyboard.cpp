#include "Keyboard.h"
#include <conio.h>

Keyboard::Keyboard()
{
	auto check_input = [&]()
	{
		while( !stop )
		{
			key = _getch();
			keyBuffer.push( key );
		}
	};

	inputThread = std::thread{ check_input };
}

Keyboard::~Keyboard()
{
	stop = true;
	inputThread.join();
}

char Keyboard::ReadBuffer() const
{
	if( keyBuffer.size() < 1 ) return( '\0' );

	const auto key = keyBuffer.front();
	keyBuffer.pop();
	return( key );
}

char Keyboard::CheckKey() const
{
	return( key );
}