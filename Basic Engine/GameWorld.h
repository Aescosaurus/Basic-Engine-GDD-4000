#pragma once

#include "GameObject.h"
#include "Vec2.h"
#include "Timer.h"

class GameWorld
	:
	public GameObject
{
public:
	void Init() override;
	void Update( const Keyboard& kbd,float dt ) override;
	void Draw( Graphics& gfx ) const override;
private:
	void GameOver();

	void DrawMessage( const std::string& msg,Graphics& gfx ) const;
private:
	std::vector<Vei2> blocks;
	Vei2 player = { Graphics::ScreenWidth / 2,Graphics::ScreenHeight - 2 };
	static constexpr int playerSize = 2;
	Vei2 ball = { Graphics::ScreenWidth / 2 + 1,player.y - 1 };
	Vei2 ballVel = { 1,-1 };
	Timer ballMoveTimer = 0.2f;
	Timer playerMoveTimer = 0.08f;
	bool gameOver = false;
	static constexpr int blockCols = 4;
};