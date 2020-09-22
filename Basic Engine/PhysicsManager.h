#pragma once

#include "MonoBehavior.h"

class PhysicsManager
	:
	public MonoBehavior,
	public Singleton<PhysicsManager>
{
public:
	void Start() override
	{
		std::cout << "PhysicsManager::Start()\n";
	}
	void Update() override
	{
		std::cout << "PhysicsManager::Update()\n";
	}
	void Shutdown() override
	{
		std::cout << "PhysicsManager::Shutdown()\n";
	}
};