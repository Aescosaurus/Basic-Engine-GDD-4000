#pragma once

#include <string>
#include "Vec2.h"
#include "Graphics.h"

class Animation
{
public:
	Animation( const std::string& frames,float holdTime );

	void Update( float dt );
	void Draw( const Vei2& pos,Graphics& gfx ) const;
private:
	std::vector<char> frames;
	int curFrame = 0;
	float frameTime = 0.0f;
	float holdTime;
};