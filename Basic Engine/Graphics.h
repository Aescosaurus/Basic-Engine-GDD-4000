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
public:
	static constexpr int ScreenWidth = 37;
	static constexpr int ScreenHeight = 12;
	std::vector<char> pixels;
};