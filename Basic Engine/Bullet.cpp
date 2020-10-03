#include "Bullet.h"

Bullet::Bullet( const Vec2& pos )
	:
	pos( pos )
{}

void Bullet::Update( float dt )
{
	pos += vel * dt;

	// todo destroy on wall or enemy
}

void Bullet::Draw( Graphics& gfx ) const
{
	gfx.PutPixel( int( pos.x ),int( pos.y ),'*' );
}
