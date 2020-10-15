#include <iostream>
#include "FrameTimer.h"
#include <thread>
#include "Keyboard.h"
#include "Graphics.h"
#include "Game.h"

int main()
{
	Keyboard kbd;
	Graphics gfx;
	Game theGame{ kbd,gfx };

	// constexpr float framerate = 60.0f;
	constexpr float framerate = 12.0f;
	constexpr float frameDiv = 1.0f / framerate;

	FrameTimer ft;
	float prev = ft.Mark();
	float lag = 0.0f;
	while( true )
	{
		const float current = ft.Mark();

		// while( lag >= frameDiv )
		// {
		// 	theGame.Update();
		// 	lag -= frameDiv;
		// }
		theGame.Update();

		gfx.BeginFrame();
		theGame.Draw();

		gfx.Present();

		const float elapsed = current - prev;
		prev = current;
		lag += elapsed;

		// frameDiv - lag
		std::this_thread::sleep_for( std::chrono::milliseconds( int( ( frameDiv - lag ) * 1000.0f ) ) );
	}

	std::cin.get();

	return( 0 );
}