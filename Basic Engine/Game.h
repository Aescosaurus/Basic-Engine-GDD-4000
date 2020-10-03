#pragma once

#include "Keyboard.h"
#include "Graphics.h"
#include "GameWorld.h"

class Game
{
public:
	Game( Keyboard& kbd,Graphics& gfx );

	void Update();
	void Draw();
private:
	Keyboard& kbd;
	Graphics& gfx;

	GameWorld world;
};