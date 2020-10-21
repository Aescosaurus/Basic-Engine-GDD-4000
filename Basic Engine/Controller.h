#pragma once

#include <vector>
#include "Vec2.h"

class Controller
{
private:
	class Gamepad
	{
	public:
		int* state;
		int dwIndex;
	};
public:
	Controller();

	void Update();

	void Rumble( float val );

	const Vec2& GetLeftStickInput() const;
	bool CheckAButtonInput() const;
private:
	std::vector<Gamepad> gamepads;
	bool connected = false;
	Vec2 leftStick = Vec2::Zero();
	bool aButton = false;
	static constexpr int aButtonMask = 0x1000;
};