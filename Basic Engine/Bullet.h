#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "GameWorld.h"

class Bullet
{
public:
	Bullet( const Vec2& pos );

	void Update( const GameWorld& world,float dt );
	void Draw( Graphics& gfx ) const;

	bool Ouch() const;
private:
	static constexpr float speed = 6.0f;
	Vec2 pos;
	Vec2 vel = Vec2::Up() * speed;
	bool ouch = false;
};