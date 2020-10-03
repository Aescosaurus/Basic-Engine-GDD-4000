#include "GameWorld.h"

GameWorld::GameWorld()
{
	tiles.resize( width * height );

	for( int y = 0; y < height; ++y )
	{
		for( int x = 0; x < width; ++x )
		{
			tiles[y * Graphics::ScreenWidth + x] =
				( x == 0 || x == width - 1 ||
				y == 0 || y == height - 1 )
				? TileType::Wall : TileType::Air;
		}
	}
}

void GameWorld::Draw( Graphics& gfx ) const
{
	for( int y = 0; y < height; ++y )
	{
		for( int x = 0; x < width; ++x )
		{
			const auto tile = tiles[y * width + x];
			gfx.PutPixel( x,y,tile == TileType::Air ? ' ' : '#' );
		}
	}
}

void GameWorld::Start()
{
	std::cout << "Starting up!\n";
}

void GameWorld::Update()
{
	std::cout << "Updating!!\n";
}

void GameWorld::Shutdown()
{
	std::cout << "Shutting down...\n";
}
