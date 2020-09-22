#pragma once

#include "MonoBehavior.h"

class SoundManager
	:
	public MonoBehavior,
	public Singleton<SoundManager>
{
public:
	void Start() override
	{
		std::cout << "SoundManager::Start()\n";
	}
	void Update() override
	{
		std::cout << "SoundManager::Update()\n";
	}
	void Shutdown() override
	{
		std::cout << "SoundManager::Shutdown()\n";
	}
};