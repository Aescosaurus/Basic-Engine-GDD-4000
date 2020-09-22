#pragma once

#include "MonoBehavior.h"

class RenderManager
	:
	public MonoBehavior,
	public Singleton<RenderManager>
{
public:
	void Start() override
	{
		std::cout << "RenderManager::Start()\n";
	}
	void Update() override
	{
		std::cout << "RenderManager::Update()\n";
	}
	void Shutdown() override
	{
		std::cout << "RenderManager::Shutdown()\n";
	}
};