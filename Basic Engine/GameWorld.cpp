#include "GameWorld.h"

void GameWorld::Init()
{
	playerPos = Vei2( Vec2{ float( Graphics::ScreenWidth / 2 ),float( Graphics::ScreenHeight - 2 ) } );

	for( int i = 0; i < 8; ++i )
	{
		aliens.emplace_back( Vec2::Right() * 4.0f + Vec2::Right() * float( i * 4 ) + Vec2::Down() * 2.0f );
	}
}

void GameWorld::Update( const Keyboard& kbd,float dt )
{
	if( gameOver || gameWin )
	{
		return; // Bad!
	}

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
				if( aliens.size() == 0 ) gameWin = true;
				if( a == aliens.end() ) break;
			}
		}

		// if( world.GetTile( int( b.x ),int( b.y ) ) == '#' )
		if( CheckWallTile( b ) )
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
			// if( world.GetTile( int( a.x ) + 1,int( a.y ) ) == '#' )
			if( CheckWallTile( a + Vei2::Right() ) )
			{
				alienDir = -1;
			}
			// else if( world.GetTile( int( a.x ) - 1,int( a.y ) ) == '#' )
			else if( CheckWallTile( a + Vei2::Left() ) )
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
						// Draw();
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

void GameWorld::Draw( Graphics& gfx ) const
{
	for( int y = 0; y < Graphics::ScreenHeight; ++y )
	{
		for( int x = 0; x < Graphics::ScreenWidth; ++x )
		{
			if( CheckWallTile( Vei2{ x,y } ) )
			{
				gfx.PutPixel( x,y,'#' );
			}
		}
	}

	gfx.PutPixel( int( playerPos.x ),int( playerPos.y ),'^' );
	for( const auto& b : bullets ) gfx.PutPixel( int( b.x ),int( b.y ),'*' );
	for( const auto& a : aliens ) gfx.PutPixel( int( a.x ),int( a.y ),alienFrame );

	if( gameOver ) DrawMessage( "Game Over!",gfx );
	else if( gameWin ) DrawMessage( "You Win!",gfx );
}

bool GameWorld::CheckWallTile( const Vei2& pos ) const
{
	return( pos.x == 0 || pos.x == Graphics::ScreenWidth - 1 ||
		pos.y == 0 || pos.y == Graphics::ScreenHeight - 1 );
}

void GameWorld::DrawMessage( const std::string& msg,Graphics& gfx ) const
{
	const auto msgLen = int( msg.length() );
	for( int i = 0; i < msgLen; ++i )
	{
		gfx.PutPixel( Graphics::ScreenWidth / 2 - msgLen / 2 + i,
			Graphics::ScreenHeight / 2,msg[i] );
	}
}
