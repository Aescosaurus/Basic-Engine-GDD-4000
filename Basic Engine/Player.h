#pragma once

#include "Vec2.h"
#include "Keyboard.h"
#include "Graphics.h"
#include "GameWorld.h"
#include "Bullet.h"
#include "Timer.h"

class Player
{
public:
	Player( const GameWorld& world );

	void Update( const Keyboard& kbd,float dt );
	void Draw( Graphics& gfx ) const;
private:
	const GameWorld& world;
	Vec2 pos = { float( Graphics::ScreenWidth ) / 2.0f,float( Graphics::ScreenHeight - 2 ) };
	static constexpr float moveSpeed = 6.0f;
	std::vector<Bullet> bullets;
	Timer refire = 1.0f;
};