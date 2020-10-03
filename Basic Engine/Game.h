#pragma once

#include "Keyboard.h"
#include "Graphics.h"
#include "GameWorld.h"
#include "FrameTimer.h"
#include "Player.h"

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
	Player player;
};