#pragma once

class Timer
{
public:
	Timer( float time )
		:
		duration( time )
	{}

	bool Update( float dt )
	{
		if( curTime <= duration ) curTime += dt;

		return( IsDone() );
	}

	void Reset()
	{
		curTime = 0.0f;
	}

	bool IsDone() const
	{
		return( curTime >= duration );
	}
public:
	float curTime = 0.0f;
	float duration;
};