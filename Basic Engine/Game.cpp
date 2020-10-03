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
	for( auto& alien : aliens )
	{
		alien.Update( dt );

		for( auto& b : bullets )
		{
			if( ( b.GetPos() - alien.GetPos() ).GetLengthSq() < Bullet::radius )
			{
				b.ApplyOuch();
				alien.ApplyOuch();
			}
		}
	}

	if( aliens.size() > 0 )
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

	player.Draw( gfx );

	for( const auto& b : bullets ) b.Draw( gfx );

	for( const auto& a : aliens ) a.Draw( gfx );
}
