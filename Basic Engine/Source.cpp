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
#include <string>

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

	Test<Vec3>( "default",ft );

	Test<Vec3Managed_<float>>( "managed",ft );

	std::cin.get();

	return( 0 );
}