#pragma once

#include "Singleton.h"

template<typename T>
class MemoryManager
	:
	public Singleton<MemoryManager<T>>
{
protected:
	class FreeStore
	{
	public:
		FreeStore* next = nullptr;
	};
public:
	MemoryManager()
	{
		ExpandPoolSize();
	}
	~MemoryManager()
	{
		CleanUp();
	}
	void* Allocate( size_t size )
	{
		if( head == nullptr ) ExpandPoolSize();

		auto* curHead = head;
		head = curHead->next;
		return( curHead );
	}
	void Free( void* ptr )
	{
		auto* curHead = ( FreeStore* )( ptr );

		curHead->next = head;
		head = curHead;
	}
	void ExpandPoolSize()
	{
		const auto size = sizeof( FreeStore* );
		auto* curHead = ( FreeStore* )( new char[size] );
		head = curHead;

		for( int i = 0; i < poolSize; ++i )
		{
			curHead->next = ( FreeStore* )( new char[size] );
			curHead = curHead->next;
		}
	}
	void CleanUp()
	{
		auto* cur = head;
		while( cur != nullptr )
		{
			delete[] cur;
			cur = cur->next;
		}
	}
protected:
	FreeStore* head = nullptr;
	static constexpr int poolSize = 1000;
};

// Use for user-defined classes.
template<typename T>
class Managed
	:
	public T
{
public:
	void* operator new( size_t size )
	{
		return( MemoryManager<T>::Get().Allocate( size ) );
	}
	void operator delete( void* ptr )
	{
		MemoryManager<T>::Get().Free( ptr );
	}
};

// Use for int/float or w/e.
template<typename T>
class ManagedFun
{
public:
	ManagedFun( T val = T() )
		:
		val( val )
	{}

	void* operator new( size_t size )
	{
		return( MemoryManager<T>::Get().Allocate( size ) );
	}
	void operator delete( void* ptr )
	{
		MemoryManager<T>::Get().Free( ptr );
	}
public:
	T val;
};