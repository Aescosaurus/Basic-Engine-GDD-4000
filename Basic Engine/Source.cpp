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
	constexpr float framerate = 4.0f;
	constexpr float frameDiv = 1.0f / framerate;

	FrameTimer ft;
	float prev = ft.Mark();
	float lag = 0.0f;
	while( true )
	{
		const float current = ft.Mark();
		const float elapsed = current - prev;
		prev = current;
		lag += elapsed;

		// while( lag >= frameDiv )
		// {
		// 	theGame.Update();
		// 	lag -= frameDiv;
		// }
		theGame.Update();

		gfx.BeginFrame();
		theGame.Draw();

		gfx.Present();
	}

	std::cin.get();

	return( 0 );
}