#pragma once

#include <thread>
#include <queue>
#include <conio.h>

class Keyboard
{
public:
	Keyboard()
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
	~Keyboard()
	{
		stop = true;
		inputThread.join();
	}

	char ReadBuffer() const
	{
		if( keyBuffer.size() < 1 ) return( '\0' );

		const auto key = keyBuffer.front();
		keyBuffer.pop();
		return( key );
	}

	char CheckKey() const
	{
		return( key );
	}
private:
	bool stop = false;
	std::thread inputThread;
	char key = '\0';
	mutable std::queue<char> keyBuffer;
	int c = 0;
};