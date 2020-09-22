#pragma once

#include "MonoBehavior.h"

class AnimationManager
	:
	public MonoBehavior,
	public Singleton<AnimationManager>
{
public:
	void Start() override
	{
		std::cout << "AnimationManager::Start()\n";
	}
	void Update() override
	{
		std::cout << "AnimationManager::Update()\n";
	}
	void Shutdown() override
	{
		std::cout << "AnimationManager::Shutdown()\n";
	}
};