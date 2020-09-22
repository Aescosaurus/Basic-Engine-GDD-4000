#pragma once

#include "Vec3.h"
#include "MemoryManager.h"
#include <algorithm>

// this is so dumb
template<typename T>
class Vec3Managed_
	:
	public Vec3_<T>,
	MemoryManager
{
public:
	Vec3Managed_( T x,T y,T z )
		:
		Vec3_<T>( x,y,z )
	{}

	void ExpandPoolSize() override
	{
		const auto size = std::max( sizeof( this ),sizeof( FreeStore* ) );
		auto* curHead = ( FreeStore* )( new char[size] );
		head = curHead;

		for( int i = 0; i < poolSize; ++i )
		{
			curHead->next = ( FreeStore* )( new char[size] );
			curHead = curHead->next;
		}

		curHead->next = nullptr;
	}
private:
	static constexpr int poolSize = 1000;
};