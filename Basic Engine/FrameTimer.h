#pragma once

#include <chrono>

class FrameTimer
{
public:
	FrameTimer()
		:
		last( std::chrono::steady_clock::now() )
	{}
	float Mark()
	{
		const auto old = last;
		last = std::chrono::steady_clock::now();
		const std::chrono::duration<float> frameTime = last - old;
		return( frameTime.count() );
	}
	float Read()
	{
		const auto old = last;
		const auto cur = std::chrono::steady_clock::now();
		const std::chrono::duration<float> frameTime = cur - old;
		return( frameTime.count() );
	}
private:
	std::chrono::steady_clock::time_point last;
};