#pragma once

#include "MonoBehavior.h"

class MemoryManager
	:
	public MonoBehavior,
	public Singleton<MemoryManager>
{
public:
	void Start() override
	{
		std::cout << "MemoryManager::Start()\n";
	}
	void Update() override
	{
		std::cout << "MemoryManager::Update()\n";
	}
	void Shutdown() override
	{
		std::cout << "MemoryManager::Shutdown()\n";
	}
};