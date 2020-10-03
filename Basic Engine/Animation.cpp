#include "Animation.h"

Animation::Animation( const std::string& frames,float holdTime )
	:
	holdTime( holdTime )
{
	for( auto c : frames )
	{
		this->frames.emplace_back( c );
	}
}

void Animation::Update( float dt )
{
	frameTime += dt;

	while( frameTime > holdTime )
	{
		frameTime -= holdTime;
		++curFrame;
	}
	if( curFrame >= int( frames.size() ) )
	{
		curFrame = 0;
	}
}

void Animation::Draw( const Vei2& pos,Graphics& gfx ) const
{
	gfx.PutPixel( pos.x,pos.y,frames[curFrame] );
}
