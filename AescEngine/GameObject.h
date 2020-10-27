#pragma once

#include "Keyboard.h"
#include "Graphics.h"

class GameObject
{
public:
	virtual void Init() {}
	virtual void Update( const Keyboard& kbd,float dt ) {}
	virtual void Draw( Graphics& gfx ) const {}
};