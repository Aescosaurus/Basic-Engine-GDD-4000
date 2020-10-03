#include "Game.h"
#include "AescUtils.h"

Game::Game( Keyboard& kbd,Graphics& gfx )
	:
	kbd( kbd ),
	gfx( gfx ),
	player( world,bullets )
{
	for( int i = 0; i < nAliens; ++i )
	{
		aliens.emplace_back( Vec2{
			( float( i + 1 ) / float( nAliens + 2 ) ) * float( Graphics::ScreenWidth ),
			1.0f } );
	}
}

void Game::Update()
{
	auto dt = ft.Mark();
	if( dt > 1.0f ) dt = 1.0f / 60.0f;

	player.Update( kbd,dt );

	for( auto& b : bullets ) b.Update( world,dt );

	// Alien update and interactions.
	for( auto& alien : aliens )
	{
		alien.Update( dt );

		// if( ( player.GetPos() - alien.GetPos() ).GetLengthSq() < Alien::radius * Alien::radius )
		if( aesc::check_coll( player.GetPos(),alien.GetPos(),Alien::radius ) )
		{
			gameOver = true;
			player.ApplyOuch();
			for( auto& a : aliens ) a.Reset();
		}

		for( auto& b : bullets )
		{
			// if( ( b.GetPos() - alien.GetPos() ).GetLengthSq() < Alien::radius * Alien::radius )
			if( aesc::check_coll( b.GetPos(),alien.GetPos(),Alien::radius ) )
			{
				b.ApplyOuch();
				alien.ApplyOuch();
			}
		}
	}

	// Swoop interaction.
	if( aliens.size() > 0 && !gameOver )
	{
		if( aliens.back().GetPos().x >= float( GameWorld::width - 2 ) )
		{
			for( auto& a : aliens ) a.FlipDir();
		}
		if( aliens.front().GetPos().x <= 1 )
		{
			for( auto& a : aliens ) a.DropDown();
		}
	}

	aesc::remove_erase_if( bullets,std::mem_fn( &Bullet::Ouch ) );
	aesc::remove_erase_if( aliens,std::mem_fn( &Alien::Ouch ) );
}

void Game::Draw()
{
	world.Draw( gfx );

	for( const auto& a : aliens ) a.Draw( gfx );

	for( const auto& b : bullets ) b.Draw( gfx );

	player.Draw( gfx );
}
