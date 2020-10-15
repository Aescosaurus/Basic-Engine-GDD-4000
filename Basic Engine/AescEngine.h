#pragma once

#include "Keyboard.h"
#include "Graphics.h"
#include "FrameTimer.h"
#include <thread>
#include "GameObject.h"
#include <vector>
#include <memory>

class AescEngine
{
public:
	AescEngine();
	~AescEngine();

	// T must inherit from GameObject.
	template<typename T>
	static GameObject& CreateObj( bool callInit = true )
	{
		objs.emplace_back( std::make_unique<T>() );
		if( callInit ) objs.back()->Init();
		return( *( objs.back().get() ) );
	}
	// TODO: Object destroy.
	void Quit();

	bool Running() const;
private:
	void GameUpdate();
	void GfxDraw();
	template<typename T>
	void ThreadFunc( T func )
	{
		FrameTimer ft;
		constexpr float frameDiv = 1.0f / framerate;

		float prev = ft.Mark();
		float lag = 0.0f;
		while( running )
		{
			const float current = ft.Mark();

			// while( lag >= frameDiv )
			// {
			// 	theGame.Update();
			// 	lag -= frameDiv;
			// }

			// theGame.Update();
			// 
			// gfx.BeginFrame();
			// theGame.Draw();
			// 
			// gfx.Present();
			func();

			const float elapsed = current - prev;
			prev = current;
			lag += elapsed;

			// frameDiv - lag
			std::this_thread::sleep_for( std::chrono::milliseconds( int( ( frameDiv - lag ) * 1000.0f ) ) );
		}
	}
private:
	Keyboard kbd;
	Graphics gfx;
	
	std::thread gameThread;
	std::thread gfxThread;

	static std::vector<std::unique_ptr<GameObject>> objs;

	bool running = true;

	// static constexpr float framerate = 60.0f;
	static constexpr float framerate = 12.0f;
};