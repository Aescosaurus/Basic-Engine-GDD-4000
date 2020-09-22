#pragma once

#include "Vec3.h"
#include "MemoryManager.h"

// this is so dumb
template<typename T>
class Vec3Managed_
	:
	public Vec3_<T>
{
public:
	Vec3Managed_( T x,T y,T z )
		:
		Vec3_<T>( x,y,z )
	{}

	void* operator new( size_t size )
	{
		return( MemoryManager::Get().Allocate( size ) );
	}
	void operator delete( void* ptr )
	{
		MemoryManager::Get().Free( ptr );
	}
};