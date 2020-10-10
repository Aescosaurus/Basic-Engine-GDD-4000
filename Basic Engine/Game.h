#pragma once

#include "Keyboard.h"
#include "Graphics.h"
#include "FrameTimer.h"
#include "GameWorld.h"
#include "Vec2.h"
#include <vector>
#include "Timer.h"

class Game
{
public:
	Game( Keyboard& kbd,Graphics& gfx );

	void Update();
	void Draw();
private:
	Keyboard& kbd;
	Graphics& gfx;
	FrameTimer ft;

	GameWorld world;

	static constexpr float playerSpeed = 6.0f;
	static constexpr float bulletSpeed = 6.0f;

	Vec2 playerPos;
	std::vector<Vec2> bullets;
	std::vector<Vec2> aliens;
	Timer alienAnim = 0.5f;
	char alienFrame = 'M';
	int alienDir = 1;
	int alienSpeed = 1;
	Timer alienMove = 1.0f;
	bool gameOver = false;
};