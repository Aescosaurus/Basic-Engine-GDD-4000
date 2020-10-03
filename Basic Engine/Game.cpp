#include "Game.h"
#include "AescUtils.h"

Game::Game( Keyboard& kbd,Graphics& gfx )
	:
	kbd( kbd ),
	gfx( gfx ),
	player( world,bullets )
{}

void Game::Update()
{
	const auto dt = ft.Mark();

	player.Update( kbd,dt );

	for( auto& b : bullets ) b.Update( world,dt );

	aesc::remove_erase_if( bullets,std::mem_fn( &Bullet::Ouch ) );
}

void Game::Draw()
{
	world.Draw( gfx );

	player.Draw( gfx );

	for( const auto& b : bullets ) b.Draw( gfx );
}
