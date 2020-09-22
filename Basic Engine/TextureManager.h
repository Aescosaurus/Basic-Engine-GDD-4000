#pragma once

#include "MonoBehavior.h"

class TextureManager
	:
	public MonoBehavior,
	public Singleton<TextureManager>
{
public:
	void Start() override
	{
		std::cout << "TextureManager::Start()\n";
	}
	void Update() override
	{
		std::cout << "TextureManager::Update()\n";
	}
	void Shutdown() override
	{
		std::cout << "TextureManager::Shutdown()\n";
	}
};