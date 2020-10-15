#pragma once

#include <vector>

class Graphics
{
public:
	Graphics();

	void ClearPixels();
	void ClearScreen();
	void Present();

	void PutPixel( int x,int y,char c );

	void FlipBuffer();
private:
	// std::vector<char>* FlipBuffer();
public:
	static constexpr int ScreenWidth = 37;
	static constexpr int ScreenHeight = 12;
private:
	std::vector<char> pixels;
	std::vector<char> pixels2;
	std::vector<char>* pPixelBuffer = &pixels;
	static constexpr char fillChar = '.';
};