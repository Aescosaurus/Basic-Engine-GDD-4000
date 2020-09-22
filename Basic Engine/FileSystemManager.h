#pragma once

#include "MonoBehavior.h"

class FileSystemManager
	:
	public MonoBehavior,
	public Singleton<FileSystemManager>
{
public:
	void Start() override
	{
		std::cout << "FileSystemManager::Start()\n";
	}
	void Update() override
	{
		std::cout << "FileSystemManager::Update()\n";
	}
	void Shutdown() override
	{
		std::cout << "FileSystemManager::Shutdown()\n";
	}
};