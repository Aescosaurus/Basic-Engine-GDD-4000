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
#include "Vec3Managed.h"

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

	FrameTimer ft;

	std::cout << "start default\n";
	const auto start = ft.Mark();
	for( int i = 0; i < 5000; ++i )
	{
		for( int j = 0; j < 1000; ++j )
		{
			auto* temp = new Vec3( 0.0f,0.0f,0.0f );
			delete temp;
		}
	}
	const auto endTime = ft.Mark() - start;
	std::cout << "end default -- took " << endTime << "s\n";

	std::cout << "start spiffy\n";
	const auto start2 = ft.Mark();
	for( int i = 0; i < 5000; ++i )
	{
		for( int j = 0; j < 1000; ++j )
		{
			auto* temp = new Vec3Managed_<float>( 0.0f,0.0f,0.0f );
			delete temp;
		}
	}
	const auto end2 = ft.Mark() - start;
	std::cout << "end spiffy -- took " << end2 << "s\n";

	std::cin.get();

	return( 0 );
}