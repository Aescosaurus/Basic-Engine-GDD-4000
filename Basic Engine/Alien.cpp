#include "Alien.h"
#include "AescUtils.h"

Alien::Alien( const Vec2& pos )
	:
	pos( pos )
{}

void Alien::Update( float dt )
{
	pos += vel * dt;
}

void Alien::Draw( Graphics& gfx ) const
{
	gfx.PutPixel( int( pos.x ),int( pos.y ),'M' );
}

void Alien::FlipDir()
{
	vel.x *= -1.0f;
}

void Alien::DropDown()
{
	++pos.y;
	FlipDir();
	vel.x += aesc::sign( vel.x ) * speedIncrease;
	pos.x += aesc::sign( vel.x ); // Make sure we no in wall.
	// vel.x = aesc::sign( vel.x ) * ( abs( vel.x ) + speedIncrease );
}

const Vec2& Alien::GetPos() const
{
	return( pos );
}
