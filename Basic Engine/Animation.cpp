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
