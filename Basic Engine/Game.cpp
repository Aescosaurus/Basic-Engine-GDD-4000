#include "Game.h"

Game::Game( Keyboard& kbd,Graphics& gfx )
	:
	kbd( kbd ),
	gfx( gfx ),
	playerPos( float( Graphics::ScreenWidth / 2 ),float( Graphics::ScreenHeight - 2 ) )
{
	for( int i = 0; i < 8; ++i )
	{
		aliens.emplace_back( Vec2::Right() * 4.0f + Vec2::Right() * float( i * 4 ) + Vec2::Down() * 2.0f );
	}
}

void Game::Update()
{
	if( gameOver )
	{
		std::cout << "Game over!\n";
		std::cin.get();
	}
	const auto dt = ft.Mark();

	// Player move.
	if( kbd.CheckKey() == 'a' ) playerPos.x -= playerSpeed * dt;
	if( kbd.CheckKey() == 'd' ) playerPos.x += playerSpeed * dt;

	if( playerPos.x < 1.0f ) playerPos.x = 1.0f;
	if( playerPos.x > float( Graphics::ScreenWidth - 2 ) ) playerPos.x = float( Graphics::ScreenWidth - 2 );

	if( kbd.CheckKey() == ' ' && bullets.size() < 2 )
	{
		bullets.emplace_back( playerPos + Vec2::Up() );
	}

	// Bullet update.
	for( auto it = bullets.begin(); it != bullets.end(); ++it )
	{
		auto& b = *it;
		b.y -= bulletSpeed * dt;

		for( auto a = aliens.begin(); a != aliens.end(); ++a )
		{
			if( Vei2( *a ) == Vei2( b ) )
			{
				a = aliens.erase( a );
				if( a == aliens.end() ) break;
			}
		}

		if( world.GetTile( int( b.x ),int( b.y ) ) == '#' )
		{
			it = bullets.erase( it );
			if( it == bullets.end() ) break;
		}
	}

	// Alien update.
	if( alienMove.Update( dt ) )
	{
		for( auto it = aliens.begin(); it != aliens.end(); ++it )
		{
			auto& a = *it;
			
			a.x += float( alienDir );
		}
		alienMove.Reset();

		// Flip dir and drop down.
		for( auto& a : aliens )
		{
			if( world.GetTile( int( a.x ) + 1,int( a.y ) ) == '#' )
			{
				alienDir = -1;
			}
			else if( world.GetTile( int( a.x ) - 1,int( a.y ) ) == '#' )
			{
				++alienSpeed;
				alienMove.duration = 1.0f / float( alienSpeed );
				for( auto& al : aliens )
				{
					++al.y;
					alienDir = 1;

					// Player oof.
					if( int( al.y ) == int( playerPos.y ) )
					{
						gameOver = true;
						Draw();
					}
				}
			}
		}
	}

	// Alien anim.
	if( alienAnim.Update( dt ) )
	{
		alienAnim.Reset();
		alienFrame = ( alienFrame == 'M' ) ? 'W' : 'M';
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

	for( const auto& a : aliens )
	{
		gfx.PutPixel( int( a.x ),int( a.y ),alienFrame );
	}
}
