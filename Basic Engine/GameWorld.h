#pragma once

#include "MonoBehavior.h"
#include "Graphics.h"

class GameWorld
	:
	public MonoBehavior
{
public:
	GameWorld();

	void Start() override;
	void Update() override;
	void Shutdown() override;

	void Draw( Graphics& gfx ) const;

	void SetTile( int x,int y,char c );

	char GetTile( int x,int y ) const;
private:
	static constexpr int width = Graphics::ScreenWidth;
	static constexpr int height = Graphics::ScreenHeight;
	static constexpr char empty = ' ';
	static constexpr char wall = '#';
	char world[height][width];
};