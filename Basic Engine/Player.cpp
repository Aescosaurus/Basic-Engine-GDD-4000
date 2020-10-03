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
}

void Player::Draw( Graphics& gfx ) const
{
	gfx.PutPixel( int( pos.x ),int( pos.y ),'^' );
}
