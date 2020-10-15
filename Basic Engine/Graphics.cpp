#include "Graphics.h"
#include <cstring>
#include <iostream>
#include <iterator>
#include <Windows.h>
#include <cassert>

Graphics::Graphics()
{
	pixels.resize( ( ScreenWidth + 1 ) * ScreenHeight );
	pixels2.resize( ( ScreenWidth + 1 ) * ScreenHeight );

	ClearPixels();
}

void Graphics::ClearPixels()
{
	// system( "cls" );

	// pPixelBuffer = FlipBuffer();

	// memset( pixels.data(),' ',pixels.size() );
	for( int y = 0; y < ScreenHeight; ++y )
	{
		for( int x = 0; x < ScreenWidth + 1; ++x )
		{
			PutPixel( x,y,fillChar );
		}
		PutPixel( ScreenWidth,y,'\n' );
	}
}

void Graphics::ClearScreen()
{
	system( "cls" );
}

void Graphics::Present()
{
	// const auto* oldBuffer = FlipBuffer();
	const auto* oldBuffer = pPixelBuffer;

	std::copy( oldBuffer->begin(),oldBuffer->end(),std::ostream_iterator<char>( std::cout,"" ) );
}

void Graphics::PutPixel( int x,int y,char c )
{
	assert( x >= 0 );
	assert( x <= ScreenWidth ); // Danger!
	assert( y >= 0 );
	assert( y < ScreenHeight );

	( *pPixelBuffer )[y * ( ScreenWidth + 1 ) + x] = c;
}

void Graphics::FlipBuffer()
{
	pPixelBuffer = &( ( pPixelBuffer == &pixels ) ? pixels2 : pixels );
}

// std::vector<char>* Graphics::FlipBuffer()
// {
// 	return( ( pPixelBuffer == &pixels ) ? &pixels2 : &pixels );
// }