#include "Graphics.h"
#include <cstring>
#include <iostream>
#include <iterator>
#include <Windows.h>
#include <cassert>

Graphics::Graphics()
{
	pixels.resize( ScreenWidth * ScreenHeight );
	pixels2.resize( ScreenWidth * ScreenHeight );

	HideCursor();
}

void Graphics::BeginFrame()
{
	system( "cls" );

	pPixelBuffer = FlipBuffer();

	// memset( pixels.data(),' ',pixels.size() );
	for( int y = 0; y < ScreenHeight; ++y )
	{
		for( int x = 0; x < ScreenWidth - 1; ++x )
		{
			PutPixel( x,y,fillChar );
		}
		PutPixel( ScreenWidth - 1,y,'\n' );
	}
}

void Graphics::Present()
{
	const auto* oldBuffer = FlipBuffer();

	std::copy( oldBuffer->begin(),oldBuffer->end(),std::ostream_iterator<char>( std::cout,"" ) );
}

void Graphics::PutPixel( int x,int y,char c )
{
	assert( x >= 0 );
	assert( x < ScreenWidth );
	assert( y >= 0 );
	assert( y < ScreenHeight );

	( *pPixelBuffer )[y * ( ScreenWidth - 1 ) + x] = c;
}

void Graphics::HideCursor()
{
	HANDLE out = GetStdHandle( STD_OUTPUT_HANDLE );
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo( out,&cursorInfo );
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo( out,&cursorInfo );
}

std::vector<char>* Graphics::FlipBuffer()
{
	return( ( pPixelBuffer == &pixels ) ? &pixels2 : &pixels );
}
