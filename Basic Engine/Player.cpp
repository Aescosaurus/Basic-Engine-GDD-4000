#include "Player.h"

Player::Player( const GameWorld& world )
	:
	world( world )
{}

void Player::Update( const Keyboard& kbd,float dt )
{
	auto move = Vec2::Zero();
	if( kbd.KeyIsPressed( 'A' ) ) --move.x;
	if( kbd.KeyIsPressed( 'D' ) ) ++move.x;

	const auto newPos = pos + move * moveSpeed * dt;
	if( world.GetTile( int( newPos.x ),int( newPos.y ) ) == GameWorld::TileType::Air )
	{
		pos = newPos;
	}

	if( refire.Update( dt ) && kbd.KeyIsPressed( ' ' ) &&
		bullets.size() < 2 )
	{
		bullets.emplace_back( Bullet{ pos } );
	}

	for( auto& b : bullets )
	{
		b.Update( dt );
	}
}

void Player::Draw( Graphics& gfx ) const
{
	gfx.PutPixel( int( pos.x ),int( pos.y ),'^' );

	for( const auto& b : bullets ) b.Draw( gfx );
}
