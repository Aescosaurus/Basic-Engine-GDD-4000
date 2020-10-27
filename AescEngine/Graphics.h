#pragma once

#include <vector>
#include <cstring>
#include <iostream>
#include <iterator>
#include <Windows.h>
#include <cassert>

class Graphics
{
public:
	Graphics()
	{
		pixels.resize( ( ScreenWidth + 1 ) * ScreenHeight );
		pixels2.resize( ( ScreenWidth + 1 ) * ScreenHeight );

		ClearPixels();
	}

	void ClearPixels()
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
	void ClearScreen()
	{
		system( "cls" );
	}
	void Present()
	{
		// const auto* oldBuffer = FlipBuffer();
		const auto* oldBuffer = pPixelBuffer;

		std::copy( oldBuffer->begin(),oldBuffer->end(),std::ostream_iterator<char>( std::cout,"" ) );
	}

	void PutPixel( int x,int y,char c )
	{
		assert( x >= 0 );
		assert( x <= ScreenWidth ); // Danger!
		assert( y >= 0 );
		assert( y < ScreenHeight );

		( *pPixelBuffer )[y * ( ScreenWidth + 1 ) + x] = c;
	}

	void FlipBuffer()
	{
		pPixelBuffer = &( ( pPixelBuffer == &pixels ) ? pixels2 : pixels );
	}
private:
	// std::vector<char>* FlipBuffer();
public:
	static constexpr int ScreenWidth = 37;
	static constexpr int ScreenHeight = 12;
private:
	std::vector<char> pixels;
	std::vector<char> pixels2;
	std::vector<char>* pPixelBuffer = &pixels;
	static constexpr char fillChar = ' ';
};