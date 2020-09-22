#pragma once

template<typename T>
class Singleton
{
public:
	static T& Get()
	{
		static T me;
		return( me );
	}
	static T* const Ptr()
	{
		return( &Get() );
	}

	// Singleton() = delete;
	Singleton( const Singleton& ) = delete;
	Singleton( const Singleton&& ) = delete;
	Singleton& operator=( const Singleton& ) = delete;
	Singleton& operator=( const Singleton&& ) = delete;
	~Singleton() = default;
protected:
	Singleton() = default;
};