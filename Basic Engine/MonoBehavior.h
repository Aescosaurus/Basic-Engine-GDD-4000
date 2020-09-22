#pragma once

#include <iostream>
#include "Singleton.h"

class MonoBehavior
{
public:
	virtual void Start()
	{}
	virtual void Update()
	{}
	virtual void Shutdown()
	{}
};