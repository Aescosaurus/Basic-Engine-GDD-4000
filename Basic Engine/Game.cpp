#include "Game.h"

Game::Game( Keyboard& kbd,Graphics& gfx )
	:
	kbd( kbd ),
	gfx( gfx ),
	playerPos( float( Graphics::ScreenWidth / 2 ),float( Graphics::ScreenHeight - 2 ) )
{
}

void Game::Update()
{
	const auto dt = ft.Mark();

	if( kbd.CheckKey() == 'a' ) playerPos.x -= playerSpeed * dt;
	if( kbd.CheckKey() == 'd' ) playerPos.x += playerSpeed * dt;

	if( kbd.CheckKey() == ' ' && bullets.size() < 2 )
	{
		bullets.emplace_back( playerPos + Vec2::Up() );
	}

	for( int i = 0; i < int( bullets.size() ); ++i )
	{
		auto& b = bullets[i];
		b.y -= bulletSpeed * dt;

		if( world.GetTile( int( b.x ),int( b.y ) ) == '#' )
		{
			bullets.erase( bullets.begin() + i );
		}
	}
}

void Game::Draw()
{
	world.Draw( gfx );

	gfx.PutPixel( int( playerPos.x ),int( playerPos.y ),'^' );
	
	for( const auto& b : bullets )
	{
		gfx.PutPixel( int( b.x ),int( b.y ),'*' );
	}
}
