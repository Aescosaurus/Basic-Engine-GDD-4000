#pragma once

#include "MonoBehavior.h"
#include "Graphics.h"
#include <vector>

class GameWorld
	:
	public MonoBehavior
{
public:
	enum class TileType
	{
		Air,
		Wall
	};
public:
	GameWorld();

	void Draw( Graphics& gfx ) const;

	TileType GetTile( int x,int y ) const;

	void Start() override;
	void Update() override;
	void Shutdown() override;
public:
	static constexpr int width = Graphics::ScreenWidth;
	static constexpr int height = Graphics::ScreenHeight;
private:
	std::vector<TileType> tiles;
};