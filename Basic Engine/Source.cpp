#include <iostream>
#include "MemoryManager.h"
#include "AnimationManager.h"
#include "FileSystemManager.h"
#include "PhysicsManager.h"
#include "RenderManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include <vector>

int main()
{
	std::vector<MonoBehavior*> managers;
	managers.emplace_back( MemoryManager::Ptr() );
	managers.emplace_back( FileSystemManager::Ptr() );
	managers.emplace_back( TextureManager::Ptr() );
	managers.emplace_back( RenderManager::Ptr() );
	managers.emplace_back( AnimationManager::Ptr() );
	managers.emplace_back( PhysicsManager::Ptr() );
	managers.emplace_back( SoundManager::Ptr() );

	for( auto& man : managers ) man->Start();
	std::cout << '\n';
	for( auto& man : managers ) man->Update();
	std::cout << '\n';
	for( auto it = managers.rbegin(); it != managers.rend(); ++it )
	{
		( *it )->Shutdown();
	}

	std::cin.get();

	return( 0 );
}