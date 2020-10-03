#pragma once

#include "Vec2.h"
#include "Graphics.h"

class Alien
{
public:
	Alien( const Vec2& pos );

	void Update( float dt );
	void Draw( Graphics& gfx ) const;

	void FlipDir();
	void DropDown();

	const Vec2& GetPos() const;
private:
	static constexpr float speedIncrease = 1.0f;
	float speed = 1.0f;
	Vec2 pos;
	Vec2 vel = { speed,0.0f };
};