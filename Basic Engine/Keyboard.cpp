#include "Keyboard.h"
#include <conio.h>

Keyboard::Keyboard()
{
	auto check_input = [&]()
	{
		while( !stop )
		{
			key = _getch();
		}
	};

	inputThread = std::thread{ check_input };
}

Keyboard::~Keyboard()
{
	stop = true;
	inputThread.join();
}

char Keyboard::CheckKey() const
{
	return( key );
}
