#include "Graphics.h"
#include <cstring>
#include <iostream>
#include <iterator>
#include <Windows.h>
#include <cassert>

Graphics::Graphics()
{
	pixels.resize( ScreenWidth * ScreenHeight );

	HideCursor();
}

void Graphics::BeginFrame()
{
	system( "cls" );
	// memset( pixels.data(),' ',pixels.size() );
	for( int y = 0; y < ScreenHeight; ++y )
	{
		for( int x = 0; x < ScreenWidth; ++x )
		{
			PutPixel( x,y,'.' );
		}
		PutPixel( ScreenWidth - 1,y,'\n' );
	}
}

void Graphics::Present()
{
	std::copy( pixels.begin(),pixels.end(),std::ostream_iterator<char>( std::cout,"" ) );
}

void Graphics::PutPixel( int x,int y,char c )
{
	assert( x >= 0 );
	assert( x < ScreenWidth );
	assert( y >= 0 );
	assert( y < ScreenHeight );

	pixels[y * ScreenWidth + x] = c;
}

void Graphics::HideCursor()
{
	HANDLE out = GetStdHandle( STD_OUTPUT_HANDLE );
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo( out,&cursorInfo );
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo( out,&cursorInfo );
}
