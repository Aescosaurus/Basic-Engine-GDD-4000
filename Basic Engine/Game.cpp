#include "Game.h"

Game::Game( Keyboard& kbd,Graphics& gfx )
	:
	kbd( kbd ),
	gfx( gfx ),
	player( world )
{}

void Game::Update()
{
	const auto dt = ft.Mark();

	player.Update( kbd,dt );
}

void Game::Draw()
{
	world.Draw( gfx );

	player.Draw( gfx );
}
