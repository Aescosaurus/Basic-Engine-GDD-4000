#pragma once

#include "GameObject.h"
#include "Vec2.h"
#include <vector>
#include "Timer.h"
#include <string>

class GameWorld
	:
	public GameObject
{
public:
	void Init() override;
	void Update( const Keyboard& kbd,float dt ) override;
	void Draw( Graphics& gfx ) const override;
private:
	bool CheckWallTile( const Vei2& pos ) const;
	void DrawMessage( const std::string& msg,Graphics& gfx ) const;
private:
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
	bool gameWin = false;
};