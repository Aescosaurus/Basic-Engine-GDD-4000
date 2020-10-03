#include <iostream>
#include "MemoryManager.h"
#include "AnimationManager.h"
#include "FileSystemManager.h"
#include "PhysicsManager.h"
#include "RenderManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include <vector>
#include "FrameTimer.h"
#include "Vec3.h"
#include <string>
#include <thread>
#include "MemoryManagerTS.h"
#include <exception>
#include "Keyboard.h"
#include "Graphics.h"

template<typename T>
void Test( const std::string& name,FrameTimer& ft )
{
	constexpr auto trials = 5000;
	constexpr auto iterations = 1000;

	std::cout << "start " << name << '\n';
	const auto start = ft.Mark();
	for( int i = 0; i < trials; ++i )
	{
		for( int j = 0; j < iterations; ++j )
		{
			T* temp = new T();
			delete temp;
		}
	}
	const auto duration = ft.Mark() - start;
	std::cout << "end " << name << " - time taken = " << duration << "s\n";
}

template<typename T>
void TestThread( const std::string& name,FrameTimer& ft )
{
	constexpr auto trials = 5000;
	constexpr auto iterations = 1000;

	const auto new_del_test = [&]()
	{
		for( int j = 0; j < iterations; ++j )
		{
			T* temp = new T();
			delete temp;
		}
	};

	std::vector<std::thread> threads;
	threads.reserve( trials );

	std::cout << "start " << name << '\n';
	const auto start = ft.Mark();

	for( int i = 0; i < trials; ++i )
	{
		threads.emplace_back( std::thread{ new_del_test } );
	}

	for( auto& t : threads )
	{
		t.join();
	}

	const auto duration = ft.Mark() - start;
	std::cout << "end " << name << " - time taken = " << duration << "s\n";
}

void RunTests()
{
	FrameTimer ft;

	std::cout << "50M alloc/dealloc per trial (5K trials 1K allocs each)\n";

	Test<Vec3>( "vec3 reg",ft );
	Test<Managed<Vec3>>( "vec3 managed",ft );

	Test<double>( "double reg",ft );
	Test<ManagedFun<double>>( "double managed",ft );

	Test<std::string>( "string reg",ft );
	Test<ManagedFun<std::string>>( "string managed",ft );

	TestThread<Vec3>( "vec3 thread",ft );
	// TestThread<Managed<Vec3>>( "vec3 managed thread unsafe",ft );
	TestThread<ManagedTS<Vec3>>( "vec3 managed thread safe",ft );
}

int main()
{
	// std::vector<MonoBehavior*> managers;
	// managers.emplace_back( FileSystemManager::Ptr() );
	// managers.emplace_back( TextureManager::Ptr() );
	// managers.emplace_back( RenderManager::Ptr() );
	// managers.emplace_back( AnimationManager::Ptr() );
	// managers.emplace_back( PhysicsManager::Ptr() );
	// managers.emplace_back( SoundManager::Ptr() );

	// for( auto& man : managers ) man->Start();
	// std::cout << '\n';
	// for( auto& man : managers ) man->Update();
	// std::cout << '\n';
	// for( auto it = managers.rbegin(); it != managers.rend(); ++it )
	// {
	// 	( *it )->Shutdown();
	// }

	// RunTests();

	Keyboard kbd;
	Graphics gfx;

	FrameTimer ft;
	// constexpr float framerate = 60.0f;
	constexpr float framerate = 4.0f;
	constexpr float frameDelta = 1.0f / framerate;
	float frameCounter = 0.0f;
	while( true )
	{
		frameCounter += ft.Mark();
		if( frameCounter >= frameDelta )
		{
			gfx.BeginFrame();

			auto gfxThread = std::thread{ &Graphics::Present,&gfx };

			// game.update
			if( kbd.KeyIsPressed( 'A' ) ) gfx.PutPixel( 5,5,'A' );

			gfxThread.join();
			// gfx.Present();
			
			frameCounter -= frameDelta;
		}
	}

	std::cin.get();

	return( 0 );
}