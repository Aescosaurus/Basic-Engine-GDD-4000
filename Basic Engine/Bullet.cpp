#include "Bullet.h"

Bullet::Bullet( const Vec2& pos )
	:
	pos( pos )
{}

void Bullet::Update( const GameWorld& world,float dt )
{
	pos += vel * dt;

	// todo destroy on wall or enemy
	if( world.GetTile( int( pos.x ),int( pos.y ) ) == GameWorld::TileType::Wall )
	{
		ouch = true;
	}
}

void Bullet::Draw( Graphics& gfx ) const
{
	gfx.PutPixel( int( pos.x ),int( pos.y ),'*' );
}

void Bullet::ApplyOuch()
{
	ouch = true;
}

bool Bullet::Ouch() const
{
	return( ouch );
}

const Vec2& Bullet::GetPos() const
{
	return( pos );
}
