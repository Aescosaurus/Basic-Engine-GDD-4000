#pragma once

#include "Vec2.h"
#include "Keyboard.h"
#include "Graphics.h"
#include "GameWorld.h"
#include "Timer.h"
#include "Bullet.h"
#include "Animation.h"

class Player
{
public:
	Player( const GameWorld& world,std::vector<Bullet>& bullets );

	void Update( const Keyboard& kbd,float dt );
	void Draw( Graphics& gfx ) const;
	void ApplyOuch();

	const Vec2& GetPos() const;
private:
	const GameWorld& world;
	Vec2 pos = { float( Graphics::ScreenWidth ) / 2.0f,float( Graphics::ScreenHeight - 2 ) };
	static constexpr float moveSpeed = 6.0f;
	Timer refire = 1.0f;
	std::vector<Bullet>& bullets;
	Animation ouchAnim = { "^*&%+",0.3f };
	bool ouch = false;
};