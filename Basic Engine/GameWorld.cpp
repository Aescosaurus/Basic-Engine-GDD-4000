#include "GameWorld.h"

GameWorld::GameWorld()
{
	Start();
}

void GameWorld::Start()
{
	for( int y = 0; y < height; ++y )
	{
		for( int x = 0; x < width; ++x )
		{
			world[y][x] = empty;

			if( x == 0 || x == width - 1 ||
				y == 0 || y == height - 1 )
			{
				world[y][x] = wall;
			}
		}
	}
}

void GameWorld::Update()
{
	// wtf am i supposed to even do in here
}

void GameWorld::Shutdown()
{
}

void GameWorld::Draw( Graphics& gfx ) const
{
	for( int y = 0; y < height; ++y )
	{
		for( int x = 0; x < width; ++x )
		{
			gfx.PutPixel( x,y,world[y][x] );
		}
	}
}

void GameWorld::SetTile( int x,int y,char c )
{
	world[y][x] = c;
}

char GameWorld::GetTile( int x,int y ) const
{
	return( world[y][x] );
}
