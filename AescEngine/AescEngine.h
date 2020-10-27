// MathLibrary.h - Contains declarations of math functions
#pragma once

#ifdef AESCENGINE_EXPORTS
#define AESCENGINE_API __declspec(dllexport)
#else
#define AESCENGINE_API __declspec(dllimport)
#endif

#include "Keyboard.h"
#include "Graphics.h"
#include "FrameTimer.h"
#include <thread>
#include "GameObject.h"
#include <vector>
#include <memory>

static std::vector<std::unique_ptr<GameObject>> objs;

class AescEngine
{
public:
	AescEngine()
	{
		// Call Functions once.
		auto gameCallFunc = [&]() { GameUpdate(); };
		auto gfxCallFunc = [&]() { GfxDraw(); };

		// Wrap function call lamb in game loop thread func lamb.
		auto gameThreadFunc = [&]() { ThreadFunc( gameCallFunc ); };
		auto gfxThreadFunc = [&]() { ThreadFunc( gfxCallFunc ); };

		// Use lamb for thread.
		gameThread = std::thread( gameThreadFunc );
		gfxThread = std::thread( gfxThreadFunc );
	}
	~AescEngine()
	{
		running = false;

		gameThread.join();
		gfxThread.join();
	}

	// T must inherit from GameObject.
	template<typename T>
	static GameObject& CreateObj( bool callInit = true )
	{
		objs.emplace_back( std::make_unique<T>() );
		if( callInit ) objs.back()->Init();
		return( *( objs.back().get() ) );
	}
	// TODO: Object destroy.
	void Quit()
	{
		running = false;
	}

	bool Running() const
	{
		return( running );
	}
private:
	void GameUpdate()
	{
		static FrameTimer ft;

		const auto dt = ft.Mark();
		for( auto& obj : objs )
		{
			obj->Update( kbd,dt );
		}
	}
	void GfxDraw()
	{
		gfx.ClearScreen();

		for( const auto& obj : objs )
		{
			obj->Draw( gfx );
		}

		gfx.Present();
		gfx.ClearPixels();
		gfx.FlipBuffer();
	}
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


	bool running = true;

	// static constexpr float framerate = 60.0f;
	static constexpr float framerate = 12.0f;
};

// extern "C" AESCENGINE_API GameObject& CreateObj( bool callInit = true );

// extern "C" AESCENGINE_API void fibonacci_init(
// 	const unsigned long long a,const unsigned long long b );