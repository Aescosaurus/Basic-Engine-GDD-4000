#include "GameWorld.h"

void GameWorld::Init()
{
	for( int y = 2; y < blockCols * 2; y += 2 )
	{
		for( int x = 2; x < Graphics::ScreenWidth - 3; x += 2 )
		{
			blocks.emplace_back( Vei2{ x,y } );
		}
	}
}

void GameWorld::Update( const Keyboard& kbd,float dt )
{
	if( gameOver ) return;

	if( playerMoveTimer.Update( dt ) )
	{
		playerMoveTimer.Reset();

		if( ball.x > player.x ) ++player.x;
		if( ball.x < player.x ) --player.x;

		if( player.x < playerSize + 1 ) player.x = playerSize + 1;
		if( player.x > Graphics::ScreenWidth - playerSize - 1 ) player.x = Graphics::ScreenWidth - playerSize - 1;
	}

	if( ballMoveTimer.Update( dt ) )
	{
		ballMoveTimer.Reset();
		ball += ballVel;

		if( ( ball.y == player.y - 1 || ball.y == player.y ) &&
			ball.x > player.x - playerSize - 1 &&
			ball.x < player.x + playerSize + 1 )
		{
			ballVel.y = -1;
			ballVel.x = ballVel.x / abs( ballVel.x ) * 2;
		}

		for( int i = 0; i < int( blocks.size() ); ++i )
		{
			if( ball.x == blocks[i].x && ball.y == blocks[i].y )
			{
				blocks.erase( blocks.begin() + i );
				ballVel.y *= -1;
			}
		}

		if( ball.x <= 2 ) ballVel.x = 1;
		if( ball.x >= Graphics::ScreenWidth - 2 ) ballVel.x = -1;
		if( ball.y <= 1 ) ballVel.y = 1;
		if( ball.y >= Graphics::ScreenHeight - 1 ) GameOver();
	}
}

void GameWorld::Draw( Graphics& gfx ) const
{
	for( int x = 0; x < Graphics::ScreenWidth; ++x ) gfx.PutPixel( x,0,'#' );
	for( int x = 0; x < Graphics::ScreenWidth; ++x ) gfx.PutPixel( x,Graphics::ScreenHeight - 1,'#' );
	for( int y = 0; y < Graphics::ScreenHeight; ++y ) gfx.PutPixel( 0,y,'#' );
	for( int y = 0; y < Graphics::ScreenHeight; ++y ) gfx.PutPixel( Graphics::ScreenWidth - 1,y,'#' );

	for( int i = player.x - playerSize; i < player.x + playerSize; ++i )
	{
		gfx.PutPixel( i,player.y,'-' );
	}

	gfx.PutPixel( ball.x,ball.y,'o' );

	for( const auto& b : blocks )
	{
		gfx.PutPixel( b.x,b.y,'#' );
	}

	if( gameOver ) DrawMessage( "Game Over :(",gfx );
}

void GameWorld::GameOver()
{
	gameOver = true;
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