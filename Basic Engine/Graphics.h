#pragma once

#include <vector>

class Graphics
{
public:
	Graphics();

	void BeginFrame();
	void Present();

	void PutPixel( int x,int y,char c );
private:
	void HideCursor();

	std::vector<char>* FlipBuffer();
public:
	static constexpr int ScreenWidth = 37 + 1;
	static constexpr int ScreenHeight = 12;
	std::vector<char> pixels;
	std::vector<char> pixels2;
	std::vector<char>* pPixelBuffer = &pixels;
	static constexpr char fillChar = '.';
};