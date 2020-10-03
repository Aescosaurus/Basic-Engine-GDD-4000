#include "Player.h"

Player::Player( const GameWorld& world,std::vector<Bullet>& bullets )
	:
	world( world ),
	bullets( bullets )
{}

void Player::Update( const Keyboard& kbd,float dt )
{
	auto move = Vec2::Zero();
	if( kbd.KeyIsPressed( 'W' ) ) --move.y;
	if( kbd.KeyIsPressed( 'S' ) ) ++move.y;
	if( kbd.KeyIsPressed( 'A' ) ) --move.x;
	if( kbd.KeyIsPressed( 'D' ) ) ++move.x;

	const auto newPos = pos + move * moveSpeed * dt;
	if( world.GetTile( int( newPos.x ),int( newPos.y ) ) == GameWorld::TileType::Air &&
		!ouch )
	{
		pos = newPos;
	}

	if( refire.Update( dt ) && kbd.KeyIsPressed( ' ' ) &&
		bullets.size() < 2 && !ouch )
	{
		bullets.emplace_back( Bullet{ pos + Vec2::Up() } );
	}

	if( ouch ) ouchAnim.Update( dt );
}

void Player::Draw( Graphics& gfx ) const
{
	// gfx.PutPixel( int( pos.x ),int( pos.y ),'^' );
	ouchAnim.Draw( Vei2( pos ),gfx );
}

void Player::ApplyOuch()
{
	ouch = true;
}

const Vec2& Player::GetPos() const
{
	return( pos );
}
