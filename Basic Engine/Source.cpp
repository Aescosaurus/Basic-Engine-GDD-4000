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
	bool exit = false;

	auto present = [&]()
	{
		while( !exit ) gfx.Present();
	};

	std::thread gfxThread{ present };

	FrameTimer ft;
	// constexpr float framerate = 60.0f;
	constexpr float framerate = 24.0f;
	constexpr float frameDiv = 1.0f / framerate;
	float frameCounter = 0.0f;
	while( !exit )
	{
		frameCounter += ft.Mark();
		if( frameCounter >= frameDiv )
		{
			gfx.BeginFrame();

			theGame.Update();
			theGame.Draw();
			
			frameCounter -= frameDiv;
		}
	}

	gfxThread.join();

	std::cin.get();

	return( 0 );
}