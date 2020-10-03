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

	void Start() override;
	void Update() override;
	void Shutdown() override;
private:
	static constexpr int width = Graphics::ScreenWidth;
	static constexpr int height = Graphics::ScreenHeight;
	std::vector<TileType> tiles;
};