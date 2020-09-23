#pragma once

#include "Vec3.h"
#include "MemoryManager.h"

// this is so dumb
template<typename T>
class Vec3Managed_
	:
	public Vec3_<T>,
	public Managed<Vec3_<T>>
{
};