#pragma once

#include <iostream>
#include "Singleton.h"

class MonoBehavior
{
public:
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Shutdown() = 0;
};